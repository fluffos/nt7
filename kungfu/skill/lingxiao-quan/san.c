#include <ansi.h>
#include <combat.h>

string name() { return HIR "神倒鬼跌三连环" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
        object weapon;
        string wname;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" + name() + "。\n");

        if (me->query_skill("force") < 250)
                return notify_fail("你的内功修为不够，难以施展" + name() + "。\n");

        if ((int)me->query_skill("lingxiao-quan", 1) < 180)
                return notify_fail("你的凌霄拳法不够娴熟，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "lingxiao-quan")
                return notify_fail("你没有激发凌霄拳法，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "lingxiao-quan")
                return notify_fail("你现在没有准备使用凌霄拳法，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        damage = damage_power(me, "cuff");
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "parry");
        msg = HIR "$N" HIR "微微一笑，施出「神倒鬼跌三连环」，右手探出，直揪$n"
              HIR "后颈。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$P" HIR "出手既快，方位又奇，$p"
                                           HIR "如何避得，当即被$N" HIR "揪住，"
                                           "重重的摔在地上！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "见势不妙，急忙凝力稳住，右臂挥出，格开$P"
                       CYN "手臂。\n" NOR;
        }

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        msg += "\n" HIR "紧接着$N" HIR "“噫”的一声，左手猛然探出，如闪电般抓向$n"
               HIR "的前胸。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "$p" HIR "只觉胸口一麻，已被$P"
                                           HIR "抓住胸口，用力顺势一甩，顿时平"
                                           "平飞了出去！\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "丝毫不为$P"
                       CYN "所动，奋力格挡，稳稳将这一招架开。\n" NOR;
        }

        attack_power(me, "cuff");
        dp = defense_power(target, "force");
        msg += "\n" HIR "又见$N" HIR "身子一矮，将力道聚于腿部，右脚猛扫$n"
               HIR "下盘，左脚随着绊去。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "结果$p" HIR "稍不留神，顿时给$P"
                                           HIR "绊倒在地，呕出一大口鲜血！\n" NOR);
        } else
        {
                msg += CYN "然而$p" CYN "沉身聚气，稳住下盘，身子一幌，没给$P"
                       CYN "绊倒。\n" NOR;
        }
        me->start_busy(2 + random(3));
        addn("neili", -200, me);
        message_combatd(msg, me, target);
        return 1;
}
