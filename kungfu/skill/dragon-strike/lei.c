// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "雷霆一击" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手使用。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你内功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你内力修为不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 180)
                return notify_fail("你降龙十八掌火候不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你没有激发降龙十八掌，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你没有准备降龙十八掌，难以施展" + name() + "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "默运内功，施展出" + name() + HIC "，全身急速转动起来，"
              "越来越快，就\n犹如一股旋风，骤然间，$N" HIC "已卷向正看"
              "得发呆的" HIC "$n。\n"NOR;

        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                addn("neili", -400, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85,
                                           HIR "$p" HIR "只见一阵旋风影中陡然现出$P"
                                           HIR "的双拳，根本来不及躲避，被重重击中，\n五"
                                           "脏六腑翻腾不休，口中鲜血如箭般喷出！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIG "可是$p" HIG "看破了$P" HIG "的企图，没"
                       "有受到迷惑，闪在了一边。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
