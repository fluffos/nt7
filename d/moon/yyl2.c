// ken 1999.12.9

#include <room.h>
inherit ROOM;
void create()
{
	set("short", "月影楼");
	set("long", @LONG
此处两边飞楼插空，雕栏绣槛，绿窗油壁。
四面香风，穿窗而入，令人沉醉。
LONG	);
	set("exits", ([ 
  "up" : __DIR__"yyl3",
  "down" : __DIR__"yyl1",
]));
	set("coor/x",-30);
	set("coor/y",1140);
	set("coor/z",90);
	setup();
}
