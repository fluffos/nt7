// This program is a part of NT MudLIB
// wuzhuan.c 奇门五转

#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_SSERVER;

int exert(object me, object target)
{
        string msg;
        int i, extra,time;
        mapping buff, data;

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你所用的内功与「奇门五转」心法相悖！\n");

        if( me->query_skill("bibo-shengong", 1) < 100 )
                return notify_fail("你的内功修为火候未到，还未领悟「奇门五转」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够，劲力不足以施展「奇门五转」！\n");
        
        if( me->query_skill("qimen-wuxing", 1) < 1200 )
                return notify_fail("你的奇门五行修为不够，还未领悟「奇门五转」！\n");

        if( BUFF_D->check_buff(me, "dodgeup") )
                return notify_fail("你正在运用「奇门五转」心法！\n");

        msg = HIG "$N脸上青气大盛，脚下缓缓踩着九宫八卦方位，头顶冒出腾腾白气，";
        msg += "四面隐隐传来潮涌之声，碧波神功已发挥到极致！\n"NOR;

        addn("neili", -200, me);
        time = me->query_con()*2;
        extra = (int)me->query_skill("qimen-wuxing",1)* query("int",me);
                extra+= (int)me->query_skill("qimen-wuxing",1)*me->query_int()/10000;
        data = ([
                "attack" : extra/2,
                "defense": extra/2,
                "dodge"  : extra,
        ]);
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "dodgeup",
                "attr"  : "bless",
                "name"  : "碧波神功·奇门五转",
                "time"  : time,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "$N只觉真气运转不畅，不得不放慢步法，调息吐纳。\n",
                "disa_type":1,
                        
        ]);
        //set_temp("wuzhuan_hit", extra/60+random(2), me);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}

