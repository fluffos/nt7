//modify by gladiator

#include <ansi.h>
#include <combat.h>

string name() { return HIY "破" HIG "定" HIC "军" HIW "山" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, weapon2;
        int damage, i, n;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword"
                 && query("skill_type", weapon) != "blade" )
                        return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");

        if (me->query_skill("daojian-guizhen", 1) < 300)
                return notify_fail("你的刀剑归真不够娴熟，不会使用" + name() + "。\n");

        if (me->query_skill("force") < 350)
                return notify_fail("你的内功修为不够高。\n");

        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用" + name() + "。\n");


        msg = HIC "$N" HIC "大吼一声，双手横握" + weapon->name() +
              HIC "，长吸一口气，全力向$n" HIC "迅猛劈去！\n\n" NOR;


        if( BUFF_D->check_buff(me, "powerup") )
        {
                msg += HIW + weapon->name() +
                HIW "无边的杀气撕裂空气，武器上所带的寒气仿佛可以冰冻一切，"
                "刃未至而气先及，$n" HIW "眉毛都蒙上了薄薄白霜！\n\n" NOR;
        }

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+=query("jiali", me);

                addn("neili", -600, me);

                if( !objectp(weapon2=query_temp("weapon", target)) )
                {
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                                       HIR "只见$n" HIR "一声惨叫，胸口给"
                                                       "劈开一个巨大的口子，鲜血汹涌喷出！\n" NOR);

                        if (me->query_skill("daojian-guizhen", 1) > 320)
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                           HIB "\n$n" HIB "身形摇晃间，感觉到"
                                                           + weapon->name() + HIB +
                                                           "上一阵刺骨的寒气侵入体内，复又喷出"
                                                           "一口鲜血！\n" NOR);

                        if (me->query_skill("daojian-guizhen", 1) > 350)
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                           HIY "\n$n" HIY "再也坚持不住，几欲晕倒"
                                                           "$N将手中利刃在地上一拖，$N顺势反手往又上"
                                                           "撩了一招，$n毫无防御，伤口再次扩大，\n"
                                                           "又是一股血柱直喷而出！\n" NOR);

                } else
                {
                        if( weapon2->is_item_make() || query("damage", weapon2)>800 ||
                            query("skill_type", weapon2) == "hammer" )
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                                           HIG "$p" HIG "横过" + weapon2->name() + HIG "试图招架，"
                                                           HIG "怎奈这刀气如此犀利，透过" + weapon2->name() +
                                                           HIG "直震得$p" HIG "狂吐鲜血，五脏六腑都要翻转过来！\n\n" NOR);
                        else
                        {
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                                           HIR "$n" HIR "见状不妙，连忙举起" +
                                                           weapon2->name() + HIR + "抵挡，在$N" HIR
                                                           "这霸气无双的一招下，" + weapon2->name() +
                                                           HIR "给震成碎片！\n\n" NOR);
                                n = 3 + random(3);
                                for (i = 0; i < n; i++)
                                {
                                        msg += (random(2) ? HIB : HIC) + "碎片四散飞溅，射入了$n的身体！\n" NOR;

                                        target->receive_damage("qi", damage / 7, me);
                                                target->receive_wound("qi",damage / 15 + random(damage / 15), me);
                                }

                                msg += "\n" + HIY + weapon->name() + HIY "余势未尽，又劈入了$n" + HIY +
                                        "的胸口，$n遭此重创，鲜血狂喷而出！\n" NOR;

                                if( query("material", weapon2) != "tian jing" && random(2) == 1 )
                                {
                                        weapon2->set_name("碎裂的"+query("name", weapon2));
                                        weapon2->move(environment(target));
                                        set("value", 0, weapon2);
                                        set("weapon_prop", 0, weapon2);
                                } else
                                {
                                        weapon2->move(environment(target));
                                        addn("consistence", - 20, weapon2);
                                }
                        }

                        target->reset_action();
                        target->receive_damage("qi", damage / 2, me);
                                               target->receive_wound("qi",
                                               damage / 4 + random(damage / 4), me);

                        if( BUFF_D->check_buff(me, "powerup") )
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 25,
                                                           HIB "\n$n" HIB "身形摇晃间，感觉到"
                                                           + weapon->name() + HIB +
                                                           "上一阵刺骨的寒气侵入体内，复又喷出"
                                                           "一口鲜血！\n" NOR);
                }
                me->start_busy(3);
                target->start_busy(1 + random(2));
        } else
        {
                msg += HIY "$n" HIY "见势不妙，抽身急退，险险避过$N"
                       HIY "的杀招，尘土飞扬中，地上裂开了一道大口子！\n"
                       HIR "$N的头上冒出一颗颗豆大的冷汗，一时之间也无法使出反击的招式！\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
                if( !target->is_busy() )
                        target->start_busy(1 + random(2));
        }

        message_combatd(sort_msg(msg), me, target);

        return 1;
}