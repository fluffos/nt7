// Room: /city/shenlong.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "神龙教");
        set("long", @LONG
shen long需要更多的说明……
LONG );

	set("exits", ([
		"west" : "/d/city/road7",
	]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
