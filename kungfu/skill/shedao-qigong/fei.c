// This program is a part of NITAN MudLIB
// fei.c 飞仙术

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "飞仙术"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("蛇岛飞仙术只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" &&
            query("skill_type", weapon) != "staff" )
                return notify_fail("你必须持剑或杖才能施展蛇岛飞仙术！\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够！\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 100)
                return notify_fail("你的蛇岛奇功的修为法还不到家，无法使用飞仙术！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        switch (random(3))
        {
        case 0:
                msg = HIY "$N" HIY "怪叫一声，手中的" + weapon->name() +
                      HIY "一晃，化作数道光影飞向$n" HIY "！\n" NOR;
                break;

        case 1:
                msg = HIY "$N" HIY "口中念念有词，手中的" + weapon->name() +
                      HIY "越使越快，渐渐形成一团光芒，笼罩了$n" HIY "！\n" NOR;
                break;

        default:
                msg = HIY "$N" HIY "怪笑两声，欺身近来，步法极其怪异，手中的" +
                      weapon->name() + HIY "忽然击出，一连数招逼向$n" HIY "！\n" NOR;
                break;
        }

        message_combatd(msg, me, target);
        addn("neili", -100, me);
        count = me->query_skill("shedao-qigong", 1) / 3;
        addn_temp("apply/attack", count, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(2));
        return 1;
}


