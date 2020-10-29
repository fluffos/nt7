// This program is a part of NITAN MudLIB
// stealth.c 仙隐迷踪
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIK "仙隐迷踪" NOR; }

int perform(object me, string skill)
{
        if( !query("yuanshen_level", me) )
                return notify_fail("你尚未转世重生，无法使用此技能！\n");
            
        if( time()-query("special/stealth", me)<21600 )
                return notify_fail("你要过些时候才能再用此技能！\n");

        message_vision(HIK "$N" HIK "施展出仙隐迷踪，身影越来越淡，渐渐隐身不见了。\n" NOR, me);

        set_temp("apply/shade_vision", 1, me);
        set("special/stealth", time(), me);
        if( me->is_fighting() && me->is_busy() ) {
                me->remove_all_killer(); 
                all_inventory(environment(me))->remove_killer(me); 
                me->stop_busy();
        }
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 30);
        return 1;
}

void remove_effect(object me)
{
        delete_temp("apply/shade_vision", me);
        tell_object(me, "你施展完仙隐迷踪，松了一口气。\n");
        message_vision(HIK "$N" HIK "的身形逐渐显露出来，变的清晰可见。\n" NOR, me);
}
