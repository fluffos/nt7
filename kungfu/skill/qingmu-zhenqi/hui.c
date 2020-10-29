// This program is a part of NITAN MudLIB 
// redl 2015.10
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "回生诀" NOR; }

int perform(object me)
{
        int recoverqi, scale, time;
        mapping buff;

        if( userp(me) && !query("can_perform/qingmu-zhenqi/hui", me) )
                return notify_fail("你目前还没有学会青木回生诀。\n");
        
                if(playerp(me) && (time = BUFF_D->get_buff_overtime(me, "qingmu_hui")) > 0 )
                                return notify_fail(MAG"青木回生诀消耗心神太甚，还需等待"+time+"秒。\n"NOR);

        if (me->query_skill("qingmu-zhenqi", 1) < 380)
                return notify_fail("你的青木真气修为不够，无法施展" + name() + "。\n");

        if ((int)me->query_skill("huisheng-jue", 1) < 2000)
                return notify_fail("你的回生诀不够娴熟，难以施展"  + name() +  "。\n");

        if( query("jing", me)<1000 )
                return notify_fail("你现在精神状态不佳，难以施展"  + name() +  "。\n");
        
        if( query("eff_qi", me)>=(query("max_qi", me)/10*7) && query("qi", me)>=(query("max_qi", me)/10*7) )
                return notify_fail("你现在气血充足，无需施展"  + name() +  "。\n");                
                                
                recoverqi = query("max_qi", me) - query("eff_qi", me);
                if (query("eff_jing", me)/10*7 < recoverqi) {
                        recoverqi = query("eff_jing", me)/10*7;
                        if( recoverqi<10000 )
                        return notify_fail("你现在精神状态危险，不适合施展"  + name() +  "。\n");
                }
                                
                scale = 1 + me->query_skill("qingmu-zhenqi", 1) / 650;
        message_sort(HIW "\n$N" HIW "握拳一顿，体内大量的"HIG"木行元磁力" HIW "喷涌，转瞬恢复了极大的伤势。\n" NOR, me);
//              if (me->is_fighting() && me->is_busy()) {
//                      me->stop_busy();
//              }
                if (scale > 3) {
                        tell_object(me, HIG "你回复了少许内力。\n" NOR);
                        addn("neili", 1000 * scale * scale, me);
                        }
                if (scale > 6) me->set_weak(0);
                
                me->receive_curing("qi", 100 + recoverqi + (int)me->query_skill("huisheng-jue", 1) * (int)me->query_skill("huisheng-jue", 1));
                set("qi", query("eff_qi", me), me);
                me->receive_wound("jing", recoverqi / scale * 3);
                me->receive_damage("jing", recoverqi / scale * 3);
                
                time = 180 - scale;
                if (time < 30) time = 30;
                buff = ([
                "caster" : me,
                "target" : me,
                "type"   : "cooldown",
                "type2"  : "qingmu_hui",
                "attr"   : "curse",
                "name"   : "青木真气·回生诀",
                "time"   : time,
                "buff_msg" : "青木回生诀消耗心神太甚，还需等待"+time+"秒方可再次施展。\n",
                "disa_msg" : "",
                "disa_type": 0,
                ]);
                BUFF_D->buffup(buff);
        
        return 1;
}

