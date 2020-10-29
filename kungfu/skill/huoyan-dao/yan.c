// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "天寰神炎" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int skill;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手才能施展" + name() + "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，无法施展" + name() + "。\n");

        if (skill = me->query_skill("huoyan-dao", 1) < 150)
                return notify_fail("你的火焰刀修为不够，无法施展" + name() + "。\n");

        if( query("neili", me)<600 || query("max_neili", me)<2000 )
                return notify_fail("你的真气不够，无法施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("你没有激发火焰刀，无法施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "huoyan-dao")
                return notify_fail("你没有准备火焰刀，无法施展" + name() + "。\n");

        if (me->query_skill_prepared("hand") == "dashou-yin")
                return notify_fail("施展" + name() + "时火焰刀不宜和密宗大手印互背！\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "一声怒嚎，狂催真气注入单掌，掌缘顿时腾起一道烈炎，接二连三朝$n"
              HIR "劈去。\n" NOR;
        message_combatd(msg, me, target);

        addn("neili", -500, me);

        addn_temp("apply/attack", skill/3, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", skill/3, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", skill/3, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", skill/3, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        addn_temp("apply/attack", skill/3, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // 消除攻击修正
        addn_temp("apply/attack", -skill*5/3, me);

        me->start_busy(1 + random(3));

        return 1;
}

