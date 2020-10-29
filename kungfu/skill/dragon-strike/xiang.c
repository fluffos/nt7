// This program is a part of NITAN MudLIB
// xiang.c 龙翔九天

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "龙翔九天"; }

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
                return notify_fail("「龙翔九天」只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("「龙翔九天」只能空手使用。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的内力修为还不够，无法施展「龙翔九天」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够！\n");

        if( query("qi", me)<800 )
                return notify_fail("你的体力现在不够！\n");

        if ((int)me->query_skill("dragon-strike", 1) < 150)
                return notify_fail("你的降龙十八掌火候不够，无法使用「龙翔九天」！\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，无法使用「龙翔九天」！\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你现在没有准备使用降龙十八掌，无法使用「龙翔九天」！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "深吸一口气，跨前一步，双掌猛然翻滚，"
              "缤纷而出，宛如一条神龙攀蜒于九天之上！\n\n" NOR;

        ap = attack_power(me, "strike") + me->query_str();
        dp = defense_power(target, "parry") + target->query_dex();

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 9;
                msg += HIR "$n" HIR "面对$P" HIR "这排山倒海攻势，完全"
                       "无法抵挡，唯有退后。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "凝神应战，竭尽所能化解$P" HIC
                       "这几掌。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count / 3, me);

        addn("neili", -300, me);
        addn("qi", -100, me);//WhyIdon'tusereceive_damage?
                                // Becuase now I was use it as a cost
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }

        me->start_busy(1 + random(5));
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count / 3, me);

        return 1;
}
