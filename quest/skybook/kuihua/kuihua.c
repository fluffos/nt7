// kuihua.c 葵花宝典
// By River@SJ 2003.1.11

inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIW"葵花宝典"NOR, ({ "kuihua baodian", "baodian", "book"}));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这就是武林第一秘籍「葵花宝典」，相传是一位宫中太监所作。\n");
		set("value", 5000);
		set("unique", 1);
		set("no_give", 1);
		set("treasure",1);
		set("material", "paper");
		set("no_get", "这样东西不能离开那儿。\n");
	}
	setup();
}

void init()
{
	if (environment() == this_player())
		add_action("do_du", "read");
}

int do_du(string arg)
{
	object me = this_player();
	object ob = this_object();
	mapping skills = me->query_skills();
	string *sk;
	int i;

	if (!(arg=="pixie-jian" || arg=="kuihua-shengong"))
		return notify_fail("你要读什么？\n");
if (arg=="pixie-jian") {
	if ( me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");

	if ( !me->query("quest/pixie/pass") || me->query("gender") == "女性" )
		return notify_fail("你是怎么得到「葵花宝典」的啊？\n");

	if ( query("owner") != me && !wizardp(me))
		return notify_fail("你是怎么得到「葵花宝典」的啊？\n");

	if ( me->query("neili") < 1500 )
		return notify_fail("你的真气不够。\n");

	if ( me->query_skill("pixie-jian", 1) < 150 )
		return notify_fail("你的辟邪剑法等级太低，无法研读「葵花宝典」。\n");

	if (environment(me)->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (environment(me)->query("pending"))
		return notify_fail("此地不宜研习「葵花宝典」！\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("卧室不宜修练，会影响别人休息。\n");
 
	if (environment(me)->query("no_fight"))
		return notify_fail("此地不宜研习「葵花宝典」！\n");

	if ( me->query("gender") == "男性" ) {

		if ( me->query("marry"))
			return notify_fail("你已结婚，恐怕不适合研习「葵花宝典」。\n");

		if ( ! skills )
			return notify_fail("你这也太。。。。\n");

		sk = keys(skills);
		i = sizeof(sk);
		while (i--) {
			if (sk[i] == "dulong-dafa"
			|| sk[i] == "guiyuan-tunafa"
			|| sk[i] == "hanbing-zhenqi"
			|| sk[i] == "huagong-dafa"
			|| sk[i] == "kuihua-shengong" 
			|| sk[i] == "jiuyin-zhengong" ) continue;

			if ( SKILL_D(sk[i])->valid_enable("force"))
				return notify_fail("你不散掉"+to_chinese(sk[i])+"，无法修习辟邪剑法。\n");
		}
		tell_object(me, HIW"\n欲练神功，引刀自宫！\n\n"NOR);
		tell_object(me, HIR"你是否愿意引刀自宫，确定吗？[Y|N]"NOR);
		input_to("cut_jj", me );
	}
	else {
		if ( me->query("jing") < 40 )
			return notify_fail("你的精太少了，不够研读「葵花宝典」。\n");

		if ((!objectp(ob = present("needle", me)) ) || (!ob->query("equipped") ))
			return notify_fail("你没用绣花针，感到无法理解这种阴柔灵活的武功。\n");

		if ( me->query_skill("pixie-jian", 1) > 240 )
			return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");

		me->receive_damage("jing", 30 );
		me->add("neili", - 50);
		me->improve_skill("pixie-jian", me->query_int());
		if (!random(8))
			message("vision", me->name() + "仔细研读着「葵花宝典」的精妙之处。\n", environment(me), me); 
		tell_object(me, "你仔细研读着「葵花宝典」的精妙之处。\n");
	}
	return 1;
  }
  if (arg=="kuihua-shengong") {
	if ( me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");

	if ( !me->query("quest/pixie/pass") || me->query("gender") == "女性" )
		return notify_fail("你是怎么得到「葵花宝典」的啊？\n");

	if ( query("owner") != me && !wizardp(me))
		return notify_fail("你是怎么得到「葵花宝典」的啊？\n");

	if ( me->query("neili") < 1500 )
		return notify_fail("你的真气不够。\n");

	if ( me->query_skill("pixie-jian", 1) < 150 )
		return notify_fail("你的辟邪剑法等级太低，无法研读「葵花宝典」。\n");

	if (environment(me)->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (environment(me)->query("pending"))
		return notify_fail("此地不宜研习「葵花宝典」！\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("卧室不宜修练，会影响别人休息。\n");
 
	if (environment(me)->query("no_fight"))
		return notify_fail("此地不宜研习「葵花宝典」！\n");

	if ( me->query("gender") == "男性" ) {

		if ( me->query("marry"))
			return notify_fail("你已结婚，恐怕不适合研习「葵花宝典」。\n");

		if ( ! skills )
			return notify_fail("你这也太。。。。\n");

		sk = keys(skills);
		i = sizeof(sk);
		while (i--) {
			if (sk[i] == "dulong-dafa"
			|| sk[i] == "guiyuan-tunafa"
			|| sk[i] == "hanbing-zhenqi"
			|| sk[i] == "huagong-dafa"
			|| sk[i] == "kuihua-shengong" 
			|| sk[i] == "jiuyin-zhengong" ) continue;

			if ( SKILL_D(sk[i])->valid_enable("force"))
				return notify_fail("你不散掉"+to_chinese(sk[i])+"，无法修习辟邪剑法。\n");
		}
		tell_object(me, HIW"\n欲练神功，引刀自宫！\n\n"NOR);
		tell_object(me, HIR"你是否愿意引刀自宫，确定吗？[Y|N]"NOR);
		input_to("cut_jj", me );
	}
	else {
		if ( me->query("jing") < 40 )
			return notify_fail("你的精太少了，不够研读「葵花宝典」。\n");

		if ((!objectp(ob = present("needle", me)) ) || (!ob->query("equipped") ))
			return notify_fail("你没用绣花针，感到无法理解这种阴柔灵活的武功。\n");

		if ( me->query_skill("kuihua-shengong", 1) > 220 )
			return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");

		me->receive_damage("jing", 30 );
		me->set("quest/pixie/pass","pass");
		me->add("neili", - 50);
		me->improve_skill("kuihua-shengong", me->query_int());
		if (!random(8))
			message("vision", me->name() + "仔细研读着「葵花宝典」的精妙之处。\n", environment(me), me); 
		tell_object(me, "你仔细研读着「葵花宝典」的精妙之处。\n");
	}
	return 1;
  }
}

private void cut_jj(string arg, object me)
{
	if( arg[0]=='y' || arg[0]=='Y' ) {
		me->set("gender", "无性");
		me->set("class", "eunuch");
		CHANNEL_D->do_channel( this_object(), "rumor", sprintf("听说%s为了修练"HIR"辟邪剑法"HIM"而引刀自宫了！"NOR, me->name(1)));
		log_file("quest/pixie",sprintf(HIR"%-18s为研读「葵花宝典」，而引刀自宫。"NOR, me->name(1)+"("+capitalize(getuid(me))+")", ), me);
		tell_object(me, HIR"你只觉得两腿间一阵剧痛，鲜血激喷而出……\n"NOR);
		me->receive_wound("qi", 4000, "引刀自宫不慎，失血过多而");
	}
	else write("你心想还是再考虑下吧。\n");
}
