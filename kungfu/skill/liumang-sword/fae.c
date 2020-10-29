// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「流氓发恶」只能对战斗中的对手使用。\n");
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("neili", me)<200 )
                return notify_fail("你现在真气不够，无法使用「流氓发恶」。\n");

        msg = HIY "$N" HIY "突然抽剑待步，左手耍出一个白色气团，叱咤的气团看起来就像一个无极盘旋向$n" HIY "。\n" NOR;

        addn("neili", -50, me);
        ap = me->query_skill("sword", 1) / 2 +
        me->query_skill("liumang-sword", 1);
        dp = target->query_skill("parry");
        if (target->is_bad()) ap += ap / 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIG "可是$p" HIG "看破了$P" HIG "的企图，镇"
                       "定逾恒，全神应对自如。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 3, me);
        target->receive_wound("jing", damage / 6, me);
        return
                HIR "$p" HIR "惊慌失措，呆在当场，被$P"
                HIR "这一掌击中要害！后面随之而来的流氓剑又直刺向胸前，顿时不知如何抵挡！\n" NOR;
}
