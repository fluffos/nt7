// linglong.c 玉玲珑

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
                return notify_fail("「玉玲珑」只能对战斗中的对手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("运用「玉玲珑」手中必须有剑！\n");

        if ((int)me->query_skill("liudaolunhui-sword", 1) < 200)
                return notify_fail("你的六道轮回剑法不够娴熟，不会使用「玉玲珑」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用「玉玲珑」。\n");
                        
        msg = HIW "\n$N" HIW "身影慢慢的浮现在$n" HIW "面前，只见$N" HIW "洒出无数晶莹剔透的"
              "玉玲珑围绕在$n" HIW "周围。\n刀光剑影的世界霎时间沉寂在这柔和的雪光之中，"
              "好一记温柔缠绵的玉玲珑\n\n" HIM "纵情山水间，挥洒天地情!\n\n" NOR;

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

                msg += HIW "$n" HIW "顿时沉寂在这梦一般的景象之中，如痴如醉中被雪玲珑击中了!\n"
                       "$n" HIW "完全陷入玉玲珑的威力之中无法自拔。\n看着剑光从前心穿过" NOR;
                
                if( objectp(weapon2=query_temp("weapon", target)) )
                {
                        msg += HIW "，手中" + weapon2->name() + HIW "当啷一声掉在地上。\n" NOR;
                        weapon2->move(environment(target));
                }
                else
                        msg += HIW "。\n" NOR;

                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
               
        } else 
        {
                msg += HIY "可$n" HIY "并没有被这绚丽的雪景所吸引,依然屹立在雪花飞舞的幻景中！\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}