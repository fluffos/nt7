// /d/gaoli/dafujia2
// Room in 高丽
// rich 99/03/28
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIC"大富之家"NOR);
        set("long", @LONG
你信步走进这家的大厅。整个大厅布置的极其豪华奢侈，一看就知
道不是普通百姓所住的地方。厅中摆着一张杉木圆桌和几张椅子，桌上
是一套精致的宜兴瓷器。
LONG
);
        set("exits", ([ 
        "south" : __DIR__"dafujia1",
        ]));
set("objects", ([
                "/d/gaoli/npc/jin" : 1,
                __DIR__"npc/yahuan":1,
        ]));
      setup();
        replace_program(ROOM);

}
