// 后山 houshan.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "后山");
        set("long", @LONG
这里是蝴蝶谷的后山，非常空旷，显得很安静，三面都是悬崖峭
壁，犹如世外桃源一般。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([
            "south" : __DIR__"huapu4",
        ]));

        setup();
}