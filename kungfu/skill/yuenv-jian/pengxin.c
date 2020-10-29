// pengxin.c 西子捧心

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int delta;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「西子捧心」只能在战斗中对对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( userp(me) && !query("can_perform/yuenv-jian/pengxin", me) )
                return notify_fail("你不会使用「西子捧心」这一绝技！\n");

        if (me->query_dex() < 35)
                return notify_fail("你的身法不够，目前还不能使用这项绝技！\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的剑术修为不够，目前不能使用「西子捧心」！\n");

        if (me->query_skill("yuenv-jian", 1) < 100)
                return notify_fail("你的越女剑术的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的轻功修为不够，无法使用「西子捧心」！\n");
 
        if( query("neili", me)<200 )
                return notify_fail("你的真气不够！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if( query("gender", me) == "女性" && 
            query("gender", target) == "女性" )
                delta=query("per", target)-query("per", me);
        else
                delta = 0;

        msg = HIG "$N" HIG "幽幽一声长叹，手中的" + weapon->name() +
              HIG "就如闪电般刺向$n的胸口。\n" NOR;
        if (delta > 0)
                msg += HIY "$n" HIY "只觉得$N" HIY "眼神中隐然透出"
                       "一股冰冷的寒意，心中不禁一颤。\n" NOR;
        else
                delta = 0;

        addn("neili", -150, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        me->start_busy(2);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword") + delta * 1000;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "$n" HIR "大吃一惊，慌忙躲避，然而剑"
                                           "气来的好快，哪里躲得开？\n只听$p" HIR
                                           "一声惨叫，胸口已经被剑气所伤！\n" NOR);
                if (ap / 3 + random(ap) > dp)
                {
                        damage /= 3;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                                   HIC "$n重创之下不禁破绽迭出，$P"
                                                   HIC "见状随手刺出" + weapon->name() +
                                                   HIC "，又是一剑！\n" HIR "就听$p"
                                                   HIR "又是一声惨叫，痛苦不堪。\n" NOR);
                }
        } else
        {
                msg += HIC "$n" HIC "见状身形急退，避开了$N"
                       HIC "的无形剑气的凌厉一击！\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}