// Room: /d/jiaxing/jxnanmen.c
// Last Modified by Lonely on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "嘉兴南门");
        set("long", @LONG
这里是嘉兴的南门。周围长着茂密的竹林。东面是座庙宇。向南可
入福建。向东南就是号称天堂的杭州城了。
LONG );
        set("exits", ([
                "north"    : __DIR__"jiaxing",
                "east"     : __DIR__"tieqiang",
                "south"    : __DIR__"jnroad4",
                "southeast": "/d/hangzhou/road1",
                "southwest": __DIR__"majiu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jiaxing");
	set("coor/x", 1190);
	set("coor/y", -1780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}