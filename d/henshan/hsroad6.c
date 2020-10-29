inherit ROOM;

void create()
{
        set("short", "林间大道");
        set("long", @LONG
这里是一条林间大道，在树丛中蜿蜒。这里已是湖南境内。北边
是湖北。路边有可供路人休息的小茶亭。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "west"        : "/d/heizhao/shanlu1",
                "northwest"   : "/d/heizhao/shanlu6",
                "southwest"   : "/d/tiezhang/lx",
                "east"   : __DIR__"chating",
                "north"  : __DIR__"hsroad7",
                "south"  : __DIR__"hsroad5",
        ]));

	set("coor/x", -6930);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}