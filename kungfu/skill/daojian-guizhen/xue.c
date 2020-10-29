// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "天下有" HIR "血" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string type, msg;
        object weapon, weapon2;
        int i, count, damage;
        int ap, dp;

        if (me->query_skill("daojian-guizhen", 1) < 200)
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        type=query("skill_type", weapon);

        if (me->query_skill(type, 1) < 250)
                return notify_fail("你的" + to_chinese(type) + "太差，"
                                   "难以施展" + name() + "。\n");

        if (me->query_skill_mapped(type) != "daojian-guizhen")
                return notify_fail("你没有激发刀剑归真，难以施展" + name() + "。\n");

        if (me->query_skill("daojian-guizhen", 1) < 250)
                return notify_fail("你的剑归真等级不够，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "手中" + weapon->name() + HIW "蓦地一抖"
              "，将「" NOR + WHT "胡家刀法" HIW "」并「" NOR + WHT
              "苗家剑法" HIW "」连环施出。霎时寒\n光点点，犹如夜陨"
              "划空，铺天盖地罩向$n" HIW "，正是一招「" HIW "天下"
              "有" HIR "血" HIW "」。\n" NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIW "$n" HIW "只见无数刀光剑影向自己逼"
                       "来，顿感眼花缭乱，心底寒意油然而生。\n" NOR;
                count = ap / 15;
                set_temp("daojian-guizhen/max_pfm", 1, me);
        } else
        {
                msg += HIG "$n" HIG "突然发现自己四周皆被刀光"
                       "剑影所包围，心知不妙，急忙小心招架。\n" NOR;
                count = ap / 30;
        }
        message_combatd(msg, me, target);

        addn("neili", -300, me);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count*2/3, me);

        for (i = 0; i < 12; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count*2/3, me);
        delete_temp("daojian-guizhen/max_pfm", me);
        me->start_busy(2 + random(2));
        return 1;
}
