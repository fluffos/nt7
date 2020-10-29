inherit ROOM;

void create()
{
        set("short", "林间大道");
        set("long", @LONG
这里是一条林间大道，在树丛中蜿蜒。这里已是湖北境内。南边
是便湖南。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "north"  : __DIR__"hsroad8",
                "south"  : __DIR__"hsroad6",
        ]));
        set("objects", ([
                "/clone/quarry/gou" : 1,
        ]));

	set("coor/x", -6930);
	set("coor/y", -5680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}