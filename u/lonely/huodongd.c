/*固定活动管理系统，用于管理每日每周定时活动的启动和通知
周：
  1、擂台打榜           20:00-23:00  无需启动
  2、自由战场           19:30-22:30  无需启动
  3、帮战之冰火岛远征   20:00-21:30  需要启动
  4、襄阳保卫战         20:30-21:30  需要启动
  5、帮派大作战         20:30-22:00  需要启动
     缤纷周末活动       20:00-23:59  无需启动
  6、帮战之冰火岛远征   20:00-21:30  需要启动
     自由战场           13:00-20:00  无需启动
     缤纷周末活动       00:00-23:59  无需启动
  7、襄阳保卫战         20:30-21:30  需要启动
     帮派大作战         20:30-22:00  需要启动
     缤纷周末活动       00:00-23:59  无需启动
*/
// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

#include <ansi.h>

#define MEMBER_D     "/adm/daemons/memberd"
#define STR_SPRINTF    "%-10s%-20s%-20s%-20s\n"

// 记录周活动显示的信息，避免重复计算
nosave string strshow = "";
// 记录time对应的天数
nosave int current_day = 0;

// 函数声明
public string get_week_num(int dtime);
public void show_week_huodong(string sday);
public void do_channel(string ch, string msg);
public int can_start_huodong(string huodong);

// 通过ctime()返回 Fri Dec 31 17:04:17 2010 取第一个空格前的
nosave mapping week_time = ([
        "Mon"  : "1",
        "Tue"  : "2",
        "Wed"  : "3",
        "Thu"  : "4",
        "Fri"  : "5",
        "Sat"  : "6",
        "Sun"  : "7",
]);

// 用于显示的活动列表，不参与计算，仅做显示
nosave mapping huodong_list = ([
        "1"   :  sprintf(STR_SPRINTF, "周一", "擂台打榜", "19:00-23:00", "help biwu"),

        "2"   :  sprintf(STR_SPRINTF, "周二", "自由战场", "19:00-20:30", "help war_free"),

        "3"   :  sprintf(STR_SPRINTF, "周三", "冰火岛远征", "20:00-21:30", "help league.war"),

        "4"   :  sprintf(STR_SPRINTF, "周四", "襄阳保卫战", "21:30-22:30", "help xywar"),

        "5"   :  sprintf(STR_SPRINTF, "周五", "缤纷周末活动", "20:00-23:59", "help wkgift") +
                 sprintf(STR_SPRINTF, "    ", "帮派大作战", "20:00-21:30", "help league.fight"),

        "6"   :  sprintf(STR_SPRINTF, "周六", "缤纷周末活动", "00:00-23:59", "help wkgift") +
                 sprintf(STR_SPRINTF, "    ", "自由战场", "13:00-20:00", "help war_free") +
                 sprintf(STR_SPRINTF, "    ", "冰火岛远征", "20:00-21:30", "help league.war"),

        "7"   :  sprintf(STR_SPRINTF, "周日", "缤纷周末活动", "00:00-23:59", "help wkgift") +
                 sprintf(STR_SPRINTF, "    ", "襄阳保卫战", "21:30-22:30", "help xywar") +
                 sprintf(STR_SPRINTF, "    ", "帮派大作战", "20:00-21:30", "help league.fight"),
]);

// 显示所有的周活动或指定某日活动
public void show_week_huodong(string sday)
{
        string str;
        int i;

        str = sprintf(HIC + STR_SPRINTF + NOR, "活动日", "活动名", "时间", "帮助文件");
        str += "=-----------------------------------------------------------------------------=\n";

        if (sday != "all")
        {
                str += HIG + huodong_list[sday] + NOR;
        }
        else
        {
                if (! sizeof(strshow) || current_day != time() / 86400 )
                {
                        strshow = "";
                        for(i = 0; i < sizeof(huodong_list); i ++)
                        {
                                if (get_week_num(time()) == sprintf("%d", i+1))
                                        strshow += HIR + huodong_list[sprintf("%d", i+1)] + NOR;
                                else
                                {
                                        if ((i+1)%2==0) // 分单双错开颜色
                                                strshow += HIG + huodong_list[sprintf("%d", i+1)] + NOR;
                                        else
                                                strshow += HIY + huodong_list[sprintf("%d", i+1)] + NOR;
                                }
                        }
                        current_day = time() / 86400;
                }
                str += strshow;
        }
        str += "=-----------------------------------------------------------------------------=\n";
        if (sday == "all")
        {
                str += HIR "红色部分表示今天的活动！\n" NOR;
                str =  "\n" HIY + "【炎黄每日活动列表  -- 欢迎参与】\n" + str + NOR;
        }
        write(str);
}

// 返回当前时间是周几，用字符串返回，周一则是“1”
public string get_week_num(int dtime)
{
        int strweek, strtemp;
        sscanf(ctime(dtime), "%s %s", strweek, strtemp);
        return week_time[strweek];
}


void create()
{
        seteuid(getuid());
        restore();
        set_heart_beat(10); // 20秒心跳一次

        set("channel_id", HIY "活动使者" NOR);
}

void remove(){save();}

// 发布全屏通告
public void do_channel(string ch, string msg)
{
        CHANNEL_D->do_channel(this_object(), ch, msg);
}

public void mud_shutdown(){save();}

/* 每1分钟次的心跳 用于检查活动开启
   通过dbase记录每个活动上次举办的时间，避免因为当机等引起的重复举行或未举行
   sday 代表周几 如周一则sday = "1"
   query("huodong_info/sday, ([
        "活动名1"  : 启动时间,
        "活动名2"  : 启动时间,
   ]))
*/
void heart_beat()
{
        string wk, strtime, str_hour, str_min, today;
        string *keys_strtime;
        int nhour, nmin, ntime;

        ntime = time();
        wk = get_week_num(ntime);
        strtime = MEMBER_D->bjtime(ntime, 0);
        keys_strtime = explode(strtime, ":");
        str_hour = keys_strtime[3];
        str_min = keys_strtime[4];
        sscanf(str_hour, "%d", nhour);
        sscanf(str_min, "%d", nmin);

        today = sprintf("%d", ntime / 86400);

        switch(wk) // 星期几
        {
        case "1": // 擂台打榜活动 19:30-23:30
                if (! query("huodong_info/" + today + "/擂台打榜")) // 还未举行
                {
                        if (nhour == 19)
                        {
                                // 开始活动
                                do_channel("chat", HIG "比武挑战活动已经开启，欢迎上台一展身手，" +
                                                       "详情见 help biwu 帮助。\n" NOR);
                                // 记录开始时间
                                set("huodong_info/" + today + "/擂台打榜", ntime);
                        }
                }
        break;

        case "2": // "自由战场", "19:00-22:00"
                if (! query("huodong_info/" + today + "/自由战场")) // 还未举行
                {
                        if (nhour == 19)
                        {
                                // 开始活动
                                do_channel("chat", HIG "自由战场活动已经开启，为了荣誉而战吧。" +
                                                       "详情见 help war_free 帮助。\n" NOR);
                                // 初始化
                                WAR_D->init_all_war();
                                // 记录开始时间
                                set("huodong_info/" + today + "/自由战场", ntime);
                        }
                }
        break;

        case "3": // "周三", "冰火岛远征",20:00-21:30"
                if (! query("huodong_info/" + today + "/冰火岛远征")) // 还未举行
                {
                        if (nhour == 20)
                        {
                                // 开始活动
                                if (! LEAGUE_D->is_in_leaguewar())
                                        LEAGUE_D->start_leaguewar();
                                // 记录开始时间
                                set("huodong_info/" + today + "/冰火岛远征", ntime);
                        }
                }
        break;

        case "4": // "周四", "襄阳保卫战", "21:30-22:30",
                if (! query("huodong_info/" + today + "/襄阳保卫战")) // 还未举行
                {
                        if (nhour == 21 && nmin == 30)
                        {
                                // 开始活动
                                if (XYWAR_D->now_status() == 0)
                                        XYWAR_D->start_xywar();
                                // 记录开始时间
                                set("huodong_info/" + today + "/襄阳保卫战", ntime);
                        }
                }
        break;

        case "5": //"周五", "缤纷周末活动", "20:00-23:59"
                  //        "帮派大作战", "20:00-22:00"
                if (! query("huodong_info/" + today + "/帮派大作战")) // 还未举行
                {
                        if (nhour == 20)
                        {
                                // 开始活动
                                LEAGUEFIGHT_D->start_leaguefitht();
                                // 记录开始时间
                                set("huodong_info/" + today + "/帮派大作战", ntime);
                        }
                }
        break;

        case "6": // 周六
                  //        "周六", "缤纷周末活动", "00:00-23:59"
                  //        "自由战场", "13:00-20:00"
                  //        "冰火岛远征", "20:00-21:30"
                if (! query("huodong_info/" + today + "/自由战场")) // 还未举行
                {
                        if (nhour == 13)
                        {
                                // 开始活动
                                do_channel("chat", HIG "自由战场活动已经开启，为了荣誉而战吧。" +
                                                       "详情见 help war_free 帮助。\n" NOR);
                                // 初始化
                                WAR_D->init_all_war();
                                // 记录开始时间
                                set("huodong_info/" + today + "/自由战场", ntime);
                        }
                }
                if (! query("huodong_info/" + today + "/冰火岛远征")) // 还未举行
                {
                        if (nhour == 20)
                        {
                                // 开始活动
                                if (! LEAGUE_D->is_in_leaguewar())
                                        LEAGUE_D->start_leaguewar();
                                // 记录开始时间
                                set("huodong_info/" + today + "/冰火岛远征", ntime);
                        }
                }
        break;

        case "7":  // 周日
                  //        "周日", "缤纷周末活动", "00:00-23:59"
                  //        "襄阳保卫战", "21:30-22:30"
                  //        "帮派大作战", "20:00-22:30"
                if (! query("huodong_info/" + today + "/襄阳保卫战")) // 还未举行
                {
                        if (nhour == 21 && nmin == 30)
                        {
                                // 开始活动
                                if (XYWAR_D->now_status() == 0)
                                        XYWAR_D->start_xywar();
                                // 记录开始时间
                                set("huodong_info/" + today + "/襄阳保卫战", ntime);
                        }
                }
                if (! query("huodong_info/" + today + "/帮派大作战")) // 还未举行
                {
                        if (nhour == 20)
                        {
                                // 开始活动
                                LEAGUEFIGHT_D->start_leaguefitht();
                                // 记录开始时间
                                set("huodong_info/" + today + "/帮派大作战", ntime);
                        }
                }
        break;

        default:
        return;
        }

        return;
}

// 来自city biwu_dating ,yinghao_dating, xinrui_datin调用
// 是否可以开始比武
public int can_start_huodong(string huodong)
{
        string wk, strtime, str_hour, str_min, today;
        string *keys_strtime;
        int nhour, nmin, ntime;

        ntime = time();
        wk = get_week_num(ntime);
        strtime = MEMBER_D->bjtime(ntime, 0);
        keys_strtime = explode(strtime, ":");
        str_hour = keys_strtime[3];
        str_min = keys_strtime[4];
        sscanf(str_hour, "%d", nhour);
        sscanf(str_min, "%d", nmin);
        str_min = keys_strtime[4];
        today = sprintf("%d", ntime / 86400);

        switch(huodong)
        {
        case "biwu": // 比武打榜 19:00 - 23:00
                if (wk == "1" &&
                   nhour >= 19 && nhour < 23)return 1;
                else
                {
                        return 0;
                }
        break;
        case "league.war":
        break;
        case "league.fight":
        break;
        case "war_free": // "周二", "自由战场", "19:00-22:00" 周六 "自由战场", "13:00-20:00"
                if (wk == "2" &&
                   nhour >= 19&&
                   nhour < 22)return 1;
                else if (wk == "6" &&
                        (nhour >= 13 && nhour < 20)
                        )return 1;
                else
                        return 0;
        break;
        case "xywar":
        break;

        default:
        return 0;
        }

        return 0;
}
