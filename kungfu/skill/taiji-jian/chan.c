// This program is a part of NITAN MudLIB
// chan.c 缠字诀

#include <ansi.h>

string name() { return "缠字诀"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「" + name() + "」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("必须拿剑才能施展「" + name() + "」。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if( query("neili", me)<query("max_neili", me)/50 )
                return notify_fail("你的内力不足以施展「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 100)
                return notify_fail("你的太极神功火候不够，难以施展「" + name() + "」。\n");

        if (me->query_skill("taiji-jian", 1) < 100)
                return notify_fail("你的太极剑法不够娴熟，不会使用「" + name() + "」。\n");

        msg = HIG "$N使出太极剑法「缠」字诀，先是连递数个虚招企图扰乱$n的攻势。\n"
              HIG "忽然手中" + weapon->name() + HIG "划出一个个圆圈，神在剑先，"
              HIG "绵绵不绝，便如撒出了一张大网，逐步向$n收紧。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -query("max_neili", me)/50, me);
                msg += HIC "\n结果太极剑意散发出的细丝越积越多，似是积成了一团团丝棉，将$p紧紧裹了起来！\n" NOR;
                target->start_busy(ap / 80 + 3);
                me->start_busy(1);
        } else
        {
                addn("neili", -query("max_neili", me)/80, me);
                msg += HIY "\n可是$p看破了$P的企图，纵身一跃，已逃出圈外。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

int help(object me)
{
        write(WHT"\n太极剑「缠字诀」："NOR"\n");
        write(@HELP
        太极剑意圆转不断，连绵不绝，临敌人之际以意驭剑，使出「缠」字诀每发
        一招，便似放出一条细丝，缠住对手，千变万化，无穷无尽，使其无法动作，
        并且可以自动不断连续发出，直至击败对手。

        要求：  最大内力 1000 以上；
                内力 500 以上；
                太极剑等级 100 以上；
                技法太极剑为招架；
                并未设制打不还手。
HELP
        );
        return 1;
}