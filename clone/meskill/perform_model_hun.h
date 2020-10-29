#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int is_player_perform() { return 1; }

string name() { return HIW "<绝招名>" NOR; }

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

        if (member_array("BASE_SKILL", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "BASE_SKILL" )
                        return notify_fail("你所使用的武器不对，难以施展" + name() + "。\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("SKILL", 1) < 400)
                return notify_fail("你" + to_chinese("SKILL") + "不够娴熟，难以施展" + name() + "。\n");

        if (member_array("BASE_SKILL", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("BASE_SKILL") != "SKILL")
                        return notify_fail("你没有准备" + to_chinese("SKILL") + "，难以施展" + name() + "。\n");
        }

        if( query("neili", me)<500 )
                return notify_fail("你现在的真气不够，难以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "<PFM发招描述>" + "\n" + NOR;

        ap = attack_power(me, "BASE_SKILL");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "BASE_SKILL")*7;
                msg += COMBAT_D->do_damage(me, target, attack, damage, 380, HIM "<PFM打中描述>" + "\n" NOR);
                addn("neili", -200, me);

                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "<PFM失误描述>" + "\n" NOR;
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
        attack_time+=query("reborn/times", me)*2;
        if (attack_time > 8)
                attack_time = 8;

        addn("neili", -attack_time*20, me);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count, me);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, (member_array("BASE_SKILL", weapon_sk) == -1 ? 0 : weapon), TYPE_LINK);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count, me);
        me->start_busy(3 + random(attack_time/ 3));
        return 1;
}
