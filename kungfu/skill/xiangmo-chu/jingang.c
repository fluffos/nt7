// This program is a part of NT MudLIB
// xiangmo.c 金刚降魔

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "金刚降魔"; }

int perform(object me, object target)
{
        object weapon;
        int lxbr,nec,damage,amount,quick,ap,dp;
        string str = @TEXT
                                                |\
                .-':'"": - -   -  -   : -  \ (1\.`-.
              .'`.  `.  :  :  :   :   : : : : : :  .';
             :-`. :   .  : :  `.  :   : :.   : :`.`.o ;
             : ;-. `-.-._.  :  :   :  ::. .' `. `., =  ;
             :-:.` .-. _-.,  :  :  : ::,.'.-' ;-. ,'''"
           .'.' ;`. .-' `-.:  :  : : :;.-'.-.'   `-'
    :.   .'.'.-' .'`-.' -._;..:---'''"~;._.-;
    :`--'.'  : :'     ;`-.;            :.`.-'`.
     `'"`    : :      ;`.;             :=; `.-'`.
             : '.    :  ;              :-:   `._-`.
              `'"'    `. `.            `--'     `._;
                        ''''
TEXT;
        if (!target) target = offensive_target(me);
        if (!target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("『金刚降魔』只能对战斗中的对手使用。\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "hammer" )
                return notify_fail("你手中无杵，如何降魔？\n");

        if (me->query_skill("longxiang", 1) < 150 && me->query_skill("mizong-neigong",1) < 150 )
                return notify_fail("你的内功火候未到，无法施展降魔绝技！\n");

        if (me->query_skill("xiangmo-chu", 1) < 150)
                return notify_fail("你的降魔杵火候未到，无法施展降魔绝技！\n");

        if (me->query_skill("necromancy",1) < 200)
                return notify_fail("你降伏法修为不够，如何降伏他人？\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("你的内力不够使用『金刚降魔』！\n");

        if( query("jingli", me) <= 500 )
                return notify_fail("你的精力不够使用『金刚降魔』！\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        nec = me->query_skill("necromancy",1);
        quick = (int)(me->query_skill("longxiang-gong",1)/100);
        if (quick < 2) quick = 2;
        amount = (int)me->query_skill("hammer")/4;

        addn_temp("apply/damage", amount*2, me);
        addn_temp("apply/attack", amount, me);
        set_temp("xiangmo_busy", 1, me);
        message_combatd(HIR"\n$N大呼酣战，口念密宗不动明王真言，使出『金刚降魔』大法。\n"NOR,me,target);
        message_combatd("$N一声高呼，身形陡转，犹如雪豹下山。\n",me,target);
        message_combatd(HIW+str+NOR,me,target);
        ap = nec + attack_power(me, "hammer");
        dp = defense_power(target, "force");

        if(random(ap)>dp/2 || !living(target))
        {
                damage=damage_power(me, "hammer");
                if (damage<500) damage=500;
                if( query("id", weapon) == "xiangmo chu")damage*=3/2;
                if (random(ap)>dp/2 || !living(target))
                {
                        message_combatd(HIR"\n$n见此情景，已不知所措，只觉头昏眼花，完全被$N降伏。\n"NOR, me,target);
                        target->receive_wound("qi", damage/3 + random(damage/3), me);
                        target->receive_wound("jing", damage/5 + random(damage/3), me);
                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("($N"+str+")\n", target);
                        if( !target->is_busy() )
                                target->start_busy(2);
                }
                else
                {       message_combatd(HIR"\n$n见此情景，极力摆脱，结果精力大耗才跳出$N的降魔幻影。\n"NOR,me,target);
                        target->receive_damage("jing", damage/5 + random(damage/3), me);
                        target->receive_wound("qi", damage/4 + random(damage/3), me);
                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("($N"+str+")\n", target);
                        if( !target->is_busy() )
                                target->start_busy(1+random(3));
                        message_combatd(HIR"\n$N见$n漏出破绽，高举手中"+query("name", weapon)+HIR"向$n袭来。\n"NOR,me,target);
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
                }
                me->start_busy(3);
        }
        else
        {
                message_combatd(HIR"$n见此情景，冥思一翻，终于识破了$N的降魔幻影。\n"NOR, me, target);
                message_combatd("只见$n不退反进，身如飘风，反而向$N发起进攻,$N顿时不知所措。\n",me,target);
                me->start_busy(4);
        }
        addn_temp("apply/damage", -amount*2, me);
        addn_temp("apply/attack", -amount, me);
        addn("neili", -query("jiali", me)-500, me);
        addn("jingli", -query("jiajin", me)-400, me);
        return 1;
}