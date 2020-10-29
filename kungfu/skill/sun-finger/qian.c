#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "一指乾坤" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("sun-finger", 1) < 100)
                return notify_fail("你一阳指诀不够娴熟，难以施展" + name() + "。\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 160)
                return notify_fail("你对经络学了解不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("你没有激发一阳指诀，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("你没有准备一阳指诀，难以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "陡然使出「" HIR "一指乾坤" HIY "」绝技，单指劲"
              "点$n" HIY "檀中要穴，招式变化精奇之极！\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force") + me->query_skill("qiantian-zhi", 1);
        dp = defense_power(target, "parry") + me->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        damage += damage*n*15/100;
                        msg += HIM"$N"HIM"运用气脉流转的辅助，使得一指乾坤伤害更强。\n"NOR;
                }
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$n" HIR "只觉胸口一麻，已被$N" HIR
                                           "一指点中，顿时气血上涌，喷出数口鲜血"
                                           "。\n" NOR);
                addn("neili", -100, me);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N" CYN "的招"
                       "数，连消带打挡开了这一指。\n" NOR;
                me->start_busy(3);
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
