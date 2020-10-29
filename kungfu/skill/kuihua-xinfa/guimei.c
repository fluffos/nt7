// guimei.c 鬼魅身法

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill = me->query_skill("force"); 

        if( BUFF_D->check_buff(me, "khxf_guimei") )
                return notify_fail("你已经在运用鬼魅身法了吧？\n");

        if( (int)me->query_skill("kuihua-xinfa", 1) < 100 )
                return notify_fail(HIY "你的葵花心法修为不够。\n" NOR);
        
        if( (int)me->query_skill("pixie-jian", 1) < 120 )
                return notify_fail(HIY "你的辟邪剑法不够熟练。\n" NOR);

        if( query("neili", me)<200 )
                return notify_fail(HIY "你现在真气不足。\n" NOR);

        msg = HIC"但见$N的身形如鬼如魅，飘忽来去，直似轻烟。衣袖带风，却不发出半点声息。\n"NOR;

        addn("neili", -200, me);
        
        data = ([
                "dex" : skill/10,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "khxf_guimei",
                "attr"  : "bless",
                "name"  : "葵花心法·鬼魅身法",
                "time"  : skill/4,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : HIR "你觉得一股浊气沉下丹田，你的鬼魅身法收功了！\n" NOR,
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}
