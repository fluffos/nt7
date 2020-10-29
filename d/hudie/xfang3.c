// 厢房 xfang3.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "厢房");
        set("long", @LONG
这是一间不大的厢房，陈设摆放十分整齐，靠左右墙边的地方各
有一张小床，看来是熬药、作饭的两个小童休息的地方。
LONG );

        set("exits", ([ 
            "west" : __DIR__"caotang",
            "south" : __DIR__"yaofang",
            "east" : __DIR__"shufang",
        ]));

        setup();
}