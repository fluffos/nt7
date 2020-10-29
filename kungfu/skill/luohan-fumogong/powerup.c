#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;
        string fam;
        
        fam = query("family/family_name", me);

        // 要求只有喝过玄冰碧火酒或是少林派玩家才能施展
        if (userp(me)
           && fam != "少林派"
            && !query("skybook/item/xuanbingjiu", me) )
                return notify_fail("你所学的内功中没有这种功能。\n");

        if (target != me)
                return notify_fail("你只能用罗汉伏魔神功来提升自己的战斗力。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me, "powerup") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        if( query("skybook/item/xuanbingjiu", me )
           && fam == "少林派")
                msg = HIY "$N" HIY "高呼一声佛号，运起罗汉伏魔神"
                                "功，全身皮肤一半呈现" NOR + HIB "靛青" HIY
                                "色，另一半却为" HIR "血红" HIY "色。\n"
                                NOR;
        else

        if (fam == "少林派")
                msg = HIY "$N" HIY "高呼一声佛号，运起罗汉伏魔神"
                                "功，全身真气澎湃，衣衫随之鼓胀。\n"
                                NOR;

        else
                msg = HIY "$N" HIY "微一凝神，运起罗汉伏魔神功，"
                                "全身肌肤竟交替呈现出" NOR + HIB "靛青" HIY
                                "与" HIR "血红" HIY "两色。\n" NOR;

 
        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "罗汉伏魔神功·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的罗汉伏魔神功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if (me->is_fighting())
                me->start_busy(3);
        return 1;
}
