// /d/gaoli/dafujia1
// Room in 高丽
// rich 99/03/28
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIC"大富之家"NOR);
        set("long", @LONG
这是一家高丽城内的富贵人家，这家主人经商一辈子，攒了不少钱，
在高丽城内盖了这么个大宅子，门口立着两个大石狮子，站着两个家丁。
LONG
);
        set("exits", ([ 
        "south": __DIR__"baihu-1",
        "north": __DIR__"dafujia2",
        ]));
set("objects",([
                "/d/gaoli/npc/jiading" : 2,
        ]));
      setup();
        replace_program(ROOM);

}
