
// fengyun.c

#include <ansi.h>

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 120) return notify_fail("你的临济十二庄修为还不够。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的内力还不够强。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真气不够。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");

        if( BUFF_D->check_buff(me, "ljz_fengyun") ) 
                return notify_fail("你此时四肢百骸真气鼓荡，不必再次运功。\n");

        msg = HIY + "只见$N微闭双眼，身旁凝起一圈白雾，瞬息间一股旋风卷过，$N身形又复清晰。\n" NOR;

        addn("neili", -level, me);
        level /= 10;
        
        data = ([
                "dex": level,
                "attack": -level/2,
                "armor" : level*15,
                "defense": level*5,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "dodgeup",
                "type2"  : "ljz_fengyun",
                "attr"  : "bless",
                "name"  : "临济十二庄·风云",
                "time"  : level*10,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的临济十二庄运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        
        tell_object(me, HIY "你暗运风云两庄，心思浮云飘空之悠闲缓慢，默想狂风荡地之迅速紧急，\n一股丹田热气分注四肢百骸，但觉身手敏捷了许多。\n" NOR);
        if (me->is_fighting()) me->start_busy(2);
        return 1;
}
