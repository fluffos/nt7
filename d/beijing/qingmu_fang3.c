#include <room.h>
inherit ROOM;

void create()
{
        set("short", "青木堂");
        set("long", @LONG
这里是一间看似很普通的民居，不过却要比通常的民居大了数倍。
房间正中一张长桌，天地会的青木堂的群豪围桌而坐，大声喧谈。
LONG );
        set("exits", ([
                "east" : "/d/beijing/qingmu_dayuan",
        ]));

        set("objects", ([
                "/d/beijing/npc/qibiaoqing" : 1,
                "/d/beijing/npc/fangang" : 1,
                "/d/beijing/npc/fengjizhong" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2840);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}