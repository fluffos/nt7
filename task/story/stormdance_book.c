 
// 七宝天岚舞

inherit TASK;
#include <ansi.h>
void create()
{
	set_name(YEL"七宝天岚舞"NOR, ({"stormdance_book"}));
	set_weight(600);
	set("task",1);
        set("owner","狂风");
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
			"一本关于七宝天岚舞的入门舞姿的书籍。\n"
			"\t\t\t\------狂风注\n");
		set("value", 1000);
		set("material", "paper");
	}
	setup();
}
