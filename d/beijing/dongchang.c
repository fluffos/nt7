inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",RED"东厂"NOR);
        set("long", @LONG
这里就是京城的特务机构——东厂。大厅内很是宽阔，这里警备
深严，穿着制服的东厂官兵和太监在这里来回走动。看来这里不宜久
留，赶快离开为妙。[2；37；0m
LONG );
        set("exits", ([
                "north" : "/d/beijing/dongchang_men",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing2" : 4,
                "/d/beijing/npc/taijian" : 1,
        ]));
        set("no_fight", 0);
	set("coor/x", -2790);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
}