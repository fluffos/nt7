// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIG "天地情长" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int cost;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("你没有激发玉箫剑法，难以施展" + name() + "。\n");

        skill = me->query_skill("yuxiao-jianfa", 1);

        if (skill < 150)
                return notify_fail("你玉箫剑法等级不够，难以施展" + name() + "。\n");

        if( query("neili", target)<300 )
                return notify_fail("看样子对方真气并不充沛，无需运用" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "$N" HIG "手中的" + weapon->name() + HIG "倏的刺出，卷起一阵"
              "阵气旋，不住的往里收缩。\n" NOR;

        ap = attack_power(me, "sword") +
             me->query_skill("chuixiao-jiafa", 1);
        dp = defense_power(target, "force") +
             target->query_skill("chuixiao-jiafa", 1);

        if (ap > dp || ap / 2 + random(ap) > dp)
        {
                addn("neili", -500, me);
                msg += HIM "$p" HIM "顿觉$P" HIM "的内力隐藏在一个个气旋中，难"
                       "以捉摸去处，只能强运内力抵消。\n" NOR;
                cost = 500 + (ap - dp) * 3 / 2;
                if( cost>query("neili", target) )
                        cost=query("neili", target);
                addn("neili", -cost, target);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -120, me);
                msg += HIC "可是$p" HIC "心神安定，丝毫没有受到困惑。\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}