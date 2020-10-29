// dan.c 飞龙斩

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("「飞龙斩」只能对战斗中的对手使用。\n");
 
        if(me->query_skill_mapped("cuff") != "feilong--cuff") 
                return notify_fail("你没有用飞龙神拳，无法使用「飞龙斩」绝招！\n");

        if (me->query_skill_prepared("cuff") != "feilong--cuff")
                return notify_fail("你没有准备使用飞龙神拳，无法施展「飞龙斩」绝招。\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用掌法绝招。\n");

        if ((int)me->query_skill("feilong--cuff", 1) < 200)
                return notify_fail("你的飞龙神拳不够娴熟，不会使用「飞龙斩」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用「飞龙斩」。\n");
                        
        msg = HIR "\n$N" HIR "突然绕到$n" HIR "身后，双拳猛的击向$n" HIR "的后腰！\n" NOR;

        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);
        
        damage = ap*2 + random(ap);
        damage+=query("jiali", me);

        if (living(target))
                dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
        else
                dp = 0;

        dp = dp*3/2;

        weapon2=query_temp("weapon", target);
        
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -damage/2, me);

                msg += HIR "\n只听“咔嚓”一声闷响！$n" HIR "喷出一口鲜血，软塌塌的摇摇欲坠……\n" NOR;
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else 
        {
                msg += HIR "\n哪知$n" HIR "早有准备，身形一展，轻易的化解了这招！\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}