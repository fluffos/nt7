// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "左偏厅");
	set("long", @LONG
这是一间别致的小厅，厅中央摆放着一张红木圆桌，
桌上放着一盘残棋，还有两杯香茗，尚有余温。
LONG	);
	set("exits", ([ 
  "east" : __DIR__"room",
  "north" : __DIR__"wgate",
]));
	set("coor/x",-40);
	set("coor/y",1110);
	set("coor/z",40);
	setup();
}
