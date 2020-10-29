// This program is a part of NITAN MudLIB
// astral.c 破妄神瞳
// Created by Lonely@NITAN (04/05/2009)

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_SSERVER;

string name() { return HIW "破妄神瞳" NOR; }

int perform(object me, string skill)
{
        string msg;
        int ap, dp;
        object target;

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

        if( !query_temp("apply/shade_vision", target) )
                return notify_fail("对方并没有运起隐身呀 ？\n");
       
        message_vision( HIR "$N" HIR "施展出破妄神瞳之术，无数星芒射向$n" 
                        HIR "。。。\n\n" NOR, me, target);

        ap = me->query_int(); 
        dp = target->query_dex();
        if( ap / 2 + random(ap) > dp ) {
                delete_temp("apply/shade_vision", target);
                message_vision( CYN "只听$n" CYN "闷哼一声，被星芒击中，顿时无法隐身！\n\n" NOR, 
                                me, target );

                tell_object( target, HIW "你的隐身被" NOR + me->name() + HIW "破除了！\n\n" NOR );           
        } else 
                message_vision( HIY "只见$n" HIY "巧妙躲闪开$N" HIY "的星芒，"
                                HIY "隐身状态丝毫没有受到影响！\n\n" NOR, me, target );

        me->start_busy( 1 + random(2) );
        return 1;
}

