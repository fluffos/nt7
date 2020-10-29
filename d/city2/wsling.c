#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", BLK"乌石岭"NOR);
        set("long", @LONG
这里就是乌石岭了，据说得名于满地的乌岩所致，具体的原因就
无从考究了，近年来大宋和蒙古连年战火，边境早已民不聊生，这里
早就成了人迹罕至之地了。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
              "north" :   __DIR__"shanlu2",
              "south" :   __DIR__"shanlu1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}

