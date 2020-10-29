// ken 1999.12.12

inherit ITEM;

void create()
{
	set_name("明月十三式", ({ "ming yue book","book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
			"这是圆月山庄中失传以久的一本刀谱。\n");
		set("value", 70);
		set("material", "paper");
		set("skill", ([
			"name": 		"blade",		// name of the skill
			"exp_required":	30000,				// minimum combat experience required
											// to learn this skill.
			"sen_cost":		30,				// gin cost every time study this
			"difficulty":	20,				// the base int to learn this skill
											// modify is gin_cost's (difficulty - int)*5%
			"max_skill":	50				// the maximum level you can learn
											// from this object.
		]) );
	}
}