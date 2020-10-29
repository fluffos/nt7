#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"牟尼堂"NOR);
        set("long",@LONG
这是天龙寺高僧们的静修之处，全以松木所制，板门木柱，木料均不去
皮，天然质朴，和一路行来金碧辉煌的殿堂截然不同。室中蒲团上分坐着三
个白须白眉的老和尚。
LONG
        );
        set("exits", ([
		"out": __DIR__"lang2",
	]));
	set("objects",([
		__DIR__"npc/ben-guan" : 1,
		__DIR__"npc/ben-xiang" : 1,
		__DIR__"npc/ben-can" : 1,
        ]));
        setup();
}
