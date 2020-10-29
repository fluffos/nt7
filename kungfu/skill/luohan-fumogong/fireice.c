#include <ansi.h>

inherit F_CLEAN_UP;

#define FIREICE "「" HIW "冰" HIR "火" HIW "九重天" NOR "」"

int exert(object me, object target)
{
        mapping buff, data;
        int skill;
        string fam;
        string msg;
        
        fam = query("family/family_name", me);

        if( userp(me) && !query("skybook/item/xuanbingjiu", me) )
                 return notify_fail("你所学的内功中没有这种功能。\n");

        if (target != me)
                return notify_fail("你只能用" FIREICE "来提升自己的战斗力。\n");

        if( BUFF_D->check_buff(me, "fireice") )
                return notify_fail("你现在正在施展" FIREICE "。\n");

        if ((int)me->query_skill("luohan-fumogong", 1) < 180)
                return notify_fail("你罗汉伏魔功火候不足，难以施展" FIREICE "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的内力修为不足，难以施展" FIREICE "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在的内力不足，难以施展" FIREICE "。\n");

        skill = me->query_skill("luohan-fumogong", 1);
        addn("neili", -300, me);
        me->receive_damage("qi", 0);

        msg = HIC "$N" HIC "纵声长啸，运转「" HIW "冰"
                        HIR "火" HIW "九重天" HIC "」真气，聚力"
                        "于掌间，光华流动，煞为壮观。\n" NOR;

        data = ([
                "unarmed_damage": skill*4, 
                "damage": skill*4,
                "armor": skill*4,
      ]); 

        buff = ([
                "caster": me,
                "target": me,
                "type"  : "fireice",
                "attr"  : "bless",
                "name"  : "罗汉伏魔功·冰火九重天",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的冰火九重天运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        
        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}
