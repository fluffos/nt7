#include <ansi.h>
#include <combat.h>

int is_scborn() { return 1; }

string name() { return HIC "剑灵之哀伤" NOR; }

int perform(object me, string skill, string arg)
{

        int armor, damage, sk;
        string msg;
        
        if( query_temp("special2/aishang", me) )
                return notify_fail("你已经处于极度的哀伤当中了，稍后再施展吧。\n");
        
        set_temp("special2/aishang", 1, me);
        
        armor = 3000;
        damage = 50000;
        sk = 500;
        
        addn_temp("apply/armor", armor, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/sword", sk, me);
        addn_temp("apply/parry", sk, me);
        addn_temp("apply/dodge", sk, me);
        addn_temp("apply/force", sk, me);

        msg = HIY "$N" HIY "轻抚「剑灵之哀伤」，刹那间，浑身散发出淡蓝色的光芒，一直蓝色的蝴蝶从$N" HIY "身体内升起，不断煽动着翅膀。"
              "蝴蝶渐渐地化作一个仙子的模样，凝视着$N" HIY "身上的「剑灵之哀伤」，慢慢地滴下眼泪 …… $N" HIY "不由自主地一阵哀伤，似"
              "乎在此刻与剑灵合为一体！\n" NOR;
        message_vision(sort_msg(msg), me) ;
        
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, armor, damage, sk :), 600);   

        return 1;
}

void remove_effect(object me, int armor, int damage, int skill)
{
        if (! objectp(me))return;

        if( query_temp("special2/aishang", me) )
        {                       
                addn_temp("apply/armor", -1*armor, me);
                addn_temp("apply/damage", -1*damage, me);
                addn_temp("apply/sword", -1*skill, me);
                addn_temp("apply/parry", -1*skill, me);
                addn_temp("apply/dodge", -1*skill, me);
                addn_temp("apply/force", -1*skill, me);
                delete_temp("special2/aishang", me);
                tell_object(me, HIG "你剑灵之哀伤施展完毕。\n" NOR);
        }
}
