// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "神威浩荡" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, cloth;
        int ap, dp, damage;
        string wp;
        string cl;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 240)
                return notify_fail("你的先天功修为不够，难以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不足，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你没有激发先天功为拳脚，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你没有激发先天功为内功，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("你没有准备使用先天功，难以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你现在的真气不足，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "只见$N" HIW "双目精光四射，双掌陡然一振，将体内积蓄的"
              "先天真气云贯推出，顿时呼啸\n声大作，先天劲道层层叠叠，宛如"
              "涛浪般涌向$n" HIW "。\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        msg += HIR "便在$n" HIR "微微一愣间，$N" HIR "罡风已然"
                               "及体，$p" HIR "一声哀嚎，全身骼络尽数断裂。\n"
                               NOR "( $n" RED "受伤过重，已经有如风中残烛，随"
                               "时都可能断气。" NOR ")\n";
                        damage = -1;
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        addn("neili", -400, me);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                                   damage, 90, HIR "$N" HIR "的"
                                                   "罡劲登时瓦解了$n" HIR "的护"
                                                   "体真气，$p" HIR "真元受损，"
                                                   "接连喷出数口鲜血。\n" NOR);

                        if( objectp(weapon=query_temp("weapon", target) )
                            && query("stable", weapon)<100
                            && ap / 3 + random(ap) > dp)
                        {
                                wp = weapon->name();
                                msg += HIW "只听“锵”的一声脆响，$n" HIW "手"
                                       "中的" + wp + HIW "在$N" HIW "内力激荡"
                                       "下应声而碎，脱手跌落在地上。\n" NOR;
                                addn("neili", -150, me);
                                set("consistence", 0, weapon);
                                weapon->move(environment(target));
                        } else
                        if( objectp(cloth=query_temp("armor/armor", target) )
                            && query("stable", cloth)<100
                            && ap / 3 + random(ap) > dp)
                        {
                                cl = cloth->name();
                                msg += HIW "只听“轰”的一声闷响，$n" HIW "身"
                                       "着的" + cl + HIW "在$N" HIW "内力激荡"
                                       "下应声而裂，化成一块块碎片。\n" NOR;
                                addn("neili", -150, me);
                                set("consistence", 0, cloth);
                                cloth->move(environment(target));
                        } else

                        if( objectp(cloth=query_temp("armor/cloth", target) )
                            && query("stable", cloth)<100
                            && ap / 3 + random(ap) > dp)
                        {
                                cl = cloth->name();
                                msg += HIW "只听“轰”的一声闷响，$n" HIW "身"
                                       "着的" + cl + HIW "在$N" HIW "内力激荡"
                                       "下应声而碎，化成一块块碎片。\n" NOR;
                                addn("neili", -150, me);
                                set("consistence", 0, cloth);
                                cloth->move(environment(target));
                        }
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -120, me);
                msg += CYN "可是$p" CYN "知道$P" CYN "这招的厉"
                       "害，不敢硬接，当即斜跃躲避开来。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}