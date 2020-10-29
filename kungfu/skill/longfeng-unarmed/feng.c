// This is player's own perform (Write by Lonely@nt2)
// Create by 剑人(Dlf) at Wed Mar  4 09:12:40 2015
// 凤之式(feng)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "凤之式" NOR; }

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

        msg = HIW "$N双拳陡然连续拍出，刚中带柔，一招「凤之式」，已将$n笼罩在掌风之中。结果$n目不暇接，顿时被$N所困阵脚大乱$n看清$N这几招的来路，但内劲所至，刚柔并济" + "\n" + NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "dodge");
        attack_time = 6;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIM "$n连忙格挡，可是这一拳力道何等之重，哪里抵挡得住？只被打得吐血三尺，连退数步！" + "\n" NOR;
                count = ap / 10;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
        } else
        {
                msg += NOR + CYN "只见$n不慌不忙，轻轻一闪，躲过了$N这一击！" + "\n" NOR;
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
