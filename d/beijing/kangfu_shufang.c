#include <room.h>
inherit ROOM;

void create()
{
        set("short", "康亲王书房");
        set("long", @LONG
这里是康亲王书房，房中书架上整整齐齐地堆放着很多书。不过
书上积了一些灰尘，显然是很久没有动过了。而书橱里的几件精巧玉
器却更显得玲珑剔透，光彩照人。
LONG );
        set("exits", ([
                "south" : "/d/beijing/kangfu_zoulang2",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}