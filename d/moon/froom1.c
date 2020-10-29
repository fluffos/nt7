// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "后花园");
	set("long", @LONG
你独自在花径徘徊，不觉来到了园子的深幽之处，只见林木葱郁，
奇花烂漫，一带清流，从花木深处泻于石隙之下，刚才的一尽奢华
皆隐于山坳树梢之间，景色美极了，也清幽极了。
LONG	);
	set("exits", ([ 
  "east" : __DIR__"fenglin",
  "west" : __DIR__"poor",
  "southup" : __DIR__"yyl",
]));
	set("coor/x",-30);
	set("coor/y",1150);
	set("coor/z",40);
	setup();
}
