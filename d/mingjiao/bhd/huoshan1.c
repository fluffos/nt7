// huoshan1.c 火山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIR"火山"NOR);
        set("long", @LONG
到这里一什么也看不见了。。。。只是有火烧身的感觉。
LONG );
	set("exits",([
		"northup" : __DIR__"huoshan2",
		"eastdown" : __DIR__"hsjiao",
	]));
	set("outdoors","冰火岛");
	setup();
}

int valid_leave(object me, string dir)
{
      if (dir == "northup")
        me->set_leader(0);
      return ::valid_leave(me, dir); 
}
