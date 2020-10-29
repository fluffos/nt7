// This is player's own perform (Write by Lonely@nt2)
// Create by 降头师(Wudu) at Wed Jun 24 12:10:22 2015
// 九转阴阳十二天(lian)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int is_player_perform() { return 1; }

string name() { return HIW "九转阴阳十二天" NOR; }

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

        if (me->is_busy()) return notify_fail(BUSY_MESSAGE);

        if (member_array("hand", weapon_sk) != -1)
        {
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "hand" )
                        return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");
        } else
        {
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("mmqf-hand", 1) < 400)
                return notify_fail("你" + to_chinese("mmqf-hand") + "不够娴熟，难以施展" + name() + "。\n");

        if (member_array("hand", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("hand") != "mmqf-hand")
                        return notify_fail("你没有准备" + to_chinese("mmqf-hand") + "，难以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N口中默念：天道无常。心神沉入十二重天境界，连空间似乎也扭曲了起来。$n大惊失色，仿佛已身在异界！" + "\n" + NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");
        attack_time = 6;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIM "$n丝毫不懂此招奥妙，一个疏神，丹田已遭重创" + "\n" NOR;
                count = ap / 5;
                addn_temp("apply/attack", count, me);
                addn_temp("apply/damage", count, me);
        } else
        {
                msg += NOR + CYN "$p见势不妙，抽身急退，险险避过$P的这记杀招，尘土飞扬中，地上出现一个大坑！" + "\n" NOR;
                count = 0;
        }

        message_sort(msg, me, target);

        attack_time+=query("reborn/times", me)*2;
        if (attack_time > 13)
                attack_time = 13;

        addn("neili", -attack_time*20, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) && ! target->is_busy()) target->start_busy(1);

                COMBAT_D->do_attack(me, target, (member_array("hand", weapon_sk) == -1 ? 0 : weapon), TYPE_LINK);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(3 + random(attack_time/ 3));

        return 1;
}
