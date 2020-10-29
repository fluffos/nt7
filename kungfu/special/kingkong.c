// This program is a part of NITAN MudLIB
// kingkong.c 大力金刚
// Created by Lonely@NITAN (04/05/2009)

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIR "大力金刚" NOR; }

int perform(object me, string skill)
{
        object target;
        string msg;
        int ap, dp;

        if( !query("yuanshen_level", me) )
                return notify_fail("你尚未转世重生，无法使用此技能！\n");

        if( !target ) { 
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        } 

        if( !target || !target->is_character() 
         || query("not_living", target) )
                return notify_fail("你打算对谁施展" + name() + "？\n");
                
        if( !me->is_fighting(target) ) 
                return notify_fail(name() + "只能对战斗中的对手使用。\n");      

        if( !query_temp("special_skill/immortal", target) )
                return notify_fail("对方并没有运起不死金身呀 ？\n");
       
        message_vision( HIR "$N" HIR "面色突然变得赤红，双手灌入巨大真力，"
                        HIR "重重一招袭向$n。\n\n" NOR, me, target);

        ap = me->query_str(); 
        dp = target->query_con();
        if( ap / 2 + random(ap) > dp ) {
                delete_temp("special_skill/immortal", target);
                message_vision( CYN "只听$n" CYN "闷哼一声，"
                                CYN "不死金身竟被$N" CYN "击溃！\n\n" NOR, me, target );

                tell_object( target, HIW "你的不死金身被" NOR + me->name() +
                                    HIW "破除了！\n\n" NOR );           
        } else 
                message_vision( HIY "只见$n" HIY "硬生生接下$N" HIY "这一招，"
                                HIY "不死金身丝毫不为所动！\n\n" NOR, me, target );

        me->start_busy( 1 + random(2) );
        return 1;
}

