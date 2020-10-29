#include <room.h>
inherit ROOM;

void create()
{
        set("short", "韦府大院");
        set("long", @LONG
这是鹿鼎公府正厅前面的一个宽阔的大院，大院里种植着各类花
草，假山水池，琼楼高台，非常豪华。院内打扫得非常干净，韦府里
的下人穿梭其中，北边是一条木制走廊，通往康府的大厅。
LONG );
       set("exits", ([
                "south" : "/d/beijing/weifu_zoulang1",
                "north" : "/d/beijing/weifu_zoulang2",
        ]));
        set("objects", ([
                "/d/beijing/npc/yuanding" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}