#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "天柱峰");
        set("long", @LONG
你爬上衡山五峰之一的天柱峰，四望群山缥缈云雾中，每每天阴
地湿时候，这里就是天柱云气的所在了。衡山派绝学天柱剑法便是从
中领悟出来的。
LONG );
        set("exits", ([ 
                "westdown"   : __DIR__"shanlu10",
                "eastdown"   : __DIR__"shanlu7",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/lu" : 1,
        ]));    

        set("no_clean_up", 0);

	set("coor/x", -6970);
	set("coor/y", -5550);
	set("coor/z", 30);
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
                return notify_fail("你的基本剑法火候不够，无法领悟天柱剑法。\n");

        if ((int)me->query_skill("tianzhu-jian", 1) > 120)
                return notify_fail("你发现已经不能从这里再领悟更高的天柱剑法。\n");

        if( query("jing", me)<25 )
                return notify_fail("你现在精神不济，过于疲倦，还是休息"
                                   "一会吧。\n");

        me->receive_damage("jing", 20);

        if (me->can_improve_skill("tianzhu-jian"))
                me->improve_skill("tianzhu-jian", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精会神的参详天柱峰，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你对「天柱剑法」有了新的领悟。\n" NOR);
        return 1;
}