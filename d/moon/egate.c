// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "走廊");
	set("long", @LONG
 松木制成的雕栏被擦拭得一尘不染，廊脊上塑有九鲤
化龙，双凤朝阳的图象。走廊曲曲折折，一直向前延伸着。
LONG	);
	set("exits", ([ 
  "south" : __DIR__"eroom1",
  "northup" : __DIR__"yqx",
]));
        set("objects",([
			__DIR__"npc/guards2" : 1,
       	]) );
	set("coor/x",-20);
	set("coor/y",1120);
	set("coor/z",40);
	setup();
}
void init()
{
	add_action("do_go","go");
}
int do_go()
{if(random(3)) {this_player()->move(this_object());return 1;}}
