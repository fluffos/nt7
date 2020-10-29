// Room: /d/suzhou/road2.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
        set("short", "青石大道");
        set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时地有人骑着马匆
匆而过。大道两旁有一些小货摊，似乎是一处集市。往东面就是号称天
堂的苏州城了。虽然是城外，但是景色宜人，绝对是一个好住处。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"road3",
                "east"  : __DIR__"ximen",
        ]));
	set("coor/x", 1070);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
}
