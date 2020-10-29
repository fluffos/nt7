inherit ROOM;

void create()
{
        set("short", "化妆间");
        set("long", @LONG
这是演员的化妆间，几个演员正对着镜子化妆，也没注意
你进来。墙边一溜挂着很多衣服。边上的柜子上放了好几个面
具，那个面具看上去很精巧，带在脸上足可以以假乱真。
LONG);

        set("exits", ([
                "east" : __DIR__"xiyuan1",

        ]));
        set("objects", ([
                __DIR__"npc/xizi1" : 2,
                __DIR__"npc/xizi3" : 1,
        ]));

        set("coor/x", -9070);
	set("coor/y", -980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}