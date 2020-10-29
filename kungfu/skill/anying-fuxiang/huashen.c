// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int i;
        mapping data, buff;
        
        if (! me->is_fighting())
                return notify_fail("你只能在战斗种使用诸天化身步。\n");

        if ((int)me->query_skill("linji-zhuang", 1) < 100)
                return notify_fail("你的临济十二庄还不够火候，使不出诸天化身步。\n");  

        if ((int)me->query_skill("anying-fuxiang", 1) < 100)
                return notify_fail("你的暗影浮香还不够火候，使不出诸天化身步。\n");  

        if( query("jing", me)<500 )
                return notify_fail("你现在精不够。\n");

        if( query("neili", me)<500 )
                return notify_fail("你现在内力不够。\n");

        if( BUFF_D->check_buff(me,"dodgeup") )
                return notify_fail("你已经在运用类似的武功了。\n");

        msg = HBYEL "$N使出暗影浮香的诸天化身步，身手登时更加灵巧！\n\n" NOR; 

        addn("neili", -200+random(100), me);
        me->recieve_damage("jing", 50);
        
        i = me->query_skill("linji-zhuang", 1) / 5;
        data = ([
                "dex" : i,
                "con" : i,      
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "dodgeup",
                "attr"  : "bless",
                "name"  : "暗影浮香·诸天化身步",
                "time"  : me->query_skill("force") / 3,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你停止了诸天化身步，深深的吸了口气。\n",                        
        ]);
        BUFF_D->buffup(buff);
        return 1;
}
