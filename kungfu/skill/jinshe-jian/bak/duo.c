// This program is a part of NITAN MudLIB
// duo.c  金蛇剑法  (夺魄)

#include <ansi.h>
inherit F_SSERVER;

void end(object target, int damage);

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;
        
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() )
                return notify_fail("夺魄只能对同地方的对手使用。\n");
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("夺魄只能对战斗中的对手使用。\n");
                
        if( (int)me->query_skill("jinshe-jian", 1) < 100 )
                return notify_fail("你的金蛇剑法不够娴熟，不会使用「夺魄」。\n");
                
        if( query("neili", me)<200 )
                return notify_fail("你现在内力太弱，不能使出夺魄。\n");
                
        if( query_temp("sword", target) == 1 )
                return notify_fail(query("name", target)+"正在魂飞魄散间，快放手攻击啊!\n");
                
        msg = HIW "$N突然眼中金芒大盛，一股寒意破空直袭$n。\n"NOR;
        addn("neili", -400, me);
        me->start_busy(1);
        
        ap=me->query_skill("sword")*3/2+query("level", me)*20+
             me->query_skill("martial-cognize", 1);
        dp=target->query_skill("dodge")+query("level", target)*20+
             target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                msg += WHT"$p被吓得魂飞魄散，只见对方攻势大盛，越战越勇。\n"NOR;
                if (! target->is_busy())
                target->start_busy(3);
                addn("neili", -100, me);
                damage = me->query_skill("jinshe-jian",1);
                damage = 0-damage/8-random(damage/8);
                
                if( !query_temp("apply/attack", target) )
                    set_temp("apply/attack", damage, target);
                else
                    addn_temp("apply/attack", damage, target);
                if( !query_temp("apply/defense", target) )
                    set_temp("apply/defense", damage, target);
                else
                    addn_temp("apply/defense", damage, target);
                set_temp("sword", 1, target);
                call_out("end", 30, target, damage);
        }
        else
        {
                msg += HIY"$p沉着应战，没有受到“夺魄”攻击的影响！\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

void end(object target,int damage)
{
        if (! objectp(target)) return;
        delete_temp("sword", target);
        addn_temp("apply/attack", 0-damage, target);
        addn_temp("apply/defense", 0-damage, target);
        message_vision(RED"$N终于从夺魄的阴影里恢复了出来。\n"NOR,target);
}

