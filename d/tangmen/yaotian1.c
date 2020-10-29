//yaotian1
#include <ansi.h>
inherit ROOM;

int do_zhao(string arg);

void create ()
{
        set ("short", "药圃");
        set ("long", @LONG
这里是唐门毒药房的药圃。这里的空气中飘荡着一股异香，闻到
这种气味，你只觉得头有一些发昏，采完药还是赶快离开吧。
LONG);
        set("area","tangmen");
        set("outdoors", "tangmen");
        set("exits", ([
                "north" : __DIR__"yaotian4",
                "east" : __DIR__"yaotian2",
        ]));
        set("yao", 5);
        setup();
}

void init()
{
        add_action("do_zhao","zhao");
}

int do_zhao(string arg)
{
        object me;
        int jingli_cost;

        me = this_player();
        jingli_cost = (-1) * (5 + random(15));

        if ( !arg || ( arg != "yao" ) )
                return notify_fail("你想干什么？\n");

        if( query_temp("find", me) )
                return notify_fail("你已经找到了一株草药，可以交差了！\n");

        if( query("jingli", me) <= (-jingli_cost) )
                return notify_fail("你太疲劳了，没有精力再找药了。\n");

        if ( (int)query("yao") >= 1 )
        {
                message_vision(YEL"$N蹲下身来，小心翼翼的在花圃中寻找着药草。\n"NOR, me);
                if( random(1+query("kar", me)-10) >= 3 )
                {
                        message_vision(HIG"$N不断的拨动着花圃中的草药，终于找到了一株。\n$N将这株药草小心的收在怀中。\n"NOR, me);
                        new(__DIR__"obj/caoyao")->move(me);
                        set_temp("find", 1, me);
                }

                addn("jingli", jingli_cost, me);
                addn("yao",-1);
        }
        else
                return notify_fail("这里都已经被翻遍了，没有什么可找的了。\n");

        return 1;
}