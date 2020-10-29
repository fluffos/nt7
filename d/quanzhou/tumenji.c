// Room: /d/quanzhou/tumenji.c
// Last Modified by Lonely on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "涂门集");
        set("long", @LONG
这是泉州南面东西向的一条干道，规模不大。南边是泉州著名的鸿
翔绸缎庄。西边是个集市，东边便是去往港口的主要通道「涂门水关」。
LONG );
        set("outdoors", "quanzhou");
        set("objects", ([
                "/d/taishan/npc/tangzi": 1,
        ]));
        set("exits", ([
                "east"  : __DIR__"tumenshuiguan",
                "west"  : __DIR__"jishi",
                "south" : __DIR__"road1",
                "north" : __DIR__"qingjingsi",
        ]));
	set("coor/x", -890);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}