// This program is a part of NITAN MudLIB
// xue.c 冰雪纷飞

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "冰雪纷飞" NOR; }

string *desc = ({
HIW"\n                  ^长空雷隐！^          \n" NOR,
HIY  "                ^^^山风凛冽！^^^       \n" NOR,
RED  "             ^^^^^^回光幻电！^^^^^^  \n" NOR,
HIM  "          ^^^^^^^^^冰河开冻！^^^^^^^^^ \n" NOR,
HIC  "       ^^^^^^^^^^^^天山雪崩！^^^^^^^^^^^^ \n" NOR,
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, level;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不对！\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候不够！\n");

        if ((int)me->query_skill("tianshan-zhang", 1) < 100)
                return notify_fail("你的天山杖法还不到家，无法使用" + name() + "！\n");

        if (me->query_skill_mapped("staff") != "tianshan-zhang")
                return notify_fail("你没有激发天山杖法，使不了" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "使出星宿绝技「冰雪纷飞」，招式变得诡秘异常！\n" NOR;
        message_combatd(msg, me);
        addn("neili", -120, me);
        level = me->query_skill("tianshan-zhang", 1);
        addn("apply/attack", level/2, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                msg = desc[i];
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn("apply/attack", -level/2, me);
        me->start_busy(1 + random(3));
        return 1;
}
