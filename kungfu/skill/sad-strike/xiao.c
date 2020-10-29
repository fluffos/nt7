// xiao.c 黯然销魂

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "黯然销魂" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手使用。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("sad-strike", 1) < 150)
                return notify_fail("你的黯然销魂掌火候不够，无法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 320)
                return notify_fail("你的内功修为不够，无法施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "sad-strike")
                return notify_fail("你现在没有准备使用黯然销魂掌，无法施展" + name() + "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIM "\n$N" HIM "一声长吟：“黯然销魂者，唯别而已矣！”，顿时心如"
              "止水，黯然神伤，\n于不经意中随手使出了" HIR "『黯然销魂』" HIM "！\n" NOR;

        ap = attack_power(me, "unarmed") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        ap *= 2;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap * 60 / 100;
                msg += HIY "$n" HIY "见$P" HIY "这一招变化莫测，奇幻无"
                       "方，不由大吃一惊，慌乱中破绽迭出。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "不敢小觑$P" HIC
                       "的来招，腾挪躲闪，小心招架。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count*2, me);

        addn("neili", -400, me);
        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }

        me->start_busy(2 + random(5));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count*2, me);

        return 1;
}
