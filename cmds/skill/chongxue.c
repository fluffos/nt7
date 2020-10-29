// This program is a part of NT MudLIB

#include <ansi.h>

#define ZHOUTIAN_D      "/adm/daemons/zhoutiand"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object tongren_ob;

        if( me->is_busy() || me->is_fighting() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || arg == "" )
                return notify_fail("指令格式 : chongxue <穴位铜人ID>\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的内功修为不足，无法将细小经脉穴位打通。\n");

        if( (int)me->query_skill("jingluo-xue", 1) < 100 )
                return notify_fail("你对经络学掌握不够，无法将细小经脉穴位打通。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你现在的气太少了，无法静心冲穴。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你现在的精太少了，无法静心冲穴。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你觉得内力颇有不足，无法将细小经脉穴位打通。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你现在的内力太少了，无法运功冲穴。\n");

        if( arg == "all" )
        {
                if( !query("jingmai/finish", me) )
                        return notify_fail("你并没有全身大小周天经脉穴道贯通过。\n");

                set("breakup", 1, me);
                message_vision( HIC "突然$N" HIC "大喝一声，一股无形气浪" 
                                HIC "陡然散布开来，四周空气登时变得燥热。\n" NOR, me); 
                tell_object(me, HIG "你顿时觉得浑身一阵轻松，一股清凉之意油然" 
                                HIG "而起，心灵一片空明，内力没有丝毫阻滞，全身经脉已然畅通，舒泰之极。\n" NOR); 
                return 1;
        }

        if( query("jingmai/finish", me) )
                return notify_fail("你已经打通全身大小周天经脉，无需再次冲穴。\n");

        if( !objectp(tongren_ob = present(arg, me)) )
                return notify_fail("你身上没有这个铜人！\n");

        if( !tongren_ob->is_tongren() )
                return notify_fail("你无法使用它来冲穴。\n");

        if( query("jingmai/"+query("jingmai_name", tongren_ob)+"/"+arg, me) )
                return notify_fail("你已经打通了这个穴位。\n");

        message_vision(HIW "$N" HIW "按照铜人所记载的冲穴方式，借助铜人之物，暗运内功，开始冲穴。\n" NOR, me);
        message_vision(HIW "只见$N" HIW "头上白雾腾腾、浑身如同笼罩在云中。\n" NOR, me);

        tell_object(me, HIG "你觉得内力在丹田源源而生，快速翻滚，体内真元运转越来越快，\n"
                        HIG"浑身燥热难当，一股真气流冲向"+query("xuewei_name", tongren_ob)+"而去。\n"NOR);


        ZHOUTIAN_D->do_chongxue(me, tongren_ob);

        me->start_busy(1);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : chongxue <穴位铜人ID>
           chongxue all    如果上世曾经大小周天经脉穴道贯通过，使用该指令冲穴

该指令可以细小经脉打通，连接成完整经脉。

HELP
);
        return 1;
}


