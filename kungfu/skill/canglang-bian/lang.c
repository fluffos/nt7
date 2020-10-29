// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;
string name() { return "巨浪滔天"; }

int perform(object me, object target)
{
        object weapon;
        int skill;
        mapping buff, data;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target
        ||      ! target->is_character()
        ||      ! me->is_fighting(target))
                return notify_fail("「巨浪滔天」只能对战斗中的对手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
        ||      query("skill_type", weapon) != "whip" )
                return notify_fail("你没有鞭在手，施不出「巨浪滔天」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力不够！\n");

        if (me->query_skill("canglang-bian", 1) < 200)
                return notify_fail("你的「沧浪鞭法 」未臻高妙境界，无法施出「巨浪滔天」！\n");

        if (me->query_skill("bibo-shengong", 1) < 200)
                return notify_fail("你的碧涛玄功修为不够，无法施出「沧浪鞭法」！\n");

        if (me->query_skill_mapped("whip") != "canglang-bian")
                return notify_fail("你所用的并非「沧浪鞭法 」，施展不出「巨浪滔天」！\n");

        if( BUFF_D->check_buff(me, "atkup") )
                return notify_fail("你已经在运用类似的武功了。\n");
                
        message_combatd(
                HIR"$N忽然将"+(query("name", query_temp("weapon", me)))+
                HIR"频频甩出，"+(query("name", query_temp("weapon", me)))+
                HIR "发出劈啪暴空之声不绝扰得$n心烦意乱。\n" NOR, me, target);
        msg = HIB "$N的招数万千，但鞭头却总是指向"+target->name()+"的周身要穴，攻击如巨浪连绵无穷无尽，"
                "令"+target->name()+"只有招架之功却无还手之力。\n" NOR;

        set_temp("julang", 1, me);

        skill =  ( me->query_skill("canglang-bian") + me->query_skill("dodge") ) / 2;
        addn("neili", -200, me);
        
        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "atkup",
                "attr"  : "bless",
                "name"  : "沧浪鞭法·巨浪滔天",
                "time"  : skill/3,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你慢慢内运内功，把真气压下！\n",                      
        ]);
        
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        me->start_busy(1+random(2));
        return 1;
}
