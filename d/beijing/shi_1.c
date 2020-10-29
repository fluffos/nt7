#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西四北大街");
        set("long", @LONG
这里是京城的西四南大街，青石铺砌道路贯通南北，著名的砖塔
儿胡同也在这条大街上。街道上的行人熙熙攘攘。南方接京城的西单
北大街，北方是西四北大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/shi_2",
                "south" : "/d/beijing/bei_3",
                "west" : "/d/beijing/minju",
        ]));
        set("objects", ([
                "/d/beijing/npc/liumang" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2830);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}