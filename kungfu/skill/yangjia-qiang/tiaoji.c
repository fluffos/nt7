// tiao.c 挑击
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIY"挑击"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int ap, dp;

	me->clean_up_enemy();
	target = me->select_opponent();

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「挑击」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");

	if( !weapon
	 || weapon->query("skill_type") != "spear"
	 || me->query_skill_mapped("spear") != "yangjia-qiang" )
		return notify_fail("你现在无法使用「挑击」。\n");

	if( !tweapon )
		return notify_fail("对方没有使用任何兵器，你无法使用「挑击」。\n");

	if((int)me->query_skill("yangjia-qiang", 1) < 120 )
		return notify_fail("你的杨家枪还不够娴熟，不会使用「挑击」。\n");

	if((int)me->query("neili") < 2000 )
		return notify_fail("你的内力不够！\n");

	if( (int)me->query_str() < 25 )
		return notify_fail("你的先天臂力不足，无法使用「挑击」。\n");

	if( me->query_skill_mapped("parry") != "yangjia-qiang"
	&& me->query_skill_mapped("parry") != "yangjia-qiang" )
                return notify_fail("你需要激发招架为杨家枪，方能使用「挑击」。\n");

	if ( weapon )
		msg = HIR"$N右手搭枪，将手中"+weapon->name()+NOR+HIR"向上挑住$n兵器，试图以己之强大臂力打掉$n兵器。\n"NOR;

	me->start_perform(3, "挑击");

	ap = me->query("combat_exp")/1000 * me->query_str(1);
	dp = target->query("combat_exp")/1000 * target->query_str(1);

	if( random(ap + dp) > dp ) {
		int move_flag = 0;
		if(tweapon->is_owner(target)) move_flag=1;
		msg += HIY"$n只感"+tweapon->name()+HIY"压力却越来越重，再也无法控制，一个把握不住，手中兵器被飞了出去。\n"NOR;
		target->add_busy(1+random(2));
		me->add("neili",-300);

		if (move_flag==0 && random(2)!=1 && tweapon->query("imbued") < 3 && tweapon->move(environment(me))){
			msg += HIY"$n的兵器被$N的枪技挑击，刹那间"+tweapon->name()+HIY"已被$N已被挑出$n控制。\n"NOR;
		}
		else {
			msg += HIY"$n被$N手中"+weapon->name()+HIY"被$N枪技压制，无法控制，只能将"+tweapon->name()+HIY"放下。\n"NOR;
			tweapon->unequip();
			tweapon->move(environment(me));
		}
	}
	else {
		me->add("neili",-200);
              msg += MAG"$n借力运功，"+tweapon->name()+CYN"随"+weapon->name()+CYN"划出一道光环，将$N挑击化于无形！\n"NOR;

	}
	me->start_busy(random(2));
	message_vision(msg, me, target);
	return 1;
}

int help(object me)
{
	write(HBMAG"\n杨家枪之「挑击」："NOR"\n");
	write(@HELP
	杨家枪绝招数独特，运用于其长枪远距离攻击之优势，
	可挑掉对方武器，使其无法使用其武器。
	perform tiaoji

	要求：	当前内力 2000 以上；
		杨家枪等级 100 以上；
		激发招架为杨家枪；
		对手若手无兵器，则无效果。
HELP
	);
	return 1;
}