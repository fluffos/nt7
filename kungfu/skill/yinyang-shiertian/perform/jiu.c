#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "九转乾坤" NOR; }

int perform(object me, object target)
{
        string msg;
        int count;
        int lvl, damage;
        int i, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "只能对战斗中的对手使用。\n");

        if( query("neili", me)<900 )
                return notify_fail("你的真气不够，无法施展" +name()+ "！\n");

        if( query("max_neili", me)<9000 )
                return notify_fail("你的内力修为还不足以使出" +name()+ "。\n");

        if ((int)me->query_skill("force") < 900)
                return notify_fail("你的内功火候不够，难以施展" +name()+ "！\n");

        if ((lvl = (int)me->query_skill("yinyang-shiertian", 1)) < 810)
                return notify_fail("你的阴阳九转十二重天还不够熟练，无法使用" +name()+ "！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        message_combatd(HIM "\n$N" HIM "运起阴阳九转十二重天，仿佛九天神龙翱翔天际，"
                     HIM "正是无上绝学" +name()+ HIM "！\n" NOR, me, target);

        ap = attack_power(me, "force");
        dp = defense_power(target, "dodge") + target->query_skill("yinyang-shiertian", 1);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                message_combatd(HIW "\n$N" HIW "身若游龙，挟风雷之力，从空中向$n"
                                HIW "猛扑下来！\n" NOR, me, target);

                if (ap * 3 / 2 + random(ap) > dp)
                {
                        damage = damage_power(me, "force")*10;
                        if( query_temp("weapon", me) )
                        {
                                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, (i + 1) * 10 ,
                                                          HIR "结果$n" HIR "躲闪不及，$N" HIR
                                                          "的内劲已破体而入，$n喉头一甜，喷出一大"
                                                          "口鲜血。\n" NOR);
                        } else
                        {
                                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, (i + 1) * 10,
                                                          HIR "结果$n" HIR "躲闪不及，$N" HIR
                                                          "的内劲已破体而入，$n喉头一甜，喷出一大"
                                                          "口鲜血。\n" NOR);
                        }
                } else
                {
                        msg = CYN "$n" CYN "气凝双臂，奋力招架，将"
                              "$N" CYN "的内劲卸掉。\n" NOR;
                }

                message_combatd(msg, me, target);

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
        }

        me->start_busy(2 + random(3));
        addn("neili", -1000-random(1000), me);
        return 1;
}

