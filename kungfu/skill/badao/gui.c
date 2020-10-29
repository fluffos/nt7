#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define LONG "「" HIY "归海一刀" NOR "」"

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LONG "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对！\n");

        if ((int)me->query_skill("badao", 1) < 500)
                return notify_fail("你霸刀不够娴熟，无法施展" LONG "。\n");

        if ((int)me->query_skill("force") < 700)
                return notify_fail("你内功火候不够，无法施展" LONG "。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你现在真气不够，无法施展" LONG "！\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("你没有激发霸刀，无法施展" LONG "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "\n$N" HIC "面露苦色，举手一刀，自上而下，刹那间，天地哭嚎，万千刀气犹如潮水海"
              "浪般壮观，铺天盖地的向前卷进，忽然，无数刀气化为一道刀芒，犹如闪电般劈向$n" HIC "。\n" NOR;

        ap=me->query_skill("blade")+me->query_skill("martial-cognize",1);
        dp=target->query_skill("dodge")+target->query_skill("martial-cognize",1);
        if (ap * 4 / 5 + random(ap) > dp)
        {
                me->start_busy(3);
                damage = ap * 3 + random(ap * 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300 + random(100),
                                           HIR "但见那凶猛无比的刀气势如破竹般的从$n" HIR "胸口透射而过，令人毛骨悚然！\n" NOR);
                addn("neili", -1800, me);
        } else
        {
                me->start_busy(3);
                msg += CYN "然而$n" CYN "轻轻一笑，左避右闪，竟将此招化解。\n" NOR;
                addn("neili", -120, me);
        }

        message_combatd(sort_msg(msg), me, target);
        
        return 1;
}
