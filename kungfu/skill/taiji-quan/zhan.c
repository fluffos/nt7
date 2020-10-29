// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "粘字诀" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

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

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("你没有激发太极拳，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "连消带打，双手成圆形击出，这"
              "正是太极拳「圆转不断」四字的精意。只\n见$N"
              HIW "随即平圈、立圈、正圈、斜圈，一个跟着一"
              "个，一个个太极圆圈顿时笼\n罩$n" HIW "四面"
              "八方。\n" NOR;

        ap = attack_power(me,"cuff");
        dp = defense_power(target,"parry");
        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -100, me);
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "登时便被套得跌跌撞撞，身"
                                           "不由主的立足不稳，犹如中酒昏迷。\n"
                                           NOR);
                me->start_busy(2);
                if (ap / 2 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(3 + ap / 80);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的企图，巧妙的拆招，没露半点破绽"
                       "。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
