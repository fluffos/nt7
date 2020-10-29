// 山路 shanlu3.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "山路");
        set("long", @LONG
这是一条弯弯曲曲的山路，东面传来阵阵清香，你循着清香走了
过去。
LONG );
        
        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "southdown" : __DIR__"shanlu1",
            "eastdown" : __DIR__"huapu1",
        ]));

        setup();
}