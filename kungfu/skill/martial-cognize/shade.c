// shade.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int lvl,i;
        object env, *inv;
       string *can_perform;

       can_perform=query("can_perform/martial-cognize", me);

       if(!can_perform || 
          !arrayp(can_perform) || 
          !sizeof(can_perform) || 
          member_array("shade",can_perform) == -1
         )
                return notify_fail("你还没有学会使用［天龙之雾］！\n");

        if (me->is_busy())
                return notify_fail("你上一个动作还没有完成，无法使用天龙之雾。\n");

        lvl = (int)me->query_skill("martial-cognize",1);

       if(lvl < 250)
                return notify_fail("你的武学修养不够高深！\n");

        if( query("jingli", me)<500 )
                return notify_fail("你的精力不够！\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("你的精力还没有达到足够的层次！\n");

       if( query("jing", me) <= 300 )
                return notify_fail("你的精神状态不好！\n");

       if( query("env/invisibility", me) )
                return notify_fail("你正在施展［天龙之雾］\n");

       if( time()-query("last_shade_time", me)<600 )
                return notify_fail("你刚使用过［天龙之雾］不久，还没有完全恢复过来，先休息一会吧。\n");

       if( environment(me) && query("no_fight", environment(me)) )
                return notify_fail("这里不能使用［天龙之雾］!\n");

        addn("jingli", -300, me);
        me->receive_damage("jing", 200);

        message_vision(HIW "$N面色凝重，两道精光从双目爆射而出，一阵白色雾气迅速涌出鼻孔，把自己浑身上下都包围着，整个人渐渐虚化．．．\n" NOR, me);
                set("env/invisible", 1, me);

       set("last_shade_time", time(), me);
       me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), lvl/5);
       if( me->is_fighting() ) me->start_busy(3);
       return 1;

}
void remove_effect(object me)
{
        delete("env/invisible", me);
        tell_object(me,"你的天龙之雾失效了！\n");
        message_vision(HIW "一阵雾气突然出现，并且越来越浓，旋即又四散而却，$N显身了。\n" NOR,me);
}