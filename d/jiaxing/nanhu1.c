// Room: /d/jiaxing/nanhu1.c
// Last Modified by Lonely on Nov. 17 2000

inherit ROOM;

void init();
int do_out();

void create()
{
        set("short", "嘉兴南湖");
        set("long", @LONG
这里是烟波浩淼的南湖。湖上几只画舫在游荡，船上的游客和青楼
女子在嘻笑。湖水很深，没有船是渡不过去的。但不知是谁在湖底钉了
一些木桩。桩顶潜在水面之下一两寸的地方。即使是不懂轻功的人走上
去也像是水上漂的样子。
LONG );
        set("exits", ([
                "south"     : __DIR__"yanyu",
                "northwest" : __DIR__"nanhu",
                "southeast" : __DIR__"road",
        ]));
        set("outdoors", "jiaxing");
        set("objects", ([
                "/clone/medicine/vegetable/heye" : random(2),
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

	set("coor/x", 1210);
	set("coor/y", -1780);
	set("coor/z", 0);
	setup();
}