// dan.c 亡月

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
                return notify_fail("「亡月」只能对战斗中的对手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("运用「亡月」手中必须有剑！\n");

        if ((int)me->query_skill("canyue-sword", 1) < 200)
                return notify_fail("你的残月剑法不够娴熟，不会使用「亡月」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用「亡月」。\n");
                        
        msg = WHT "\n$N" WHT "剑尖忽然起了奇异的震动。剑尖本来是斜斜指向$n" WHT "，震动一起，万物忽然间全都静止。\n"
              "就连周围的空气，都彷佛也已停顿。\n" WHT "没有任何言语可以形容这种情况，只有一个字，一个很简单的字...\n\n"
              HIR "死！ \n\n" HIB "流水乾枯，变化穷尽，生命终结，万物灭亡！\n\n" NOR; 

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

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -damage/2, me);

                msg += HIR "$N" HIR "手中的" + weapon->name() + HIR "似乎苏醒过来，$n的生命却在逐渐流逝，一切已无法再改变。 \n" NOR;
                
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
               
        } else 
        {
                msg += HIR "$N" HIR "一剑失去目标，忽然觉得灵魂仿佛被抽入" + weapon->name() + RED "再也无法控制！"
                       + weapon->name() + HIR "差点脱手而出！\n" NOR; 

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}