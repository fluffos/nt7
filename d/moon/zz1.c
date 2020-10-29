// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "阳关大道");
	set("long", @LONG
一条笔直的大路，向着西方蔓延着，看来是通向遥远的边疆的。
LONG	);
	set("exits", ([ 
  "north" : __DIR__"zz7",
  "west" : __DIR__"zz2",
  "east" : "/d/xj/heimiao",
]));
	set("coor/x",-10);
	set("coor/y",1000);
	set("coor/z",0);
	setup();
}
