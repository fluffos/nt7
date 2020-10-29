// /d/gaoli/xuanwumen
// Room in 高丽
#include <ansi.h>
inherit ROOM;


void create()

{
set("short", "鸭绿江南岸");

        set("long", @LONG
这里是鸭绿江的南岸。从这里乘船北上，就可以到中原的北方了。
这里停泊着几艘小船，看远处还有小船要靠近岸来。
LONG
        );
        

set("outdoors", "gaoli");
set("exits", ([
                "south" : "/d/changbaishan/shanlu5",
"north" : __DIR__"jiangbei",

                               
        ]));
       setup();
        
}
