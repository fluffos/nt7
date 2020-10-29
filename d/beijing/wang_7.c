inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
这里就是京城最为著名的王府井大街。你走在这条繁忙的街道上，
街道上车水马龙，人来人往，热闹非凡。南边接京城的交通要道东长
安街，西边通往地安门东大街。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_9",
                "south" : "/d/beijing/wang_5",
                "east" : "/d/beijing/wang_8",
                "west" : "/d/beijing/dong_1",
        ]));

        set("objects", ([
                "/d/beijing/npc/girl3" : 1,
        ]));

	set("coor/x", -2780);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}