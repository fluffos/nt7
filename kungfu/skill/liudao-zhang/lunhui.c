// lunhui.c 六道杖法绝招：轮回罔生
// By Alf, Last Update 2001.10

#include <ansi.h>

int perform(object me, object target)
{
    object weapon;
        string msg;
    int damage,sk1,sk2,exp1,exp2,stf;

    if( !target || !target->is_character() || !me->is_fighting(target) )
        return notify_fail("「轮回罔生」只能对战斗中的对手使用。\n");

    sk1 = (int)me->query_skill("staff");
    if(target->query_skill_mapped("parry")==target->query_attack_skill())
        sk2 = ((int)target->query_skill("parry")+(int)target->query_skill("dodge"))/2;
    else
        sk2 = ((int)target->query_skill("parry",1)+(int)target->query_skill("dodge"))/2;
    exp1=query("combat_exp", me);
    exp2=query("combat_exp", target);
    stf = (int)me->query_skill("liudao-zhang",1);
        
    if( !objectp(weapon=query_temp("weapon", me) )
     || query("skill_type", weapon) != "staff" )
        return notify_fail("你使用的武器不对。\n");
                
    if(stf < 100 )
        return notify_fail("你的六道杖法不够娴熟，无法使出「轮回罔生」。\n");
                                
     if( query("neili", me)<300 )
        return notify_fail("你现在内力太弱，不能使用「轮回罔生」。\n");

    msg = 
HIY"$N突然冷哼一声，手腕一挺，劲气贯处，"+weapon->name()+HIY"去势如箭，向$n当胸疾刺！\n"NOR;

    if (random(sk1*sk1*sk1/1000+exp1/100) > (sk2*sk2*sk2/2000+exp2/200) || !living(target))
    {
        if(stf<300)
            target->start_busy( stf / 40 + random(2));
        else
            target->start_busy(4);
                
        damage = (int)me->query_skill("liudao-zhang", 1);
        damage = damage +  stf;
        damage = damage +  (int)me->query_skill("stf", 1);

        target->receive_damage("qi", damage*1/2,me);
        target->receive_wound("qi", damage/3,me);
        addn("neili", -400, me);
        me->start_busy(3);
        msg += HIM"$n只觉后背一凉，胸前被"+weapon->name()+HIM"刺了个对穿，不由长声惨呼！\n"NOR;
    }

    else
    {
        msg += YEL"可是$n早有防备，身形闪处，将$N的这一击轻易化解。\n"NOR;
        addn("neili", -100, me);
        me->start_busy(4);
    }

    message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
    return 1;
}
