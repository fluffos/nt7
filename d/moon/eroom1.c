// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "右偏厅");
	set("long", @LONG
 这里是专门招待来访贵宾用膳的地方，厅中央摆放着
一张黑玉打磨而成的八仙桌，上面放着几只玉盏，能坐
在这里的，都是武林中成名的人物。
LONG	);
	set("exits", ([ 
  "west" : __DIR__"room",
  "north" : __DIR__"egate",
]));
	set("coor/x",-20);
	set("coor/y",1110);
	set("coor/z",40);
	setup();
}
