
#include <ansi.h>

inherit F_SSERVER;

string name() { return "同归剑法"; }

int perform(object me, object target)
{
        string weapon;
        int skill;
        int ap, dp, damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("同归剑法只能对战斗中的对手使用。\n");

        if( query_temp("tonggui", me) )
                return notify_fail("你已在使用同归剑法！\n");

        if( query("eff_qi", me)>query("max_qi", me)*2/3 )
                return notify_fail("你好端端的，跟人家同归干什么？\n");

        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("你所用的并非先天功，无法施展同归剑法！\n");

        if( me->query_skill("xiantian-gong",1) < 100 )
                return notify_fail("你的先天功火候未到，无法施展同归剑法！\n");


        if( me->query_skill("sword") < 135 )
                return notify_fail("你的全真剑法修为不足，还不会使用同归剑法！\n");

        if( query("neili", me) <= 100 )
                return notify_fail("你的内力不够使用同归剑法！\n");
        if( query("jingli", me) <= 150 )
                return notify_fail("你的精力不够使用同归剑法！\n");


        msg = HIY"$N使出「同归剑法」，剑气纵横，只攻不守，招招拼命，凶狠危险之至！\n" NOR;
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        if( ap / 2 + random(ap) > dp )
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(random(3));
                damage=query("qi", target);
                target->receive_damage("qi", damage-10,me);
                target->receive_wound("qi", damage-10,me);
                msg += HIC "$n疾忙斜跃，但剑急如电，只觉一阵钻心剧痛，剑尖扎入胸前，鲜血飞溅！\n"NOR;
                set("neili", 0, me);
        }
        else
        {
                me->start_busy(2);
                set("neili", 100, me);
                msg += HIY"可是$n微微一笑，气定神闲，身形轻变，闪过剑招。\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
