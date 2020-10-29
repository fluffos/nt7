// This is player's own perform (Write by Lonely@nt2)
// Create by 星云锁链(Fuyuan) at Thu Mar  5 06:07:56 2015
// 乱拳打死老师傅(luan)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "乱拳打死老师傅" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if (member_array("unarmed", weapon_sk) != -1)
        {
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "unarmed" )
                        return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");
        } else
        {
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

        msg = HIW "$N被晃得有点眼晕，把牙一咬，心一横，想要以伤换伤，对$n的所有招式全都不管不顾，乱拳向$n全身疯狂打去。" + "\n" + NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "dodge");
        attack_time = 6;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIM "结果$n闪避不及，鼻子被$N一拳砸个正着，顿时鼻血喷涌，飞流直下，无奈后退。" + "\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
        } else
        {
                msg += NOR + CYN "可是$p识破了$P这一招，一个驴打滚狼狈闪开。" + "\n" NOR;
                count = 0;
        }

        message_sort(msg, me, target);

        attack_time+=query("jieti/times", me)*2;
        if (attack_time > 13)
                attack_time = 13;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) && ! target->is_busy()) target->start_busy(1);

                COMBAT_D->do_attack(me, target, (member_array("unarmed", weapon_sk) == -1 ? 0 : weapon), 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(3 + random(attack_time/ 3));

        return 1;
}
