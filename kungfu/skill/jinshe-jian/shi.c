#include <ansi.h>
#include <combat.h>

#define SHEN "「" HIY "金蛇噬天" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHEN "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对，难以施展" SHEN "。\n");

        if ((int)me->query_skill("jinshe-jian", 1) < 200)
                return notify_fail("你金蛇剑法不够娴熟，难以施展" SHEN "。\n");

        if (me->query_skill_mapped("sword") != "jinshe-jian")
                return notify_fail("你没有激发衡山五神剑，难以施展" SHEN "。\n");

        if ((int)me->query_skill("force", 1) < 240)
                return notify_fail("你的内功火候不够，难以施展" SHEN "。\n");

        if ((int)me->query_skill("dodge", 1) < 240)
                return notify_fail("你的轻功火候不够，难以施展" SHEN "。\n");  

        if( query("max_neili", me)<4500 )
                return notify_fail("你的内力修为不足，难以施展" SHEN "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你现在的真气不够，难以施展" SHEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        msg = HIY "一道金光划过，$N" HIY "消失得无影无踪，猛然间只见一条"
              "金蛇从天而下，" + weapon->name() + HIY "已将$n" HIY "笼罩。\n" NOR;

        message_sort(msg, me, target);
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                if( me->query_family() == "五毒教" )
                        damage *= 3;

                // 十分之一的几率可被招架
                if (random(10) <= 1 && ap / 2 < dp)
                {
                        damage = damage / 3;

                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                                  HIG "$n" HIG "见$N" HIG "一道金光闪过"
                                                  "，急忙收敛心神奋力招架。哪知$P这"
                                                  "招力道非凡，$p一声闷哼，连退几步，喷"
                                                  "出一口鲜血。\n" NOR);
                        addn("neili", -200, me);
                        me->start_busy(3 + random(2));
                } else 
                {
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                                  HIR "$n" HIR "见$N" HIR "金光划过，心"
                                                  "底不由大惊，登时听得“噗嗤”一声，剑"
                                                  "气透体而过。\n" NOR);
                        addn("neili", -300, me);
                        me->start_busy(2 + random(3));
                }
        } else
        {
                msg = CYN "\n然而$n" CYN "以快对快，飞身一跳"
                      "已然躲过$N" CYN "这一招。\n" NOR;
                addn("neili", -150, me);
                me->start_busy(2);
        }
        message_sort(msg, me, target);
        return 1;
}
