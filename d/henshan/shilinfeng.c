#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石廪峰");
        set("long", @LONG
芙蓉峰是衡山五峰之一，每逢下雨的时候，雨水打在峰中的岩石
上，发出巨大的回声，声音洪亮，犹如书院中的读书声，是以该峰由
此而来，衡山派的石廪剑法也由此而悟。
LONG );

        set("exits", ([
                "westdown"   : __DIR__"liuyunping",
        ]));

        set("objects", ([
                __DIR__"npc/dizi1" : 2,
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6920);
	set("coor/y", -5520);
	set("coor/z", 40);
	setup();
}

void init()
{       
        add_action("do_think", "think");
}

int do_think(string arg)
{
        object here, me = this_player();
        int add;

        if( query("special_skill/clever", me) )
                add = me->query_int() * 4;
        else
                add = me->query_int() * 3;

        if (! living(me) || arg != "feng")
                return notify_fail("你要参悟什么？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你现在正忙着呢。\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("你的基本剑法火候不够，无法领悟石廪剑法。\n");

        if ((int)me->query_skill("shilin-jian", 1) > 120)
                return notify_fail("你发现已经不能从这里再领悟更高的石廪剑法。\n");

        if( query("jing", me)<25 )
                return notify_fail("你现在精神不济，过于疲倦，还是休息"
                                   "一会吧。\n");

        me->receive_damage("jing", 20);

        if (me->can_improve_skill("shilin-jian"))
                me->improve_skill("shilin-jian", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精会神的参详石廪峰，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你对「石廪剑法」有了新的领悟。\n" NOR);
        return 1;
}