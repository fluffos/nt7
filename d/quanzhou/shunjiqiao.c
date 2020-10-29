// Room: /d/quanzhou/shunjiqiao.c
// Last Modified by Lonely on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "顺济桥");
        set("long", @LONG
这是横跨晋河的一座石拱桥。桥宽水深，水陆交通便捷，是南去的
唯一出口。一队官兵驻扎在这里。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "south"     : __DIR__"portroad3",
                "north"     : __DIR__"huajiaoting",
                "southeast" : __DIR__"shibosi",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", -900);
	set("coor/y", -7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}