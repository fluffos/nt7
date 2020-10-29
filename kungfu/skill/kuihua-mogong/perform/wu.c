// wu.c 群魔乱舞

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("群魔乱舞只能对战斗中的对手使用。\n");
 
        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，无法施展群魔乱舞！\n");

        if ((lvl = me->query_skill("kuihua-mogong", 1)) < 150)
                return notify_fail("你的葵花魔功火候不够，无法施展群魔乱舞！\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("你手里拿的不是剑，怎么施"
                                           "展群魔乱舞？\n");
                if( me->query_skill_mapped("sword") != "kuihua-mogong" )
                        return notify_fail("你还没有激发葵花魔攻为剑法，无法施展群魔乱舞。\n"); 
        } else
        {
                if (me->query_skill_prepared("finger") != "kuihua-mogong")
                        return notify_fail("你并没有准备使用葵"
                                           "花魔功，如何施展群魔乱舞？\n");
        }

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "默运葵花魔功，身形变得奇快无比，接连向$n"
              HIR "攻出数招！\n" NOR;
        i = 5;
        if (lvl / 2 + random(lvl) > (int)target->query_skill("dodge"))
        {
                msg += HIR "$n" HIR "只觉得眼前一花，发现四周都是$N"
                       HIR "的身影，不由暗生惧意，接连后退。\n" NOR;
                count = me->query_skill("kuihua-mogong", 1);
                addn_temp("apply/damage", count, me);
                addn_temp("apply/attack", count, me);
          set_temp("kuihua-mogong/wu_powerup", 1, me);
                i += random(6);
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "身法好快，哪里"
                       "敢怠慢，连忙打起精神小心应对。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -i*20, me);

        if( i > 12 ) i = 12;
        set_temp("action_flag", 1, me);
        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (i > 5 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
        }
        delete_temp("action_flag", me);

       if( query_temp("kuihua-mogong/wu_powerup",me))
       {
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
       }
        me->start_busy(3 + random(3));
        return 1;
}
