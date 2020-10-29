// lian.c 连字诀

#include <ansi.h>
#include <combat.h>

string name() { return "连字诀"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int time;
        int count;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「" + name() + "」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("必须拿剑才能施展「" + name() + "」。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真气不够，无法施展「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 200)
                return notify_fail("你的太极神功火候不够，难以施展「" + name() + "」。\n");

        if ((int)me->query_skill("taiji-jian", 1) < 200)
                return notify_fail("你的太极剑还不到家，无法使用「" + name() + "」。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("你没有激发太极剑法，无法使用「" + name() + "」。\n");

        time = me->query_skill("taiji-jian") / 20;
        if (time > 10) time = 10;
        if (time < 1) time = 1;

        msg = HIC "$N" HIC "一声长啸，灵台清明，凝神归元，使出太极剑中的「" + name() + "」。\n"
              HIY "手中" + weapon->name() + HIY "招式陡然变得凌厉无比，一转念"
              HIY "间已然攻出" + chinese_number(time) + "招！\n" NOR;

        message_combatd(msg, me, target);
        skill = me->query_skill("taiji-jian", 1) / 2;
        addn("apply/attack", skill, me);
        addn("apply/damage", skill*2, me);
        addn("neili", -(time*100), me);

        for (i = 0; i < (time); i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, TYPE_LINK);
        }

        addn("apply/attack", -skill, me);
        addn("apply/damage", -skill*2, me);
        me->start_busy(1+ random(3));
        return 1;
}
