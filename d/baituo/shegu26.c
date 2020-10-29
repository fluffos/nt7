// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蛇谷树林");
        set("long", @LONG
这是白驼山的蛇谷之中，林木葱郁，北方传来轰轰的激流巨响，
似乎是一座瀑布。
LONG );

        set("exits", ([ 
            "north" : __DIR__"shegu27",
            "south" : __DIR__"shegu25",
        ]));

        set("cost", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49980);
        set("coor/y", 20220);
        set("coor/z", 20);
        setup();
}

void init()
{
        set("enter_shegu", 1, this_player());
}