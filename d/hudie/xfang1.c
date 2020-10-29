// 厢房 xfang1.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "厢房");
        set("long", @LONG
这里是一间很大的厢房，陈设虽然比较简陋，但是十分干净，摆
放十分别致，靠近墙边的地方放了一些木床，看来是给求医的病人住
宿用的。
LONG );

        set("sleep_room", "1");
        set("no_fight", "1");

        set("exits", ([ 
            "north" : __DIR__"yaofang",
            "west" : __DIR__"caojing",
            "east" : __DIR__"huapu2",
        ]));

        setup();
}