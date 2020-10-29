inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
这里就是京城最为著名的王府井大街。你走在这条繁忙的街道上，
街道上车水马龙，人来人往，热闹非凡。南边是京城的交通要道东长
安街，东边邻街处有一家当铺。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_8",
                "south" : "/d/beijing/wang_4",
                "west" : "/d/beijing/wang_5",
                "east" : "/d/beijing/dangpu",
        ]));

        set("objects", ([
                "/d/beijing/npc/boy2" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}