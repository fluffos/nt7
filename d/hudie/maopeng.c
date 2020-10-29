// 茅棚 maopeng.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "茅棚");
        set("long", @LONG
这里是一间简陋的茅棚，里面堆放着一些干柴和茅草，看来是用
来生火用的，墙边靠着一些花锄和浇水用的水壶。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([
            "north" : __DIR__"xfang2",
            "west" : __DIR__"huapu3",
            "east" : __DIR__"caojing",
        ]));

        setup();
}