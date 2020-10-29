// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "阳关大道");
	set("long", @LONG
一条笔直的大路，向着西方蔓延着，看来是通向遥远的边疆的。
可惜前方好象还在修路，行人纷纷折返。
LONG	);
	set("exits", ([ 
  "west" : "/d/moon/zz1",
  "east" : "/d/xj/heimiao",
]));
	set("coor/x",-20);
	set("coor/y",1000);
	set("coor/z",0);
	setup();
}
