#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
	int i, l;
	i = (int)me->query_skill("qiantian-yiyang", 1);
	l = (int)me->query_skill("buddhism", 1);

	if (!me->query("tls"))
	if ((i >= 10 && (int)me->query("shen") < i * 5)
	 || (i >= 50 && (int)me->query("shen") < i * 8)
	 || (i >= 100 && (int)me->query("shen") < i * 10))
		return notify_fail("大理乃是明门正派，看来你的侠义正气还不够啊！\n");

	if ( me->query("tls") && i > 10 && i < 150 && l < i - 10)
		return notify_fail("你的佛学修为看来不能抑止你的心中的好胜之心了！\n");

	if (me->query_skill("force", 1) < 20)
		return notify_fail("你的基本内功火候还不够，无法领会乾天一阳功。\n");

	if (i > 99 && (string)me->query("gender") != "男性")
		return notify_fail("你不是纯阳之身，无法领会更高层的乾天一阳功。\n");

	if ( me->query("menggu"))
		return notify_fail("乾天一阳功怎可和邪派功夫混为一体？\n");

	if ( i > me->query_skill("force", 1) + 10 && i >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
	if((int)me->query_skill("qiantian-yiyang", 1) >= 200) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("qiantian-yiyang", (int)me->query_int());
			me->add("neili", -100);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高乾天一阳功了。\n");
	}
	else return notify_fail("你现在的乾天一阳功修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"qiantian-yiyang/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIY + me->name()+"结珈而坐，神态安详"NOR,
		"start_my_msg" : "你盘膝坐下，闭目合什，运起乾天一阳神功，一股纯阳真气开始在体内运转。\n",
		"start_other_msg" : me->name()+"盘膝坐下，闭目合什,神态安详，周身似乎有一层金光笼罩。\n",
		"halt_msg" : "$N双掌一分，平摊在胸，迅速收气，停止真气的流动。\n",
		"end_my_msg" : "你真气在体内运行了一个周天，缓缓收气于丹田，慢慢睁开了眼睛。\n",
		"end_other_msg" : "只见"+me->name()+"慢慢睁开眼睛，周身笼罩的金光逐渐隐去。\n"
	]);
}

int ob_hit(object ob, object me, int damage)
{
	int i,neili,j;

	if( !me->query_temp("dali/jujing") ) return 0;

	if ( me->query_temp("weapon")) return 0;

	if ( me->query_skill_mapped("finger") != "yiyang-zhi"
	|| me->query_skill_prepared("finger") != "yiyang-zhi") return 0;

	if( me->is_busy() ) j = 2; else j = 1;

	if( damage > me->query("qi")/2 ) {
		me->add_temp("dali/jujing1",damage*j);
		neili = 13000 - me->query_skill("force")*10;
		if( neili < me->query("neili") ) {
			me->add("neili",-neili);
			if( wizardp(me) && me->query("env/test") )
				tell_object(me,sprintf("dec: %d,%d\n",damage,neili));
			message_vision(CYN"$N以一阳指柔劲吸收掉$n全部的攻击。\n"NOR, me, ob);
			return -damage;
		}
	}

	//if( random(me->query("combat_exp")) < ob->query("combat_exp")/3 ) return 0;

	i = me->query_skill("force") / 10;
	i = min(i,70);
	i = i/3 + random(i);
	i = damage * i / 100;

	me->add_temp("dali/jujing1", i*j);
	if( wizardp(me) && me->query("env/test") )
		tell_object(me,sprintf("dec: %d(%d) \n",i,damage));
	message_vision(CYN"$N以一阳指柔劲吸收掉$n部分攻击。\n"NOR, me,ob);

	return -i;
}
