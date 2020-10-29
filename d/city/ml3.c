// Room: /city/milin.c

inherit ROOM;

void create()
{
	set("short", "青竹林");
        set("long", @LONG
这是一片茂密的青竹林，一走进来，你仿佛迷失了方向。
LONG );
	set("exits", ([
		"east" : __FILE__,
		"west" : "/d/city/ml4",
		"south" : "/d/city/dongmen",
		"north" : __FILE__,
	]));
	set("outdoors", "city");
	set("coor/x", 50);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}