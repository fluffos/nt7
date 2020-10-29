// pi.c 开天辟地

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "开天辟地"; }

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;
        int n;
        int delta;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「开天辟地」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("运用「开天劈地」手中必须有刀！\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 600)
                return notify_fail("你的胡家刀法不够娴熟，不会使用「开天辟地」。\n");

        if ((int)me->query_skill("force") < 650)
                return notify_fail("你的内功修为不够高。\n");

        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用「开天劈地」。\n");

        msg = HIC "$N" HIC "一声长笑，双手紧握" + weapon->name() +
              HIC "刀柄，长吸一口气，全力向$n" HIC "迅猛劈去！\n\n"NOR;

        //if( query_temp("hu/freeze", me) )
        if (query_temp("lengyue-shengong_freeze", target))
        {
                msg += HIW + weapon->name() +
                HIW "寒气逼人，刀身撕裂空气，片片雪花飘落，刀未至气先及，$n" HIW "眉毛都蒙上了薄薄白霜！\n\n"NOR;
        }

        ap = attack_power(me, "blade") + me->query_skill("force");
        if (living(target))
                 dp = target->query_skill("force") + defense_power(target, "parry");
        else     dp = 0;

        delta = ABILITY_D->check_ability(me, "ap_power-hjdf-pi"); 
        if( delta ) ap += ap*delta/100;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+=query("jiali", me);
                delta = ABILITY_D->check_ability(me, "da_power-hjdf-pi"); // 门派ab
                if( delta ) damage += damage*delta/100;
                addn("neili", -damage/2, me);
                if( !objectp(weapon2=query_temp("weapon", target)) )
                {
                        /*
                        target->receive_damage("qi",damage,me);
                        target->receive_wound("qi",damage/2 + random(damage/2),me);
                        msg += HIR "只见$n" HIR "一声惨叫，胸口给"
                                "劈开一个巨大的口子，鲜血汹涌喷出！\n"NOR;
                        if( query_temp("hu/freeze", me) )
                        {
                                damage /= 3;
                                target->receive_damage("qi",damage,me);
                                target->receive_wound("qi",damage/2 + random(damage/2),me);
                                msg += HIR "\n$n" HIR "身形摇晃间，感觉到"
                                        + weapon->name() + HIR +
                                        "上一阵刺骨的寒气侵入体内，复又喷出一口鲜血！\n" NOR;
                        }
                        */
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                                       HIR "只见$n" HIR "一声惨叫，胸口给"
                                                       "劈开一个巨大的口子，鲜血汹涌喷出！\n" NOR);

                        if (query_temp("lengyue-shengong_freeze", target))
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                           HIB "\n$n" HIB "身形摇晃间，感觉到"
                                                           + weapon->name() + HIB +
                                                           "上一阵刺骨的寒气侵入体内，复又喷出"
                                                           "一口鲜血！\n" NOR);
                } else
                {
                        /*
                        msg += HIR "$n" HIR "见状不妙，连忙举起" + weapon2->name() + HIR +
                                "抵挡，在$N这霸气无边的一招下，" + weapon2->name() + HIR +
                                "给震成碎片！\n" NOR;
                        for (i = 0;i < 2 + random(5);i++)
                        {
                                msg += HIB "碎片四散飞溅，射中了$n的身体！\n" NOR;
                                target->receive_damage("qi",damage/7,me);
                                        target->receive_wound("qi",damage/15 + random(damage/15),me);
                        }
                        msg += HIR + weapon->name() + HIR "余势未尽，又劈入了$n" + HIR +
                                "的胸口，$n遭此重创，鲜血狂喷而出！\n" NOR;

                        if( !weapon2->is_item_make() )
                        {
                                weapon2->set_name("碎裂的"+query("name", weapon2));
                                weapon2->move(environment(target));
                                set("value", 0, weapon2);
                                set("weapon_prop", 0, weapon2);
                        }
                        else
                                weapon2->move(environment(target));
                        */
                        if (weapon2->is_item_make() || weapon2->query("damage") > 800 ||
                            weapon2->query("skill_type") == "hammer")
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                                           HIG "$p" HIG "横过" + weapon2->name() + HIG "试图招架，"
                                                           HIG "怎奈这刀气如此犀利，透过" + weapon2->name() +
                                                           HIG "直震得$p" HIG "狂吐鲜血，五脏六腑都要翻转过来！\n\n" NOR);
                        else
                        {
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                                           HIR "$n" HIR "见状不妙，连忙举起" +
                                                           weapon2->name() + HIR + "抵挡，在$N" HIR
                                                           "这霸气无双的一招下，" + weapon2->name() +
                                                           HIR "给震成碎片！\n\n" NOR);
                                n = 2 + random(5);
                                for (i = 0; i < n; i++)
                                {
                                        msg += (random(2) ? HIB : HIC) + "碎片四散飞溅，射入了$n的身体！\n" NOR;

                                        target->receive_damage("qi", damage / 7, me);
                                                target->receive_wound("qi",damage / 15 + random(damage / 15), me);
                                }

                                msg += "\n" + HIY + weapon->name() + HIY "余势未尽，又劈入了$n" + HIY +
                                        "的胸口，$n遭此重创，鲜血狂喷而出！\n" NOR;

                                weapon2->set_name("碎裂的" + weapon2->query("name"));
                                weapon2->move(environment(target));
                                weapon2->set("value", 0);
                                weapon2->set("weapon_prop", 0);
                        }
                        target->reset_action();
                        target->receive_damage("qi",damage/2,me);
                                        target->receive_wound("qi",damage/4 + random(damage/4),me);

                        /*
                        if( query_temp("hu/freeze", me) )
                        {
                                damage /= 4;
                                target->receive_damage("qi",damage,me);
                                target->receive_wound("qi",random(damage),me);
                                msg += HIR "\n$n" HIR "身形摇晃间，感觉到"
                                        + weapon->name() + HIR +
                                        "上一阵刺骨的寒气侵入体内，复又喷出一口鲜血！\n" NOR;
                        }
                        */
                        if (target->query_temp("lengyue-shengong_freeze"))
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                                           HIB "\n$n" HIB "身形摇晃间，感觉到"
                                                           + weapon->name() + HIB +
                                                           "上一阵刺骨的寒气侵入体内，复又喷出"
                                                           "一口鲜血！\n" NOR);
                }
                /*
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "( $n"+str+" )\n";
                */
                me->start_busy(3);
                if (! target->is_busy()) target->start_busy(1 + random(2));
        } else
        {
                msg += HIY "$n" HIY "见势不妙，抽身急退，险险避过$N"
                       HIY "的这记开天辟地，尘土飞扬中，地上裂开了一道大口子！\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
