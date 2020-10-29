// ken 1999.12.9

#include <room.h>
inherit ROOM;
void create()
{
	set("short", "月影楼顶");
	set("long", @LONG
此处两边飞楼插空，雕栏绣槛，绿窗油壁。
四面香风，穿窗而入，令人沉醉。
LONG	);
	set("exits", ([ 
  "down" : __DIR__"yyl2",
]));
        set("objects",([
			__DIR__"npc/ding" : 1,
                        __DIR__"npc/guards3" : 2,
       	]) );
	set("coor/x",-30);
	set("coor/y",1140);
	set("coor/z",100);
	setup();
}
