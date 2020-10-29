// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "前花园");
	set("long", @LONG
但见绿树浓阴稠密，楼台倒影于池塘，微风吹动，水波荡漾；
回首园中，蔷薇满架，香气袭人，馨馥满庭。透过婆娑树影，
往北隐隐看到清风阁的一角飞檐。
LONG	);
	set("exits", ([ 
  "northup" : __DIR__"qfg",
  "south" : __DIR__"room",
]));
	set("coor/x",-30);
	set("coor/y",1120);
	set("coor/z",40);
	setup();
}
