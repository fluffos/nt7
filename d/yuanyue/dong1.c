// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h> 

void create()
{
        set("short", "山隙中");
        set("long", @LONG
这里阴森黝暗，伸手不见五指，又极潮湿，仅容一人通过。向前
方望去，却不知有多深远。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "eastup" : __DIR__"dong0",
                "west" : __DIR__"gu",
 
        ]));
         
        set("coor/x",140);
        set("coor/y",0);
        set("coor/z",10);
        setup();
        replace_program(ROOM);
}
