// This program is a part of NITAN MudLIB
// bafang.c 威镇八方

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "威镇八方"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「威镇八方」只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手才能使用「威镇八方」！\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("shenzhang-bada", 1) < 200)
                return notify_fail("你的神掌八打修为不够，目前不能使用「威镇八方」！\n");

        if( query("neili", me)<700 )
                return notify_fail("你的真气不够，无法使用「威镇八方」！\n");

        if (me->query_skill_mapped("strike") != "shenzhang-bada")
                return notify_fail("你没有激发神掌八打，不能使用「威镇八方」！\n");

        msg = HIY "$N" HIY "深深的吸了一口气，大喝一声，全身衣袍无风自鼓，"
                   HIY "然后提气往上一纵，居高临下，双掌奋力击下，刹那间，内劲犹如旋风般"
                   "击向$n" + HIY "！\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*20;
        dp=defense_power(target,"parry")+target->query_dex()*20;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -350, me);

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$N" CYN "的企图，轻轻"
                       CYN "向后飘出数丈，躲过了这一致命的一击！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}