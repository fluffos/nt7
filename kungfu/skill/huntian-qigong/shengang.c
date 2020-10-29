// This program is a part of NITAN MudLIB
// shengang.c 混天气功混天神罡

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        object weapon;
        string msg;
        int d_count, count, qi, maxqi, skill;
        mapping buff, data;

        weapon=query_temp("weapon", me);

        if( !query("can_exert/huntian-qigong/shengang", me) )
                return notify_fail(HIG "你还没有受到某人的指点，还不会使用这种功夫。\n" NOR);

        if( BUFF_D->check_buff(me,"shield") )
                return notify_fail(HIG "你已经在运混元天罡了。\n" NOR);

        if( query("neili", me)<200 )
                return notify_fail("你的内力还不够！\n");

        if( (int)me->query_skill("huntian-qigong", 1) < 150 )
                return notify_fail("你的混天气功的修为不够，不能使用混元天罡! \n");

        msg = WHT "$N使出混天气功绝学「混元天罡」，一股白气自顶心泥丸发散而下，全身弥漫在白色薄雾中！\n" NOR;

        qi = query("qi", me);
        maxqi = query("max_qi", me);
        skill = (int) (me->query_skill("huntian-qigong", 1) / 6);
        count = me->query_str();
        d_count = (int)me->query_dex() / 2;

	        
        if( qi > (maxqi * 0.4) )
        {
                addn("neili", -150, me);
                
                data =  ([
                        "damage" : skill*20,
	                "unarmed_damage" : skill*20,
	                "attack": skill*2,
	                "defense":skill*2,
                        "dex" : skill/5,
	        ]);
                buff =
                ([
			"caster": me,
			"target": me,
			"type"  : "shield",
			"attr"  : "bless",
			"name"  : "混天气功·混天神罡",
			"time"  : skill,
			"buff_data": data,	
			"buff_msg" : msg,
			"disa_msg" : "白色的薄雾渐渐散去，$N的身形步法又变的清晰可见。\n",
			"disa_type": 1,
                ]);

                BUFF_D->buffup(buff);
        
        } 
        else
        {
                msg = HIR "$N拼尽毕生功力想提起混元天罡，但自己受伤太重，没能成功!\n" NOR;
                message_combatd(msg, me, target);
        }
        if( me->is_fighting() ) me->start_busy(3);
        return 1;
}
