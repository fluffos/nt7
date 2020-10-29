// Room: /d/jiaxing/jiaxing.c
// Last Modified by Lonely on Nov. 17 2000


inherit ROOM;

void create()
{
        set("short", "嘉兴城");
        set("long", @LONG
这里是江南名城嘉兴。城东是风景如画的南湖。城北早先有座醉仙
楼，当年全真七子之一的丘处机和江南七怪就在那里盟约寻找忠良之后。
不知道什么原因店主把它迁到扬州了。
LONG );
        set("exits", ([
                "west"  : __DIR__"jnroad2",
                "east"  : __DIR__"nanhu",
                "south" : __DIR__"jxnanmen",
        ]));
        set("outdoors", "jiaxing");
        set("no_clean_up", 0);
	set("coor/x", 1190);
	set("coor/y", -1770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}