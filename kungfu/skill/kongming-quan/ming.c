
#include <ansi.h>

inherit F_SSERVER;

string name() { return "灵台空明"; }

int perform(object me, object target)
{
        object weapon;
        int damage,skill,wap,wdp;
        string *limb, result, str,msg;
        mapping buff, data;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("灵台空明只能对战斗中的对手使用。\n");

        if( BUFF_D->check_buff(me, "atkup") )
                return notify_fail("你已在使用类似功法了！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("空手才能施展灵台空明！\n");

        if( me->query_skill_mapped("unarmed") != "kongming-quan" )
                return notify_fail("你所用的并非空明拳，不能施展灵台空明！\n");

        if( me->query_skill_prepared("unarmed") != "kongming-quan" )
                return notify_fail("你所备的并非空明拳，不能施展灵台空明！\n");

        /*
        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("你所用的并非先天功，施展不出灵台空明！\n");
        */

        if( me->query_skill("force") < 100 )
                return notify_fail("你的先天功火候未到，无法施展灵台空明！\n");

        if( me->query_skill("unarmed") < 100 )
                return notify_fail("灵台空明需要精湛的空明拳方能有效施展！\n");

        if( query("neili", me) <= 300 )
                return notify_fail("你的内力不够使用灵台空明！\n");

        if( query("jing", me) <= 200 )
                return notify_fail("你的精不够使用灵台空明！\n");


        msg = HIY"$N深吸一口气，目光猛然清澈无比，接着双拳十字交错，缓缓向$n推了过去！\n\n"NOR;
        message_combatd(msg, me, target);

        skill =  ( me->query_skill("unarmed") + me->query_skill("force") ) / 3;

        data = ([
                "attack" : skill/2,
                "unarmed_damage": skill, 
                "defense": skill/2,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "atkup",
                "attr"  : "bless",
                "name"  : "空明拳·灵台空明",
                "time"  : skill/10,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你吸了一口气，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn("neili", -skill/2, me);

        addn("jing", -100, me);
        me->start_busy(random(2));
        return 1;
}
