#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, jing_wound;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「域外梵音」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("tanqin-jifa", 1) < 120)
                return notify_fail("你的弹琴技法尚且不够熟练, 发不出「域外梵音」！\n");

        if (me->query_skill("kunlun-jian", 1) < 120)
                return notify_fail("你的昆仑剑法等级不够, 发不出「域外梵音」！\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的内力修为尚且无法达到使用「域外梵音」所需的境界！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，运足「域外梵音」所需的内力！\n");

        msg = MAG "$N微微一笑，左手横握剑柄，右手五指对准" + weapon->name() + NOR + MAG"剑脊轻轻弹拨，剑身微颤，声若龙吟。\n顿时发出一阵清脆的琴音......\n" NOR;

        skill = me->query_skill("kunlun-jian",1);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                jing_wound = damage_power(me, "sword") +
                           (int)me->query_skill("tanqin-jifa", 1) * 2;

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, jing_wound, 70,
                                           MAG "$n顿时只觉琴音犹如两柄利剑一般刺进双耳，刹那间头晕目眩，全身刺痛！\n" NOR);
                me->start_busy(2 + random(2));
        } else
        {
                addn("neili", -50, me);
                msg += HIG "可是$n赶忙宁心静气，收敛心神，丝毫不受$N琴音的干扰。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
