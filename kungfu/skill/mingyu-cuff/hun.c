// hun.c 凝雪神功

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("mingyu-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("凝雪神功只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("cuff") != "mingyu-cuff") 
                return notify_fail("你没有用明玉拳，无法使用「凝雪神功」绝招！\n");

        if (me->query_skill_prepared("cuff") != "mingyu-cuff")
                return notify_fail("你没有准备使用明玉拳，无法施展「凝雪神功」绝招。\n");

        if (skill < 100)
                return notify_fail("你的明玉拳等级不够，练好了再来！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必须空着双手才能使用掌法绝招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIW "\n$N" HIW "默运运起明玉拳法的" HIC "凝雪神功" HIW "，忽的长啸一声，大喝一声“雪海茫茫~~~~~”\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIW "\n紧接着地面上响起了一阵轻而密的劈啪之声，眼看着岩石以及泥土的表面上，\n"
              HIW "瞬时凝结起了寸余高的冰块。“唰”地一下，向$n袭来。\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIW "$n" HIW "躲闪不急，惨叫一声，直挺挺地被冻僵了。\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIC "$n" HIC "见势不妙，猛地向后一跃，躲开了飞来的冰块。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

