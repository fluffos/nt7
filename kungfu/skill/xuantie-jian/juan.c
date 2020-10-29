// This program is a part of NITAN MudLIB
// juan.c 卷字诀

#include <ansi.h>

inherit F_SSERVER;

string name() { return "卷字诀"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("卷字诀只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("xuantie-jian", 1) < 70)
                return notify_fail("你的玄铁剑法不够娴熟，不能使用卷字诀。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，不能使用卷字诀。\n");

        if( query("neili", me)<100 )
                return notify_fail("你现在内力太弱，不能使用卷字诀。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("你没有激发玄铁剑法，不能施展卷字诀。\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N一抖手中的" + weapon->name() + HIY "，自下而上的朝$n"
              HIY "卷了过去，曲曲折折，变化无常！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        
        if (query("can_perform/surge-force/new", me) && me->query_skill("surge-force", 1) )
	{
		ap += ap / 4;
	}
	
        if (ap / 2 + random(ap) > dp)
        {
                target->start_busy(ap / 80 + 2);
                addn("neili", -50, me);
                msg += YEL "$p" YEL "连忙竭力招架，一时无暇反击。\n" NOR;
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企图，斜跃避开了$P"
                       CYN "的攻击。\n"NOR;
                addn("neili", -25, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}