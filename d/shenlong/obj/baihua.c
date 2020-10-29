#include <ansi.h>
inherit ITEM;

void create()
{
	set_name("百花腹蛇膏", ({"baihua gao", "gao","baihua"}));
	/*if (clonep())
		set_default_object(__FILE__);
	else*/ {
		set("unit", "枚");
		set("long", "这是一枚珍贵的百花腹蛇膏。\n");
		set("value", 20000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	int limit;
	int max_limit;

	limit = me->query_current_neili_limit();
	max_limit = me->query_neili_limit();
	if( query("max_neili", me)<limit )
	{
        addn("max_neili", 5+random(5), 	me);
        set("neili",query("max_neili",  me), 	me);
		if( query("max_neili", me)>max_limit )
set("max_neili", max_limit, 			me);
		
		message_vision(HIY "$N吃下一枚百花腹蛇膏，顿然间只觉一股清凉之气直沁心肺...\n" NOR, this_player());
	}
	else
		message_vision(HIY "$N吃下一枚百花腹蛇膏，但是好象没什么用.\n" NOR, this_player());

	destruct(this_object());
	return 1;
}