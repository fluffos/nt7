#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "神龙洞");
    set("long", @LONG
这里便是当年收伏蛇精的英雄—赛神龙的栖身之地，据说，当年
赛神龙耗尽毕生功力将蛇精镇压于蛇洞内，而自己却终身守护在蛇洞
内，以防蛇精重出人间。
LONG);

	set("exits", ([
		"out" : __DIR__"dong2.16",
		"north": __DIR__"shedong3",
		"south":__DIR__"shedong4",
		"west":__DIR__"shedong2",
		
		
		
	]));
	set("objects",  ([
		__DIR__"npc/sai" : 1,
	]));
		
	setup();
	replace_program(ROOM);
}
