// ice@fy4
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
    string msg;
    int extra, bonus, i, n, num,res1,res2;
    object weapon;
    object *enemy;

    if ( me->query("class")!= "bandit")
		    return notify_fail("神教弟子才能领悟快刀。\n");
    if(userp(me) && (int)me->query_skill("tianya-blade",1) < 400)
	return notify_fail("你的天涯明月刀还不够精纯！\n");
/* if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("［快刀］只能对战斗中的对手使用。\n");*/
    enemy = me->query_enemy();
    if (me->query("class")!= "bandit"&&me->query_skill_mapped("force") != "yueying"&&me->query("force")<me->query("force_factor")*2)
     return notify_fail("非月影神功催动［快刀］ 需要"+me->query("force_factor")*2+"点内力。\n");

    if (!me->is_fighting()) return notify_fail("［快刀］只能对战斗中的对手使用。\n");

    if(target)
	return notify_fail("快刀不需要指定使用对象！！\n");
    weapon=me->query_temp("weapon");

    msg = HIR "\n$N"+HIR"将刀横于胸前，左手中指在刀背上一弹，右手借力挥刀。。。\n"NOR;
    combat_message_vision(msg,me);
    num = sizeof(enemy);
    if (me->query("class")!= "bandit") {
    	if (num>2) num = 2;
    }
    n = num+1;
    if(n==1) n=2;
    if(n > 5) n = 5;

    extra = me->query_skill("blade") + me->query_skill("move");
    if (me->query_skill("tianya-blade",1)>2000||me->query_skill("move",1)>2000)
    extra += me->query_skill("tianya-blade",1)*me->query_skill("move",1)/5;
    else  if (me->query_skill("tianya-blade",1)>1000||me->query_skill("move",1)>1000)
    extra += me->query_skill("tianya-blade",1)*me->query_skill("move",1)/7;
    else  if (me->query_skill("tianya-blade",1)>500||me->query_skill("move",1)>500)
    extra += me->query_skill("tianya-blade",1)*me->query_skill("move",1)/10;

    if ( me->query("class")== "bandit")
	bonus = extra/3;
    if((int)me->query_skill("tianya-blade",1) > 120) extra = extra + bonus;
    if( (me->query("class")== "bandit") && ((int)me->query_temp("bladeup")) )  extra += random(extra/4);
    	extra += me->query_agi()*me->query_str()/10;
    if(weapon && weapon->query("for_modao"))  extra += extra * weapon->query("for_modao")/5;
    	if (me->query("for_practice_modao")) extra += extra * me->query("for_practice_modao")/10;
    for(i=0;i<num;i++)
    {
	target = enemy[i];
	if (target) {
	 COMBAT_D->do_magic_attack(me,target,weapon,TYPE_REGULAR,extra+extra/2,HIW"只见一道亮光从$n"+HIW"身前划过！！"NOR);

} else 	return notify_fail("［快刀］只能对战斗中的对手使用。\n");
    }
   if (me->query("class")!= "bandit"&&me->query_skill_mapped("force") != "yueying")
   	me->add("force",-me->query("force_factor")*2);

    if (me->query_busy()<n)
	me->start_busy(n);
    return 1;
}
