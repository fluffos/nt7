// ysroad2.c 岩石路
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIR"岩石路"NOR);
        set("long", @LONG
岩石路皆由火山灰堆成，厉时久，地面十分坚硬。在这里已可以
看见那缕黑烟之中竟有红火光不断的喷出，原来黑烟之处是一座活火
山，走到这里已感到一丝的热气扑面而来，再走十多里路就到达火山
脚下了。
LONG );
	set("exits",([
		"west" : __DIR__"hsjiao",
		"east" : __DIR__"ysroad1",
	]));
	set("outdoors","冰火岛");
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "west"){ 
	   me->set_leader(0);
           me->receive_damage("jing", 100);
           me->receive_damage("qi", 100);
         }
         return ::valid_leave(me, dir); 
}
