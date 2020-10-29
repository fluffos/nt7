#include <ansi.h>
#include <combat.h>

#define XING "「" HIR "穹外飞星" NOR "」"

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
        mapping buff, data;
        int skill, i, p, n;
        mixed my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XING "只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你现在手中没有拿着暗器，难以施展" XING "。\n");

        if (weapon->query_amount() < 15)
                return notify_fail("至少要有十五枚暗器才能施展" XING "。\n");

        if ((skill = me->query_skill("mantian-xing", 1)) < 80)
                return notify_fail("你的满天星不够娴熟，难以施展" XING "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功修为不足，难以施展" XING "。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的内力修为不足，难以施展" XING "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你现在真气不足，难以施展" XING "。\n");

        if( BUFF_D->check_buff(target, "mtx_xing") ) 
                return notify_fail("对方已经中了你的绝招，现在是废人一个，赶快进攻吧！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        addn("neili", -100, me);
        weapon->add_amount(-15);

        msg = HIR "$N" HIR "蓦地飞身跃起，十指箕张，施出「穹外飞星」将"
              "手中" + weapon->name() + HIR "尽数凌空射出。\n霎时破空声"
              "骤响，" + weapon->name() + HIR "便如同陨星飞坠一般，笼罩"
              "$n" HIR "各处大穴！\n" NOR;

        my_exp=attack_power(me, "throwing");
        ob_exp=defense_power(target, "dodge");

        //me->want_kill(target);
        if (my_exp / 2 + random(my_exp * 3 / 2) > ob_exp)
        {
                if (target->query_skill("parry") < me->query_skill("throwing"))
                {
                        n = 2 + random(2);
                        if (random(my_exp) > ob_exp) n += 1 + random(2);
                        if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
                        if (random(my_exp / 4) > ob_exp) n += 1 + random(2);

                        msg += HIR "结果$n" HIR "一声惨叫，同时中了$P" HIR +
                               chinese_number(n)+query("base_unit", weapon)+
                               weapon->name() + HIR "，直感两耳轰鸣，目不视"
                               "物。\n" NOR;

                        while (n--)
                        {
                                COMBAT_D->clear_ahinfo();
                                weapon->hit_ob(me, target,
                                               query("jiali", me)+100+n*10);
                        }

                        set_temp("feixing", 1, target);
                        data = ([
                                "attack": -skill/4, 
                                "defense": -skill/4, 
                        ]);
                        buff = ([
                                "caster": me,
                                "target": target,
                                "type"  : "mtx_xing",
                                "attr"  : "curse",
                                "name"  : "满天星·穹外飞星",
                                "time"  : skill/15,
                                "buff_data": data,      
                                "buff_msg" : "",
                                "disa_msg" : HIY "渐渐的你觉得力气一丝丝的恢复了。\n" NOR,
                        
                        ]);
                        BUFF_D->buffup(buff);
                        
                        target->receive_damage("qi", skill, me);
                        target->receive_wound("qi", skill/2, me);

                        p=query("qi", target)*100/query("max_qi", target);

                        if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                                msg += pmsg;

                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);

                        tell_object(target, RED "你现在要穴受到重损，乃至全身"
                                            "乏力，提不上半点力道！\n" NOR);
                        tell_object(me, HIC "你心知刚才这招已打中对方要寒，不"
                                            "禁暗自冷笑。\n" NOR);
                } else
                {
                        msg += HIR "$n" HIR "集中生智，双手画圈回旋挥舞，拨弄"
                               "开了要害处的杀着，可还是受了点轻伤。\n" NOR;

                        target->receive_damage("qi", skill);
                        target->receive_wound("qi", skill/2);

                        p=query("qi", target)*100/query("max_qi", target);
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                        message_combatd(msg, me, target);

                        tell_object(target, RED "你只觉全身几处一阵刺痛，知道"
                                            "自己虽被击中，但却是避开了要穴。"
                                            "\n" NOR);
                        //target->kill_ob(me);
                        me->start_busy(1 + random(2));
                }
        } else
        {
                 msg += CYN "可是$n" CYN "小巧腾挪，好不容易避开了"
                        CYN "$N" CYN "铺天盖地的攻击。\n" NOR;
                 me->start_busy(3);
                 message_combatd(msg, me, target);
        }
        return 1;
}
