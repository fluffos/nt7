// Room: /city/caizhu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "财主大门");
        set("long", @LONG
一座富丽堂皇的大宅院出现在你的眼前，两头高大的石狮子镇守
在了大门两侧，朱漆大门足足有三寸厚。门上挂着两个灯笼，写着『
崔』字。崔家是当地首富，而且以蛮横著称。几条狼狗嚎叫着向你冲
了过来。
LONG );
	set("exits", ([
		"south" : "/d/city/xidajie2",
		"north" : "/d/city/dayuan",
	]));
	set("objects", ([
		"/d/city/npc/wolfdog" : 2,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -20);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}