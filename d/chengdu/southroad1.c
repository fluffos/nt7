// Room: southroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "南大街");
        set("long", @LONG
你走在南大街上，踩着坚实的青石板地面。这里显得热闹多了。
东北方向是东大街，往西一直走都是南大街。东南方向传来阵阵喧闹，
那里有个客店，杏帘分明： 锦城驿。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "northeast"  : __DIR__"eastroad3",
            "southeast"  : __DIR__"kedian",
            "west"       : __DIR__"southroad2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15210);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}