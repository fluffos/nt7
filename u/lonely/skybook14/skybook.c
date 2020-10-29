// skybook.c 十四天书任务相关指令

#include <ansi.h>

#define DB_D          "/adm/daemons/dbd"
#define DIALOG_D      "/adm/daemons/dialogd"
#define SUICONG_D     "/adm/daemons/suicongd"
#define SKYBOOK_D     "/adm/daemons/skybookd"

inherit F_CLEAN_UP;

int help(object me);

mapping skybooks = ([

        "1" : "飞狐外传:★★★☆",
        "2" : "雪山飞狐:★★★☆",
        "3" : "连城诀:★★★",
        "4" : "天龙八部:★★★★★",
        "5" : "射雕英雄传:★★★★★",
        "6" : "白马啸西风:★★★",
        "7" : "鹿鼎记:★★★★",
        "8" : "笑傲江湖:★★★★★",
        "9" : "书剑恩仇录:★★★★",
        "10" : "神雕侠侣:★★★★★",
        "11" : "侠客行:★★★★☆",
        "12" : "倚天屠龙记:★★★★★",
        "13" : "碧血剑:★★★★☆",
        "14" : "鸳鸯刀:★★★☆",
]);

// 用于对应天书的管理OB，每本天书对应1个管理OB
mapping skybook_id = ([
        "飞狐外传"    : "feihuwaizhuan",
        "雪山飞狐"    : "xueshanfeihu", 
        "连城诀"      : "lianchengjue", 
        "天龙八部"    : "tianlongbabu",
        "射雕英雄传"  : "shediaoyingxiongzhuan",
        "白马啸西风"  : "baimaxiaoxifeng",
        "鹿鼎记"      : "ludingji",
        "笑傲江湖"    : "xiaoaojianghu",
        "书剑恩仇录"  : "shujianenchoulu",
        "神雕侠侣"    : "shendiaoxialv", 
        "侠客行"      : "xiakexing",    
        "倚天屠龙记"  : "yitiantulongji",
        "碧血剑"      : "bixuejian",
        "鸳鸯刀"      : "yuanyangdao",
]);

void create() 
{
        seteuid(getuid());

}

string Get_Pingjia(int nPoint)
{
        if (nPoint == 1)return "★";
        if (nPoint == 2)return  "★★";
        if (nPoint == 3)return "★★★";
        
        return "未完成";
}

int main(object me, string arg)
{
        string sBook, msg, sDiff, sJindu, sPingjia;
        int i;

        if (! arg)return help(me);
        
        if (arg == "list")
        {
                msg =  HIY "\n你翻开十四天书，发现记载了以下内容…………\n" NOR;
                msg += HIC"----------------------------------------------------------------------------\n" NOR;
                msg +=  sprintf(HIG "%-20s%-20s%-20s%-20s\n" NOR, "天书", "难度", "完成进度", "完成评价");
                msg += HIC"----------------------------------------------------------------------------\n" NOR;
                
                for (i = 0; i < sizeof(skybooks); i ++)
                {
                        sscanf(skybooks[sprintf("%d", i+1)], "%s:%s", sBook, sDiff);
                        // 完成进度，首先判断是否激活
                        if (! me->query("skybook14/" + sBook + "/激活"))
                        {
                                sJindu = NOR + WHT "未激活" NOR;
                        }
                        else
                        {
                                // 激活了，判断是否已经接了任务
                                if (! me->query("skybook14/" + sBook + "/当前章节"))
                                        sJindu = HIR "已激活" NOR;
                                else
                                        sJindu = HIG + me->query("skybook14/" + sBook + "/当前章节") + NOR;
                        }

                        sBook = HIG + sBook[0..1] + NOR + sBook[2..(sizeof(sBook)-1)];
                        // 获取评价
                        sPingjia = Get_Pingjia(me->query("skybook14/" + sBook + "/完成评价"));

                        msg += sprintf("%-36s%-20s%-20s%20s\n", sBook, sDiff, sJindu, sPingjia);
                }

                msg += HIC"----------------------------------------------------------------------------\n" NOR;
                msg += HIY"skybook cha <天书名> 可查看天书详情\n" NOR;
                msg += HIY"skybook jihuo <天书名> 可激活\n" NOR;
                msg += HIY"skybook reset <天书名> 可重置天书\n" NOR;
                msg += HIY"skybook start <天书名> 可继续天书任务\n" NOR;                
                write(msg);
                return 1;
        }
        
        if (sscanf(arg, "cha %s", sBook) == 1)
        {
                if (! me->query("skybook14/" + sBook + "/激活"))
                        return notify_fail(sBook + "还未激活，请用 " HIG + "skybook jihuo " + sBook + NOR " 激活\n");
                        
                if (me->query("skybook14/" + sBook + "/当前章节") == 0)
                        return notify_fail(sBook + "还未开始，请用 " HIG + "skybook start " + sBook + NOR " 开始\n");

                msg = HIY + "\n" + sBook + "天书记载了以下内容…………\n" NOR;
                msg += HIC"----------------------------------------------------------------\n" NOR;
                msg += HIY "当前章节：" + me->query("skybook14/" + sBook + "/当前章节") + "\n" NOR;
                msg += HIY "任务描述：" HIG + me->query("skybook14/" + sBook + "/当前任务") + "\n" NOR;
                if (wizardp(me))
                        msg += HIY "任务编号：" + sprintf("%d", me->query("skybook14/" + sBook + "/任务编号")) +  "\n" NOR;
                msg += HIY "任务状态：" + (me->query("skybook14/" + sBook + "/任务状态") == 1 ? HIG "已完成" NOR: HIC "进行中" NOR) + "\n" NOR;
                msg += HIY "完成评价：" + (me->query("skybook14/" + sBook + "/当前章节") != "已完成" ? "未完成" : me->query("skybook14/" + sBook + "/完成评价")) + "\n" NOR;
                msg += HIC"----------------------------------------------------------------\n" NOR;
                msg += HIY"任务若完成，可输入 skybook start " + sBook + " 来交付任务！\n\n" NOR;
                
                write(msg);
                return 1;
        }
        if (sscanf(arg, "jihuo %s", sBook) == 1)
        {
                string *get2kskills, *keys_myskills;
                mapping getmyskills;
                
                if (! wizardp(me))return notify_fail("暂时未开放，敬请期待！\n");
                
                if (me->query("skybook14/" + sBook + "/激活"))
                        return notify_fail(sBook + "已经激活了！\n");
                
                if (! me->query("scborn/ok"))
                        return notify_fail("你还没有转世重生，无法激活天书，转世说明见 help scborn\n");
                
                
                
                // 不同天书不同激活条件
                switch(sBook)
                {
                         case "连城诀":
                                
                         if (me->query("skybook14/" + sBook + "/激活条件"))
                         {
                                if (! me->query_temp("want_jihuo_skybook/" + sBook) )
                                {
                                        me->set_temp("want_jihuo_skybook/" + sBook, 1);
                                        write(HIG "激活" HIY + sBook + HIG "将损耗你的" + HIY + 
                                              CHINESE_D->chinese(me->query("skybook14/" + sBook + "/激活条件")) + HIG +
                                              "100级，如果确定请再输入一次该指令！\n" NOR);
                                        
                                        return 1;
                                }
                                
                                me->delete_temp("want_jihuo_skybook/" + sBook);
                                
                                // 降低技能，开始激活
                                me->add_skill(me->query("skybook14/" + sBook + "/激活条件"), -200);

                                me->delete("skybook14/" + sBook + "/激活条件");
                                
                                me->set("skybook14/" + sBook + "/激活", 1);
                                
                                write(HIG "天书" HIY + sBook + HIG "已激活，输入 skybook start + sBook + 开启序章！\n" NOR);

                                // 初始化
                                me->set("skybook14/" + sBook + "/当前章节", "序章");
                                me->set("skybook14/" + sBook + "/当前任务", "输入 skybook start " + sBook + " 打开天书序幕吧!");
                                me->set("skybook14/" + sBook + "/任务编号", 1);
                                
                                __FILE__->main(me, "cha " + sBook);

                                log_file("0激活天书.log", me->query("id") + "激活" + sBook + " 降低技能 " + 
                                         me->query("skybook14/" + sBook + "/激活条件") + " at " + ctime(time()) + "\n");
                                
                                return 1;
                         }

                         // 大于1500LV的技能随机降低200级，若没有大于1500的技能，则不能激活
                         getmyskills = me->query_skills();                       
                         if (! sizeof(getmyskills))return notify_fail("你连技能都没有学，还想闯天书？\n");
                         keys_myskills = keys(getmyskills);
                         get2kskills = ({});
                         for (i = 0; i < sizeof(keys_myskills); i ++)
                                if (getmyskills[keys_myskills[i]] >= 1500)
                                        get2kskills += ({keys_myskills[i]});

                        if (! sizeof(get2kskills))
                                return notify_fail("激活连城诀天书至少需要一项技能达到1500级！\n");

                        me->set_temp("want_jihuo_skybook/" + sBook, 1);

                        // 随机选择1个需要损耗的技能
                        me->set("skybook14/" + sBook + "/激活条件", get2kskills[random(sizeof(get2kskills))] );

                        write(HIG "激活" HIY + sBook + HIG "将损耗你的" + HIY + 
                              CHINESE_D->chinese(me->query("skybook14/" + sBook + "/激活条件")) + HIG +
                              "200级，如果确定请再输入一次该指令！\n" NOR);

                        return 1;                       
                        break; // up 连城诀

                        default:
                                return notify_fail(sBook + "天书不存在或暂未开放！\n");

                }// switch
                
                return 1;
        }
        if (sscanf(arg, "start %s", sBook) == 1)
        {
                object obtianshu;
                string sTianshu;
                
                if (me->is_fighting() || me->is_busy())
                        return notify_fail("你正忙着呢，等下再试吧！\n");
                
                if (! me->query("skybook14/" + sBook + "/激活"))
                        return notify_fail(sBook + "还未激活，请用 " HIG + "skybook jihuo " + sBook + NOR " 激活\n");               

                // 交给天书OB管理
                sTianshu = skybook_id[sBook];
                if (! objectp(obtianshu = find_object("/clone/skybook14/" + sTianshu + "/" + sTianshu)))
                        obtianshu = load_object("/clone/skybook14/" + sTianshu + "/" + sTianshu);

                if (! objectp(obtianshu))return notify_fail("天书管理OB错误，请联系新手导师或管理员处理！\n");

                obtianshu->startbook(me, sBook);
                
                return 1;               
                
        }
        if (sscanf(arg, "reset %s", sBook) == 1)  // 每次重置需要消耗特殊材料
        {
                if (! me->query("skybook14/" + sBook + "/激活"))
                        return notify_fail(sBook + "还未激活，请用 " HIG + "skybook jihuo " + sBook + NOR " 激活\n");   

                if (me->query("skybook14/" + sBook + "/当前章节") != "已完成")
                        return notify_fail(sBook + "还未完成，不能重置！\n");   
                
                // 重置需要消耗SCB
                if (DB_D->query_data("yhshop/scb/" + me->query("id")) < 99)
                {
                        return notify_fail("重置天书需要花费99商城币，你没有足够的剩余商城币！\n");
                }
                
                if (! me->query_temp("want_reset_tianshu/" + sBook))
                {
                        write(HIG "重置" + HIY + sBook + HIG "需要花费99商城币，如果你确定请再输入一次该指令！\n" NOR);
                        me->set_temp("want_reset_tianshu/" + sBook, 1);
                        
                        return 1;
                }
                
                me->delete_temp("want_reset_tianshu/" + sBook);

                // 扣除SCB
                DB_D->set_data("yhshop/scb/" + me->query("id"), DB_D->query_data("yhshop/scb/" + me->query("id"))-99);

                log_file("0天书重置.log", me->query("id") + " 重置 " + sBook + " at " + ctime(time()) + "\n");
                
                me->delete("skybook14/" + sBook);
                me->save();

                // 重置后不用帮忙激活
                me->set("skybook14/" + sBook + "/激活", 0);

                write("重置" + sBook + "完毕！\n");

                return 1;
        }       
        if (wizardp(me) && sscanf(arg, "enddialog %s %d", sBook, i) == 2)  // 测试指令，用于巫师直接跳过剧情对话
        {
                object obroom;
                
                if (! objectp(obroom = find_object("/clone/skybook14/" + sBook + "/" + sBook)))
                        obroom = load_object("/clone/skybook14/" + sBook + "/" + sBook);                

                obroom->dialog_end(me, i);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
指令格式 : skybook

skybook list                 ：查看十四天书总览
skybook cha <天书中文名>     ：查看对应的天书详情
skybook jihuo <天书中文名>   ：激活对应的天书
skybook start <天书中文名>   ：继续上次未完的天书任务
skybook reset <天书中文名>   ：当天书完成后，可重置天书后重新再做一次该天书任务

HELP );
    return 1;
}
