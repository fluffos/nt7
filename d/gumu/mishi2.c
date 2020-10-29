// mishi2.c 密室
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
这里是古墓中的密室，四周密不透风，你只能借着墙上昏暗的灯光
来勉强分辨方向。墙是用整块的青石砌合起来的，接合的甚是完美，你
难以从中找出一丝缝隙。墙上(wall)好象雕有一些文字。
LONG        );
        set("exits", ([
                "east"  : __DIR__"mishi3",
                "west"  : __FILE__,
                "north" : __FILE__,
                "south" : __DIR__"mishi1",
                "up" : __DIR__"houting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", 30);
        set("coor/z", 100);
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

        if (! here = find_object(__DIR__"mishi2"))
                here = load_object(__DIR__"mishi2");

        if( query("special_skill/clever", me) )
                add = me->query_int() * 4;
        else
                add = me->query_int() * 3;

        if (! living(me) || arg != "wall")
                return notify_fail("你要参悟什么？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你现在正忙着呢。\n");

        if ((int)me->query_skill("sword", 1) < 30)
                return notify_fail("你的内功修为不够，无法领悟墙"
                                   "上的心法。\n");

        if( !query("can_learn/yunv-xinfa/wall", me) )
                return notify_fail("你研究了半天，却发现墙壁上的心法"
                                   "甚难领悟。\n");

        if ((int)me->query_skill("yunv-xinfa", 1) < 180)
                return notify_fail("你发现墙上所记载的心法过于深奥，自"
                                   "己一时难以领悟。\n");

        if ((int)me->query_skill("yunv-xinfa", 1) > 240)
                return notify_fail("你发现墙上所记载的心法过于肤浅，自"
                                   "己无法领会到任何东西。\n");

        if( query("jing", me)<35 )
                return notify_fail("你现在精神不济，过于疲倦，还是休息"
                                   "一会吧。\n");

        me->receive_damage("jing", 30);

        if (me->can_improve_skill("yunv-xinfa"))
                me->improve_skill("yunv-xinfa", add);

        me->start_busy(random(2));
        message_vision(HIY "\n$N" HIY "聚精会神的参详墙上所记载的心法，"
                       "似有所悟。\n" NOR, me);
        write(HIC "你对「玉女心法」有了新的领悟。\n" NOR);
        return 1;
}

