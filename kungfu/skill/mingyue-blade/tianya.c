// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "天涯"HIW"明月" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, wn;
        int delta;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("mingyue-blade", 1) < 200)
                return notify_fail("你天涯明月刀不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 280 )
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的内力修为不够，难以施展" + name() + "。\n");

        if( query("neili", me)<600 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "mingyue-blade")
                return notify_fail("你没有激发天涯明月刀，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        msg = HIC "$N" HIC "手中的 " + weapon->name() +  HIC "悄然探出，变化中突然收劲，$n一时不查，身形顿时被$N的" + weapon->name() + HIC"吸住，\n"
                  "只听$N一声轻蔑的哼声，" + weapon->name() + HIC"从$n头顶位置闪电下劈！\n "NOR;

        ap = attack_power(me, "blade");
        dp = defense_power(target, "dodge");

        delta = ABILITY_D->check_ability(me, "ap_power-myd-tianya"); // 门派ab
        if( delta ) ap += ap*delta/100;
        
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                damage+= random(damage);
                
                delta = ABILITY_D->check_ability(me, "da_power-myd-tianya"); // 门派ab
                if( delta ) damage += damage*delta/100;
        
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           HIR "$n" HIR "顿时大惊失色，呆若木鸡,避无可避，"
                                           "顿时被砍得血肉模糊，鲜血崩流！\n" NOR);
                addn("neili", -500, me);
                addn("shen", -100, me);
        } else
        {
                me->start_busy(3);
                msg += HIC "$p" HIC "见$P来势汹涌，心知绝不可挡，当即向后横移数尺，终于躲闪开来。\n" NOR;
                addn("neili", -400, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
