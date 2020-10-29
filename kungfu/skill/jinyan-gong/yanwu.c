// This program is a part of NITAN MudLIB

#include <combat.h>
#include <ansi.h>

inherit F_SSERVER;

string name() { return "鹰飞雁舞"; }

int perform(object me, object target)
{
        string msg;
        int lvl1, amount;
        mapping buff, data;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「鹰飞雁舞」轻功绝技只能对战斗中的对手使用。\n");

        if( BUFF_D->check_buff(me, "dodgeup") )
                return notify_fail("你正在运用「鹰飞雁舞」轻功绝技！\n");

        /*
        if( me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你所用的内功与「鹰飞雁舞」轻功绝技运气方式相悖！\n");
        */

        if( me->query_skill_mapped("dodge") != "jinyan-gong")
                return notify_fail("你所用的身法与「鹰飞雁舞」招式不同，无法使用！\n");

        if( me->query_skill("dodge") < 134 )
                return notify_fail("你的身法修为不够，还无法施展「鹰飞雁舞」轻功绝技！\n");

        if( me->query_skill("force") < 59 )
                return notify_fail("你的内功修为火候未到，无法施展「鹰飞雁舞」轻功绝技！\n");

        if( query("neili", me)<600 )
                return notify_fail("你的内力不够，劲力不足以施展「鹰飞雁舞」轻功绝技！\n");

        msg = HIC "$N清啸一声，身法陡然加快。$N的身影时如鹰击长空、时如群雁飞舞，令人眼花撩乱，煞是好看。\n\n" NOR;

        lvl1 = (int)me->query_skill("dodge");
        
        addn("neili", -(lvl1)/3, me);
        
        data = ([
                "dex"    : lvl1/5,
                "defense": lvl1/3,
        ]);

        buff = ([
                "caster": me,
                "target": me,
                "type"  : "dodgeup",
                "attr"  : "bless",
                "name"  : "金雁功·鹰飞雁舞",
                "time"  : lvl1/8,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : HIY "$N身形渐停，深吸一口气，收回了「鹰飞雁舞」轻功绝技。\n" NOR,
                "disa_type": 1,
                        
        ]);
        BUFF_D->buffup(buff);
        return 1;
}
