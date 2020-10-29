// 小径 xiaojing.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "小径");
        set("long", @LONG
你走了一阵，突然发现几只蝴蝶向前飞去，你心里不由一喜，向
着蝴蝶飞的方向走了过去。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"xiaojing1",
            "south" : __DIR__"huacong1",
        ]));

        setup();
}