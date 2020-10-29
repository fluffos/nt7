//金蛇剑--金蛇狂舞 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("金蛇狂舞只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功不够娴熟，不能使用金蛇狂舞。\n");

        if ((int)me->query_skill("jinshe-jian", 1) < 150)
                return notify_fail("你的金蛇剑法不够娴熟，不能使用金蛇狂舞。\n");


        if( query("neili", me)<400 )
                return notify_fail("你现在内力太弱，不能使用金蛇狂舞。\n");

        if (me->query_skill_mapped("sword") != "jinshe-jian")
                return notify_fail("你没有激发金蛇剑法，不能使用金蛇狂舞。\n");

        if (!living(target))
                return notify_fail("对方已经这样了，不用这么费力吧。\n");

        msg = HIY "$N" HIY "当下不及细想，身随剑走，绵绵而上,使出一招“金蛇狂舞”，"
              "手中的" + weapon->name() + HIY "挥出无数弯曲的剑刃,如影随形,永无止歇!。\n" NOR;
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                me->start_busy(2);
                    if (!target->is_busy())
                target->start_busy(1 + random(2));

                damage = damage_power(me, "sword");
                addn("neili", -200, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                       HIR "剑光一闪," HIR "$n" HIR "的胸口赫然留下一道弯弯血痕! \n" NOR);

                                         
        } else
        {
                me->start_busy(3);
                msg += CYN "$p" CYN "瞧不清敌招来路，惊惶中只得连连倒退! \n" NOR;
                      
        }
        message_combatd(msg, me, target);

        return 1;
}
