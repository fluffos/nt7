// Room: /city/xidajie1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "西大街");
        set("long", @LONG
这是一条宽阔的青石板街道，向东西两头延伸。西大街是衙门所
在，行人稀少，静悄悄地很是冷清。东边是一个热闹的广场。南边是
兵营。北边就是衙门了。
LONG );
        set("outdoors", "city");
	set("no_clean_up", 0);
	set("exits", ([
		"east"  : "/d/city/guangchang",
		"south" : "/d/city/bingyindamen",
		"west"  : "/d/city/xidajie2",
		"north" : "/d/city/yamen",
	]));

	set("coor/x", -10);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}