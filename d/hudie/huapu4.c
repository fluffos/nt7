// 花圃 huapu4.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "花圃");
        set("long", @LONG
这里是蝴蝶谷的花圃，是『见死不救』胡青牛用来种各种各样药
材的，里面种满了诸般花草。
LONG );

        set("no_clean_up", 0);
        set("outdoors", "蝴蝶谷");

        set("exits", ([
            "north" : __DIR__"houshan",
            "south" : __DIR__"chufang",
        ]));

        setup();
}