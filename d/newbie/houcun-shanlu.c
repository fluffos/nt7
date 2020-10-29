inherit ROOM;

void create()
{
        set("short", "后村山路");
        set("long", @LONG
这是一条蜿蜒的泥土小路，是通向后山的唯一的道路，路
两旁开满不知名的野花，阵阵花香飘过，真是一片美丽的田园
风光。但随着山势越来越高，路也渐渐难走起来。
LONG);
        set("exits", ([
                "west" : __DIR__"houcun-road",
                "east" : __DIR__"luanshigang",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("objects", ([
                "/clone/quarry/tu" : 20+random(20),
        ]));
        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}