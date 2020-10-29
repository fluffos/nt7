// dan.c 剑气无双

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
                return notify_fail("「剑气无双」只能对战斗中的对手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("运用「剑气无双」手中必须有剑！\n");

        if ((int)me->query_skill("snowstar-sword", 1) < 200)
                return notify_fail("你的雪影寒星剑法不够娴熟，不会使用「剑气无双」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用「剑气无双」。\n");
                        
        msg = HIW "\n$N" HIW "灵台清明，身随意走，剑气如虹，手中" + weapon->name() + HIW "激起一道如匹练般的剑光，毫无花哨的刺向$n" HIW "。\n\n" NOR;

        ap = me->query_skill("sword") + me->query_skill("force");
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

                if (weapon2)
                {
                        msg += HIR "\n$n" HIR "见$N" HIR "来势凶猛，匆忙抵挡下，手中" + weapon2->name() + HIR "被震成几截，断裂当场！\n" NOR;
                        damage -= damage/3;
                        weapon2->set_name("碎裂的"+query("name", weapon2));
                        weapon2->move(environment(target));
                        set("value", 0, weapon2);
                        set("weapon_prop", 0, weapon2);
                        target->reset_action();
                }
                msg += HIR "$n" HIR "面对这大巧若拙的一剑，顿时呆立当场，眼睁睁看着" + weapon->name() + HIR "从自己的胸口穿过，目光中透出一种不可思议的神色。\n" NOR;
                
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
               
        } else 
        {
                msg += HIR "$n" HIR "急忙左右跳跃，终于脱出了剑光的包围。\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}