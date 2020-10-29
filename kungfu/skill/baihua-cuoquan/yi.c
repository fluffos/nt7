// yi.c 百花错易

#include <ansi.h>
#include <combat.h>

#define YI "「" HIW "百花错易" NOR "」"

inherit F_SSERVER;
 
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

        if( userp(me) && !query("can_perform/baihua-cuoquan/yi", me) )
                return notify_fail("你还没有受到高手指点，还不会运用" YI "。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(YI "只能对战斗中的对手使用。\n");
 
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(YI "只能空手施展。\n");
                
        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力的修为不够，现在无法使用" YI "。\n");

        if ((int)me->query_skill("force") < 280)
                return notify_fail("你的内功火候不足，无法使用" YI "。\n");

        if ((int)me->query_skill("baihua-cuoquan", 1) < 150)
                return notify_fail("你的百花错拳火候不够，无法使用" YI "。\n");

        if (me->query_skill_prepared("unarmed") != "baihua-cuoquan")
                return notify_fail("你现在没有准备使用百花错拳，无法使用" YI "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，无法运用" YI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "大喝一声，双掌纷飞，擒拿手中夹着鹰爪功，左手查"
              "拳，右手绵掌。攻出去是\n八卦掌，收回时已是太极拳，诸家杂陈，"
              "毫无规律，铺天盖地向$n" HIW "狂涌而去。\n\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 12;
                msg += HIR "$n" HIR "只见$P" HIR "运拳如奔，快拳缤纷递出，"
                       "顿感头晕目眩，不知该如何抵挡。\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "只见$p" HIY "运拳如奔，快拳缤纷递出，"
                       "连忙振作精神勉强抵挡。\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        addn_temp("apply/attack", count, me);

        addn("neili", -300, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }

        me->start_busy(1 + random(6));
        addn_temp("apply/attack", -count, me);

        return 1;
}
