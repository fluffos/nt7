inherit ROOM;

void create()
{
        set("short", "西门");
        set("long", @LONG
开封府内西面的主要交通要道，街道两边店铺林立，行人车马如
梭。小商贩们挑着担子来回吆喝。此地向东就是相国寺的放生池，再
向北过去不远，就能见到延庆观的大门了。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"wroad",
                "west" : "/d/zhongzhou/eroad3",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5080);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}