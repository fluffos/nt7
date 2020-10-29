// Room: /d/xiangyang/southjie2.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
这里是襄阳城里的繁华地段，虽然久经战火，但在郭靖等人的保
卫下，襄阳的老百姓过着非常安安稳稳的生活。西边是襄阳城内最大
的一家赌场。东边是一座两层的楼阁，挂着『酒』的招帘，门额上悬
挂一方横匾，上书『觅香楼』三字。一阵阵酒肉香味扑鼻而来。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"nixianglou",
                "west"  : __DIR__"duchang",
                "south" : __DIR__"southjie3",
                "north" : __DIR__"southjie1",
        ]));
        set("objects", ([
                "/d/city/npc/liumang" : 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("coor/x", -7820);
	set("coor/y", -790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}