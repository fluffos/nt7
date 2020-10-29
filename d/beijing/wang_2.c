inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
这里就是京城最为著名的王府井大街。你走在这条繁忙的街道上，
街道上车水马龙，人来人往，热闹非凡。南边是京城的交通要道东长
安街。可以望见西边有一座富丽堂皇的建筑，那是当朝皇上的第一宠
臣——韦公爷的府邸。东边就是京城的刑场，是朝廷处决钦犯的场所。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_4",
                "south" : "/d/beijing/caroad_e2",
                "east" : "/d/beijing/xingchang",
                "west" : "/d/beijing/wang_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng1" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}