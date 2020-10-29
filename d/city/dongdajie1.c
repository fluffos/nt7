// Room: /city/dongdajie1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "东大街");
        set("long", @LONG
这是一条宽阔的青石板街道，向东西两头延伸。东边不时地传来
金属撞击声，西边人声嘈杂。北边是一座简朴的院子，半月形的大门
上方写着『白鹿书院』四个烫金大字，苍劲有力。里面不时地传来学
生们抑扬顿挫的读书声。南边是一家杂货铺。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east" : "/d/city/dongdajie2",
		"south" : "/d/city/zahuopu",
		"west" : "/d/city/guangchang",
		"north" : "/d/city/shuyuan",
	]));

	set("objects", ([
		"/clone/npc/xunbu" : 1,
	]));
	set("coor/x", 10);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}