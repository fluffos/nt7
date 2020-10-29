// hand.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
       int lvl;
       string *can_perform;

       can_perform=query("can_perform/martial-cognize", me);

       if(!can_perform || 
          !arrayp(can_perform) || 
          !sizeof(can_perform) || 
          member_array("hand",can_perform) == -1
         )
                return notify_fail("你还没有学会使用［天龙之手］！\n");

        if (me->is_busy())
                return notify_fail("你上一个动作还没有完成，无法使用天龙之手。\n");

        lvl = (int)me->query_skill("martial-cognize",1);

       if(lvl < 250)
                return notify_fail("你的武学修养不够高深！\n");

        if( query("jingli", me)<500 )
                return notify_fail("你的精力不够！\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("你的精力还没有达到足够的层次！\n");

       if( query("jing", me) <= 300 )
                return notify_fail("你的精神状态不好！\n");

        if( !target || !target->is_character() )
                return notify_fail("你要对谁使用［天龙之手］？\n");

        if( target->is_corpse() )
                return notify_fail("来不及了，只有活人才能救醒。\n");

       if(me->is_fighting() || target->is_fighting())
                return notify_fail("战斗中不能使用［天龙之手］！\n");

        addn("jingli", -400, me);
        me->receive_damage("jing", 250);

       if (target == me)
                message_vision( HIY "$N双手交叠贴在额头, 闭上眼睛缓缓低吟...\n" NOR, me);
        else
                message_vision( HIY "$N一手放在$n的天灵盖上, 一手贴在$n的后心, 闭上眼睛缓缓低吟...\n" NOR, me, target);
        message_vision( HIY "$N脸上绽放出婴孩般的笑容，似乎正处身于西方极乐世界...\n" NOR, target);

       if( query("jing", target)<1 )
                set("jing", 1, target);
       if( query("max_jing", target)<1 )
                set("max_jing", 1, target);

       if( query("qi", target)<1 )
                set("qi", 1, target);
       if( query("eff_qi", target)<1 )
                set("eff_qi", 1, target);

        if(! living(target))
                target->revive();

       target->remove_all_killer();
        return 1;
}