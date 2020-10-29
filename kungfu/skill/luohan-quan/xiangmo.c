// This program is a part of NITAN MudLIB
// xiangmo.c 罗汉降魔

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
       
        // if (userp(me) && ! me->query("can_perform/luohan-quan/xiangmo"))
        //        return notify_fail("你还没有受过高人指点，无法施展「罗汉降魔」。\n");
                
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「罗汉降魔」只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("luohan-quan", 1) < 20)
                return notify_fail("你的罗汉拳法不够娴熟，现在还无法使用「罗汉降魔」。\n");
                                
        if( query("neili", me)<50 )
                return notify_fail("你现在真气不够，无法运用「罗汉降魔」。\n");
                        
        if (me->query_skill_mapped("cuff") != "luohan-quan") 
                return notify_fail("你没有激发罗汉拳，无法使用罗汉降魔！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "嗨的一声，一拳平平朝$n"
              HIY "打出，姿势有板有眼，颇具风范。\n" NOR;

        ap = attack_power(me, "cuff"); 
        dp = defense_power(target, "parry"); 
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "cuff");
                addn("neili", -30, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "只见$n" HIR "一个招架失误，登时"
                                           "被这拳打了个正着，闷哼一声，退了一步。\n" NOR);
                me->start_busy(1 + random(2));
        } else 
        {
                msg += CYN "可是$p" CYN "轻轻一格，架住了$P"
                       CYN "的来拳。\n" NOR;
                addn("neili", -10, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
