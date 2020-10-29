inherit ROOM;

void create()
{
        set("short", "王府井大街");
        set("long", @LONG
这里就是京城最为著名的王府井大街。你走在这条繁忙的街道上，
街道上车水马龙，人来人往，热闹非凡。南边接京城的交通要道东长
安街，西边通往地安门东大街。从东边传来一阵嘈杂的喧闹声，那是
京城著名的怡红院。
LONG );
       set("exits", ([
                "north" : "/d/beijing/wang_10",
                "south" : "/d/beijing/wang_6",
                "east" : "/d/beijing/yihongyuan",
                "west" : "/d/beijing/wang_7",
        ]));

        set("objects", ([
                "/d/beijing/npc/richman1" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}