inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
你走在西大街上，感到这里的街面要比别处的干净、整洁。大概
因为靠近衙门、兵营可受保护的缘故，富人们都喜欢住在这里。东边
静悄悄地没有几个行人，西边是西城门通往郊外。南边是一座镖局，
北边的楼上写着『天宝阁』，那里是人们读书消遣的好去处。
LONG );
        set("outdoors", "city");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"xidajie2",
                "south" : __DIR__"biaoju",
                "west"  : __DIR__"ximen",
                "north" : __DIR__"tianbaoge",
        ]));

        set("objects", ([
                "/clone/npc/walker" : 1,
                __DIR__"npc/gongzi" : 1,
        ]));

	set("coor/x", -30);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}