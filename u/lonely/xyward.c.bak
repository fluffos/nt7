
// #pragma optimize
// #pragma save_binary

#include <ansi.h>
#include <localtime.h>
#include <getconfig.h>

#define WARRING           2
#define THEEND            0
#define WAIT_START        3
#define XYNPC            "/kungfu/class/generate/xiangyang/"
#define GIFT_EXP_BASE    10000
#define GIFT_POT_BASE    10000
#define GIFT_MAR_BASE    3000
#define GIFT_WEI_BASE    10000
#define GIFT_YUE_BASE    10000
#define DB_D             "/adm/daemons/dbd"

#define MEMBER_D         "/adm/daemons/memberd"

// 东邪，西毒，南帝，北丐可随机增援
#define DONGXIE          "/kungfu/class/generate/xiangyang/huang"
#define XIDU             "/kungfu/class/generate/xiangyang/ouyangfeng"
#define NANDI            "/kungfu/class/generate/xiangyang/yideng"
#define BEIGAI           "/kungfu/class/generate/xiangyang/hong"

// 杨过和小龙女
#define YANGGUO          "/kungfu/class/generate/xiangyang/yang"
#define LONGNV           "/kungfu/class/generate/xiangyang/longnv"

// 增加的蒙古兵
#define MORE_SOLDIER     10
// 调动襄阳守军间隔
#define MOVE_WAIT        60

// 增加的襄阳士兵数量
#define ADD_XY_SOLDIER   120

// 增派蒙古兵次数
#define ADD_MGB_TIMES    3

// 增加蒙古兵时间间隔
#define ADD_MGB_WAIT     120

// 测试标志
#define TEST             0

// 是否允许开放标志
#define ALLOW_START      1

inherit F_DBASE;

int status = 0;                // 襄阳战状态
int start_status = 0;          // 系统状态，1 表明开始，则不再重复调用
int sign_up_status = 0;        // 报名标志
string *p = ({});             // 参加襄阳战的玩家物件列表

int start_time = 0;           // 襄阳保卫战开始时间
int attack_time = 0;          // 蒙古人开始攻城时间

int tiemuzhen = 0;            // 本次是否出现铁木真

int n_mg_tq = 0, n_mg_zb = 0, n_mg_gb = 0 , n_mg_bb = 0;// 骑兵、哲别、弓兵、步兵数量
int n_xy_sb = 0; // 襄阳士兵

int n_xy_sb2; // 襄阳士兵最初数量
int n_mg_sb2; // 蒙古士兵最初数量

int add_mgb_times = 0; // 增援蒙古兵次数
int query_add_mgb_times(){return add_mgb_times;}

int last_add_mgb_time = 0; // 上次增援蒙古兵时间
int last_combat_change_time = 0; // 上次调整战术的时间
int add_xyb_flag = 0; // 增派襄阳士兵标志

public int query_add_xyb_flag(){return add_xyb_flag;}

// 江湖人士增援的消息
string xy_msg1 = "----";
string query_xy_msg1(){return xy_msg1;}

// 1 为襄阳  2 为蒙古
int who_win; // 襄阳保卫战谁胜利

// 襄阳保卫战序列号 RAN_NUM
// 该序列号在每次开始前随机产生，作用是标注本次襄阳保卫战斗的唯一性
// 每杀死一个蒙古并则做设置 /xywar/RAN_NUM/point, point根据杀死的蒙古兵等级来设置
int RAN_NUM = 0;

public int get_who_win(){return who_win;}
public int set_who_win(int who){who_win = who;}
public void player_die(string id);
public int get_ran_num(){return RAN_NUM;} // 获取本次襄阳保卫战序列号

object xy_guojing; // 郭靖
int guojing_moved = 0; // 郭靖是否已经与蒙古人交战

// 新增蒙古援军所在方位，攻击方向则反向（由巫师动态控制）
string yb_attack_where = "none";
string query_yb_attack_where() { return yb_attack_where; }
string set_yb_attack_where(string str_where) { return yb_attack_where = str_where; }


// /kungfu/class/generate/xiangyang/guo.c 调用
public int if_guojing_moved()
{
        return guojing_moved;
}

// 免死调用
int die_xywar(object me)
{
        me->delete_override("die");

        // 保卫战已经结束则没有死亡保护
        if (status == THEEND)return 0;

        me->move("d/city/wumiao");

        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("eff_qi"));
        me->set("eff_jing", me->query("max_jing"));
        me->set("jing", me->query("eff_jing"));
        me->set("jingli", me->query("max_jingli"));

        me->revive();
        tell_object(me, BLINK + HIG "你已经退出襄阳保卫战！\n" NOR);
        player_die(me->query("id"));

        me->save();

        return 1;
}

// 移动NPC到蒙古军营前对军营其他PLAYER做清理
void clear_junying()
{
        object room;
        object *ob;
        int i, j;

        for (i = 1; i < 4; i ++)
        {
                if (! objectp(room = find_object("/d/xiangyang/junying" + sprintf("%d", i))))
                        room = load_object("/d/xiangyang/junying" + sprintf("%d", i));

                if (! objectp(room))
                {
                        log_file("xywar_clear_junying", "junying" + sprintf("%d", i) + " load object fail.\n");
                        return;
                }

                ob = all_inventory(room);

                if (! sizeof(ob))continue;

                // 将在军营的所有玩家移动的武庙
                for (j = 0; j < sizeof(ob); j ++)
                {
                        if (playerp(ob[j]))
                        {
                                ob[j]->move("/d/city/wumiao");
                                continue;
                        }
                }
        }

        XYWAR_D->xywar_message(HIW "蒙古军营清理完毕！\n" NOR);
}

// 设置报名参加襄阳保卫战的玩家免除死亡
void set_no_die(object me)
{
        me->set_override("die", (: call_other, __FILE__, "die_xywar", me:));

        return;
}


int is_guojing_died = 0;     // 郭靖是否死亡

string xysb_poision = "襄阳城内四周";

void start_xywar();                // 襄阳战开始
void reset_data();                 // 襄阳战结束后重新设置数据
string xywar_message(string msg);  // 襄阳战报
void set_now_status(int flag);     // 设置战斗状态

void combat_xjtuibing();          // 战术：虚假退兵
void combat_sdjixi();             // 战术：声东击西

string more_soldier_poision;  // 某一方向上士兵多MORE_SOLDIER名

string player_leader; // 玩家将领的ID

int last_move_xysolder = 0; // 上次调动襄阳守军的时间
int query_last_move_xysolder(){ return last_move_xysolder;}

// 四大门驻并地点
mapping doors = ([
        "west"  :      "/d/xiangyang/guandao_1",
        "east"  :      "/d/zhongzhou/toyy",
        "south" :      "/d/xiangyang/caodi6",
        "north" :      "/d/xiangyang/caodi3",
]);

mapping doors_name = ([
        "west"  :      "白虎门",
        "east"  :      "青龙门",
        "south" :      "朱雀门",
        "north" :      "玄武门",
]);

string random_doors_name()
{
        string *keys_name;

        keys_name = keys(doors_name);

        return doors_name[keys_name[random(sizeof(keys_name))]];
}

// /kungfu/class/generate/xiangyang/guo.c random_move()调用
public mixed get_doors()
{
        return doors;
}

// 襄阳士兵四大门驻并地点
mapping doors2 = ([
        "west"  :      "/d/xiangyang/westgate1",
        "east"  :      "/d/xiangyang/eastgate1",
        "south" :      "/d/xiangyang/southgate1",
        "north" :      "/d/xiangyang/northgate1",
]);

mapping doors2_name = ([
        "west"  :      "白虎内门",
        "east"  :      "青龙内门",
        "south" :      "朱雀内门",
        "north" :      "玄武内门",
]);

// 襄阳最接近中央广场的四个地点
mapping doors3 = ([
        "west"  :      "/d/xiangyang/westjie1",
        "east"  :      "/d/xiangyang/eastjie1",
        "south" :      "/d/xiangyang/southjie1",
        "north" :      "/d/xiangyang/anfupailou",
]);

mapping doors3_name = ([
        "west"  :      "襄阳城西大街",
        "east"  :      "襄阳城东大街",
        "south" :      "襄阳城南大街",
        "north" :      "安抚府牌楼",
]);

// 四大门的兵力数量
// ({ 铁骑、哲别、弓兵、 步兵  })
mapping n_soldier = ([
        "west"  :      ({0, 0, 0, 0}),
        "east"  :      ({0, 0, 0, 0}),
        "south" :      ({0, 0, 0, 0}),
        "north" :      ({0, 0, 0, 0}),
]);

// 将方向反向
public string re_poision(string p)
{
        if (! sizeof(p))return "";

        switch(p)
        {
                case "west":
                        return "east";
                case "east":
                        return "west";
                case "north":
                        return "south";
                default:
                        return "north";
        }
}

// 襄阳战结束
void xywar_over()
{
        status = THEEND;
        xywar_message(HIR "提示：本次襄阳保卫战由于报名人数不足，宣告结束。\n" NOR);
        reset_data();           // 襄阳战结束后重新设置数据

        return;
}

// 保卫战失败
// 蒙古胜利
public void war_fail()
{
        who_win = 2;;

        call_out("xywar_message", 4, HIY "本次襄阳保卫战以残败收场，蒙古人长驱直入，占领了襄阳，从此生灵涂炭，民不聊生 ……！\n");
        call_out("xywar_message", 5, HIY "而参与那次惨烈的襄阳保卫战的义士们却永远不会被后人所遗忘！\n");

        set_now_status(THEEND);

        return;
}

// 奖励所有参战玩家
void gift_to_player()
{
        object dob;
        int i, n;
        string str_ran_num;


        n = sizeof(p);

        // 将本次襄阳保卫战序列号转化为字串
        str_ran_num = sprintf("%d", RAN_NUM);

        for (i = 0; i < n; i ++)
        {
                dob = find_player(p[i]);

                if (! objectp(dob))continue;

                // 设置功勋
                dob->add("xywar/win", 1);

                // 根据战斗中杀敌数量来进行奖励，一个未杀则奖励设置为最低
                if (dob->query("xywar/xy_" + str_ran_num))
                {
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : GIFT_EXP_BASE + dob->query("xywar/xy_" + str_ran_num),
                                           "pot"      : GIFT_POT_BASE + dob->query("xywar/xy_" + str_ran_num) / 2,
                                           "weiwang"  : GIFT_WEI_BASE + dob->query("xywar/xy_" + str_ran_num) / 20,
                                           "score"    : GIFT_YUE_BASE + dob->query("xywar/xy_" + str_ran_num) / 20,
                                           "mar"      : GIFT_MAR_BASE + dob->query("xywar/xy_" + str_ran_num) / 20,
                                           "prompt"   : "你在襄阳保卫战胜利后"]), 999);
                        dob->delete("xywar/xy_" + str_ran_num);
                }
                else
                {
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : GIFT_EXP_BASE,
                                           "pot"      : GIFT_POT_BASE,
                                           "weiwang"  : GIFT_WEI_BASE,
                                           "score"    : GIFT_YUE_BASE,
                                           "mar"      : GIFT_MAR_BASE,
                                           "prompt"   : "你在襄阳保卫战胜利后"]), 999);
                }
                dob->save();

                /*
                // 根据经验来划分奖励
                if (dob->query("combat_exp") >= 30000000)
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : GIFT_EXP_BASE + random(GIFT_EXP_BASE / 2),
                                           "pot"      : GIFT_POT_BASE + random(GIFT_POT_BASE / 2),
                                           "weiwang"  : GIFT_WEI_BASE + random(GIFT_WEI_BASE / 2),
                                           "score"    : GIFT_YUE_BASE + random(GIFT_YUE_BASE / 2),
                                           "mar"      : GIFT_MAR_BASE + random(GIFT_MAR_BASE / 2),
                                           "prompt"   : "你在襄阳保卫战胜利后"]), 999);
                else
                        GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : GIFT_EXP_BASE / 2 + random(GIFT_EXP_BASE / 3),
                                           "pot"      : GIFT_POT_BASE / 2 + random(GIFT_POT_BASE / 3),
                                           "weiwang"  : GIFT_WEI_BASE / 2 + random(GIFT_WEI_BASE / 3),
                                           "score"    : GIFT_YUE_BASE / 2 + random(GIFT_YUE_BASE / 3),
                                           "mar"      : GIFT_MAR_BASE / 2 + random(GIFT_MAR_BASE / 3),
                                           "prompt"   : "你在襄阳保卫战胜利后"]), 999);
         */
        }

}

// 保卫战胜利
// 襄阳胜利
// 奖励所有参战玩家
public void war_win()
{
        who_win = 1;

        gift_to_player();

        set_now_status(THEEND);

        call_out("xywar_message", 4, HIW "由于襄阳守军及玩家地奋力抵抗，终于击退了蒙古军，襄阳保卫战胜利！\n");

        return;
}

// 蒙古人占领中央广场
void arrived_center()
{
        if (status == THEEND)return;

        war_fail();

        xywar_message(HIR "蒙古人已占领襄阳中央广场，本次襄阳保卫战以襄阳失陷告终！\n" NOR);

}

// 由于报名玩家剩余不到五名，战斗失败
void war_end_player()
{
        if (status == THEEND)return;

        xywar_message(HIR "由于参与襄阳保卫战的玩家已剩余不到五名，难以继续抵抗蒙古人的攻势。" NOR);
        xywar_message(HIR "蒙古人长驱直入，占领了襄阳，从此生灵涂炭，民不聊生 ……" NOR);
        xywar_message(HIR "而参与那次惨烈的襄阳保卫战的义士们却永远不会被后人所遗忘！\n" NOR);

        set_now_status(THEEND);

}

// 外部调用 /kungfu/class/generate/xiangyang/xyshibing.c调用
// 判断目前是否受到调动
public int is_moved()
{
        if (xysb_poision == "襄阳城内四周")return 0;

        return 1;
}

// 襄阳士兵目前的位置
// 外部可调用
public string xy_soldier_poision(string para)
{
        if (xysb_poision == "襄阳城内四周")
                return xysb_poision;

        switch(para)
        {
                // 返回地名
                case "name" :
                        return doors3_name[xysb_poision];

                // 返回方位
                case "poision" :
                        return xysb_poision;

                case "env" :
                        return doors3[xysb_poision];

                default:return "error";
        }
}

// 蒙古军总数量
int total_menggu_soldier(string route)
{
        int i, j, total = 0;
        string *key_n_soldier;
        int *route_n_soldier;

        key_n_soldier = keys(n_soldier);

        // 返回襄阳士兵总数
        if (route == "xiangyang")
        {
                return n_xy_sb;
        }

        // 返回蒙古士兵总数
        if (route == "total")
        {
                for (j = 0; j < sizeof(key_n_soldier); j ++ )
                {
                        for (i = 0; i < sizeof(n_soldier[key_n_soldier[j]]); i ++)
                        {
                                total = total + n_soldier[key_n_soldier[j]][i];
                        }
                }

                return total;
        }

        // 某一移动方向上的蒙古军总数量
        if (stringp(route))
        {
                route_n_soldier = n_soldier[route];

                if (sizeof(route_n_soldier))
                {
                        for (i = 0; i < sizeof(route_n_soldier); i ++ )
                        {
                                total = total + route_n_soldier[i];
                        }
                }

                return total;
        }
}

// key = "max" || key = "min"
// 返回n_soldier 中士兵力量最强或最弱的组
// 其中士兵 参数为1、弓兵为2, 哲别为3，骑兵为4
string max_min_n_soldier(string keys)
{
        int i, j, power_w, power_e, power_s, power_n;
        int max_tmp1, max_tmp2, min_tmp1, min_tmp2;
        int max_result, min_result;
        string smax_tmp1, smax_tmp2, smin_tmp1, smin_tmp2;
        string smax_result, smin_result;
        string key_n_soldier;

        if (keys != "max" && keys != "min")return "NULL";

        power_w = 0;
        for (i = 0; i < 4; i ++)
        {
                power_w = power_w + n_soldier["west"][i];
        }
        power_e = 0;
        for (i = 0; i < 4; i ++)
        {
                power_e = power_e + n_soldier["east"][i];
        }
        power_n = 0;
        for (i = 0; i < 4; i ++)
        {
                power_n = power_n + n_soldier["north"][i];
        }
        power_s = 0;
        for (i = 0; i < 4; i ++)
        {
                power_s = power_s + n_soldier["south"][i];
        }

        max_tmp1 = power_w >= power_e ? power_w : power_e;
        smax_tmp1 = power_w >= power_e ? "west" : "east";
        max_tmp2 = power_n >= power_s ? power_n : power_s;
        smax_tmp2 = power_n >= power_s ? "north" : "south";

        min_tmp1 = power_w <= power_e ? power_w : power_e;
        smin_tmp1 = power_w <= power_e ? "west" : "east";
        min_tmp2 = power_n <= power_s ? power_n : power_s;
        smin_tmp2 = power_n <= power_s ? "north" : "south";

        max_result = max_tmp1 >= max_tmp2 ? max_tmp1 : max_tmp2;
        smax_result = max_tmp1 >= max_tmp2 ? smax_tmp1 : smax_tmp2;
        min_result = min_tmp1 <= min_tmp2 ? min_tmp1 : min_tmp2;
        smin_result = min_tmp1 <= min_tmp2 ? smin_tmp1 : smin_tmp2;

        if (keys == "max")
        {
                return smax_result;
        }

        if (keys == "min")
        {
                return smin_result;

        }

}

// 蒙古士兵死亡通告，用于系统判断每组军队数量
// 襄阳士兵通告，用于系统判断襄阳士兵总数量
void soldier_die(string route, int which)
{
        if (route == "xiangyang") // 襄阳士兵死亡
        {
                n_xy_sb -= 1;
                if (n_xy_sb <= 0)n_xy_sb = 0;
                return;
        }

        // route 代表west, east, south, north中的一种， which 代表兵种
        if (route != "west" &&
            route != "north" &&
            route != "south" &&
            route != "east")return;

        // 0 代表骑兵、1代表哲别、2代表弓兵、3代表步兵
        if (which < 0 || which > 3)return;

        // 将ROUTE反一次
        route = re_poision(route);

        n_soldier[route][which] -= 1;



        if (n_soldier[route][which] <= 0)n_soldier[route][which] = 0;

        return;
}

// 判断郭靖是否已经死亡
int is_guojing_die()
{
        return is_guojing_died;
}

// 郭靖死亡
// 郭靖死亡后所有襄阳士兵自动撤退
void guojing_die()
{
        is_guojing_died = 1; // 标志郭靖已死亡
}

// 报名参加襄阳战
void sign_up(string id)
{
        if (! sizeof(p)) p = ({});

        p += ({ id });

        return;
}


// 返回已报名的人数
public int n_sign_up(){return sizeof(p);}

// 返回报名的数组
public string *p_sign_up(){return p;}

// 检查某ID是否报名状态仍然有效
int if_sign_up(string id)
{
        if (! sizeof(p))return 0;

        if (member_array(id, p) != -1)return 1;

        return 0;
}

// 外部调用，玩家死亡后从襄阳保卫站报名中删除
public void player_die(string id)
{
        if (! stringp(id))return;
        if (! if_sign_up(id))return;

        p -= ({ id });

        return;
}

// 检查离线的报名玩家并删除之
void sub_check_player()
{
        int i;
        for (i = 0; i < sizeof(p); i ++ )
        {
                if (! objectp(find_player(p[i])))
                {
                        p -= ({ p[i] });
                        return sub_check_player();
                }
        }

        if (sizeof(p) < 5 && status == WARRING && ! TEST)war_end_player();

}

// 检查离线的报名玩家并删除之
// 调用 sub_check_player()执行
void check_player()
{
        int i;
        remove_call_out("check_player");
        call_out("check_player", 10); // 检查参加襄阳战的玩家

        if (! sizeof(p))return;

        sub_check_player();

        return;
}

// 返回各种状态
// 1=襄阳胜利 | -1=蒙古胜利
// 2=进行中   | 0=结束或未开始
// 3=等待进攻
int now_status(){return status;}

// 设置各种状态
void set_now_status(int flag)
{
        // 如果状态为结束战斗
        if (flag == THEEND)
        {
                status = THEEND;
                call_out("xywar_message", 10, HIG "本次襄阳保卫战已结束，系统将于1分钟内释放资源，襄阳恢复平静。");
                reset_data(); // 初始化所有数据
        }

        status = flag;
}

// 报名标志，1=可以报名  0=不可以报名
int sign_up_status(){return sign_up_status;}

// 设置报名标志
void set_sign_up_status(int flag){sign_up_status = flag;}

// 退兵标志
int dest_status()
{
        if (status == THEEND)
        {
                return 1;
        }

        return 0;
}

// 过滤不接受故事信息的人
int filter_listener(object ob)
{
            // 计划中不接收
        if (ob->query("doing") == "scheme") return 0;
        return 1;
}

// 襄阳战系统通告
void xywar_message(string msg)
{
        string prompt;
        object *listeners;

        prompt = HIY "【襄阳战报】" NOR;
        listeners = filter_array(users(), (: filter_listener :));
        message( "story",  prompt + HIC + msg + "\n" NOR, listeners );
}

void do_attack_msg(string msg)
{
        if (status == THEEND)return;

        xywar_message(msg);
}

// 郭靖通告：过滤没有报名的人
int filter_listener2(object ob)
{
        if (member_array(ob->query("id"), p) == -1)return 0;

        return 1;
}

// 郭靖通告
void guojing_message(string msg)
{
        string prompt;
        object *listeners;

        prompt = HIY "【郭靖】" NOR;
        listeners = filter_array(users(), (: filter_listener2 :));
        message( "story",  prompt + HIR + msg + "\n" NOR, listeners );
}

// 每月1日和15日晚上8点30开始
void check_time()
{
        string *str_bjtime,bjtime1;

        remove_call_out("check_time");
        call_out("check_time", 15);

        // 如果发现战斗开始标志
        if (start_status)return;

        // 1小时内不能重复自动启动
        if (time() - DB_D->query_data("xywar/last_auto_start") < 36000)
                return;

        // 检查是否到了启动时间，如果是则设置开始标志
        // 返回北京时间 (年:月:日:时:分:秒)
        bjtime1 = MEMBER_D->bjtime(time(), 0);
        str_bjtime = explode(bjtime1, ":");

        // 每月1日，或15日20：30分开始
        if (str_bjtime[2] == "1" || str_bjtime[2] == "15")
        {
                if (str_bjtime[3] == "20" && str_bjtime[4] == "30")
                        DB_D->set_data("xywar/start", 1);
        }

        // 检查开始标志，并启动
        if (DB_D->query_data("xywar/start"))
        {
                DB_D->set_data("xywar/start", 0);
                DB_D->set_data("xywar/last_auto_start", time());
                log_file("xywar", "xywar 于 " + ctime(time()) + " 自动启动！\n");
                start_xywar();
        }
}

void create()
{
        seteuid(getuid());
        set("channel_id", "襄阳战斗系统");
        set("no_clean_up", 1);
        CHANNEL_D->do_channel(this_object(), "sys", "系统已经启动。");

        if (! ALLOW_START)return;

        remove_call_out("check_time");
        call_out("check_time", 10); // 检查襄阳战开始时间
        remove_call_out("check_player");
        call_out("check_player", 10); // 检查参加襄阳战的玩家
        remove_call_out("check_combatd");
        call_out("check_combatd", 30); // 战斗战术系统总控函数
}

// 战斗战术系统总控文件，用于控制蒙古军队战术军队调整
void check_combatd()
{
                int total, w, e, s, n;
                int xytotal;
                string max_route;
                string dj_name;

                remove_call_out("check_combatd");
                call_out("check_combatd", 10);

                // 襄阳战结束
                if (status == THEEND)return;

                // 各门人数及总人数
                total = total_menggu_soldier("total");
                xytotal = total_menggu_soldier("xiangyang");
                w = total_menggu_soldier("west");
                e = total_menggu_soldier("east");
                s = total_menggu_soldier("south");
                n = total_menggu_soldier("north");

                // 襄阳士兵死伤过半提示
                if (xytotal < n_xy_sb2 / 2 && ! guojing_moved)
                {
                        xywar_message(HIW "宋军探子：报！！目前我宋军已经死伤过半，情况十分危急。\n" NOR);

                        //
                        if (! is_guojing_die())
                        {
                                xywar_message(HIW "郭靖：好，既然如此，我郭某誓与襄阳共存亡 ……" NOR);
                                xywar_message(HIR "听说郭靖亲自上阵，与蒙古人决一死战。\n" NOR);

                                call_out("xywar_message", 2, HIY "蒙古将领：蒙古勇士们向前冲啊，宋军已经溃不成军了。\n");

                                // 将guojing 移动到蒙古人最多的地方
                                if (objectp(xy_guojing))
                                {
                                        max_route = max_min_n_soldier("max");
                                        xy_guojing->move(doors[max_route]);

                                        // 设置移动方向
                                        xy_guojing->set("route", re_poision(max_route));

                                        // 已经移动标志
                                        guojing_moved = 1;
                                }
                        }
                }

                // 正在战斗中，适时调整战术
                /*
                */
                if (status == WARRING || (status == WAIT_START && total_menggu_soldier("total") < 120))
                {
                        // 1.  蒙古军队数量少于80时派兵增援
                        if (add_mgb_times < ADD_MGB_TIMES &&
                               time() - last_add_mgb_time >= ADD_MGB_WAIT &&
                               (status == WARRING || status == WAIT_START) &&
                               total_menggu_soldier("total") < 120)
                        {
                                last_add_mgb_time = time();
                                call_out("xywar_message", 2, HIW "蒙古探子：报！宋军得江湖人士支持，顽强抵抗，我军目前伤亡惨重！");
                                call_out("xywar_message", 4, HIW "蒙古将领“嗯”了一声：看来，我们应该采取一些行动了，传令放狼烟……");
                                call_out("xywar_message", 5, HIY "襄阳探子：报！蒙古人已放出狼烟，加派援军进攻襄阳！");
                                call_out("combat_add_soldier", 7);

                        }

                        // 2.  蒙古军队进攻3分钟后开始调整战术
                        if (time() - attack_time > 180 &&
                            time() - last_combat_change_time > 90 && // 距离上次战术调整时间为90秒
                            random(5) == 1)
                        {
                                last_combat_change_time = time();

                                switch(random(5))
                                {
                                        // 虚假退兵
                                        case 0:
                                                combat_xjtuibing();
                                                break;
                                        // 声东击西
                                        default :
                                                combat_sdjixi();
                                                break;
                                }
                        }

                        // 蒙古人全灭，则襄阳胜利
                        if (total_menggu_soldier("total") <= 0)
                        {
                                xywar_message(HIG "蒙古军已经全军覆没！");
                                war_win();
                                return;
                        }

                        // 防御30分钟则代表襄阳胜利
                        if (time() - attack_time > 1800)
                        {
                                xywar_message(HIG "郭靖：襄阳城经过众多玩家及将士的努力，已经坚守超过30分钟");
                                xywar_message(HIG "郭靖：蒙古人粮草辎重已经消耗殆尽，只得暂时退兵！");
                                war_win();
                                return;
                        }
                }

                // 正在等待进攻
                if (status == WAIT_START)
                {
                        if (random(3) == 1)
                        {
                                switch(random(10))
                                {
                                        case 0:
                                                xywar_message("郭靖：蒙古人正在调配军队，请保卫襄阳的义士做好相关准备，随时备战。");
                                                xywar_message("黄蓉：各位守城玩家请各自分配好任务，准备随时迎击蒙古军，誓死保卫襄阳。\n");
                                                break;
                                        case 1:
                                                xywar_message("郭靖：蒙古的千夫长在从军前都是一代成名的武学宗师，万万不可轻视。");
                                                xywar_message("郭靖：玩家只要守(guard)住路口，蒙古人便无法通过，但被拦截的蒙古人会主动攻击守住路口的玩家。");
                                                xywar_message("黄蓉：蒙古千夫长不主动攻击经验在2亿以下的玩家，同时经验在2亿以下的玩家即使守(guard)住路口\n"
                                                              "            后，也无法拦截住千夫长。\n");

                                                break;
                                        case 2:
                                                xywar_message("蒙古探子：襄阳城内突然集聚了大量江湖人士，看来他们想死守城池。");
                                                if (tiemuzhen)dj_name = "成吉思汗";
                                                else dj_name = "蒙古将领";
                                                xywar_message(dj_name + "：哼，两军交锋岂同江湖撕斗，一群乌合之众必将死于乱箭之下。\n");
                                                break;
                                        case 3:
                                                xywar_message("黄蓉：参战的玩家在杀死任意蒙古人后都会获得一定的经验和潜能奖励。");
                                                xywar_message("黄蓉：如果襄阳保卫战胜利则所有参战玩家（不包括中途退出的）都将获得丰富的奖励\n");
                                                break;
                                        case 4:
                                                xywar_message("黄蓉：在对抗蒙古人时系统会自动关闭参战玩家的战斗信息，中途切勿打开，以免影响游戏速度。\n");
                                                break;
                                        case 5:
                                                xywar_message("黄蓉：蒙古人诡计多端，在战斗中会随时调整战术，也可能会派兵增援。");
                                                xywar_message("黄蓉：玩家将领请根据双方战斗状况随时做出战略调整，指挥各参战玩家抵抗蒙古人进攻。\n");
                                                break;
                                        case 6:
                                                xywar_message("郭靖：玩家将领可在本次襄阳保卫战中使用一次兵符，使用后可增加120名襄阳守军。");
                                                xywar_message("郭靖：使用兵符的指令是 " HIY "xy add xyb " HIC "。\n");
                                                break;
                                        case 7:
                                                xywar_message("郭靖：一旦玩家与蒙古人对面，蒙古人则会自动叫杀，佩带隐身符则可隐身于蒙古人中，不被主动攻击。\n");
                                                break;
                                        case 8:
                                                if (tiemuzhen)
                                                {
                                                        xywar_message("郭靖：郭某自幼跟随大汗铁木真驰骋大漠，弯弓射雕，不想今日却对战沙场。");
                                                        xywar_message("郭靖：不过国难当头，蒙古人杀掠成性，今日郭某将誓死保卫我大宋江山，死守襄阳。");
                                                        xywar_message("郭靖：参战玩家可选出数名高手偷袭蒙古军营，只要杀死成吉思汗铁木真蒙古人便不攻自破。\n");
                                                        break;
                                                }
                                                xywar_message("郭靖：郭某自幼跟随大汗铁木真驰骋大漠，与蒙古哲别弯弓射雕，不想今日却对战沙场。");
                                                xywar_message("郭靖：不过国难当头，蒙古人杀掠成性，今日郭某将誓死保卫我大宋江山，死守襄阳。");
                                                xywar_message("郭靖：蒙古哲别在蒙古语中为“神射手”，其箭法精准，切忌不可轻视。");
                                                xywar_message("郭靖：如果可能玩家在集中优势兵力解决千夫长后应集中全力将哲别消灭。\n");
                                                break;
                                        case 9:
                                                xywar_message("襄阳城四周已经弥漫着浓烈的硝烟味，城民早已各自收拾细软，随时准备趁乱逃命，场面一片混乱。");
                                                break;
                                        default:
                                                xywar_message(HIW "蒙古军士：三军已集合完毕，粮草辎重、刀枪箭矢已点算完毕，随时可以开战。" NOR);
                                                xywar_message(HIY "襄阳军士：我军已集合完毕，四城门均要道均已有重兵把守，我军誓于蒙古人周旋到底。\n" NOR);

                                                break;
                                }
                        }
                }

                /*
                战术：蒙古军队可在战斗中根据条件改变战术
                1、声东击西
                2、虚假退兵
                3、增派兵力
                */
}

// 襄阳战结束，重置相关数据
void reset_data()
{
            p = ({});                 // 参加襄阳战的玩家物件列表
        status = THEEND;          // 襄阳战状态
        start_status = 0;         // 系统状态 恢复到未开始状态
        sign_up_status = 0;       // 报名标志
            tiemuzhen = 0;            // 本次是否出现铁木真
        n_mg_tq = 0;
        n_mg_zb = 0;
        n_mg_gb = 0;
        n_mg_bb = 0;              // 骑兵、哲别、弓兵、步兵数量
        n_xy_sb = 0;              // 襄阳士兵数量
        is_guojing_died = 0;      // 郭靖是否死亡标志

        add_mgb_times = 0;             // 增援蒙古兵次数
        add_xyb_flag = 0;              // 增援襄阳士兵次数标志
        last_add_mgb_time = 0;         // 上次增援蒙古兵时间
        guojing_moved = 0;             // 郭靖是否已经与蒙古人交战
        xysb_poision = "襄阳城内四周"; // 襄阳守军驻扎地
        player_leader = "";            // 玩家将领的ID
        last_move_xysolder = 0;        // 上次调动襄阳守军的时间
        start_time = 0;                // 襄阳保卫战开始时间
        attack_time = 0;               // 蒙古人开始攻城时间
        who_win = 0;                   // 谁胜利
        xy_msg1 = "----";              // 襄阳增援消息，杨过等
        yb_attack_where = "none";      // 新增蒙古兵攻击方向

}


// 蒙古人开始进攻襄阳
void do_attack()
{
        if (status == THEEND)return;

        xywar_message(HIR "蒙古人开始围攻襄阳城！" NOR);
        attack_time = time();
        status = WARRING;
}

// 播报蒙古军战报
// 大约每分钟播放一次，直到开始攻城
void do_combatd_message(int i)
{
        string dj_name;
        if (tiemuzhen)
        {
                dj_name = "成吉思汗";
        }
        else
                dj_name = "蒙古大将";

        if (status == THEEND)return;

        switch(i)
        {
                case 1:
                        xywar_message(dj_name + "：传我号令，全军在此扎营，五分钟后全军开始围攻襄阳城！");
                        break;
                // 报告蒙古人总军力
                case 2:
                        xywar_message("宋军探子：本次蒙古军队总数量约为：" + HIY + sprintf("%d", total_menggu_soldier("total"))  + HIC "　人！并分四"
                                  "路，分别驻扎在朱雀门，白虎门，青龙门及玄武门外。");
                        if (tiemuzhen)
                        {
                                xywar_message(HIR "宋军探子：本次蒙古军由成吉思汗铁木真亲自率领。" NOR);
                        }
                        break;
                //
                case 3:
                        xywar_message("宋军探子：襄阳城内宋军已调配完毕，随时准备迎击蒙古军。");
                        break;
                //
                case 4:
                        xywar_message("郭靖：请报名参加襄阳保卫战的玩家自行组织，守住四大门路口，防止蒙古人攻入襄阳中央广场。");
                        break;
                //
                case 5:
                        xywar_message("宋军探子：蒙古军队已开始进行调动，随时会有所行动。");
                        break;
                case 6:
                        xywar_message(dj_name + "：传我号令，全军于３０秒后开始进攻襄阳城。");
                        xywar_message(HIR "蒙古人于30秒后开始进攻襄阳城，请注意守好相关路口。" NOR);
                        xywar_message(HIY "战斗中请使用指令 " HIR "xy" HIY " 随时查看战况详情。" NOR);
                        if (tiemuzhen)
                        {
                                xywar_message(HIG "胜利条件：1、杀死成吉思汗\t       " HIM "失败条件：1、蒙古人占领襄阳中央广场\n" HIG
                                              "\t              2、防守蒙古人攻击30分钟\t         " HIM "2、所有参加襄阳保卫战的玩家剩余不到五名\n" HIG
                                              "\t              3、全部歼灭蒙古人\n"
                                              HIG "\t              4、蒙古人退兵\n" NOR);
                        }
                        else
                        {
                                xywar_message(HIG "胜利条件：1、防守蒙古人攻击30分钟\t       " HIM "失败条件：1、蒙古人占领襄阳中央广场\n" HIG
                                              "\t              2、全部歼灭蒙古人。\t       " HIM "          2、所有参加襄阳保卫战的玩家剩余不到五名\n"
                                              HIG "\t              3、蒙古人退兵\n" NOR);
                        }

                        // 30秒后蒙古军开始进攻
                        remove_call_out("do_attack");
                        call_out("do_attack", 30);

                        call_out("do_attack_msg", 22, HIM "城外发出漫天战鼓之声，蒙古军士蠢蠢欲动。");
                        call_out("do_attack_msg", 26, HIM "一声犀利地号角声响起，万山雷动，卷起漫天狂沙，蒙古人军队已开始调动。");

                        return;
                        break;

        }
        i += 1;
        remove_call_out("do_combatd_message");
        if (TEST)call_out("do_combatd_message", 2, i);
        else call_out("do_combatd_message", 50 + random(11), i);

        return;
}

// 停止报名，检查报名是否达到人数要求
void check_sign_up()
{
        string dj_name; // 大将的姓名
        object ob;

        // 停止报名
        sign_up_status = 0;

        xywar_message(HIY "郭靖：各位江湖义士，很感谢大家的支持，现在停止报名，并公布我军统计的报名人数！" NOR);
        xywar_message(HIW "襄阳副将：本次总共有 " HIY + chinese_number(sizeof(p)) + HIW " 位玩家报名参加襄阳保卫战！" NOR);

        // 检查离线玩家，从报名中删除之
        sub_check_player();

        // 参加人数过少，结束襄阳战，蒙古人退兵
        if (sizeof(p) < 20 && ! TEST)
        {
                status = 0; // 襄阳战结束标志

                xywar_message("各位江湖义士，本次襄阳保卫战报名人数不足20人，既然天意如此，也罢！\n");

                if (tiemuzhen)dj_name = "成吉思汗";
                else dj_name = "大将军";

                switch(random(5))
                {
                         case 1:
                                 call_out("xywar_message", 4, "蒙古副将：报告" + dj_name + "，我军部分士兵突然染上瘟疫，目前已经无法战斗。");
                                 call_out("xywar_message", 6, dj_name + "：啊？竟有此事，立刻通知全军立即撤退 ……");
                                 break;
                         case 2:
                                 call_out("xywar_message", 4, "蒙古探子：报告" + dj_name + "，襄阳城内居然毫无动静，也不见防守的军士，恐有诈。");
                                 call_out("xywar_message", 6, dj_name + "：恩，有道理，我也正觉得纳闷。马上通知全军迅速撤兵，然后从长计议！");
                                 break;
                         default:
                                 call_out("xywar_message", 4, "蒙古百夫长：报告" + dj_name + "，我军运粮车无故自燃，粮草辎重已损失殆尽。");
                                 call_out("xywar_message", 6, dj_name + "哼，坏我大事，来啊，拖出去砍了！立即通知全军火速撤退，以免宋军乘机偷袭！");
                                 break;
                }

                call_out("xywar_message", 8, "宋兵：报~~！蒙古人突然下令撤军，所有来袭军队已全部撤回！");

                call_out("xywar_over", 10);
                return;
        }

        // 随机选择一个
        if (sizeof(p))player_leader = p[random(sizeof(p))];

        if (sizeof(player_leader))ob = find_player(player_leader);

        if (objectp(ob))
        {
                // 选择玩家将领
                xywar_message(HIG "本次襄阳保卫战由" + HIY + ob->name() + "(" + ob->query("id") + ")" HIG
                                 "担任襄阳守军将领，可以根据战况调动襄阳守军(xy xmove 方向)。\n");
        }

        xywar_message("宋兵：报~~！蒙古军将会在五分钟后围攻襄阳，请做好相关准备，死守(guard)蒙古军必经之路。");

        // 10秒钟后开始每搁一分钟播报蒙古军队情况
        remove_call_out("do_combatd_message");
        call_out("do_combatd_message", 10, 1);

        return;
}

// 分配军队数量
int allot_soldier()
{
        int i, k;
        string *key_n_soldier;

        // 军队数量
        n_mg_tq = 40 + random(10);
        //n_mg_zb = 40 + random(10);
        n_mg_zb = 60 + random(20);
        //n_mg_gb = 60 + random(20);
        n_mg_gb = 120 + random(40);
        //n_mg_bb = 60 + random(20);
        n_mg_bb = 120 + random(40);
        n_xy_sb = 80 + random(20);

            // 1/5出现铁木真
        if (random(5) == 1)tiemuzhen = 1;

        // 出现铁木真兵力增加20%
        if (tiemuzhen)
        {
                n_mg_tq = n_mg_tq + n_mg_tq / 5;
                n_mg_zb = n_mg_zb + n_mg_zb / 5;
                n_mg_gb = n_mg_gb + n_mg_gb / 5;
                n_mg_bb = n_mg_bb + n_mg_bb / 5;
        }

        // 随机选择一个门士兵较多
        key_n_soldier = keys(n_soldier);
        i = random(sizeof(key_n_soldier));

        // 该方向上多MORE_SOLDIER名士兵
        more_soldier_poision = key_n_soldier[i];

            // ({ 铁骑、哲别、弓兵、 步兵  })
            // 平均分配到四门
        for (k = 0; k < sizeof(key_n_soldier); k ++ )
        {
                n_soldier[key_n_soldier[k]] = ({ n_mg_tq / 4,
                                                 n_mg_zb / 4,
                                                 n_mg_gb / 4,
                                                 n_mg_bb / 4,
                                               });
        }

            // ({ 铁骑、哲别、弓兵、 步兵  })
            // 随机一个门士兵较多
        n_soldier[more_soldier_poision] = ({ n_mg_tq / 4 + MORE_SOLDIER,
                                             n_mg_zb / 4 + MORE_SOLDIER,
                                             n_mg_gb / 4 + MORE_SOLDIER,
                                             n_mg_bb / 4 + MORE_SOLDIER,
                                       });

        // 记录最初蒙古军总数
        n_mg_sb2 = total_menggu_soldier("total");
        n_xy_sb2 = total_menggu_soldier("xiangyang");

        return 1;
}

// 初始化军队
int init_soldier()
{
        /**
        1、初始化郭靖
        2、设置襄阳战等待标志
        3、产生蒙古军队物件并移动到各自的位置
        4、产生襄阳士兵并分配到四个门
        **/
        object ob, mg_dj;// 蒙古大将
        string *key_doors;
        string re_route; // 方向反向
        //int n_mg_tq, n_mg_zb, n_mg_bb, n_mg_gb, n_xy_sb;
        int i, n;

        // 设置等待攻击标志
        status = WAIT_START;

        xy_guojing = new(XYNPC + "guo");
        if (tiemuzhen)mg_dj = new(XYNPC + "tiemuzhen");
        else mg_dj = new(XYNPC + "mgdajiang");

        // 根据事先分配的数量进行各种兵种分配

        // 8个千夫长
        for (i = 0; i < 8 ; i ++)
        {
                ob = new(XYNPC + "mgqianfuzhang");

                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                // 分配到四大门

                // 东门
                if (i < 2)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南门
                if (i >= 2 && i < 4)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西门
                if (i >= 4 && i < 6)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北门
                if (i >= 6)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        // 12个百夫长
        for (i = 0; i < 12 ; i ++)
        {
                ob = new(XYNPC + "mgbaifuzhang");

                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                // 分配到四大门

                // 东门
                if (i < 3)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南门
                if (i >= 3 && i < 6)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西门
                if (i >= 6 && i < 9)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北门
                if (i >= 9)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }
        // 4个副将
        for (i = 0; i < 4; i ++)
        {
                ob = new(XYNPC + "mgfujiang");

                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                // 分配到四大门

                // 东门
                if (i == 0)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南门
                if (i == 1)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西门
                if (i == 2)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北门
                if (i == 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        n = n_mg_tq / 4;

        // n_mg_tq个铁骑兵
        for (i = 0; i < n_mg_tq ; i ++)
        {
                ob = new(XYNPC + "mgqibing");

                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                // 分配到四大门

                // 东门
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北门
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        n = n_mg_zb / 4;

        // n_mg_zb个哲别
        for (i = 0; i < n_mg_zb ; i ++)
        {
                ob = new(XYNPC + "mgzhebie");

                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                // 分配到四大门

                // 东门
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北门
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        n = n_mg_gb / 4;

        // n_mg_gb个弓兵
        for (i = 0; i < n_mg_gb ; i ++)
        {
                ob = new(XYNPC + "mggongbing");

                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                // 分配到四大门

                // 东门
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北门
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        n = n_mg_bb / 4;

        // n_mg_bb个步兵
        for (i = 0; i < n_mg_bb ; i ++)
        {
                ob = new(XYNPC + "mgbubing");

                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                // 分配到四大门

                // 东门
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors["east"]);
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors["south"]);
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors["west"]);
                }
                // 北门
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors["north"]);
                }
        }

        // 在more_soldier_poision门多增加MORE_SOLDIER名士兵
        re_route = re_poision(more_soldier_poision);

        for (i = 0; i < MORE_SOLDIER ; i ++)
        {
                ob = new(XYNPC + "mgbubing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                ob = new(XYNPC + "mggongbing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                ob = new(XYNPC + "mgqibing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                ob = new(XYNPC + "mgzhebie");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);
        }

        // 记录，有时候会出现没有襄阳士兵
        if (n_xy_sb <= 1)log_file("xiangyang_xysb", "ok at " + ctime(time()) + "\n");

        n = n_xy_sb / 4;

        // n_xy_sb个襄阳士兵
        for (i = 0; i < n_xy_sb ; i ++)
        {
                ob = new(XYNPC + "xyshibing");

                // 分配到四大门
                // 东门
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors2["east"]);
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors2["south"]);
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors2["west"]);
                }
                // 北门
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors2["north"]);
                }
        }

        key_doors = keys(doors);

        // 郭靖移动到中央广场
        xy_guojing->move("/d/xiangyang/guangchang");


        // 移动NPC到军营前清理军营其他PLAYER
        clear_junying();

        // 蒙古大将移动到军营
        if (tiemuzhen)
        {
                mg_dj = new(XYNPC + "tiemuzhen");
                mg_dj->move("/d/xiangyang/junying3");
                // 设置本次襄阳保卫战的序列号
                mg_dj->set("ran_num", RAN_NUM);
        }
        else
        {
                mg_dj = new(XYNPC + "mgdajiang");
                mg_dj->move("/d/xiangyang/junying3");
                // 设置本次襄阳保卫战的序列号
                mg_dj->set("ran_num", RAN_NUM);
        }

        // 两名千夫长保护大将
        for (i = 0; i < 2; i ++)
        {
                ob = new(XYNPC + "mgqianfuzhang");
                ob->move(environment(mg_dj));
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                if (tiemuzhen)
                        ob->force_me("guard tie muzhen");
                else
                        ob->force_me("guard menggu dajiang");
        }

        // 如果有铁木真则增加
        // 8名千夫长，4名副将，20名铁骑、20名哲别保护
        if (tiemuzhen)
        {
                for (i = 0; i < 8; i ++ )
                {
                        ob = new(XYNPC + "mgqianfuzhang");
                        ob->move(environment(mg_dj));
                        ob->force_me("guard tie muzhen");
                        // 设置本次襄阳保卫战的序列号
                        ob->set("ran_num", RAN_NUM);
                }

                for (i = 0; i < 4; i ++ )
                {
                        ob = new(XYNPC + "mgfujiang");
                        ob->move(environment(mg_dj));
                        ob->force_me("guard tie muzhen");
                        // 设置本次襄阳保卫战的序列号
                        ob->set("ran_num", RAN_NUM);
                }

                // 要设置不计算士兵数量标志
                for (i = 0; i < 20; i ++ )
                {
                        ob = new(XYNPC + "mgqibing");
                        ob->set("no_total", 1);
                        ob->move(environment(mg_dj));
                        ob->force_me("guard tie muzhen");
                        // 设置本次襄阳保卫战的序列号
                        ob->set("ran_num", RAN_NUM);
                }

                for (i = 0; i < 20; i ++ )
                {
                        ob = new(XYNPC + "mgzhebie");
                        ob->set("no_total", 1);
                        ob->move(environment(mg_dj));
                        ob->force_me("guard tie muzhen");
                        // 设置本次襄阳保卫战的序列号
                        ob->set("ran_num", RAN_NUM);
                }
        }

        // 移动10名步，10名弓手兵到军营外/d/xiangyang/junying1
        // 守护方向north
        for (i = 0; i < 10; i ++)
        {
                ob = new(XYNPC + "mgbubing");
                ob->set("no_total", 1);
                ob->move("/d/xiangyang/junying1");
                ob->force_me("guard north");
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                ob = new(XYNPC + "mggongbing");
                ob->set("no_total", 1);
                ob->move("/d/xiangyang/junying1");
                ob->force_me("guard north");
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);
        }

        // 移动6名千夫长，40名哲别，40名铁骑守护军营/d/xiangyang/junying2
        for (i = 0; i < 6; i ++)
        {
                ob = new(XYNPC + "mgqianfuzhang");
                ob->move("/d/xiangyang/junying2");
                ob->force_me("guard north");
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);
        }
        for (i = 0; i < 40; i ++)
        {
                ob = new(XYNPC + "mgzhebie");
                ob->set("no_total", 1);
                ob->move("/d/xiangyang/junying2");
                ob->force_me("guard north");
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);

                ob = new(XYNPC + "mgqibing");
                ob->set("no_total", 1);
                ob->move("/d/xiangyang/junying2");
                ob->force_me("guard north");
                // 设置本次襄阳保卫战的序列号
                ob->set("ran_num", RAN_NUM);
        }

        call_out("xywar_message", 2, "蒙古军队已经抵达襄阳城外安营扎寨，现在全军正侯命待发！");

        call_out("xywar_message", 15, "宋兵探子：此次蒙古军队人数大约为： " HIY +
                                      sprintf("%d", total_menggu_soldier("total")) + HIC " 人。");

        // 郭靖通知玩家进行报名
        call_out("xywar_message", 5, HIY "郭靖：各路江湖豪杰，武林同道，现今蒙古人即将围攻襄阳，情况危机，"
                                         "如愿保卫襄阳出一份力，请\n            速到" HIM "襄阳中央广场" HIY "进行报名吧！" NOR);

        // 设置可报名标志
        sign_up_status = 1;

            // 5分钟后停止报名，并检查报名人数是否达到要求
        remove_call_out("check_sign_up");
        if (TEST)call_out("check_sign_up", 10);
        else call_out("check_sign_up", 300);

        return;
}
// 襄阳援军达到后的动作
void add_xy_soldier_action()
{
        call_out("xywar_message", 1, HIY "蒙古探子：报！襄阳援兵已经部署完毕，分散于四城门抵抗我军。" NOR);

        if (random(2) == 1)
                call_out("xywar_message", 3, HIY "蒙古将领：哼！看来他们是在做最后的垂死挣扎，传令加强进攻，尽快拿下城池。" NOR);
        else
                call_out("xywar_message", 3, HIY "蒙古将领：传令全军将士加强攻势，万万不可轻敌，这次务必要顺利拿下襄阳城" NOR);
}

// 增加襄阳士兵
void add_xy_soldier()
{
        object ob;
        string re_route; // 方向反向
        int i, n, k;
        string *key_n_soldier;

        if (now_status() != WARRING && now_status() != WAIT_START && ! TEST)return;

        n_xy_sb = ADD_XY_SOLDIER;
        n = ADD_XY_SOLDIER / 4;

        // n_xy_sb个襄阳士兵
        for (i = 0; i < n_xy_sb ; i ++)
        {
                ob = new(XYNPC + "xyshibing");

                // 分配到四大门
                // 东门
                if (i < n)
                {
                        ob->set("route", "west");
                        ob->move(doors3["east"]);
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        ob->set("route", "north");
                        ob->move(doors3["south"]);
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        ob->set("route", "east");
                        ob->move(doors3["west"]);
                }
                // 北门
                if (i >= n * 3)
                {
                        ob->set("route", "south");
                        ob->move(doors3["north"]);
                }
        }


        // 修改襄阳军数量记录表
        n_xy_sb = n_xy_sb + ADD_XY_SOLDIER;

        xywar_message(HIY "襄阳援兵已抵达襄阳城，并平均分散在四门抵御蒙古人。");

        call_out("add_xy_soldier_action", 2);

        return;
}

// 外部调用：增加襄阳士兵，起前端调用，增加延迟效果作用
void add_xy_soldier_ext(object me)
{
        // 检查是否可调用
            if (now_status() != WARRING && now_status() != WAIT_START)
            {
                    write("战斗还没有开始呢。\n");
                    return;
            }

        // 调用后增加调用标志
        add_xyb_flag = 1;

        call_out("xywar_message", 2, HIR + me->name() + "使用兵符，增派襄阳守军。" NOR);
        call_out("xywar_message", 4, HIR + "襄阳援军正在分配和调动，援军抵达后将平均分散在四门抵抗蒙古军。" NOR);
        call_out("xywar_message", 6, HIR + "襄阳援军即将抵达襄阳城，请提前做好相关战术调动。" NOR);
        call_out("add_xy_soldier", 12);
}

// 蒙古人派兵增援
// 需要在设置方位的时候检查 yb_attack_where 变量，如果不为"none"则需要单独设置
// 目的是将援军火力在某一方向上集中，便于攻城
void add_soldier()
{
        object ob;
        string re_route; // 方向反向
        int i, n, k;
        string *key_n_soldier;

        // 根据事先分配的数量进行各种兵种分配

        // 8个千夫长
        for (i = 0; i < 8 ; i ++)
        {
                ob = new(XYNPC + "mgqianfuzhang");
                // 分配到四大门

                // 东门
                if (i < 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南门
                if (i >= 2 && i < 4)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西门
                if (i >= 4 && i < 6)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北门
                if (i >= 6)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        // 12个百夫长
        for (i = 0; i < 12 ; i ++)
        {
                ob = new(XYNPC + "mgbaifuzhang");
                // 分配到四大门

                // 东门
                if (i < 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南门
                if (i >= 3 && i < 6)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西门
                if (i >= 6 && i < 9)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北门
                if (i >= 9)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }
        // 4个副将
        for (i = 0; i < 4; i ++)
        {
                ob = new(XYNPC + "mgfujiang");
                // 分配到四大门

                // 东门
                if (i == 0)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南门
                if (i == 1)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西门
                if (i == 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北门
                if (i == 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        n = n_mg_tq / 4;

        // n_mg_tq个铁骑兵
        for (i = 0; i < n_mg_tq ; i ++)
        {
                ob = new(XYNPC + "mgqibing");

                // 分配到四大门

                // 东门
                if (i < n)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北门
                if (i >= n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        n = n_mg_zb / 4;

        // n_mg_zb个哲别
        for (i = 0; i < n_mg_zb ; i ++)
        {
                ob = new(XYNPC + "mgzhebie");

                // 分配到四大门

                // 东门
                if (i < n)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北门
                if (i >= n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        n = n_mg_gb / 4;

        // n_mg_gb个弓兵
        for (i = 0; i < n_mg_gb ; i ++)
        {
                ob = new(XYNPC + "mggongbing");

                // 分配到四大门

                // 东门
                if (i < n)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北门
                if (i >= n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        }
                }
        }

        n = n_mg_bb / 4;

        // n_mg_bb个步兵
        for (i = 0; i < n_mg_bb ; i ++)
        {
                ob = new(XYNPC + "mgbubing");

                // 分配到四大门

                // 东门
                if (i < n)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "west");
                                ob->move(doors["east"]);
                        }
                }

                // 南门
                if (i >= n && i < n * 2)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "north");
                                ob->move(doors["south"]);
                        }
                }

                // 西门
                if (i >= n * 2 && i < n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "east");
                                ob->move(doors["west"]);
                        }
                }
                // 北门
                if (i >= n * 3)
                {
                        if (yb_attack_where != "none")
                        {
                                ob->set("route", re_poision(yb_attack_where));
                                ob->move(doors[yb_attack_where]);
                        }
                        else
                        {
                                ob->set("route", "south");
                                ob->move(doors["north"]);
                        };
                }
        }

        // 在more_soldier_poision门多增加MORE_SOLDIER名士兵
        re_route = re_poision(more_soldier_poision);

        for (i = 0; i < MORE_SOLDIER ; i ++)
        {
                ob = new(XYNPC + "mgbubing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);

                ob = new(XYNPC + "mggongbing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);

                ob = new(XYNPC + "mgqibing");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);

                ob = new(XYNPC + "mgzhebie");
                ob->set("route", re_route);
                ob->move(doors[more_soldier_poision]);
        }

        // 修改蒙古军数量记录表
        key_n_soldier = keys(n_soldier);

        for (k = 0; k < sizeof(key_n_soldier); k ++ )
        {
                n_soldier[key_n_soldier[k]] = ({ n_soldier[key_n_soldier[k]][0] + n_mg_tq / 4,
                                                 n_soldier[key_n_soldier[k]][1] + n_mg_zb / 4,
                                                 n_soldier[key_n_soldier[k]][2] + n_mg_gb / 4,
                                                 n_soldier[key_n_soldier[k]][3] + n_mg_bb / 4,
                                               });
        }

            // ({ 铁骑、哲别、弓兵、 步兵  })
            // 随机一个门士兵较多
        n_soldier[more_soldier_poision] = ({
                                             n_soldier[more_soldier_poision][0] + MORE_SOLDIER,
                                             n_soldier[more_soldier_poision][1] + MORE_SOLDIER,
                                             n_soldier[more_soldier_poision][2] + MORE_SOLDIER,
                                             n_soldier[more_soldier_poision][3] + MORE_SOLDIER,
                                          });

        xywar_message(HIR "蒙古人增援部队已抵达襄阳，并准备开始攻城。");

        // 散布虚假消息
        if (yb_attack_where != "none")
        {
                string string_ran_doors = random_doors_name();

                xywar_message(HIY "蒙古大将：蒙古援军听令，所有分队朝着" + HIR + string_ran_doors +
                              HIY "方向进攻，不得有误。" NOR);
                xywar_message(NOR + YEL "顷刻间，离" + string_ran_doors + NOR + YEL "不远处，尘土飞扬，"
                              "似乎聚集了大量军队。" NOR);
        }

        return;
}

// 江湖人士支援
void support_npc()
{
        object ob1, ob2, ob3, ob4;
        string guard_door,guard_door_name;
        string *sp;
        string pos;

        if (random(10) > 3 && ! TEST)return;

        switch(random(2))
        {
                // 杨过和小龙女
                case 0:
                        call_out("xywar_message", 2, HIW "杨过：郭伯伯，现今襄阳有难，诛杀蒙古鞑子怎能不算过儿一份！" NOR);
                        call_out("xywar_message", 5, HIW "小龙女：过儿，你到哪儿我就跟你到哪儿 ……" NOR);
                        call_out("xywar_message", 8, HIY "郭靖大笑：好好好！男儿以保家卫国为己任，有过儿你和龙姑娘在，我就放心了！" NOR);
                        // 随机选择一个门守护
                        sp = keys(doors2);
                        pos = sp[random(sizeof(sp))];
                        guard_door = doors2[pos];
                        guard_door_name = doors2_name[pos];
                        call_out("xywar_message", 12, HIW "杨过：我和龙儿也是路过此地，听说蒙古人将要围攻襄阳城，所以便来看看。" NOR);
                        call_out("xywar_message", 15, HIW "杨过：我和龙儿决定了要助郭伯伯一臂之力，保卫襄阳城。" NOR);
                        call_out("xywar_message", 18, HIW "小龙女望了郭靖一眼点了点头。" NOR);
                        call_out("xywar_message", 20, HIY "郭靖激动地说到：好，过儿。那你们就守护" + HIR + guard_door_name + HIY "吧！" NOR);
                        call_out("xywar_message", 22, HIW "言毕，杨过和小龙女直奔" + guard_door_name + "。" NOR);

                        ob1 = new(YANGGUO);
                        ob2 = new(LONGNV);

                        ob1->move(guard_door);
                        ob1->force_me("guard " + re_poision(pos));
                        ob2->move(guard_door);
                        ob2->force_me("guard " + ob1->query("id")); // 小龙女只保护杨过
                        ob1->set("mate", ob2);
                        ob2->set("mate", ob1);

                        xy_msg1 = "杨过和小龙女前来支援，守护" + HIR + guard_door_name;
                        break;

                // 东邪等
                case 1:
                        call_out("xywar_message", 2, HIW "黄药师：哼！蒙古鞑子竟然如此嚣张，我黄老邪就偏要跟你们会会！" NOR);
                        call_out("xywar_message", 6, HIY "欧阳锋：哈哈哈！既然黄老邪有这个雅兴，那我西毒欧阳锋怎能不凑凑热闹，哈哈哈！" NOR);
                        call_out("xywar_message", 10, HIM "一灯大师双手合十道：可怜我天下苍生又将置身火海，生灵涂炭，老衲岂能坐视不理！" NOR);
                        call_out("xywar_message", 14, HIG "洪七公：哈哈，这么热闹？我老叫花子可不能错过……" NOR);
                        call_out("xywar_message", 18, HIC "郭靖一脸兴奋：好好好！襄阳有救了！" NOR);
                        call_out("xywar_message", 20, HIR "听说东邪、西毒、南帝、北丐四大宗师加入到襄阳保卫战当中，共同抗击蒙古人。" NOR);

                        ob1 = new(DONGXIE);
                        ob2 = new(XIDU);
                        ob3 = new(NANDI);
                        ob4 = new(BEIGAI);
                        ob1->move(doors2["east"]);
                        ob1->force_me("guard " + "west");
                        ob2->move(doors2["west"]);
                        ob2->force_me("guard " + "east");
                        ob3->move(doors2["south"]);
                        ob3->force_me("guard " + "north");
                        ob4->move(doors2["north"]);
                        ob4->force_me("guard " + "south");

                        xy_msg1 = "东邪、西毒、南帝、北丐四大高手前来增援，分别守护四门。";

                        break;

                default:
                        return;
        }
}

void start_story(int i)
{
        string *story = ({
                "宋朝末年，朝廷昏庸腐败，蒙古人大举伐宋，天下生灵涂炭，民不聊生 ……",
                "襄阳城乃宋朝战略要地，连年来为夺取襄阳，蒙古人起用重兵围攻 ……",
                "但是，郭靖黄蓉夫妇长年来带领襄阳兵士，死守城池，顽强抵抗，令蒙古人久攻不下。",
                "蒙古军营 ……",
                "成吉思汗：襄阳不取，难以成就我蒙古大业，看来需要加派兵力强攻襄阳城！",
                "成吉思汗：传我号令，加派兵力，准备强攻襄阳，此次一定要将襄阳城拿下。",
                HIR "提示：蒙古成吉思汗派出重兵进攻襄阳！" NOR,
                "襄阳城内。"
                "宋兵：报！，据前方探子回报，蒙古人已派兵直逼襄阳！！！",
                "郭靖：哎，蒙古人久攻襄阳不下，这次一定又加重兵力，欲强取我襄阳城。",
                "郭靖顿了顿对宋兵吩咐道：传令襄阳所有军士加强戒备，等待号令！",
                "宋兵应了一声转身出去。",
                "郭靖长叹道：这次蒙古人大举进攻襄阳，不知道又要有多少无辜的人牺牲，哎...",
                "郭靖顿了顿对坐在一旁的黄蓉说道：这次蒙古人来势汹汹，对襄阳志在必得，以目前襄阳城的兵力恐怕坚守不了多久，\n"
                "            不知蓉儿你有什么好办法可以帮助渡过这一次危难，保住襄阳城！",
                "黄蓉站起在房中走了一圈对郭靖说道：以目前的形势看，敌强我弱，如果光靠襄阳城目前这点兵力恐怕 ……",
                "黄蓉顿了顿又道：不如以靖哥哥你的大名，招募天下英雄豪杰来此共同作战，或可保住襄阳城。",
                "郭靖猛然间手一拍桌子将正在思索的黄蓉吓了一大跳：好，就这么决定了，这次无论如何都要守住襄阳城。",
                "黄蓉：@@",
                "此时，一位宋兵急匆匆地跑了进来道：郭将军，据探子回报，蒙古军已逼近襄阳，大约五分钟后可抵达城外！",
                "郭靖正色道：传令襄阳全体军士，振作精神，随时准备和蒙古人开战。",
                "宋军应了一声，转身跑出去。",
                "郭靖和黄蓉低声交谈了几句后也跟着出去，直奔军营 …… 大战一触即发！",
                HIR "提示：蒙古军队将于五分钟后抵达襄阳城外，请正在任务的玩家停止任务，以免无辜受害！！！" NOR,
        });



        // 五分钟后
        // 二分钟后
        // 随机判断是否江湖人士参与
        if (i >= sizeof(story))
        {
                remove_call_out("init_soldier");
                if (TEST)call_out("init_soldier", 5);
                else call_out("init_soldier", 300); // 初始化必要数据

                // 江湖人士资援襄阳
                remove_call_out("support_npc");
                if (TEST)call_out("support_npc", 2);
                else call_out("support_npc", 120);

                return;
        }

        xywar_message(story[i]);
        i += 1;

        remove_call_out("start_story");
        call_out("start_story", 4, i);
        return;
}

// 开始襄阳战
void start_xywar()
{
        /*
        1、分配军队数量，紧根着开始故事情节叙述
        2、1、完成五分钟后初始化-->init_soldier()
        3、正式启动战斗
        */

        start_status = 1;    // 设置情节开始以免系统重复调用
        start_time = time();  // 设置开始时间

        RAN_NUM = 100 + random(900); // 产生本次襄阳保卫战序列号，共三位数

        allot_soldier(); // 分配军队数量

        // 开始叙述故事
        start_story(0);

}

// 返回本次玩家将领
// 如果其退出战斗则返回 “无“
string leader_player()
{
        if (! if_sign_up(player_leader))return "无";

        return player_leader;
}

// 玩家可控制襄阳守军
// 1、查询目前守军守卫地点
// 2、设置守军集合兵力守卫地点
// 如果襄阳士兵死完则无法再显示
// 蒙古军派遣援军后1分钟内无法查询

// 查询守军及蒙古军情况
void show_soldier(object me)
{
        int total, xytotal, w, e, s, n;
        string msg;

        total = total_menggu_soldier("total");
        xytotal = total_menggu_soldier("xiangyang");
        w = total_menggu_soldier("west");
        e = total_menggu_soldier("east");
        s = total_menggu_soldier("south");
        n = total_menggu_soldier("north");

        msg =  HIR "\n根据探子的消息，带来以下襄阳战报：\n" NOR;
        msg += HIC "--------------------------------------------------------------------\n" NOR;
        if (time() - last_move_xysolder < 60)
        {
                msg += HIG "蒙古军刚增派了大量援军，目前准确人数正在刺探当中 ……\n" NOR;
        }
        else
        {
                msg += HIG "蒙古军总数：" HIR + sprintf("%d", total) + HIG "人，其中："
                       "青龙门" HIR + sprintf("%d", e) + HIG "人，朱雀门" HIR + sprintf("%d", s) + HIG "人，"
                       "白虎门" HIR + sprintf("%d", w) + HIG "人，玄武门" HIR + sprintf("%d", n) + HIG "人。\n" NOR;
        }

        msg += HIW "襄阳守军总人数: " HIR + sprintf("%d", xytotal) + HIW "人，主要集中在" HIR +
               xy_soldier_poision("name") + "(" + xy_soldier_poision("poision") + HIW ")。\n" NOR;
        msg += HIC "--------------------------------------------------------------------\n" NOR;

        tell_object(me, msg);

        return;
}


// 调动襄阳守军
// 权限在/cmds/usr/xy.c 里做判断
void move_xysoldier(object me, string p)
{
        int xytotal;
        string msg, dj_name;

        if (now_status() != WARRING && now_status() != WAIT_START)
        {
                write("襄阳保卫战还没有开始，你无法调动襄阳守军。\n");
                return;
        }

        // 上次调动时间间隔至少为MOVE_WAIT秒
        if (time() - last_move_xysolder < MOVE_WAIT)
        {
                write("距离上次调动襄阳守军时间不足60秒，士兵疲惫，无法连续调动。\n");
                return;
        }

        xytotal = total_menggu_soldier("xiangyang");

        if (xytotal < 5)
        {
                write("目前襄阳守军数量太少，无法进行调动。\n");
                return;
        }

        if (p != "west" && p != "east" && p != "north" && p != "south")
        {
                write("你要将襄阳守军往哪个方向调动？(west|north|east|south)\n");
                return;
        }

        // 设置襄阳守军新的防守方向
        xysb_poision = p;

        // 设置调动时间
        last_move_xysolder = time();

        write("你已经下令调动襄阳守军，襄阳守军正赶往" + HIY + xy_soldier_poision("name") + NOR "地点抵御蒙古人。\n" NOR);

        xywar_message(HIG + me->name() + "正在调动襄阳守军，襄阳守军已经赶往" + HIY + xy_soldier_poision("name") + HIG "地点抵御蒙古人。\n" NOR);

        if (tiemuzhen)dj_name = "成吉思汗";
        else dj_name = "蒙古大将";

        switch(random(5))
        {
                case 0:
                        msg = "哼，此次襄阳城至在必得，这只是宋军在做垂死的抵抗。";
                        break;
                case 1:
                        msg = "哈哈哈，雕虫小技，不过是以卵击石，螳臂当车而已。";
                        break;
                case 2:
                        msg = "咦？次此宋军将领是何许人也？竟然懂得如此用兵，看来中原人才辈出，我等切不可轻敌。";
                        break;

                default:
                        msg = "哼，我蒙古勇士以一敌十，尔等老弱残兵岂能与我蒙古人的争锋。";
                        break;
        }

        msg = HIM + dj_name + "：" + msg + NOR;

        xywar_message(msg);

        return;
}


// 调用蒙古军战术
// 增加援军
void combat_add_soldier()
{

            // 最多增加ADD_MGB_TIMES次
            if (add_mgb_times >= ADD_MGB_TIMES)
            {
                    write("增援次数已达极限。\n");
                    return;
            }

            if (now_status() != WARRING && now_status() != WAIT_START)
            {
                    write("战斗还没有开始呢。\n");
                    return;
            }

            last_add_mgb_time = time();
            add_mgb_times += 1;

            write(HIW "你下令派出蒙古军增援。\n" NOR);

            // 开始准备调动
            xywar_message(HIR "蒙古人点燃了狼烟，通知蒙古军增援。" NOR);

            // 延迟派兵
            remove_call_out("delay_add_soldier");
            call_out("delay_add_soldier", 30 + random(10));

            call_out("xywar_message", 3, HIR "蒙古援军已经收到讯息，准备开始调动。");
            call_out("xywar_message", 8, HIR "蒙古增援部队已开始起程，很快将达到襄阳。");
            call_out("xywar_message", 15, HIR "蒙古援军正连夜赶路，即将抵达襄阳城。");
}

// 蒙古延迟派兵
void delay_add_soldier()
{
        if (now_status() != WARRING && ! TEST)return;

        // 派兵增援
        add_soldier();
}

// 战术：虚假退兵
void combat_xjtuibing()
{

}

// 战术：声东击西
void combat_sdjixi()
{

}

// 集中兵力攻击某门
// 参数pos 为方向，指相对于襄阳广场的方向 west,east,north,south
void combat_attack_all(string pos)
{
        // 50%几率虚假说明攻击方向
        if (random(2) == 1)
        {
        }



}
