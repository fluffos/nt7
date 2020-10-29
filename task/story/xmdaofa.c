
#include <ansi.h>
inherit TASK;

void create()
{
    set_name(HIG "降魔道法" NOR, ({ "xmdaofa" }) );
	set_weight(500);
        set("owner","南贤");
	if( clonep() )
		set_default_object(__FILE__);
	else {
        set("unit", "本");
        set("long",HIR "降魔道法---南贤著--- \n" NOR);
		set("value", 10000);
        set("no_put_in",1); 
        set("task",1);
	}
}
