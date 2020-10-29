#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "宋军大营"NOR);
        set("long", @LONG
这里就是「大宋」军营了，一面大旗高高树起，上面书着一个斗
大的隶书「宋」字，前面不远就是宋军元帅的帐营了。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
               "south" :   __DIR__"sying1",
               "north" :   __DIR__"syuanmen1",
        ]));

        set("objects", ([

        ]));

        setup();
        replace_program(ROOM);
}

