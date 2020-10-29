// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "正院");
	set("long", @LONG
 这里简直就是一个小型的广场，所有的地面都是用整齐的
青石铺成，忙碌的家丁和侍女匆匆的走过，没有人理会你，
看着通向四方的路，你简直不知道该向哪里走了。
LONG	);
	set("exits", ([ 
  "north" : __DIR__"room",
  "south" : __DIR__"fgaden",
  "east" : __DIR__"eroom",
  "west" : __DIR__"wroom",
]));
        set("coor/x",-30);
	set("coor/y",1100);
	set("coor/z",40);
        set("objects",([
       	]) );
	setup();
}
