// This is player's own perform (Write by Lonely@nt2)
// Create by 剑人(Dlf) at Tue Mar  3 12:07:49 2015
// 龙之式(long)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "龙之式" NOR; }

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

        if ((int)me->query_skill("longfeng-unarmed", 1) < 400)
                return notify_fail("你" + to_chinese("longfeng-unarmed") + "不够娴熟，难以施展" + name() + "。\n");

        if (member_array("unarmed", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("unarmed") != "longfeng-unarmed")
                        return notify_fail("你没有准备" + to_chinese("longfeng-unarmed") + "，难以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N双手合结「龙之式」，脚踏阴阳八卦阵,方圆十里美女如云，阵阵美妙的音乐，令$n心神不定，神情恍惚。突然间一圈圈碧芒围向$n，震得$n吐血连连！" + "\n" + NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "unarmed");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 90, HIM "$n尚未回过心神，结果发现$N的「龙之式」强大冲入体内，登感呼吸不畅。乘此良机，$N的强大力道如同排山倒海一般奔向$n，周遭狂风大作，飞砂走石！" + "\n" NOR);
                addn("neili", -200, me);
                me->start_busy(1);
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "$n拼力纵身后跃，险险避过此致命一击，心有余悸。" + "\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_sort(msg, me, target);
        return 1;
}
