// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define XIAO "「" HIW "龙啸九天" NOR "」"

int can_not_hubo() { return 1;}

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, count;
        int i, damage;
        mapping buff;
        int time;
        int delta, delta2;

/*
        if( query("family/family_name", me) != "丐帮" )
                return notify_fail("你不是丐帮弟子，无法使用" XIAO "。\n");
*/

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAO "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(XIAO "只能空手使用。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 1000)
                return notify_fail("你降龙十八掌火候不够，难以施展" XIAO "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你没有激发降龙十八掌，难以施展" XIAO "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你没有准备降龙十八掌，难以施展" XIAO "。\n");

        if ((int)me->query_skill("force") < 1200)
                return notify_fail("你的内功修为不够，难以施展" XIAO "。\n");

        if( query("max_neili", me)<30000 )
                return notify_fail("你的内力修为不够，难以施展" XIAO "。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你现在的真气不足，难以施展" XIAO "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
        if( objectp(weapon=query_temp("weapon", target)) )
        {
                msg = HIW "$N" HIW "暴喝一声，全身内劲迸发，气贯右臂奋力外扯，企图将$n"
                      HIW "的" + weapon->name() + HIW "吸入掌中。\n" NOR;

                ap = attack_power(me, "strike");
                dp = defense_power(target, "parry");

                delta = ABILITY_D->check_ability(me, "ap_power-xlz-xiao"); // 门派ab
                if( delta ) ap += ap*delta/100;

                if (ap / 2 + random(ap) > dp)
                {
                        addn("neili", -300, me);
                        msg += HIR "$n" HIR "只觉周围气流涌动，手中" + weapon->name() +
                               HIR "竟然拿捏不住，向$N" HIR "掌心脱手飞去。\n" NOR;

                        weapon->move(environment());
                } else
                {
                        addn("neili", -200, me);
                        msg += CYN "$n" CYN "只觉周围气流涌动，慌忙中连将手中" + weapon->name() +
                               CYN "挥舞得密不透风，使得$N" CYN "无从下手。\n" NOR;
                }
                message_combatd(msg, me, target);
        }

        msg = WHT "忽然$N" WHT "身形激进，施出降龙十八掌之「" HIW "震惊百里" NOR +
              WHT "」，全身真气鼓动，双掌如排山倒海般压向$n" WHT "。\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);
     damage+= damage / 300 * me->query_str();
     damage = damage / 10;

        delta = ABILITY_D->check_ability(me, "ap_power-xlz-xiao"); // 门派ab
        if( delta ) ap += ap*delta/100;
        delta2 = ABILITY_D->check_ability(me, "da_power-xlz-xiao"); // 门派ab
        if( delta2 ) damage += damage*delta2/100;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 200,
                                           HIR "$n" HIR "只觉一股罡风涌至，根本不"
                                           "及躲避，$N" HIR "双掌正中前胸，鲜血如"
                                           "箭般喷出。\n" NOR);
                target->set_weak(5);
                addn("neili", -400, me);
        } else
        {
                msg += CYN "$n" CYN "眼见$N" CYN "来势汹涌，丝毫不"
                       "敢小觑，急忙闪在了一旁。\n" NOR;
                addn("neili", -200, me);
        }

        message_combatd(msg, me, target);

        msg = HIY "紧跟着$N" HIY "施出降龙十八掌「" HIW "飞龙在天"
              HIY "」，双掌翻滚，宛如一条神龙攀蜒于九天之上。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if( delta ) ap += ap*delta/100;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "面对$N" HIR "这排山倒海般的攻"
                       "势，完全无法抵挡，招架散乱，连连退后。\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIC "$n" HIC "心底微微一惊，心知不妙，急忙"
                       "凝聚心神，竭尽所能化解$N" HIC "数道掌力。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count/3, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy())
                        target->start_busy(5);

                COMBAT_D->do_attack(me, target, 0, TYPE_LINK);
        }
        addn("neili", -300, me);
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count/3, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if( delta ) ap += ap*delta/100;

        msg = HIW "$N" HIW "右掌斜挥，前招掌力未消，此招掌力又到，竟然又攻出一招「" HIR "亢龙有悔" HIW "」，掌夹风势，势如破竹，\n"
              HIW "便如一堵无形气墙，向前疾冲而去。$n" HIW "只觉气血翻涌，气息沉浊。\n" NOR;
        
        addn("neili", -400-random(600), me);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage * 3;
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 280 + random(20),
                                          HIR "结果$p躲闪不及，$P掌劲顿时穿胸而"
                                          "过，顿时口中鲜血狂喷。\n" NOR);
        } else
        {
                msg += HIC "$p眼见来势凶猛，身形疾退，瞬间"
                       "飘出三丈，脱出掌力之外。\n" NOR;
        }
        message_combatd(msg, me, target);

        me->start_busy(3 + random(3));
        
        return 1;
}

