// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "无影神拳" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;
        int delta;
        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必须空手才能施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "shenzhaojing")
                return notify_fail("你没有激发神照经神功为空手技能，无法施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "shenzhaojing")
                return notify_fail("你现在没有准备使用神照经神功，无法施展" + name() + "。\n");

        if ((int)me->query_skill("shenzhaojing", 1) < 200)
                return notify_fail("你的神照经神功火候不够，无法施展" + name() + "。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的基本拳脚火候不够，无法施展" + name() + "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的内力修为不足，无法施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真气不够，无法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "倏然跃近，无声无影击出一拳，去势快极，拳影重"
              "重叠叠，直袭$n" HIR "而去。\n"NOR;

        lvl = me->query_skill("shenzhaojing", 1);

        ap=attack_power(me,"force")+me->query_con()*10;
        dp=defense_power(target,"force")+target->query_con()*10;
        
        delta = ABILITY_D->check_ability(me, "ap_power-szj-ying"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");
                damage+= query("jiali", me);
                
                delta = ABILITY_D->check_ability(me, "da_power-szj-ying"); // 门派ab
                if( delta ) damage += damage*delta/100;
        
                addn("neili", -400, me);
                target->affect_by("shenzhao", ([
                        "level":query("jiali", me)+random(query("jiali", me)),
                        "id":query("id", me),
                        "duration" : lvl / 50 + random(lvl / 20) ]));
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK,
                               damage, 90, HIR "$n" HIR "见拳势变换莫测，只是"
                               "微微一愣，已被$N" HIR "一拳正中胸口，神照经内"
                               "劲顿\n时便如山洪爆发一般，透体而入。\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "来势汹涌，急忙提气跃开。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
