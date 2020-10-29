// wu.c 群魔乱舞

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        object weapon;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && query("gender", me) != "无性" && !query("special_skill/ghost",me))
                return notify_fail("你的性别与日月内功相斥，无法使用此绝招！\n");  

        if (! target || ! me->is_fighting(target))
                return notify_fail("群魔乱舞只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你没有装备剑，不能用这一招。\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("你并没有使用辟邪剑法，无法使用此绝招！\n"); 

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，无法施展群魔乱舞！\n");

        if ((lvl = (int)me->query_skill("pixie-jian", 1)) < 350)
                return notify_fail("你的辟邪剑法火候不够，无法施展群魔乱舞！\n");

        msg = HIR "$N" HIR "一声长吟，身形变得奇快无比，接连向$n"
              HIR "攻出数招！\n" NOR;
        i = 7;
        if (lvl / 2 + random(lvl) > (int)target->query_skill("parry") || !living(target))
        {
                msg += HIR "$n" HIR "只觉得眼前一花，发现四周都是$N"
                       HIR "的身影，不由暗生惧意，接连后退。\n" NOR;
                count = (lvl + (int)me->query_skill("kuihua-xinfa", 1)) / 2;
                if( me->query_skill_mapped("force") != "kuihua-xinfa")
                count /= 2;
                addn_temp("apply/attack", count, me);
                i += random(6);
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "身法好快，哪里"
                       "敢怠慢，连忙打起精神小心应对。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        addn("neili", -i*20, me);
        addn_temp("str", 2000, me); 

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (i > 7 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_LINK);
        }

        addn_temp("apply/attack", -count, me);
        addn_temp("str", -2000, me); 
        me->start_busy(1 + random(6));
        return 1;
}
