#include <room.h>
inherit ROOM;

void create()
{
        set("short", "永内东街");
        set("long", @LONG
永内东街是一条繁华的大街，也是北京最杂乱的地段。一条宽阔
的青石大道从中穿过，向东西两头延伸。西边是京城里著名的凡陛桥。
从北边飘来一阵阵诱人的花香，顿时你的精神为之一振。南边是一个
打铁铺， 不时传来叮叮咚咚的敲打声。
LONG );
        set("exits", ([
                "south" : "/d/beijing/tiepu",
                "north" : "/d/beijing/huadian",
                "east" : "/d/beijing/yong_3",
                "west" : "/d/beijing/yong_1",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2780);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}