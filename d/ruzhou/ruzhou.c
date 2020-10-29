inherit ROOM;

void create()
{
        set("short", "汝州城");
        set("long", @LONG
汝州城是本府的大城，立来是兵家必争之地。故州治在此驻扎重
兵，盘查南来北往的行人，并负责翦灭附近山上的草寇。由于这里是
去嵩山的必经之道，官兵盘查也十分严格。从这里向东出城门，可以
到五岳之中的嵩山了。
LONG
        );

        set("exits", ([
                "south" : __DIR__"nandajie",
                "west"  : __DIR__"xidajie",
                "east"  : __DIR__"dongdajie",
                "north" : __DIR__"beidajie",
        ]));

        set("objects", ([
                "/clone/npc/xunbu" : 1,
                "/clone/npc/walker"  : 1,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
