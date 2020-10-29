#include <ansi.h>

inherit F_SSERVER;
string name() { return "即世即空"; }

int perform(object me, object target)
{
        object weapon;
        int damage, club;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("「即世即空」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你手中无棍，怎能运用「即世即空」？！\n");

        if( query_temp("sl_leidong", me) )
                return notify_fail("你刚使完「雷动九天」，目前气血翻涌，无法再次运用！\n");

        if( (int)me->query_skill("weituo-chu", 1) < 120)
                return notify_fail("你韦陀杵修为还不够，还未能使用「雷动九天」！\n");

        if( me->query_skill("force", 1) < 120 )
                return notify_fail("你的内功修为火候未到，施展只会伤及自身！\n");

        if( query("max_neili", me) <= 1500 )
                return notify_fail("你的内力修为不足，劲力不足以施展「雷动九天」！\n");

        if( query("neili", me) <= 600 )
                return notify_fail("你的内力不够，劲力不足以施展「雷动九天」！\n");

        message_combatd(BLU "\n突然$N大喝一声：「即世即空」，面色唰的变得通红，须发皆飞，真气溶入" +
                           weapon->name() + BLU "当中，“嗡”的一声，发出" HIW " 闪闪光亮 " BLU "！\n " NOR, me);

        damage = me->query_skill("weituo-chu", 1) + me->query_skill("buddhism",1);
        damage /= 6;
        club = me->query_skill("staff") / 3;

        if ( userp(me) )
        {
                addn("neili", -300, me);
                if( damage>query("weapon_prop/damage", weapon)*2 )
                     damage=query("weapon_prop/damage", weapon)*2;
                else addn("rigidity", 1, weapon);
        }

        set_temp("sl_leidong", 1, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/attack", damage, me);

        call_out("remove_effect1", club/2, me, weapon, damage);
        call_out("remove_effect2", club * 2/3, me);
        me->start_exert(club * 2 / 6, "「即世即空」");

        return 1;
}

void remove_effect1(object me, object weapon, int damage)
{
        if (!me) return;
        addn_temp("apply/attack", -damage, me);

        if (!weapon) {
                set_temp("apply/damage", 0, me);
                return;
        }
        addn_temp("apply/damage", -damage, me);
        message_vision(HIY "\n$N一套「即世即空」使完，手中"NOR + weapon->name() + HIY"上的光芒渐渐也消失了。\n"NOR, me);
}

void remove_effect2(object me)
{
        if (!me) return;
        delete_temp("sl_leidong", me);
        tell_object(me, HIG "\n 你经过一段时间调气养息，又可以使用「即世即空」了。\n"NOR);
}
