// dan.c 亢龙无悔

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
                return notify_fail("「亢龙无悔」只能对战斗中的对手使用。\n");
 
        if(me->query_skill_mapped("cuff") != "mingyu-cuff") 
                return notify_fail("你没有用明玉拳，无法使用「亢龙无悔」绝招！\n");

        if (me->query_skill_prepared("cuff") != "mingyu-cuff")
                return notify_fail("你没有准备使用明玉拳，无法施展「亢龙无悔」绝招。\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用掌法绝招。\n");

        if ((int)me->query_skill("mingyu-cuff", 1) < 200)
                return notify_fail("你的明玉拳不够娴熟，不会使用「亢龙无悔」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你现在内力太弱，不能使用「亢龙无悔」。\n");
                        
        msg = HIB "\n$N" HIB "把全身劲力运于双拳，一声大喝，平平地向$n推出双掌！\n" NOR;

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
        
        if (ap / 3 + random(ap/2) > dp)
        {
                damage += damage/2;
                addn("neili", -damage/2, me);

                msg += HIR "\n只听见啪的一声巨响，$N" HIR "的双拳已经扎扎实实的打在$n" HIR "身上了！\n" NOR;
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else if (ap / 2 + random(ap) > dp)
        {
                damage += damage/2;
                addn("neili", -damage/2, me);

                if (weapon2)
                {
                        msg += HIM "\n$n" HIM "避无可避，只好举起手中的" NOR + weapon2->name() + HIM "硬挡一招。\n"
                               HIM "只听“啪”的一声，$n" HIM "的" NOR + weapon2->name() + HIM "已经被打成两截。\n" NOR;
                        if (ap / 3 + random(ap) > dp)
                        {
                                damage -= damage/3;
                                msg += HIM "$N" HIM "拳势顿得一顿，却依然重重地打在了$n" HIM "身上。\n" NOR;
                        } else
                        {
                                damage -= damage/2;
                                msg += HIM "$n" HIM "虽然兵器被打断，却也缓了口气，乘机避开。\n" NOR;
                        }
                        weapon2->set_name("断裂的"+query("name", weapon2));
                        weapon2->move(environment(target));
                        set("value", 0, weapon2);
                        set("weapon_prop", 0, weapon2);
                        target->reset_action();
                } else
                {
                        msg += HIG "\n$n" HIG "避无可避，只好也同样双拳平推硬挡一招。\n"
                               HIG "一声惊天动地地巨响，双拳相交之下，$n" HIG "被震地气血翻涌。\n" NOR;
                        if (ap / 2 + random(ap) > dp)
                        {
                               msg += HIG "$N" HIG "的拳劲丝毫不受影响，依然重重的打在了$n" HIG "的身上！\n" NOR;
                        } else if (ap / 2 + random(ap*2) > dp)
                        {
                               msg += HIG "$n" HIG "虽然挡开了$N" HIG "的雷霆一击，却仍然被拳风所伤，只觉一阵窒息。\n" NOR;
                               damage -= damage/3;
                        } else
                        {
                               msg += HIG "两人拳劲相交之下，$N" HIG "的全力一击被完全化解。\n" NOR;
                               damage -= damage; 
                        }

                }               
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else
        {
                if (weapon2)
                        msg += HIY "$n" HIY "以四两拨千斤之法，随意挥动" NOR + weapon2->name() + HIY "，便拨开了$N" HIY "的"HIR"亢龙无悔。\n" NOR;
                else
                        msg += HIY "$n" HIY "以四两拨千斤之法，随意挥手，便拨开了$N" HIY "的"HIR"亢龙无悔。\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}