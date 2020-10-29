// yangpi.c
// Modified by Lane@SJ

inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIW"山羊皮"NOR, ({ "shanyang pi", "yangpi", "pi" }));
	set_weight(250);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "张");
		set("long","这是一张山羊皮，上面写满了许多希奇古怪的字。\n");
		set("treasure", 1);
		set("value", 200000);
		set("material", "skin");
		set("no_drop", 1);
		set("no_give", 1);
		set("no_get", 1);
		set("no_steal", 1);
		set("skill", ([
/*                        "name": "jiuyin-baiguzhua",     // name of the skill
			"exp_required":	300000,	// minimum combat experience required
                        "jing_cost":    30,     // jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
                        "max_skill":    62      // the maximum level you can learn
*/
		]) );
	}
}

void init()
{
	add_action("do_du", "read");
}

int do_du(string arg)
{
	object me = this_player();
	int level;

	if( !id(arg) ) return 0;

	if( me->is_busy() )
		return notify_fail("你现在正忙着呢。\n");

	if( me->is_fighting() )
		return notify_fail("你无法在战斗中专心下来研读新知！\n");

	if( !me->query("quest/jiuyin2/emei") )
		return notify_fail("你根本无法理解山羊皮上希奇古怪的字！\n");

	if( !me->query_skill("literate", 1) )
		return notify_fail("你是个文盲，先学点文化(literate)吧。\n");        

	if( me->query("jing") < 30 )
		return notify_fail("你现在过于疲倦，无法专心下来研读新知。\n");

	if( me->query_int() < 32 )
		return notify_fail("由于你的悟性不够，无法研习山羊皮。\n");

	if( me->query("combat_exp") < 1500000 )
		return notify_fail("你的实战经验不够，无法领会山羊皮上的文字。\n");

	level = me->query_skill("jiuyin-baiguzhua", 1);

	if( level >= 62 )
		return notify_fail("山羊皮上的文字对你而言已经太浅了。\n");

	me->receive_damage("jing", 30);
	write("你研读「山羊皮」上的文字，颇有心得。\n");
	me->improve_skill("jiuyin-baiguzhua", me->query_skill("literate", 1)+level);
	if( !random(9) ) message("vision", me->name() + "正在钻研一张山羊皮。\n", environment(me), ({me}));
	return 1;
}
