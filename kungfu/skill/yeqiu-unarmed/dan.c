// This is player's own perform (Write by Lonely@nt2)
// Create by 星云锁链(Fuyuan) at Thu Mar  5 07:38:01 2015
// 鸡飞蛋打(dan)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "鸡飞蛋打" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int attack;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (member_array("unarmed", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "unarmed" )
                        return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("yeqiu-unarmed", 1) < 400)
                return notify_fail("你" + to_chinese("yeqiu-unarmed") + "不够娴熟，难以施展" + name() + "。\n");

        if (member_array("unarmed", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("unarmed") != "yeqiu-unarmed")
                        return notify_fail("你没有准备" + to_chinese("yeqiu-unarmed") + "，难以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N从裤兜里摸出两枚鸡蛋攥在手里，冲着$n嘿嘿阴笑几声，然后用力一捏，$n浑身一震，打一哆嗦，被$N近身在下阴狠狠踢了一脚。" + "\n" + NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "unarmed");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 90, HIM "结果$n闪避不及，被$N的踹得眼仁泛白，嘴歪眼斜，半天动弹不得。" + "\n" NOR);
                addn("neili", -200, me);
                me->start_busy(1);
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "可是$p识破了$P这一招，趁势向后一跃避开。" + "\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_sort(msg, me, target);
        return 1;
}
