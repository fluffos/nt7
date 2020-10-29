// xian.c  云龙三现

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
                return notify_fail("云龙三现只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
                
        if ((int)me->query_skill("yunlong-jian", 1) < 50)
                return notify_fail("你的云龙剑法不够娴熟，不会使用「云龙三现」。\n");
                                
        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，不能使用「云龙三现」。\n");
                        
        if( query("neili", me)<300 )
                return notify_fail("你现在真气不够，不能使用「云龙三现」。\n");
                        
        msg = HIM "$N" HIM "微微一笑，猛吸一口气，以气驭剑攻击虚虚实实的攻向$n"
              HIM "！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);

                addn("neili", -180, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "只见$N" HIR "手中剑光幻作一条金龙，腾空而"
                                           "起倏的罩向$n" HIR "，\n$p" HIR "只觉一股大力"
                                           "铺天盖地般压来，登时眼前一花，两耳轰鸣，哇的"
                                           "喷出一口鲜血！！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "猛地向前一跃，跳出了$P"
                       CYN "的攻击范围。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
