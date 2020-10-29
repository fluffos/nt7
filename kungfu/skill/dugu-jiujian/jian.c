#include <ansi.h>

#define HUA "「" MAG "剑心通明" NOR "」"

inherit F_SSERVER;

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int skill;

        if( !query("scborn/ok", me) )
                return notify_fail("你所使用的外功中没有这个功能。\n");

        if (me->query_skill_mapped("sword") != "dugu-jiujian")
                return notify_fail("你还没有激发独孤九剑。\n");
                
        if( !query("can_learn/dugu-jiujian/nothing", me) )
                return notify_fail("你还没有进入无招境界，何谈剑心通明？\n");
                
        if ((int)me->query_skill("dugu-jiujian", 1) < 1000)
                return notify_fail("你的独孤九剑等级不够，难以施展" HUA "。\n");
                                        
        if( query_temp("dugu_sword", me) )
                return notify_fail("你已经运起" HUA "了。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你所使用的武器不对！\n");
                
        if( query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不对！\n");
                
        if( query("neili", me)<250 )
                return notify_fail("你此时的内力不足，难以施展" HUA "。\n");

        msg = MAG "$N" MAG "凝神聚气，挥洒手中兵器，进入无招无我，剑心通明境界！\n\n" NOR;

        message_combatd(msg, me, target);

        if (me->is_fighting())
                me->start_busy(1);

        skill = me->query_skill("dugu-jiujian", 1);

        addn_temp("apply/damage", skill*2, me);
        set_temp("dugu_sword", 1, me);

        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, skill * 2 :), 180);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("dugu_sword", me) )
        {
                addn_temp("apply/damage", -1*amount, me);
                delete_temp("dugu_sword", me);
                tell_object(me, "你的" HUA "运行完毕，将内力收回丹田。\n");
        }
}