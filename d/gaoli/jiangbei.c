// /d/gaoli/xuanwumen
// Room in 高丽
#include <ansi.h>
inherit ROOM;



void create()

{
set("short", "鸭绿江北岸");

        set("long", @LONG
这里是鸭绿江的北岸。从这里乘船南下，就可以到高丽了。这里的
人比较多，这里停泊着几艘小船，看远处还有小船要靠近岸来。
LONG
        );
        
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"milin1",
"south" : __DIR__"jiangnan",
                               
        ]));
       setup();
        
}
