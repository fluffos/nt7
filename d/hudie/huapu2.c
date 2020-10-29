// 花圃 huapu2.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "花圃");
        set("long", @LONG
这里是蝴蝶谷的花圃，是『见死不救』胡青牛用来种各种各样药
材的，里面种满了诸般花草。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([
            "west" : __DIR__"xfang1",
        ]));

        setup();
}