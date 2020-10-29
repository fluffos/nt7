// 小径 xiaojing1.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "小径");
        set("long", @LONG
你沿着小路行了一程，蝴蝶逐渐多了起来，你更加加快脚步向前
走去。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"xiaojing2",
            "south" : __DIR__"xiaojing",
        ]));

        setup();
}