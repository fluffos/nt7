#include <ansi.h>
#include <combat.h>

#define SHENG "「" HIW "连环决" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int level;
 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHENG "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" SHENG "。\n");

        if (level = me->query_skill("tianjian", 1) < 20)
                return notify_fail("你的天剑修为不够（要求天剑二十级），难以施展" SHENG "。\n");

        if (me->query_skill_mapped("sword") != "tianjian")
                return notify_fail("你没有激发天剑，难以施展" SHENG "。\n");

        if( query("neili", me)<15 )
                return notify_fail("你现在真气（要求15的内力）不够，难以施展" SHENG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了（对方已死亡），用不着这么费力吧？\n");

        msg = HIY "$N" HIY "身法忽快，手中" + weapon->name() +
              HIY "回转，突然「唰！唰！」数剑，连连刺向$n" HIY "。\n" NOR;

        message_combatd(msg, me, target);

        addn("neili", -10, me);

        me->start_busy(1 + random(2));
        addn_temp("apply/attack", level, me);
        addn_temp("apply/damage", level*2, me);

                for (i = 0; i < 4; i++)
                {
                        if (! me->is_fighting(target))break;

                        if (random(2))target->start_busy(1);
                        
                        COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
                }

                addn_temp("apply/attack", -level, me);
                addn_temp("apply/damage", -level*2, me);

                if( query("newbie_quest/leixing", me) == "perform" )
                {
                                set("newbie_quest/completed", 1, me);
                                me->save();
                                tell_object(me, HIG "你已经学会了如何施展绝招，快回去找老村长领取奖励吧！\n" NOR);
                }

        return 1;
}
