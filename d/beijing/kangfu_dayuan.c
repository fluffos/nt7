#include <room.h>
inherit ROOM;

void create()
{
        set("short", "康府大院");
        set("long", @LONG
这是康亲王府大门东边的一个宽阔的大院，院内打扫得非常干净，
周围还种满了各类花草，康府里的下人穿梭其中，北边是一条木制走
廊，通往康府的大厅。
LONG );
       set("exits", ([
                "west" : "/d/beijing/kangfu_men",
                "north" : "/d/beijing/kangfu_zoulang1",
        ]));
        set("objects", ([
                "/d/beijing/npc/jiading_k" : 2,
                "/d/beijing/npc/yuanding" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}