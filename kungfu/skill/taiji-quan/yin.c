// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "引字诀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, ap, dp, damage;
        string msg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        skill = me->query_skill("taiji-quan", 1);

        if (skill < 150)
                return notify_fail("你的太极拳等级不够，难以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真气不够，难以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "taiji-quan")
                return notify_fail("你没有激发太极拳，难以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "taiji-quan")
                return notify_fail("你现在没有准备使用太极拳，无法使用" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "双手一圈，施出「引」字诀，如抱太极，一股"
              "雄浑无比的力道组成了一个旋涡，圈向$n" HIW "。\n" NOR;
        addn("neili", -100, me);

        ap = attack_power(me,"cuff");
        dp = defense_power(target,"parry");

        if (ap / 2 + random(ap * 4 / 3) > dp)
        {
                addn("neili", -10, me);
                damage = damage_power(me, "cuff");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "$n" HIR "微微一楞，登时被这力道带"
                                           "得在原地急转七八下，如转陀螺，如旋纺"
                                           "锤。\n" NOR);
                me->start_busy(2);
                if (ap / 2 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 80 + 3);
        } else
        {
                msg += CYN "$n" CYN "见状连忙使出“千斤坠”之力定"
                       "住身形，摆脱了$N" CYN "的力道。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
