#include <ansi.h>
#include <combat.h>

#define YANG "「" HIY "破阳刀" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
  
        me = this_player();

        if( userp(me) && !query("can_perform/poguang-dao/yang", me) )
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YANG "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不对，难以施展" YANG "。\n");

        if ((int)me->query_skill("poguang-dao", 1) < 120)
                return notify_fail("你破光刀法不够娴熟，难以施展" YANG "。\n");

        if (me->query_skill_mapped("blade") != "poguang-dao")
                return notify_fail("你没有激发破光刀法，难以施展" YANG "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，难以施展" YANG "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你现在的真气不够，难以施展" YANG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();
                           
        msg = HIW "\n$N" HIW "一声怒喝，内劲瀑涨，施展出绝招「" HIY "破阳刀" HIW 
              "」手中" + wn + HIW "出神般的挥舞而出，虽然招式看似简单，但其中却"
              "蕴藏着无穷的威力，有如神助一般。" NOR;

        message_sort(msg, me, target);

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                 msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                          HIR "$n" HIR "见$N" HIR "来势凶猛，刀"
                                          "光闪烁，惊骇间肩膀已中一刀，一股鲜血" 
                                          "喷涌而出。\n" NOR);
                 me->start_busy(2 + random(4));
                 addn("neili", -200, me);
        } else
        {
                 msg = CYN "然而$n" CYN "以快制快，侧身"
                      "一跳，躲过这招。\n" NOR;

                 me->start_busy(2);
                 addn("neili", -180, me);
        }
        message_combatd(msg, me, target);

        return 1;
}


