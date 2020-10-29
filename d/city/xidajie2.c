// Room: /city/xidajie2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "西大街");
        set("long", @LONG
你走在西大街上，感到这里的街面要比别处的干净、整洁。大概
因为靠近衙门、兵营可受保护的缘故，富人们都喜欢住在这里。东边
静悄悄地没有几个行人，西边是西城门通往郊外。南边是一座武馆，
北边是一所富丽堂皇的大宅院。
LONG );
        set("outdoors", "city");
	set("no_clean_up", 0);
	set("exits", ([
		"east"  : "/d/city/xidajie1",
		"south" : "/d/city/wuguan",
		"west"  : "/d/city/xidajie3",
		"north" : "/d/city/caizhu",
	]));

        set("objects", ([
                "/d/quanzhen/npc/youfang": 1,
	]));

	set("coor/x", -20);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}