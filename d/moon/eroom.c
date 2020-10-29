// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "东厢房");
	set("long", @LONG
这里是供宾客休息的地方。所有的家具都被擦拭的
一尘不染。南墙上挂着一幅《松下舞剑图》。
LONG	);
	set("exits", ([ 
  "west" : __DIR__"gaden",
]));
//          set("objects",([
//			__DIR__"npc/shinu" : 1,
//       	]) );
	set("coor/x",-20);
	set("coor/y",1100);
	set("coor/z",40);
	setup();
}
