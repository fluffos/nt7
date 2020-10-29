// This program is a part of NITAN MudLIB
// jianzhang.c  剑掌五连环

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "剑掌五连环" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对！\n");

        if( query("neili", me)<160 )
                return notify_fail("你的真气不够，无法施展" + name() + "！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，难以施展" + name() + "！\n");

        if ((int)me->query_skill("huashan-sword", 1) < 50)
                return notify_fail("你的华山剑法还不到家，无法施展" + name() + "！\n");

        if (me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("你没有激发华山剑法，无法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "使出华山派绝技「" HIW "剑掌五连环" HIY"」，身法陡然加快！\n" NOR;
        message_combatd(msg, me);
        addn("neili", -120, me);

        count = me->query_skill("sword");
        addn_temp("apply/attack", count/2, me);

        for (i = 0; i < 5; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(3) == 1)
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count/2, me);
        me->start_busy(1 + random(3));
        return 1;
}
