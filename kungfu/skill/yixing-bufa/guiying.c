// guiying.c

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "无形鬼影"; }

int perform(object me, object target)
{
        mapping buff;
        object weapon;
        int skill;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「无形鬼影」只能在战斗中使用。\n");

        if ((int)me->query_skill("yixing-bufa", 1) < 100 )
                return notify_fail("你的意形步法等级不够，不能使出「无形鬼影」！\n");

        if ((int)me->query_skill("dodge", 1) < 100 )
                return notify_fail("你的基本轻功极不够娴熟，不能使出「无形鬼影」！\n");

        if ( me->query_skill_mapped("dodge") != "yixing-bufa"
             || me->query_skill_mapped("force") != "busi-shenlong")
                return notify_fail("你现在无法使出「无形鬼影」进行牵制！\n");

        if( query("neili", me)<300 )
                return notify_fail("你现在真气太弱，不能使出「无形鬼影」！\n");

        if( query("neili", me)<1000 )
                return notify_fail("你现在内力太弱，不能使出「无形鬼影」！\n");

        if( target->is_busy() )
                return notify_fail("对手已经手忙脚乱了,快点攻击吧！\n");

        if( BUFF_D->check_buff(me, "yxbf_guiying") )
                return notify_fail("你已经使出「无形鬼影」步法！\n");

        msg = HIB"$N前后游走，身形闪动，脚踏意形步法，化出数个身形。\n"
                "$n被此「无形鬼影」所迷惑，手足无措，不知哪个$N是真，哪个是假。\n"NOR;
        target->start_busy(4);
        me->start_busy(1);
        addn("neili", -200, me);
        skill = me->query_skill("yixing-bufa", 1)/3;

        buff = ([
                "caster": me,
                "target": me,
                "type"  : "yxbf_guiying",
                "attr"  : "bless",
                "name"  : "碧波神功·战神",
                "time"  : skill,
                "buff_data": "guiying",      
                "buff_msg" : msg,
                "disa_msg" : HIB"$N长吁一声，放慢步法，分身立即消失不见！\n"NOR,
                "disa_type": 1,
                        
        ]);
        BUFF_D->buffup(buff);

        return 1;
}
