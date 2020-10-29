inherit ROOM;

void create()
{
        set("short", "后村小路");
        set("long", @LONG
这是一条蜿蜒的青石铺就的小路，是通向后山的唯一的道
路，路两旁开满不知名的野花，阵阵花香飘过，真是一片美丽
的田园风光。
LONG);
        set("exits", ([
                "west" :  __DIR__"lianwuchang",
                "east" : __DIR__"houcun-shanlu",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("objects", ([
                "/clone/quarry/tu" : 20 + random(20),
        ]));
        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}
