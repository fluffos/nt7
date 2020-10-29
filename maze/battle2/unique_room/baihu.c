
#include <ansi.h>
inherit ROOM;

string show_jiqi();
int do_duoqu(string arg);
mapping data = ([]);

void create()
{
        set("short", HIY "白虎祭台" NOR);
        set("long",@LONG
你站在祭台上，感觉脚下异常冰冷。祭台上杂乱不堪，正
中插着一面祭旗（jiqi），上面似乎已经染满了鲜血。这里似
乎发生过激烈的打斗，不知道是为了争夺什么。你不由思绪万
千，“尘归尘，土归土 …… 世人究竟为了哪般？”
LONG);

        set("outdoors", "battlefield");
        set("no_clean_up", 1);
        set("item_desc", ([
                "jiqi"   :  (: show_jiqi :),
        ]));

        setup();
        set_heart_beat(1);
}

void init()
{
        add_action("do_duoqu", "duoqu");
}

string show_jiqi()
{
        int i;
        string *key;
        string  str;
        object  me = this_player();
        object  ob;
        string  team_name;

        if( !sizeof(data) )
                return HIG "现在还没有人夺取祭旗，赶紧夺取(duoqu jiqi)吧。\n" NOR;



        str  = HIG "现在祭旗夺取的情况如下：\n" NOR;
        str += sprintf(HIC "%-20s%-20s\n" NOR, "队伍", "夺旗时长");
        str += HIC "-------------------------------\n" NOR;
        key = keys(data);

        for( i=0; i<sizeof(key); i++ )
                str += sprintf("%-20s%-20s\n", key[i], time_period(data[key[i]]));

        str += HIC "-------------------------------\n" NOR;

        if( objectp(ob = query("jiqi_owner")) )
        {
                team_name = query_temp("battle/team_name", ob);
                str += HIC "现在祭旗正被" HIY +"【" + team_name + "】的" + ob->name() +
                       HIY "(" + query("id", ob) + ")" HIC + "夺取中！\n" NOR;
        }
        else
        {
                str += HIG "现在祭旗没有被夺取，赶紧夺取（duoqu jiqi）吧！\n" NOR;
        }
        return str;
}

 // 夺取旗帜
int do_duoqu(string arg)
{
        object me = this_player();
        object ob;
        string team_name;

        if( !arg || arg != "jiqi" )
                return notify_fail("你要夺取什么？\n");

        if( time() - query_temp("last_do_duoqu", me) < 10 )
                return notify_fail("你距离上次夺旗尝试时间不足10秒，不能连续尝试！\n");

        // 有人夺取时不能夺取
        if( objectp(ob = query("jiqi_owner")) )
        {
                me->set_temp("last_do_duoqu", time());
                return notify_fail(HIR "祭旗正被" + HIY + ob->name() + HIY "(" + query("id", ob) + ")" HIR "夺取中！\n" NOR);
        }

        // 夺取
        set("jiqi_owner", me);
        team_name = query_temp("battle/team_name", me);
        if( !undefinedp(data[team_name]) )
        {
                write(HIG "你夺取了祭旗，你的队伍总共夺取祭旗时间为：" HIY + time_period(data[team_name]) + HIG "。\n" NOR);
                tell_room(this_object(), HIG + me->name() + HIG "夺取了祭旗，其所在队伍【" + team_name +
                          "】总共夺取祭旗时间为：" HIY + time_period(data[team_name]) + HIG "。\n" NOR, ({ me }));
        }
        else
        {
                write(HIG "你夺取了祭旗，开始统计记时。。。\n" NOR);
                tell_room(this_object(), HIG + me->name() + HIG "夺取了祭旗，其所在队伍【" + team_name + "】。\n" NOR, ({ me }));
        }
        return 1;
}

void heart_beat()
{
        int time;
        object me;
        string team_name;

        me = query("jiqi_owner");

        if( !objectp(me) )
                return;

        if( !living(me) || environment(me) != this_object() )
        {
                delete("jiqi_owner");
                return;
        }

        BATTLEFIELD_D->add_bonus_score(me, 1);

        team_name = query_temp("battle/team_name", me);

        // 累计夺旗时间
        if( undefinedp(data[team_name]) )
                data[team_name] = 1;
        else
                data[team_name] += 1;

        time = data[team_name];

        // 累计到10分钟则胜利
        if( time >= 600 )
        {
                BATTLEFIELD_D->win_battle(team_name);
                return;
        }

        if( time >= 540 )
        {
                if( !(time % 10) )
                        CHANNEL_D->channel_broadcast("war", HIR"战"NOR RED"争"HIR"："+team_name+HIR"总共夺取"+query("short")+"祭旗时间为：" HIY +time_period(time) + HIR "，即将获得最终胜利..."NOR);
        }
        return;
}
