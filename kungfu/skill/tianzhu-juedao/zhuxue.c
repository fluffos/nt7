/*
由于劈断对方武器的功能是这个perform最大的威力，但为了保持独孤九剑在
这一方面的第一地位，特地对发挥这一威力的条件，在程序中做了如下限制
希望以后的巫师不要更改这些设定，毕竟在weapon武功中，不能超越lonely-sword的地位。
*/

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2,target,*inv;
        int skill, ap, dp, neili_wound, qi_wound,equip,skill1;
        int damage;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill  = me->query_skill("tianzhu-juedao",1);
        skill1 = me->query_skill("shaolin-xinfa",1);


        if( !(me->is_fighting() ))
            return notify_fail("「"+HIR"融雪逐日"NOR+"」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
            return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("buddhism",1) < 220)
                return notify_fail("你佛法修为不足，不能使用「"+HIR"融雪逐日"NOR+"」！\n");

        if( skill < 150)
            return notify_fail("你的天竺绝刀等级不够, 不能使用「"+HIR"融雪逐日"NOR+"」！\n");
        if(me->query_skill("shaolin-xinfa",1)<150)
            return notify_fail("你的少林心法等级不够, 不能使用「"+HIR"融雪逐日"NOR+"」！\n");
 
        if( query("neili", me)<400 )
            return notify_fail("你的内力不够，无法运用「"+HIR"融雪逐日"NOR+"」！\n");

        msg = HIY "$N纵身跃起,使出"+HIR"「融雪逐日」"NOR+""+HIY"，挥舞"NOR""+weapon->name()+ 
              NOR+HIY"从半空中挥刀直劈下来，\n刀锋离地尚有数尺，地下已是尘沙飞扬，败草落叶被"
              "刀风激得团团而舞，\n将$n逃遁退避的空隙封的严严实实。\n"NOR;
        message_vision(msg, me, target);

        ap = random(me->query_skill("blade") + skill);
        dp = target->query_skill("dodge")/2;
        damage = ap / 2 + random(ap / 2);

        if( dp < 10 )
            dp = 10;
        if( random(ap) > dp )
        {
            if(userp(me))
                 addn("neili", -250, me);
            msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60, 
                                       HIC"$n避无可避,只觉一股刚猛之极的劲风扑面而来，使人直欲窒息。\n"
                                       "$n极力后退隔挡，却只见"NOR""+weapon->name()+""HIC"刀光一闪，"
                                       "毫不停息，一刀正中面门。\n"NOR); 

            me->start_busy(2+random(2)); 

       if( query("str", me) >= 20
        && objectp(weapon2=query_temp("weapon", target) )
       && me->query_str() >= 45                              
        && query("max_neili", me)>2500
        && !query("betrayer", me )
       && skill > 200                                           
       && skill1 > 200      
        && !query("no_drop", weapon2 )
        && !query("no_get", weapon2 )
        && !query("no_put", weapon2 )
        && !query("no_beg", weapon2 )
        && !query("no_steal", weapon2 )
        && !query("no_give", weapon2 )
       && random(2) == 1)        
       {
                inv = all_inventory(target);
                for(equip=0; equip<sizeof(inv); equip++)
                {
                          if( query("weapon_prop", inv[equip]) && (query("equipped", inv[equip]) == "wielded") )

                          {
                                 msg += HIW "$N力道未尽，手中刀势不绝，连带$n手上"NOR+
                                 query("name", inv[equip])+HIW"一起劈断。\n只听当的一"
                                 "声，$n手上的"NOR+query("name", inv[equip])+HIW"已"
                                 "被劈成两半，掉在了地上！\n"NOR;
                                  message_vision(msg, me,target);

                                  inv[equip]->unwield();
                                  inv[equip]->reset_action();
                                  inv[equip]->move(environment(target));
                                  set("name", "断掉的"+query("name", inv[equip]), inv[equip]);
                                  set("value", 0, inv[equip]);
                                  set("weapon_prop", 0, inv[equip]);
                                  set("long", "一把破烂武器，从中断开，破口整齐，看来是被高手一刀劈开的。\n", inv[equip]);
                        }
                }

                return 1;
        }
        }
        else
        {
            if(userp(me))
                 addn("neili", -100, me);
            msg = HIW"可是$n轻轻往旁边一闪,闭过了$N这必杀的一刀。\n"NOR;
            me->start_busy(2+random(2));
        }
        message_combatd(msg, me, target);

        return 1;
}

