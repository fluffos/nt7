// Room: hslin.c
// By River 98/12
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "黑森林");
	set("long", @LONG
你快步而行，只见迎面黑压压的一座大森林。走近前去，只见左首一排九
株大松树参天并列，好象有些异样。
LONG
	);
	set("exits", ([
		"south" : __DIR__"tiesuo",
	]));
	set("outdoors", "大理");
	setup();
}

void init()
{
	add_action("do_enter","enter");
}

int do_enter(string arg)
{
	object me = this_player();

	if ( arg!="第四株" ) return notify_fail ("你要往哪里走？\n");
	if ( me->is_busy() || me->is_fighting() ) return notify_fail ("你现在正忙着呢。\n");

	write(HIW"\n你绕到第四株树后，拨开长草，树上出现一洞，你钻进树洞，左手拨开枯草，\n"+
              "右手摸到一个大铁环，用力提起，木板掀开，下面便是一道石级。走下几级，\n"+
              "双手托着木板放回原处，沿石级向下走去，三十余级后石级右转，数丈后折而\n"+
              "向上，上行三十余级，来到平地。\n\n"NOR,me);
	me->move(__DIR__"caodi");
	return 1;
}