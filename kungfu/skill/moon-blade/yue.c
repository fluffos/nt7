#include <ansi.h>
#include <combat.h>

string name() { return HIY "当时明月在" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
        int fmsk = me->query_skill("motun-tianxia", 1);
        
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

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("moon-blade", 1) < 120)
                return notify_fail("你的圆月弯刀还不到家，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "moon-blade")
                return notify_fail("你没有激发圆月弯刀，难以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "刀气横空，刀光烁闪，连环七刀，每刀均令$n" HIY "不得不全神应付，\n"
              "每刀均是朴实古拙，偏又有，明月当空的感觉。\n"
              "且刀刀均针对$n" HIY "的身形变化，似是把$n" HIY "看通看透一般！\n" NOR;

        ap = attack_power(me, "blade") + me->query_skill("force", 1);
        ap += ap * (fmsk/100)* 5 / 100;
        dp = defense_power(target, "force") + target->query_skill("force", 1);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+= query("jiali", me);
                damage *= 3;
                damage += damage * (fmsk/100)* 5 / 100;
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 600,
                                           HIR "霎时一股冰寒的刀气掠过全身，$n"
                                           HIR "全身顿时鲜血淋漓，摇摇欲倒！\n" NOR);
                me->start_busy(2);
                if (ap / 2 + random(ap * 2) > dp && ! target->is_busy())
                        target->start_busy(ap / 80 + 3);
        } else
        {
                msg += CYN "$p" CYN "大吃一惊，也不招架，当即向后"
                       "横移数尺，避开了$P" CYN "这一招。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

