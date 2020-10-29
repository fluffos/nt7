// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "大厅");
	set("long", @LONG
这是一间金碧辉煌的大厅，汉白玉为阶，两旁一排石交椅，
石阶上方摆放着一张巨案。看来是此处是山庄集会之所。
LONG	);
	set("exits", ([ 
  "north" : __DIR__"froom",
  "south" : __DIR__"gaden",
  "east" : __DIR__"eroom1",
  "west" : __DIR__"wroom1",
]));
        set("objects",([
			__DIR__"npc/guards2" : 2,
                        __DIR__"npc/npc4" : 1,
       	]) );
	set("coor/x",-30);
	set("coor/y",1110);
	set("coor/z",40);
	setup();
}
