#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "后山山洞");
        set("long", @LONG
这里是全真教开山祖师王重阳真人静修的山洞。洞虽不大但却布
置得很是雅致，便似大户人家的客厅一样。洞壁上悬挂着副画(hua)，
桌椅茶几都很精致。
LONG );
        set("exits", ([
                "out" : __DIR__"xiaolu12",
        ]));
        set("item_desc", ([
                "hua": YEL "\n画中是一个中年道士的背影，看不出什么相"
                       "貌，画中道人一手\n指着天，画角题着「" HIR "活"
                       "死人像" NOR + YEL "」几个字。\n" NOR,
        ]) );

        set("objects", ([
                CLASS_D("quanzhen") + "/wang" : 1,
        ]));
        set("coor/x", -2670);
        set("coor/y", 130);
        set("coor/z", 150);
        setup();
}

void init()
{
        add_action("do_ketou", "ketou");
}


int do_ketou(string arg)
{
        object paper, me = this_player();
        int level1, level2, level3;

        if (me->is_busy()) return notify_fail("你正在忙着呢。\n");

        message_vision("$N恭恭敬敬地在神案前的团蒲上跪了下来，对着神位磕了三个响头。\n", me);
        // me->receive_damage("qi", random(30));
        me->start_busy(1);

        if( query("qi", me) <= 50 )
                write("你只觉得脑子有些昏昏沉沉的。\n");
        if( query("qi", me) <= 30 )
                write("你觉得天旋地转，似乎马上便要晕去。\n");

        if( !(query("family/family_name", me) == "全真教") )
                return 1;

        level1 = me->query_skill("xiantian-gong", 1);
        level2 = me->query_skill("taoism", 1);
        level3 = me->query_skill("quanzhen-jian", 1);

        if( level1>300 && level2>300 && level3>300 && random(50) == 1 && !query_temp("quanzhen/shentong_paper", me) )
        {
                paper=new(__DIR__"obj/shentong_paper");
                if ( !paper ) return 1;

                addn("paper_count", -1);
                set_temp("quanzhen/shentong_paper", 1, me);

                message_vision(HIG"$N在团蒲上重重地一磕，团蒲的边上忽然裂了开来，露出一小段丝绢。\n"NOR,me);
                write("你仔细的将丝绢抽出一看，上面密密麻麻的记载了练功心法，似乎与先天\n");
                write("功一脉相承，但却更加深奥。\n");
                message_vision("$N连忙将密笈收好。\n",me);
                paper->move(me, 1);
        }

        return 1;
}