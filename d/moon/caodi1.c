// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "芳草地");
	set("long", @LONG
这里到处是各式各样的奇花异草。向左看去，则有一个小湖，
幽风袭面，清香暗涌。北面则是陡峭的山崖，刚才所见的灯
光似乎就来自这座山上。
LONG
	);
	set("exits", ([ 
  "east" : __DIR__"caodi",
            ]));
 set("objects",([
			__DIR__"obj/grass" : 1,
       	]) );
	set("coor/x",-40);
	set("coor/y",1050);
	set("coor/z",0);
	setup();
}
