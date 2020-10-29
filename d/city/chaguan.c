// Room: /city/chaguan.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "春来茶馆");
        set("long", @LONG
你一走进来，就闻到一股茶香沁入心脾，精神为之一爽。几张八
仙桌一字排开，坐满了客人，或高声谈笑，或交头接耳。你要想打听
江湖掌故和谣言，这里是个好所在。
LONG );
	set("resource/water", 1);
	set("exits", ([
		"east" : "/d/city/nandajie2",
//                "up" : "/d/city/chashi",
	]));
	set("objects", ([
		"/d/city/npc/aqingsao" : 1,
	]));
	set("coor/x", -10);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
        "/clone/board/player_b"->foo();
}