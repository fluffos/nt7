#include <room.h>
inherit ROOM;

void create()
{
        set("short", "虎坊路");
        set("long", @LONG
这里是京城的虎坊路，它西接凡陛桥。只要你身上有两钱儿，在
这里就会受到热情的招呼。任何你不知道的事，在这里打听一下，都
可以知道个八九不离十。南边有一家小小的面馆，从里面传来一阵轰
闹声。
LONG );
        set("exits", ([
                "south" : "/d/beijing/mianguan",
                "east" : "/d/beijing/fu_2",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2820);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}