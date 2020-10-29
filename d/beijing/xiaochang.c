#include <room.h>
inherit ROOM;

void create()
{
        set("short", "校场");
        set("long", @LONG
这里是京城兵营东方的一个大校场，校场里密密麻麻到处都是官
兵，在武将的指挥下列队操练，一个个官兵生龙活虎，整齐的排列着。
还有些太监在四处走动。东边是京城里著名的王府井大街。
LONG );
        set("exits", ([
                "east" : "/d/beijing/wang_3",
        ]));

        set("objects", ([
                "/d/beijing/npc/taijian" : 1,
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/bing2" : 2,
                "/d/beijing/npc/bing3" : 2,
                "/d/beijing/npc/yuqian1" : 1,
        ]));

	set("coor/x", -2790);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
}