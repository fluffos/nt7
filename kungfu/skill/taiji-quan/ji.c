#include <ansi.h>
#include <combat.h>

string name() { return HIW "挤字诀" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;
        int delta;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        skill = me->query_skill("taiji-quan", 1);

        if (skill < 150)
                return notify_fail("你的太极拳等级不够，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("你没有激发太极拳，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "taiji-quan")
                return notify_fail("你现在没有准备使用太极拳，无法使用" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "使出太极拳「挤」字诀，右脚实，左脚虚，粘连粘"
              "随，右掌已搭住$n" HIW "左腕，横劲发出。\n" NOR;

        damage = damage_power(me,"cuff");
        damage+= query("jiali", me);

        ap = attack_power(me,"cuff");
        dp = defense_power(target,"parry");
        
        delta = ABILITY_D->check_ability(me, "ap_power-tjq-ji"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        delta = ABILITY_D->check_ability(me, "da_power-tjq-ji"); // 门派ab
        if( delta ) damage += damage*delta/100;
        
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -30, me);
                me->start_busy(2);
                target->receive_damage("jing", damage);
                target->receive_wound("jing", damage);
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK,
                       damage, 40, HIR "$n" HIR "稍不留神，让$N" HIR
                       "这么一挤，只觉全身力气犹似流入汪洋大海，无影"
                       "无踪。\n" NOR);
        }
        else
        {
                addn("neili", -10, me);
                msg += CYN "$n" CYN "见状大吃一惊，急忙向后猛退数步，"
                       "终于避开了$N" CYN "这一击。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}