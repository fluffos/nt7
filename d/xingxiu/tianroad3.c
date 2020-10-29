// room: /d/xingxiu/tianroad3.c
// Last Modified by Lonely on Feb. 28 2001

inherit ROOM;

void init();
int do_jump(string arg);

void create()
{
        set("short", "天山山路");
        set("long", @LONG
这里是天山东麓，山风从山上吹来，你冷得瑟瑟发抖。路边是一片
草原。西面一条深涧(valley)挡住了上山的路。
LONG );
        set("exits", ([
                "northup"  : __DIR__"xxroad4",
                "eastdown" : __DIR__"xxh",
        ]));
        set("item_desc", ([
                "valley" : "深涧有三丈多宽，不知道能不能跳(jump)过去。\n"
        ]) );
        set("objects", ([
                CLASS_D("xingxiu")+"/azi" : 1
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "xingxiu");
        set("coor/x", -51000);
        set("coor/y", 20100);
        set("coor/z", 20);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if( arg=="valley" )
        {
/*                if (present("horse", me)) { */
                if( query_temp("marks/骑", me) )
                {
                        message("vision", me->name() + "猛地一提缰绳，胯下的伊犁马一声长嘶越过了深涧。\n", environment(me), ({me}) );
                        write("你猛地一提缰绳，胯下的伊犁马一声长嘶越过了深涧。\n");
                        me->move("/d/xingxiu/tianroad4");
                        message("vision","只听得唏溜溜一声马嘶，" + me->name() + "从深涧的那端纵马跳了过来，好似当年马跳\n檀溪的玄德公。\n", environment(me), ({me}) );
                        write( "只听得唏溜溜一声马嘶，你从深涧的那端纵马跳了过来，真是酷呆了。\n你乐得从马背上滚了下来。\n");
                        set_temp("marks/骑", 0, me);
                        return 1;
                }
                else
                {
                        write("你试了试，发现深涧的那边比这边高，非是人力可以跳上去的。\n");
                        return 1;
                }
        }
}
/*
int do_jump(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg != "valley")
                return notify_fail("你要往哪跳？\n");

        message_vision(HIY "\n$N" HIY "豫了一下，鼓气勇气，朝着对面的山崖跳了过"
                       "去。\n\n" NOR, me);

        if ((int)me->query_skill("dodge", 1) < 100 )
        {
                me->move(__DIR__"shanjiao");
                me->receive_wound("qi", 300);
                me->unconcious();
                message("vision", HIR "\n突然听得「砰」的一声，只见一个人从上面"
                                  "的山峰上坠了下来，真是壮观。\n" NOR,
                                  environment(me), ({me}));
        } else
        {
                me->move(__DIR__"tianroad4");
                message("vision", HIY "\n只见" + me->name() + HIY "从对面的山崖"
                                  "上跳了过来。\n" NOR, environment(me), ({me}));
        }
        return 1;
}

*/