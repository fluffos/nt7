inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
这里就是京城最为著名的王府井大街。你走在这条繁忙的街道上，
街道上车水马龙，人来人往，热闹非凡。南边接京城的交通要道东长
安街，西边不远处是繁华的地安门东大街广场。北方是京城著名的『
全聚德』烤鸭店。东边是一家戏院，是京城百姓休息和娱乐的场所。
LONG );
       set("exits", ([
                "north" : "/d/beijing/quanjude",
                "south" : "/d/beijing/wang_8",
                "west" : "/d/beijing/wang_9",
                "east" : "/d/beijing/xiyuan",
        ]));

        set("objects", ([
                "/d/beijing/npc/youren" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}