// wizlist.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

string get_title(string wiz_lvl);
string get_mission(string arg);
string *mission = ({ });

int sort_level(mixed ob1, mixed ob2)
{
        if (wiz_level(ob1) != wiz_level(ob2))
                return wiz_level(ob2) - wiz_level(ob1);
        return ob1 < ob2 ? -1 : 1;
}

string time_period(int time)
{
        int t, d, h, m, s;
        string str;

        t = time;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if (d) str = chinese_number(d) + "天";
        else str = "";

        if (h) str += chinese_number(h) + "小时";

        return str;
}

int main(object me, string arg)
{
        int adm_n, arc_n, wiz_n, app_n, imm_n;
        string *list;
        string desc;
        string msg, str, att, r;
        int i, j, k, t, y;
        object ob;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        desc = NOR + LOCAL_MUD_NAME() + "目前的巫师有：\n";
        desc += "------------------------------------------------------------------------\n" NOR;
        desc += BBLU HIW "巫师等级        巫师人物    目前任务              连线状态              \n"NOR;
        desc += "------------------------------------------------------------------------\n" NOR;

        list = sort_array(SECURITY_D->query_wizlist(), (: sort_level :));

        for(i = 0; i < sizeof(list); i++)
        {
                switch (wizhood(list[i]))
                {
                        case "(admin)"          : adm_n++; break;
                        case "(arch)"           : arc_n++; break;
                        case "(wizard)"         : wiz_n++; break;
                        case "(apprentice)"     : app_n++; break;
                        case "(immortal)"       : imm_n++; break;
                }
        }

        r = "";

        for(i = 0; i < sizeof(list); i++)
        {
                if (r != wizhood(list[i]))
                {
                        r = wizhood(list[i]);
                        switch (wizhood(list[i]))
                        {
                                case "(admin)"          : msg = "系统管理"; k = adm_n; break;
                                case "(arch)"           : msg = "程序开发"; k = arc_n; break;
                                case "(wizard)"         : msg = "开发辅助"; k = wiz_n; break;
                                case "(apprentice)"     : msg = "玩家管理"; k = app_n; break;
                                case "(immortal)"       : msg = "管理辅助"; k = imm_n; break;
                        }
                        j = 1;
                } else
                {
                        msg = "";
                        j++;
                }

                if (k == 1)
                        str = "------";
                else
                        str = "--┳--";

                if (k != j && k != 1 && j != 1)
                        str = "  ┣--";
                if (k == j && k != 1 && j != 1)
                        str = "  ┗--";

                if (objectp(ob = find_player(list[i])) && me->visible(ob))
                {
                        if( !intp(query_temp("time", ob)) ||
                            !query_temp("time", ob) )
                                set_temp("time", time(), ob);

                        t=time()-query_temp("time", ob);

                        if (t < 3600)
                                att = "连线不足一小时";
                        else
                                att = "连线" + time_period(t);

                        y = 1;
                } else
                {
                        if (file_size(DATA_DIR "login/" + list[i][0..0] + "/" + list[i] + __SAVE_EXTENSION__) < 0)
                                t = 0;
                        else
                        t = time() - (stat(sprintf("%slogin%s%s%s",
                                                   DATA_DIR, "/" + list[i][0..0] + "/",
                                                   list[i], __SAVE_EXTENSION__), -1)[1]);
                        if (t < 3600)
                                att = "离线不足一小时";
                        else
                                att = "离线" + time_period(t);

                        y = 0;
                }

                if (y) desc += HBRED;
                else desc += HIC;

                desc += sprintf("%-8s %-6s %-10s  %-22s%-22s\n" NOR, msg, str, list[i],
                                filter_color(get_mission(list[i])), att);
        }

        desc += "------------------------------------------------------------------------\n" NOR;
        desc += NOR "\n";
        write(desc);
        return 1;
}

string get_mission(string arg)
{
        int i;
        string wiz, mis;

        if (file_size("/adm/etc/wizmission") > 0)
                mission = explode(read_file("/adm/etc/wizmission"), "\n");

        for(i = 0; i < sizeof(mission); i++)
        {
                if (mission[i][0]== '#' ||
                    sscanf(mission[i], "%s %s", wiz, mis) != 2)
                        continue;

                if (wiz != arg) continue;

                return mis;
        }
        return "任务未定";
}

int help(object me)
{
        write(@HELP
指令格式 : wizlist

用途 : 列出目前所有的巫师名单。
HELP );
        return 1;
}
