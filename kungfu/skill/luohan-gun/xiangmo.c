// xiangmo.c 罗汉降魔－－十八罗汉棍

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        
        if (! target) target = offensive_target(me);
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("「罗汉降魔」只能对战斗中的对手使用。\n");

        if (me->query_skill("luohan-gun", 1) < 100) 
        return notify_fail("你的罗汉棍法不够娴熟，现在还无法使用「罗汉降魔」。\n");
                                
        if( query("neili", me)<150 )
        return notify_fail("你现在真气不够，无法运用「罗汉降魔」。\n");
                
        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "嗨的一声，一棍平平朝$n"
              HIY "扫出，招式虽然简单，但是却也是力道极重。\n" NOR;

        ap = attack_power(me, "club");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "club");
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "只见$n" HIR "一个招架失误，登时"
                                           "被这棍打了个正着，闷哼一声，退了一步。\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "可是$p" CYN "轻轻一格，架住了$P"
                       CYN "的棍势。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}