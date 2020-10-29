// 剑动莫名

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "剑动莫名"; }
int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int i,j,times,n;
        int delta;

        i = me->query_skill("wuming-jianfa", 1)/60;
        j = me->query_skill("sword")/10;

        if( !target ) 
        {
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }
        if( !target || !me->is_fighting(target) ) 
                return notify_fail("你只能对战斗中的对手使用绝招「剑动莫名」。\n"); 
                
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必须使用武器才能使用「剑动莫名」！\n");
                
        if( (int)me->query_str() < 35 ) 
                return notify_fail("你的臂力不够, 还不能使用这项绝技! \n");
                
        if( (int)me->query_skill("sword",1) < 600 ) 
                return notify_fail("你的基本剑法的火候还不到家, 不能使用这一绝技 !\n");
                
        if( me->query_skill_mapped("sword") != "wuming-jianfa" ) 
                return notify_fail("你没有激发无名剑法，无法施展" + name() + "。\n");

        if( (int)me->query_skill("wuming-jianfa", 1) < 500 ) 
                return notify_fail("你的无名剑法的火候还不到家, 不能使用这一绝技 !\n");
                
        if( query("neili", me) < 50000)
                return notify_fail("你的真气不够！\n");
                
        if( query("max_neili", me) < 50000)
                return notify_fail("你的内力修为不够！\n");
        
        // 禁止互博使用        
        if( me->is_busy() ) 
                return notify_fail("你上一个动作还没有完成！\n");

        msg = MAG "\n$N脸现幽思,往事如潮涌上心头,手中剑望空斜指一股怨气从剑尖散发弥漫开来！\n" NOR;
        message_combatd(msg, me);
        
        ob = target;
        addn_temp("apply/str", i, me);
        addn_temp("apply/attack", j, me);
        
        addn("neili", -random(5000)-5000, me);
        
        times = (int)(me->query_skill("wuming-jianfa", 1)/50) - 1;
        if( times > 9 ) times = 9;
        
        for ( n=0; n<times; n++ )
        {
                if ( !ob ) break;
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me), TYPE_LINK);
        }
        addn_temp("apply/str", -i, me);
        addn_temp("apply/attack", -j, me);
                
        me->start_busy(3);
        if ( ob && !ob->is_busy() ) 
                ob->start_busy(1+random(2));
        return 1;
}
