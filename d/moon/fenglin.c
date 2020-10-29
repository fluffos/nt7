// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "枫林");
	set("long", @LONG
一踏入枫林，那浓得化不开的红，和着枫叶特有的清香
扑面而来。刹那间，你的身心完全被这浓得化不开的红
所陶醉了，驻足留连，久久不愿离去......
LONG	);
	set("exits", ([ 
  "west" : __DIR__"froom1",
]));
         set("objects",([
			__DIR__"obj/feng" : 1,
                        __DIR__"npc/npc3" : 1,
       	]) );
	set("coor/x",-20);
	set("coor/y",1150);
	set("coor/z",40);
	setup();
}
