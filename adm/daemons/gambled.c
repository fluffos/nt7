// Daemon : /adm/daemons/gambled.c
// 博彩系统
// By jjgod for hell. 00/05/07.
// Update by Lonely

#include <ansi.h>

inherit F_SAVE;

#define DATA_FILE               DATA_DIR "gambled"
#define INITING                 "initing"
#define OPENING                 "opening"
#define STOPPED                 "stopped"
#define FINISHING               "finishing"

mapping item_data = ([
 "十强赛冠军预测" : ([ "long" : "世界杯外围赛之十强赛马上就要开始"
                                "了，究竟本次十强赛谁能出线？中国"
                                "队能否顺利冲出亚洲？能否根治恐韩"
                                "恐伊症？请你在你认为可以出线的队"
                                "伍上下注吧！",
                       "end_time" : 1210996409,
                       "status"   : OPENING,
                       "min_money" : 10000, 
                       "number" : 3,
                       "subject" : ([ "中国队" : 10, 
                                      "法国队" : 20, 
                                      "德国队" : 50, 
                                      "英国队" : 70, 
                                      "美国队" : 80, 
                                      "巴西队" : 100, ]),
                     ]), 
]);

mapping user_data = ([
"wind" : ([ "十强赛冠军预测" : ([ "team" : ({ "中国队", "巴西队",
                                               "法国队", }),
                                   "money" : 80000, ]),
           ]),
]);

public void change_status(string name, string status);
public string query_status(string name);
public mapping query_item(string name);
private void change_name(string arg, object me, string name);
private void change_long(object me, string arg, string long);
private void change_date(string arg, object me, string name);
private void change_number(string arg, object me, string name);
private void change_money(string arg, object me, string name);
private void change_team_type(string arg, object me, string name);
private void get_name_end(string arg, object me);
/****************************************************************
 *                                                              *
 *            有关本博彩系统(About this Gamble system)          *
 *                                                              *
 *     本博彩系统采用全自动形式，即巫师手动设定一个项目以后，只 *
 * 要等待比赛结束后将比赛结果输入，就可以完成一整个博彩游戏的过 *
 * 程。                                                         *
 *                                                              *
 *     单一项目的整个运行流程如下：                             *
 *                                                              *
 *     1、输入项目内容，此时为创建态(Initing)。                 *
 *     2、开始允许投注，此时为开放态(Opening)。                 *
 *     3、停止继续投注，此时为停止态(Stopped)。                 *
 *     4、结束这个项目，此时为结束态(Finishing)。               *
 *                                                              *
 *     管理时的调用结构如下：                                   *
 *                                                              *
 *                          管理系统主界面                      *
 *        +----------+----------+----------+----------+         *
 *     创建项目   修改项目   查看投注   结束项目   退出系统     *
 *        |          |          |          |          |         *
 *     输入名称   选择项目   选择玩家   选择项目     退出       *
 *        |          |          |          |                    *
 *     输入描述   修改子项   查询完毕   删除完毕                *
 *        |          |          |          |                    *
 *     结束时间   修改完毕      |          |                    *
 *        |          |          |          |                    *
 *     最少投注      |          |          |                    *
 *        |          |          |          |                    *
 *     投注数量      |          |          |                    *
 *        |          |          |          |                    *
 *     创建完毕------+----------+-------返回界面                *
 *                                                              *
 * 储存数据：                                                   *
 *                                                              *
 *     item_data 映射：项目数据                                 *
 *     user_data 映射：用户数据                                 *
 *                                                              *
 * 函数列表：                                                   *
 *                                                              *
 *     供外部调用的：                                           *
 *     public void start_manage()  ：进入管理界面               *
 *     public void printf_over()   : 设置结果界面               *
 *     public void do_chip()       ：进入投注界面               *
 *     public void change_status() ：修改项目状态               *
 *     public string query_status()：查询项目状态               *
 *     public mapping query_item() ：获取项目数据               *
 *     public mapping query_data() ：获得所有纪录               *
 *                                                              *
 *     内部私有的：                                             *
 *     private void write_prompt()      ：显示管理界面          *
 *     private void end_manage()        ：退出管理界面          *
 *     private void get_type()          ：选择管理类别          *
 *     private void get_name()          ：输入项目名称          *
 *     private void select_change_type()：选择修改类别          *
 *     private void get_long()          ：输入项目描述          *
 *     private void get_team_number()   ：输入队伍数量          *
 *     private void get_team_info()     ：输入队伍数据          *
 *     private void get_date_off()      ：输入结束时间          *
 *     private void get_chip_number()   ：输入投注数量          *
 *     private void get_name_todel()    ：选择删除项目          *
 *     private void get_user()          ：选择查询玩家          *
 *     private void get_user_info()     ：获得玩家信息          *
 *                                                              *
 *     此外，采用 heart_beat 定时判定一个项目是否应该停止，目前 *
 * 的 heart_beat 设定值为 30，即结束时间精确率为 +- 60s。       *
 *                                                              *
 ****************************************************************/
 
// 创建存盘文件
void create()
{
        seteuid(getuid());
        restore();
}

// 返回存盘文件位置
string query_save_file()
{
        return DATA_FILE;
}

void remove()
{
        save();
}

void mud_shutdown()
{
        save();
}

// 提示符
private void write_prompt(object me)
{
        write("您打算：" WHT "A" NOR "、创建新的项目 " WHT "B" NOR "、修改旧的项目 "
              WHT "C" NOR "、查看玩家投注 \n" WHT "        D" NOR "、结束一个项目 " WHT
              "E" NOR "、删除一个项目 " WHT "F" NOR "、退出管理系统 \n");
        write("请选择：");
        input_to("get_type", me);

}

// 退出管理
private void end_manage()
{
        write("\n您放弃了博彩管理。\n");
        write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
        return;
}

// 进入管理系统
public void start_manage(object me)
{
        write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
        write("\t\t\t  " + MUD_NAME + "博彩管理程序\n\n");
        write_prompt(me);
        return;
}

// 选择管理的类别
private void get_type(string arg, object me)
{
        array  users, items;
        string msg = "";
        int i, j;
        
        switch (arg)
        {
        case "a": 
        case "A":
                items = keys(item_data);
                msg = "目前的项目有：\n\n";
                
                for (i = 0; i < sizeof(items); i++)
                {
                        msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
                }
                
                if (! sizeof(items)) msg = "";
                
                write(msg);
                write("\n您打算创建新的博彩项目。\n");
                write("请输入新建的项目名称：");
                input_to("get_name", me);
                return;
        case "b": 
        case "B": 
                items = keys(item_data);
                
                if (! sizeof(items))
                {
                        write("\n目前没有可修改项目。\n\n");
                        
                        write("查询完毕。\n");
                        write_prompt(me);
                        return;
                }
                
                msg = "目前的项目有：\n\n";
                
                for (i = 0; i < sizeof(items); i++)
                {
                        msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
                }
                write(msg);
                write("\n您打算修改旧的博彩项目。\n");
                write("请输入您要修改的项目名称：");
                input_to("get_name", me);
                return;
        case "c": 
        case "C": 
                users = keys(user_data);
                
                write("您打算查看玩家投注情况。\n");
                
                if (! sizeof(users))
                {
                        write("\n目前没有任何玩家投注。\n\n");
                        
                        write("查询完毕。\n");
                        write_prompt(me);
                        return;
                }
                
                write("目前投注的玩家有：\n\n");
                msg = WHT "";
                
                for (i = 0; i < sizeof(users); i++ )
                {
                        msg += sprintf("%10s", users[i]);
                        j++;
                        if (! (j % 5)) msg += "\n";
                }
                write(msg + NOR);
                write("\n\n一共有 " WHT + i + NOR " 名玩家已经投注。\n");
                write("\n请选择你具体查看的玩家：");
                input_to("get_user", me);
                return;
        case "d": 
        case "D": 
                write("你打算结束一个博彩项目。\n");
                
                items = keys(item_data);
                // 必须是已经停止的项目才行
                items = filter_array(items, (: query_status($1) == OPENING :));
                
                if (! sizeof(items))
                {
                        write("\n目前没有可修改项目。\n\n");
                        
                        write("查询完毕。\n");
                        write_prompt(me);
                        return;
                }
                
                msg = "目前的项目有：\n\n";
                
                for (i = 0; i < sizeof(items); i++)
                {
                        msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
                }
                write(msg);
                write("\n请输入您要结束的项目名称：");
                input_to("get_name_end", me);
                return;
        case "e": 
        case "E": 
                write("你打算删除一个博彩项目。\n");
                
                items = keys(item_data);
                
                if (! sizeof(items))
                {
                        write("\n目前没有可修改项目。\n\n");
                        
                        write("查询完毕。\n");
                        write_prompt(me);
                        return;
                }

                msg = "目前的项目有：\n\n";
                
                for (i = 0; i < sizeof(items); i++)
                {
                        msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
                }
                write(msg);
                write("\n请输入您要删除的项目序号：");
                input_to("get_name_todel", me);
                return;
        default: 
                end_manage();
                return;
        }
        
}

// 选择管理的项目名称
private void get_name(string arg, object me)
{
        array teams;
        string msg = "", team;
        int i, num;
        mapping item;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        // 修改旧项目
        if (mapp(item_data[arg]) && sizeof(item_data[arg]) >= 5)
        {
                teams = keys(item_data[arg]["subject"]);
                
                for (i = 0; i < sizeof(teams); i++)
                {
                        team = teams[i];
                        msg += sprintf("%10s：" WHT "1 : %d\n" NOR , team, item_data[arg]["subject"][team]);
                }
                
                change_status(arg, INITING);
                write("\n1、名称：" WHT + arg + NOR "\n"
                      "2、描述：\n\n" WHT + sort_msg(item_data[arg]["long"]) + NOR "\n\n"
                      "3、结束时间：" WHT + CHINESE_D->chinese_time(5, ctime(item_data[arg]["end_time"])) + 
                      (item_data[arg]["end_time"] > time() ? "" : HIR "(已结束)") + NOR "\n"
                      "4、可投注数量：" WHT + item_data[arg]["number"] + " 个\n" NOR 
                      "5、最小投注量：" WHT + item_data[arg]["min_money"] + " 两黄金\n" NOR 
                      "6、队伍及赔率：\n\n" + msg + "\n" );
                write("请选择您要修改的项目：");
                input_to("select_change_type", me, arg);
                return;
        }
        else if (sscanf(arg, "%d", num) == 1  &&
                 mapp(item = item_data[keys(item_data)[num - 1]]) && sizeof(item) >= 5)
        {
                teams = keys(item["subject"]);
                arg = keys(item_data)[num - 1];
                
                for (i = 0; i < sizeof(teams); i++)
                {
                        team = teams[i];
                        msg += sprintf("%10s：" WHT "1 : %d\n" NOR , team, item["subject"][team]);
                }
                
                change_status(arg, INITING);
                write("\n1、名称：" WHT + arg + NOR "\n"
                      "2、描述：\n\n" WHT + sort_msg(item["long"]) + NOR "\n\n"
                      "3、结束时间：" WHT + CHINESE_D->chinese_time(5, ctime(item["end_time"])) +  
                      (item["end_time"] > time() ? "" : HIR "(已结束)") + NOR "\n"
                      "4、可投注数量：" WHT + item["number"] + " 个\n" NOR 
                      "5、最小投注量：" WHT + item["min_money"] + " 两黄金\n" NOR
                      "6、队伍及赔率：\n\n" + msg + "\n" );
                write("请选择您要修改的项目：");
                input_to("select_change_type", me, arg);
                return;
        }
        // 创建新项目
        else
        {
                item_data[arg] = ([ ]);
                change_status(arg, INITING);
                save();
                write("\n请输入项目的详细描述：\n");
                me->edit((: call_other, __FILE__, "get_long", me, arg :));
                return;
        }
}

private void select_change_type(string arg, object me, string name)
{
        switch (arg)
        {
        case "1":
                write("\n你打算修改这个项目的名称。\n");
                write("你打算改成什么呢：");
                input_to("change_name", me, name);
                return;
        case "2":
                write("\n你打算修改这个项目的长描述。\n");
                write("你打算改成什么呢：");
                me->edit((: call_other, __FILE__, "change_long", me, name :));
                return; 
        case "3": 
                write("\n你打算修改这个项目的结束时间。\n");
                write("这个项目将在多少天后结束？");
                input_to("change_date", me, name);
                return; 
        case "4": 
                write("\n你打算修改这个项目的可投注队伍数。\n");
                write("这个项目允许的投注队伍数为：");
                input_to("change_number", me, name);
                return; 
        case "5": 
                write("\n你打算修改这个项目的最小投注量。\n");
                write("你打算改成多少呢：");
                input_to("change_money", me, name);
                return;
        case "6": 
                write("\n你打算修改这个项目的队伍数据。\n");
                write("你要怎么修改？[" WHT "1" NOR "、修改 " WHT "2" NOR "、删除]");
                input_to("change_team_type", me, name);
                return;
        default: 
                change_status(name, OPENING);
                write("\n你放弃了修改。\n\n");
                write("修改完毕。\n");
                write_prompt(me);
                return;
        }
}

// 修改项目的名称
private void change_name(string arg, object me, string name)
{
        mapping item;
        
        if (arg == "")
        {
                change_status(name, OPENING);
                end_manage();
                return;
        }
        if (mapp(item_data[arg]))
        {
                change_status(name, OPENING);
                write("\n这是一个已存在的项目，不可以修改。\n\n");
                write("你回到了博彩管理主界面。\n");
                write_prompt(me);
                return;
        }
        item = item_data[name];
        item_data[arg] = item;
        map_delete(item_data, name);
        change_status(arg, OPENING);
        save();
        
        log_file("gamble",sprintf("%schangetheitem%s'snameto%son%s.\n",query("id", me),
                           name, arg, ctime(time())));

        write("\n项目 " WHT + name + NOR + " 的名字已经被成功改为了 " WHT + arg + NOR + "。\n\n");
        write("修改完毕，你回到了管理系统主界面。\n");
        write_prompt(me);
        return;
}

// 输入项目的长描述
private void change_long(object me, string arg, string long)
{
        if (long == "")
        {
                change_status(arg, OPENING);
                end_manage();
                return;
        }

        item_data[arg]["long"] = replace_string(long, "\n", "");
        change_status(arg, OPENING);
        save();
                
        write("\n项目" WHT + arg + NOR "的描述已经被成功改为了\n " WHT + sort_msg(long) + NOR "\n\n");
        write("修改完毕，你回到了管理系统主界面。\n");
        write_prompt(me);
        return;
}

private void change_date(string arg, object me, string name)
{
        int day, time;
        
        if (arg == "")
        {
                change_status(name, OPENING);
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", day) || day <= 0)
        {
                write("\n非法的格式，请重新输入。\n\n");
                
                write("请问这个项目将在多少天后结束投注？[格式：" WHT "5" NOR "]");
                input_to("change_date", me, name);
                return;
        }
        
        time = time() + 86400 * day;       
        item_data[name]["end_time"] = time;
        change_status(name, OPENING);
        save();
                
        write("\n项目" WHT + name + NOR "的结束时间已经被成功改为了 " WHT + chinese_number(day) + NOR " 天左右结束。\n\n");
        write("修改完毕，你回到了管理系统主界面。\n");
        write_prompt(me);
        return;
}

private void change_number(string arg, object me, string name)
{
        int number;
        
        if (arg == "")
        {
                change_status(name, OPENING);       
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", number) || number <= 0)
        {
                write("\n非法的格式，请重新输入。\n\n");
                
                write("请输入允许玩家选择的队伍数目：");
                input_to("change_number", me, name);
                return;
        }
        
        item_data[name]["number"] = number;
        change_status(name, OPENING);
        save();
        
        write("\n项目 " WHT + name + NOR + " 的投注队伍数已经被成功改为了 " WHT + chinese_number(number) + NOR + "个。\n\n");
        write("修改完毕，你回到了管理系统主界面。\n");
        write_prompt(me);
        return;
}

private void change_money(string arg, object me, string name)
{
        int money;
        
        if (arg == "")
        {
                change_status(name, OPENING);
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", money) || money <= 0)
        {
                write("\n非法的格式，请重新输入。\n\n");
                
                write("请输入项目的最少投注黄金量：[格式：" WHT "10000" NOR "]");
                input_to("get_least_money", me, name);
                return;
        }
        
        item_data[name]["min_money"] = money;
        change_status(name, OPENING);
        save();

        write("\n项目 " WHT + name + NOR + " 的最小投注量已经被成功改为了 " WHT + chinese_number(money) + NOR + "。\n\n");
        write("修改完毕，你回到了管理系统主界面。\n");
        write_prompt(me);
        return;
}

// 选择修改队伍的数据类型
private void change_team_type(string arg, object me, string name)
{
        if (arg == "")
        {
                change_status(name, OPENING);
                end_manage();
                return;
        }
        if (arg == "1")
        {
                write("\n你打算修改项目" + name + "的队伍数据。\n");
                input_to("change_team_info", me, name);
                return;
        }
        else 
        {
                write("\n你打算删除项目" + name + "的一个队伍数据。\n");
                input_to("del_team_info", me, name);
                return;
        }
}

// 输入项目的长描述
private void get_long(object me, string arg, string long)
{
        if (long == "")
        {
                end_manage();
                return;
        }

        item_data[arg]["long"] = replace_string(long, "\n", "");
        save();
        
        write("\n请输入项目包含的队伍数目：");
        input_to("get_team_number", me, arg);
        
        return;
}

// 输入项目的队伍数
private void get_team_number(string arg, object me, string name)
{
        int times;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        sscanf(arg, "%d", times);
        
        if (times > 20 || times <= 0)
        {
                write("对不起，这个数目是不合法的。\n");
                
                write("请输入项目包含的队伍数目：");
                input_to("get_team_number", me, name);
                
                return;
        }
        
        // 初始化队伍映射
        item_data[name]["subject"] = ([ ]);
        save();
        
        write("\n请输入第一个队伍的名称及赔率[格式：" WHT "中国队:30" NOR "]：");
        input_to("get_team_info", me, name, times);
        
        return;
}

// 输入具体一个队伍的信息
private void get_team_info(string arg, object me, string name, int times)
{
        string team;
        int bonus;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (sscanf(arg, "%s:%d", team, bonus) != 2)
        {
                write("格式错误，请重新输入。\n");
                write("请输入第一个队伍的名称及赔率[格式：" WHT "中国队:30" NOR "]：");
                input_to("get_team_info", me, name, times);
        
                return;
        }
        
        // 防止出现重复输入
        if (item_data[name]["subject"][team])
        {
                write("这个队伍已经输入过了。\n");
                write("请输入下一个队伍的名称及赔率[格式：" WHT "中国队:30" NOR "]：");
                input_to("get_team_info", me, name, times);
        
                return;
        }
        
        item_data[name]["subject"][team] = bonus; 
        
        // 如果所有的队伍都输入完了
        if (times == sizeof(item_data[name]["subject"]))
        {
                write("\n请问这个项目将在多少天后结束投注？[格式：" WHT "5" NOR "]");
                input_to("get_date_off", me, name);
                return;
        }
        
        write("目前还剩下：" + (times - sizeof(item_data[name]["subject"])) + "个队。\n");
        
        item_data[name]["subject"][team] = bonus;
        save();
        
        write("\n请输入下一个队伍的名称及赔率[格式：" WHT "中国队:30" NOR "]：");
        input_to("get_team_info", me, name, times);
        
        return;
}

// 输入结束的时间
private void get_date_off(string arg, object me, string name)
{
        int day, time;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", day) || day <= 0)
        {
                write("\n非法的格式，请重新输入。\n\n");
                
                write("请问这个项目将在多少天后结束投注？[格式：" WHT "5" NOR "]");
                input_to("get_date_off", me, name);
                return;
        }
        
        time = time() + 86400 * day;
        
        item_data[name]["end_time"] = time;
        save();
        
        write("\n项目" WHT + name + NOR "将在 " WHT + CHINESE_D->chinese_time(5, ctime(time)) +
              NOR " 左右结束。\n\n");
              
        write("请输入项目的最少投注黄金量：[格式：" WHT "10000" NOR "]");
        input_to("get_least_money", me, name);
        return;
}

// 输入最少投注量
private void get_least_money(string arg, object me, string name)
{
        int money;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", money) || money <= 0)
        {
                write("\n非法的格式，请重新输入。\n\n");
                
                write("请输入项目的最少投注黄金量：[格式：" WHT "10000" NOR "]");
                input_to("get_least_money", me, name);
                return;
        }
        
        item_data[name]["min_money"] = money;
        save();
        
        write("\n项目" WHT + name + NOR "的最小投注量是 " WHT + money +
              NOR " 两黄金。\n\n");
        
        write("请输入允许玩家选择的队伍数目：");
        input_to("get_chip_number", me, name);
        return;
}

// 输入允许玩家选择的队伍数目
private void get_chip_number(string arg, object me, string name)
{
        int number;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", number) 
            || number <= 0
            || number >= sizeof(item_data[name]["subject"]))
        {
                write("\n非法的格式，请重新输入。\n\n");
                
                write("请输入允许玩家选择的队伍数目：");
                input_to("get_chip_number", me, name);
                return;
        }
        
        item_data[name]["number"] = number;
        save();
        
        write("项目" WHT + name + NOR "允许玩家选择的队伍数目是 " WHT + chinese_number(number) +
              NOR " 个。\n\n");
              
        // 全部内容编辑完毕
        change_status(name, OPENING);
        save();
        
        log_file("gamble",sprintf("%screateagambleitemcalled%son%s.\n",query("id", me),
                           name, ctime(time())));

        write("全部内容编辑保存完毕。\n");
        
        write("你回到的管理系统主界面。\n"); 
        write_prompt(me);        
        return;
}

// 删除一个项目
private void get_name_todel(string arg, object me)
{
        int number;
        array names;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", number) || number <= 0)
        {
                write("\n非法的格式，请重新输入。\n\n");
                
                write("请输入你要删除的项目序号：");
                input_to("get_name_todel", me);
                return;
        }
        
        names = keys(item_data);
        if (! mapp(item_data[names[number - 1]]))
        {
                write("\n没有这个项目。\n\n");
                
                write("请输入你要删除的项目序号：");
                input_to("get_name_todel", me);
                return;
        }
        
        write("项目" WHT + names[number - 1] + NOR "被成功删除了。\n\n");
        map_delete(item_data, names[number - 1]);
        log_file("gamble",sprintf("%sdeleteagambleitemcalled%son%s.\n",query("id", me),
                           names[number - 1], ctime(time())));
        save();
        
        write("你回到的管理系统主界面。\n"); 
        write_prompt(me);        
        return;
}

// 玩家投注界面
public void do_chip(object me)
{
        array items = keys(item_data);
        string msg = "目前允许投注的项目有：\n\n";
        int i;
        
        write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
        write("\t\t  「" HIW + MUD_NAME + "博彩公司" NOR "」\n\n");
        
        if (! sizeof(items))
        {
                write("没有可供下注的项目。\n");
                write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
                return;
        }
        
        for (i = 0; i < sizeof(items); i++)
        {
                // 如果没有开放
                if (query_status(items[i]) != OPENING)
                        continue;
                msg += WHT + (i+1) + NOR "、" + items[i] + "\n";
        }
        write(msg);
        write("\n请选择您要参与博彩的项目[" WHT "Enter" NOR " 退出]：");
        input_to("select_name_tochip", me);
        
        return;
}

// 选择投注的项目
private void select_name_tochip(string arg, object me)
{
        string name, *teams, msg = "";
        int i;
        mapping item;
        string id=query("id", me);
                
        if (arg == "")
        {
                write("\n你放弃了投注。\n");
                write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
                return;
        }

        if (! sscanf(arg, "%d", i) || i <= 0)
        {
                write("\n你发烧了？怎么可能会有这个项目？\n");
                write("请选择您要参与博彩的项目[" WHT "Enter" NOR " 退出]：");
                input_to("select_name_tochip", me);
        
                return;
        }
        
        name = keys(item_data)[i - 1];
        
        if (! mapp(item = item_data[name]))
        {
                write("\n没发烧？但确实没有这个项目呀。\n");
                write("请选择您要参与博彩的项目[" WHT "Enter" NOR " 退出]：");
                input_to("select_name_tochip", me);
        
                return;
        }
 
        if (mapp(user_data[id]) &&
            sizeof(user_data[id][name]) >= 2)
        {
                teams = user_data[id][name]["team"];
                for (i = 0; i < sizeof(teams); i++)
                {
                        msg += sprintf("%10s：" WHT "1 : %d\n" NOR , teams[i], item["subject"][teams[i]]);
                }                
                write("\n这个项目你不是已经投注了吗？可不能反悔哦。\n");
                write("\n1、名称：" WHT + name + NOR "\n"
                        "2、描述：\n\n" WHT + sort_msg(item["long"]) + NOR "\n\n"
                        "3、结束时间：" WHT + CHINESE_D->chinese_time(5, ctime(item["end_time"])) + 
                        (item["end_time"] > time() ? "" : HIR "(已结束)") + NOR "\n"
                        "4、可投注数量：" WHT + item["number"] + " 个\n" NOR 
                        "5、已投注黄金：" WHT + user_data[id][name]["money"] + " 两黄金\n" NOR
                        "6、队伍及赔率：\n\n" + msg + "\n" );

                write("请选择您要参与博彩的项目[" WHT "Enter" NOR " 退出]：");
                input_to("select_name_tochip", me);
                return; 
        }
                
        if (item["status"] != OPENING)
        {
                write("\n这个项目还没开放或者是已经停止了，你还是换一个吧。\n");
                write("请选择您要参与博彩的项目[" WHT "Enter" NOR " 退出]：");
                input_to("select_name_tochip", me);
        
                return;
        }
        
        /*
        // 投注是分开来一队一队的投
        if (mapp(user_data[id]) && 
            arrayp(teams = user_data[id][name]["team"]) && 
            sizeof(teams) >= item_data[name]["number"])
        {
                write("你下注的队伍已经够多的了。\n");
                return;
        }
        */                  
        
        teams = keys(item["subject"]);
                
        for (i = 0; i < sizeof(teams); i++)
        {
                msg += sprintf("%10s：" WHT "1 : %d\n" NOR , teams[i], item["subject"][teams[i]]);
        }

        write("\n1、名称：" WHT + name + NOR "\n"
                        "2、描述：\n\n" WHT + sort_msg(item["long"]) + NOR "\n\n"
                        "3、结束时间：" WHT + CHINESE_D->chinese_time(5, ctime(item["end_time"])) + 
                        (item["end_time"] > time() ? "" : HIR "(已结束)") + NOR "\n"
                        "4、可投注数量：" WHT + item["number"] + " 个\n" NOR 
                        "5、最小投注量：" WHT + item["min_money"] + " 两黄金\n" NOR
                        "6、队伍及赔率：\n\n" + msg + "\n" );

        write("请输入你要投注的队伍[多个用“" WHT "," NOR "”隔开]：");

        input_to("select_team_tochip", me, name);

        return;
}

// 选择投注的队伍
protected void select_team_tochip(string arg, object me, string name)
{
        array teams, all_teams;
        int i, n;
        
        if (arg == "")
        {
                write("\n你放弃了投注。\n");
                write(HIW "－－－－－－－－－－－－－－－－－－－－－－－－－－\n" NOR);
                return;
        }

        if (! item_data[name])
        {
                write(name + "\n");
                write("Non data.\n");
                return;
        }

        if (! arrayp(teams = explode(arg, ",")) ||
            ! n = sizeof(teams))
        {
                write("\n输入格式错误，请重新输入。\n");
                write("请输入你要投注的队伍[多个用“" WHT "," NOR "”隔开]：");
                input_to("select_team_tochip", me, name);
                return;
        }
        
        all_teams = keys(item_data[name]["subject"]);
        if (n != item_data[name]["number"])
        {
                write("\n输入的队伍数目不符合。\n");
                write("请重新输入你要投注的队伍[多个用“" WHT "," NOR "”隔开]：");
                input_to("select_team_tochip", me, name);
                return;
        }
        
        for (i = 0; i < n; i++)
        {
                if (member_array(teams[i], all_teams) == -1)
                {
                        write("\n这个队伍不属于这个项目。\n");
                        write("请重新输入你要投注的队伍[多个用“" WHT "," NOR "”隔开]：");
                        input_to("select_team_tochip", me, name);
                        return;
                }
        }
        
        user_data+=([query("id", me):([name:(["team":teams])])]);
        
        write("\n你选择下注的队伍是" WHT + implode(teams, NOR "、" WHT) + NOR + "。\n\n");
        write("\n请输入你要下注的黄金：");
        input_to("get_money_tochip", me, name);
        
        return;
}

protected void get_money_tochip(string arg, object me, string name)
{
        string id;
        int money;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        
        if (! sscanf(arg, "%d", money) || money <= 0)
        {
                write("\n非法的格式，请重新输入。\n\n");
                
                write("请输入最少投注黄金量：[格式：" WHT "10000" NOR "]");
                input_to("get_money_tochip", me, name);
                return;
        }
        
        id=query("id", me);
        
        if (count_lt(money, item_data[name]["min_money"]))
        {
                write("你至少要下注" + chinese_number(item_data[name]["min_money"]) + "两黄金吧。\n");
                input_to("get_money_tochip", me, name);
                return;
        }
        
        if( count_le(query("balance", me),count_mul(money,10000)) )
        {
                write("\n你银行的存款余额不足，请重新输入。\n\n");                                 
                write("请输入最少投注黄金量：[格式：" WHT "10000" NOR "]");
                input_to("get_money_tochip", me, name);
                return;
        }
        
        set("balance", count_sub(query("balance", me),count_mul(money,10000)), me);
        user_data[id][name] += ([ "money" : money ]);                               
        save();
        
        write("投注成功。\n");
        return;
}

// 选择查询的玩家
private void get_user(string arg, object me)
{
        mapping user;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        if (! mapp(user = user_data[arg]))
        {
                write("没有这个投注用户。\n");
                write("请选择你具体查看的玩家：");
                input_to("get_user", me);
                return;
        }
        write("用户 " + WHT + arg + NOR " 参加投注的项目有：\n\n" WHT + implode(keys(user), NOR "/" WHT) + NOR "\n");
        
        write("\n请选择具体查看的项目：");
        input_to("get_user_info", me, arg);
        
        return;
}

// 获得玩家的具体信息
private void get_user_info(string arg, object me, string id)
{
        mapping user;
        
        if (arg == "")
        {
                end_manage();
                return;
        }
        if (! mapp(user = user_data[id][arg]))
        {
                write("没有这个项目。\n");
                write("请选择具体查看的项目：");
                input_to("get_user_info", me, arg);
                return;
        }
        write("\n投注者：" + WHT + id + NOR + "\n");
        write("项目名：" + WHT + arg + NOR + "\n");
        write("投注量：" + WHT + user_data[id][arg]["money"] + NOR " 两黄金" + NOR + "\n");
        write("投注队伍：" WHT + implode(user_data[id][arg]["team"], NOR " & " WHT) + NOR + "\n\n");
        
        write("查询完毕，你回到的管理系统主界面。\n"); 
        write_prompt(me); 
        return;
}

private void get_name_end(string arg, object me)
{
        if (arg == "")
        {
                end_manage();
                return;
        }
              
        change_status(arg, STOPPED);        
        write("修改完毕，你回到的管理系统主界面。\n"); 
        write_prompt(me); 
        return;
}

// 改变项目的状态
public void change_status(string name, string status)
{
        if (mapp(item_data[name]))
        {
                item_data[name]["status"] = status;
                save();
                return;
        }
        else return;
}

// 查询项目的状态
public string query_status(string name)
{
        if (! stringp(name) || name == ""
            || ! mapp(item_data[name]))
        {
                return INITING;
        }
        else
        {
                return item_data[name]["status"];
        }
}

// 返回一个项目内容(以供博彩屋调用)
public mapping query_item(string name)
{
        if (mapp(item_data[name]))
                return item_data[name];
}

// 返回整个数据库
varargs public mapping query_data(int raw)
{
        if (raw)
                return user_data;
        return item_data;
}
