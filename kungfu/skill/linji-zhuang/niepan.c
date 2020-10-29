// Written by Lonely@nitan.org
// 凤凰涅磐 转世技能

#include <ansi.h>
inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill;
        mapping buff, data;
        string msg;
        int time;

        if( userp(me) && !query("can_exert/linji-zhuang/niepan", me) ) 
                return notify_fail("你未得高人指点，不知该如何施展凤凰涅磐。\n");  
        
        /*
        if( query("family/family_name", me) != "峨嵋派" )
                return notify_fail("你不是峨嵋弟子，无法使用凤凰涅磐。\n");
        */
        if( userp(me) && !query("yuanshen", me) )
                return notify_fail("你尚未悟道，无法使用凤凰涅磐！\n");
        
        skill = me->query_skill("linji-zhuang", 1);
        if( skill < 1000 )
                return notify_fail("你的临济十二庄修为还不够，无法使用凤凰涅磐！\n");

        if( query("jingli", me)<1000 )
                return notify_fail("你的真气不够。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你的内力不够。\n");

        if( objectp(target) && target != me ) {
                if( !target->query_weak() )
                        return notify_fail(target->name() + "并没有处于虚弱状态。\n");

                addn("neili", -1000, me);
                me->receive_damage("qi", 0);
                target->clear_weak();
                message_combatd(HIY "只见$N" HIY "屏息静气，双掌贴在"+target->name()+"背后，交错运行大小二庄，只见"+target->name()+"全身被紫芒笼罩。\n" NOR, me);
                tell_object(target, HIG"\n你感觉身体状态慢慢的复原了。。。\n\n" NOR);
                tell_object(me, HIG"\n你替"+target->name()+"消除了虚弱状态。。。\n\n" NOR);
                if( me->is_fighting() ) me->start_busy(3);
                return 1;
        }

        if( BUFF_D->check_buff(me, "ljz-niepan") ) 
                return notify_fail("你已经在运起凤凰涅磐了。\n");
        
        if( userp(me) ) 
        {
                if( (time = BUFF_D->get_buff_overtime(me, "ljz_niepan")) > 0 )
                        return notify_fail(MAG"神光离合消耗心神太甚，还需等待"+time+"秒。\n"NOR);
        }
        
        addn("neili", -1000, me);
        me->receive_damage("qi", 0);

        msg = HIY "$N" HIY "神色忽而欢叹、忽而忧心、转瞬间又化做不喜不悲之状，\n随著$N" 
              HIY "张开眼神，一屡精光乍现及逝，$N"HIY"的气习却已全然不同。\n" NOR;

        data = ([
                "avoid_busy": 90,
                "avoid_weak": 90,
                "reduce_damage": 70,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "ljz-niepan",
                "attr"  : "bless",
                "name"  : "临济十二庄·凤凰涅磐",
                "time"  : skill/5,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的临济十二庄运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        
        time  = skill/5 + 40;
        time -= ABILITY_D->check_ability(me, "cd-ljz-niepan"); // ab门派减cd
        time -= ABILITY_D->check_ability(me, "reduce_cd", 2); // talent减cd 
                
        buff =
	([
	        "caster" : me,
	        "target" : me,
	        "type"   : "cooldown",
	        "type2"  : "ljz_niepan",
	        "attr"   : "curse",
	        "name"   : "临济十二庄·凤凰涅磐",
	        "time"   : time,
	        "buff_msg" : "凤凰涅磐消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
	        "disa_msg" : "",
	        "disa_type": 0,
	]);
	BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
