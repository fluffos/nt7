// Room: /city/wumiao2.c
// YZC 1995/12/04 

#include <room.h>

#define BOARD_TOC "/doc/board/toc"
#define BOARD_DIR "/doc/board/"
inherit ROOM;
string look_shu();

void create()
{
	set("short", "武庙二楼");
        set("long", @LONG
这里是岳王庙的二楼，这里供的是岳飞的长子岳云和义子张宪，
两尊塑像金盔银铠，英气勃勃。
LONG );

	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg", 1);
	set("no_sleep_room", 1);

        set("objects", ([
                "/adm/npc/gifter" : 1,
        ]));

	set("exits", ([
		"down" : "/d/city/wumiao",
                "up" : "/d/city/mingrentang",
	]));
	set("coor/x", -10);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
}