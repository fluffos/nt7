// ysroad1.c 岩石路
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIR"岩石路"NOR);
        set("long", @LONG
这是一岩石路，由此去火山尚须四十多里路。但在此已可以看到
四面山上一缕黑烟冲天而起。岩石路皆由火山灰堆成，厉时久，地面
十分坚硬。
LONG );
	set("exits",([
		"east" : __DIR__"shishan",
		"west" : __DIR__"ysroad2",
	]));
	set("outdoors","冰火岛");
	setup();
}
