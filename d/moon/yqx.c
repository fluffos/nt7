// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "倚秋轩");
	set("long", @LONG
这里是丁鹏平时最爱驻足的地方，因为青青在的时候经常会
斜倚小窗，静静地看着远处的红枫，独坐很久很久.......
LONG	);
	set("exits", ([ 
  "westup" : __DIR__"qfg",
  "southdown": __DIR__"egate",
]));
        set("objects",([
			__DIR__"npc/guards2" : 2,
                        __DIR__"npc/npc1" : 1,
       	]) );
	set("coor/x",-20);
	set("coor/y",1130);
	set("coor/z",50);
	setup();
}
