#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "五绝连环" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg, skill;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || (query("skill_type", weapon) != "staff"
            && query("skill_type", weapon) != "sword") )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("duanjia-jian", 1) < 120)
                return notify_fail("你的段家剑法不够娴熟，难以施展" + name() + "。\n");

        skill=query("skill_type", weapon);

        if (me->query_skill_mapped(skill) != "duanjia-jian")
                return notify_fail("你现在没有激发段家剑，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "深吸一口气，脚下步步进击，稳重之极，手中的" +
              weapon->name() + HIY "使得犹如飞龙一般，缠绕向$n" HIY "！\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -100, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(1 + random(3));
        return 1;
}
