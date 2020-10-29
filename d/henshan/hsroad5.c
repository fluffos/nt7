inherit ROOM;

void create()
{
        set("short", "林间大道");
        set("long", @LONG
这里是一条林间大道。这里是湖南境内。南边通向南岭的一个山
口。路东隐隐可以看到一角城墙。西面是一座猛恶山林。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "west"     : "/d/motianya/mtroad1",
                "east"     : __DIR__"hsroad4",
                "north"    : __DIR__"hsroad6",
                "southup"  : __DIR__"hsroad9",
        ]));

	set("coor/x", -6930);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}