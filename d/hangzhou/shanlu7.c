// shanlu7.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUILD_ROOM;
void create()
{
        set("short", "山路");
        set("long", @LONG
山路崎岖，曲折蜿延。四周林木苍翠，修竹茂密。山路旁是涵碧
亭，在这里极目远眺，群山环湖尽收眼底。西边是上山的路，往东便
是下山的路。
LONG);
        set("exits", ([
            "eastdown": __DIR__"yuhuangsj",
            "westup"  : __DIR__"yuhuangsd",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 790);
	set("coor/y", -2100);
	set("coor/z", 10);
	setup();
}
