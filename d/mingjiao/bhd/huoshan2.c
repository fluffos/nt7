// huoshan2.c 火山口
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIR"火山口"NOR);
        set("long", @LONG
到了这里就等于到了地狱了。
LONG );
	set("exits",([
		"southdown" : __DIR__"huoshan1",
	]));
        set("outdoors","冰火岛");
	setup();
}

void init()
{
        object me =this_player();
        me->set_temp("die_reason", "误入火山口烧死");
       	me->die();
}
