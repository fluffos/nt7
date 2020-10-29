// This is player's own perform (Write by Lonely@nt2)
// Create by 星云锁链(Fuyuan) at Thu Mar  5 08:38:13 2015
// 雷霆雨露(lei)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "雷霆雨露" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count, damage;
        int attack_time;
        int attack, i;

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

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N觉得鼻子有点不通，用拇指堵住一个鼻孔，猛一发力，“噗”的一声，对着$n来了个单管喷射。" + "\n" + NOR;

        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "unarmed");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 80, HIM "结果$n闪避不及，被一团黏糊糊的鼻屎喷了一脸，立马脸色惨白，吐了个昏天暗地。" + "\n" NOR);
                addn("neili", -200, me);

                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "可是$p大惊失色，竭尽全力方才$P险险避开。" + "\n" NOR;
                addn("neili", -100, me);
        }

        message_sort(msg, me, target);

        msg = HIW "$N" HIW "余势未尽，招式陡然变得凌厉无比，一转念间已然攻出数招。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 20;
                msg += HIR "$n" HIR "见$P" HIR "来势迅猛之极，一时不知该如"
                       "何作出抵挡，竟呆立当场。\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "见$p" HIY "来势迅猛之极，甚难防备，连"
                       "忙振作精神，小心抵挡。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        attack_time = 3;
        attack_time+=query("jieti/times", me)*2;
        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, (member_array("unarmed", weapon_sk) == -1 ? 0 : weapon), 0);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(3 + random(attack_time/ 3));
        return 1;
}
