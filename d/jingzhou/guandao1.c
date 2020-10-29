inherit ROOM;

void create()
{
        set("short", "官道" );
        set("long", @LONG
你走在一条大官道上，两旁不时有人从你身边走过，西面通向荆
州，东边是武昌城的西门。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : "/d/wuchang/ximen",
                  "west" : __DIR__"guandao2",
        ]));

        set("no_clean_up", 0);

        set("coor/x", -7040);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}