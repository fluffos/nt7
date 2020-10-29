// Room: /city/dongdajie2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "东大街");
        set("long", @LONG
你走在东大街上，踩着坚实的青石板地面。东边是东城门，可以
听到守城官兵的吆喝声，与西边朗朗的读书声混杂在一起。北边是一
家老字号的药铺，南边是打铁铺，叮叮当当的声音老远就能听到。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east"  : "/d/city/dongdajie3",
		"south" : "/d/city/datiepu",
		"west"  : "/d/city/dongdajie1",
		"north" : "/d/city/yaopu",
	]));

	set("coor/x", 20);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}