#include <room.h>
inherit ROOM;

void create()
{
        set("short", "永内东街");
        set("long", @LONG
永内东街是一条繁华的大街，也是北京最杂乱的地段。一条宽阔
的青石大道从中穿过，向东西两头延伸。西边是京城里著名的凡陛桥。
北面是一家豪华的大赌场，此时正从里面传来一阵阵不堪入耳的声音。
南边是汇英酒楼，在京城中，也算是小有名气的。
LONG );
        set("exits", ([
                "south" : "/d/beijing/huiying",
                "north" : "/d/beijing/duchang",
                "east" : "/d/beijing/yong_2",
                "west" : "/d/beijing/tianqiao",
        ]));
        set("objects", ([
                "/d/beijing/npc/dipi" : 1,
                "/d/beijing/npc/boy1" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}