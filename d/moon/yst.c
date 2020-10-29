// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "一水天");
	set("long", @LONG
从这里一眼就可以看到泻玉泉淙淙的流水，微风拂过，隐约听到
有如琴音的流水声，会同这里古朴的摆设和装饰，令你仿佛置身
世外桃源，唯愿独自去体味那种恬静与适意。
LONG	);
	set("exits", ([ 
  "eastup" : __DIR__"qfg",
  "southdown": __DIR__"wgate",
]));
       set("objects",([
			__DIR__"npc/guards2" : 2,
                        __DIR__"npc/npc2" : 1,
       	]) );
	set("coor/x",-40);
	set("coor/y",1130);
	set("coor/z",50);
	setup();
}
