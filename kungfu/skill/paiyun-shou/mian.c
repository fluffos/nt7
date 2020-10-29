// This program is a part of NITAN MudLIB
// mian 绵绵不绝


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "绵绵不绝"; }

int perform(object me, object target)
{
        string msg,x;
        int i,j,k,y;

        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target) )
                return notify_fail("「绵绵不绝」只能在战斗中对对手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("使用「绵绵不绝」时必须空手！\n");

        if( (int)me->query_skill("paiyun-shou", 1) < 120 )
                return notify_fail("你的排云推手不够娴熟，不会使用「绵绵不绝」。\n");

        if( query("max_neili", me)<1100 )
                return notify_fail("你现在内力修为不够，不能使用「绵绵不绝」。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在内力太弱，不能使用「绵绵不绝」。\n");

        if( me->query_skill_prepared("hand") != "paiyun-shou"
        ||  me->query_skill_mapped("hand") != "paiyun-shou")
                return notify_fail("你必须全面运用排云推手，才能使用「绵绵不绝」。\n");


        i = (me->query_skill("paiyun-shou", 1)/2);
        if( target->is_busy() ) i*=2;
        if( (int)me->query_skill("paiyun-shou", 1) > 400 )
        {
                y = 10;
        } else
        if( (int)me->query_skill("paiyun-shou", 1) > 180 )
        {
                y = 8;
        }
        else
        {
                y = 6;
        }
        msg = HIY "$N忽然身随掌起，双掌圈动，似虚而实，似柔而刚。一掌拍出，第二掌接踵而至，一连"+chinese_number(y)+"掌，其意如排云滚滚。\n" NOR;
        message_combatd(msg, me, target);
        addn_temp("apply/attack", i, me);

        for(k = 0; k < y; k++)
        {
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);
        }
        addn_temp("apply/attack", -i, me);
        addn("neili", -400, me);
        me->start_busy(2);
        return 1;
}
