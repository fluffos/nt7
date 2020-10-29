// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "祭血神刀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int fmsk = me->query_skill("xueying-dafa", 1);
        
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不对，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 160)
                return notify_fail("你的血刀大法还不到家，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你没有激发血刀大法为刀法，难以施展" + name() + "。\n");

        if( query("qi", me)<100 )
                return notify_fail("你目前气血翻滚，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你目前真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = attack_power(me, "blade");
        dp = defense_power(target, "force");

        msg = HIR "$N" HIR "挥刀向左肩一勒，血珠顿时溅满刀面，紧接着右臂"
              "抡出一片血光向$n" HIR "当头劈落。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                addn("neili", -150, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + fmsk / 8,
                                           HIR "$n" HIR "只见血刀疾闪，眼前一阵血"
                                           "红，刀刃劈面而下，鲜血飞溅，不禁惨声"
                                           "大嚎！\n" NOR);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$n" CYN "侧身避让，不慌不忙，躲过了$N"
                       CYN "的必杀一刀。\n"NOR;
                addn("neili", -100, me);
        }
        me->receive_wound("qi", 50);
        message_combatd(msg, me, target);
        return 1;
}
