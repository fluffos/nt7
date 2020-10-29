// Room: /d/xiangyang/xinluofang.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "新罗坊");
        set("long", @LONG
新罗坊，顾名思义是给新罗人住的地方，不过其实现在新罗已经
被高丽所灭掉，这里应该叫做高丽坊的。可是大家已经习惯了，于是
便还这么叫。这里住着许多高丽商人，也有些高丽的使臣进东京城路
过襄阳，便也住在这里。这里的高丽商人总有很多很好的货物，大家
都喜欢来买，于是这里就非常的热闹了。
LONG );
        set("exits", ([
                "south" : __DIR__"northroad1",
        ]));
        set("objects", ([
                __DIR__"npc/gaoli" : 1,
        ]));
        set("coor/x", -7820);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}