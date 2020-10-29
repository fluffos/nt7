// This program is a part of NITAN MudLIB
// duo.c  金蛇剑法  (夺魄)

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, ap, dp;
        string msg;
        mapping buff, data;
        
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
                
        if( BUFF_D->check_buff(target, "jinshe_duo") )
                return notify_fail(query("name", target)+"正在魂飞魄散间，快放手攻击啊!\n");
                
        msg = HIW "$N突然眼中金芒大盛，一股寒意破空直袭$n。\n"NOR;
        addn("neili", -400, me);
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += WHT"$p被吓得魂飞魄散，只见对方攻势大盛，越战越勇。\n"NOR;
                if( !target->is_busy() ) target->start_busy(3);
                addn("neili", -100, me);
                skill = me->query_skill("jinshe-jian",1);
                
                data = ([
                        "attack"  : -skill/2,
                        "defense" : -skill/2,
                ]);
                buff = ([
                        "caster":me,
			"target": target,
			"type":"jinshe_duo",
			"attr":"curse",
			"name":"金蛇剑法·夺魂",
			"time": skill/3,
                        "buff_data": data,
			"buff_msg": msg,
			"disa_msg": RED"$N终于从夺魄的阴影里恢复了出来。\n"NOR,
			"disa_type": 1,
                ]);
        }
        else
        {
                msg += HIY"$p沉着应战，没有受到“夺魄”攻击的影响！\n"NOR;
        }
        message_combatd(msg, me, target);
        me->start_busy(1);
        return 1;
}
