// 空地 kongdi.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "空地");
        set("long", @LONG
这里是一片大的空地，据说当年蝴蝶谷誓师大会便是在这里进行
的，空地右边有一条小溪，弯弯曲曲不知通往何方。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
            "north" : __DIR__"niupeng",
            "northeast" : __DIR__"shanlu1",
            "northwest" : __DIR__"shanlu2",
            "southwest" : __DIR__"xiaojing2",
        ]));

        setup();
}