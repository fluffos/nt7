// xiulian.c

#include <ansi.h>

inherit F_CLEAN_UP;

int mending(object me);
int halt_mending(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int lvl;
        object where;
        string msg, sign;

        seteuid(getuid());
        where = environment(me);

        if (! arg) return notify_fail("你要修炼什么？\n");
                
        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( !query("no_fight", where) )
                return notify_fail("在这里修炼？不太安全吧？\n");

        if( !query("sleep_room", where) )
                return notify_fail("你得找一个能够休息的地方修炼。\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你现在的气太少了，无法静心修炼。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你现在的精太少了，无法静心修炼。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你现在的内力太少了，无法静心闭关。\n");
                
        if (! me->query_skill("yinyang-shiertian"))
                return notify_fail("你连阴阳九转十二重天还没有学会，怎么去修炼？\n");

        if( query("yinyang-shiertian/succeed", me) )
                return notify_fail("你已经将阴阳九转十二重天修炼到了最高境界！\n");
                                
        lvl = me->query_skill("yinyang-shiertian", 1);                                
        
        switch (arg)
        {
        case "shier":         
        
                if( !query("can_perform/yinyang-shiertian/zhen", me) )
                        return notify_fail("你还没有修炼成阴阳境界，就想修炼十二重天境界？\n");
                 
                if( !query("can_perform/yinyang-shiertian/jiu", me) )
                        return notify_fail("你还没有修炼成乾坤境界，就想修炼十二重天境界？\n");
                        
                if (lvl < 1200)
                        return notify_fail("你的阴阳九转十二重天修为不够，难以修炼十二重天境界！\n");

                if( query("max_neili", me)<50000 )
                        return notify_fail("你觉得内力颇有不足，看来目前还难以修炼十二重天境界。\n");

                if( query("max_jingli", me)<50000 )
                        return notify_fail("你觉得精力颇有不足，看来目前还难以修炼十二重天境界。\n");

                if( query("max_qi", me)<50000 )
                        return notify_fail("你觉得气血颇有不足，看来目前还难以修炼十二重天境界。\n");

                if( query("potential", me)-query("learned_points", me)<500000 )
                        return notify_fail("你的潜能不够，没法修炼。\n");
                                                                
                msg = "十二重天";
                sign = "shier";
                break;
                
        case "qiankun":        
        
                if( !query("can_perform/yinyang-shiertian/zhen", me) )
                        return notify_fail("你还没有修炼成阴阳境界，就想修炼乾坤境界？\n");
                 
                if( query("can_perform/yinyang-shiertian/jiu", me) )
                        return notify_fail("你已经修炼成乾坤境界，不必再重复修炼！\n");
                                                        
                if (lvl < 800)
                        return notify_fail("你的阴阳九转十二重天修为不够，难以修炼乾坤境界！\n");

                if( query("max_neili", me)<30000 )
                        return notify_fail("你觉得内力颇有不足，看来目前还难以修炼乾坤境界。\n");

                if( query("max_jingli", me)<30000 )
                        return notify_fail("你觉得精力颇有不足，看来目前还难以修炼乾坤境界。\n");

                if( query("max_qi", me)<30000 )
                        return notify_fail("你觉得气血颇有不足，看来目前还难以修炼乾坤境界。\n");

                if( query("potential", me)-query("learned_points", me)<300000 )
                        return notify_fail("你的潜能不够，没法修炼。\n");                        
                        
                msg = "乾坤";
                sign = "qiankun";
                break;
                
        case "yinyang":

                if( query("can_perform/yinyang-shiertian/zhen", me) )
                        return notify_fail("你已经修炼成阴阳境界，不必再重复修炼！\n");
                        
                if (lvl < 500)
                        return notify_fail("你的阴阳九转十二重天修为不够，难以修炼阴阳境界！\n");

                if( query("max_neili", me)<10000 )
                        return notify_fail("你觉得内力颇有不足，看来目前还难以修炼阴阳境界。\n");

                if( query("max_jingli", me)<10000 )
                        return notify_fail("你觉得精力颇有不足，看来目前还难以修炼阴阳境界。\n");

                if( query("max_qi", me)<10000 )
                        return notify_fail("你觉得气血颇有不足，看来目前还难以修炼阴阳境界。\n");

                if( query("potential", me)-query("learned_points", me)<100000 )
                        return notify_fail("你的潜能不够，没法修炼。\n");                        
                
                msg = "阴阳";
                sign = "yinyang";
                break;
                
        default:
                return notify_fail("你想要修炼什么？！\n");                
        }


        message_vision("$N盘膝坐下，开始冥神运功，闭关修行阴阳九转十二重天。\n", me);
        set("startroom", base_name(where), me);
        set("doing", "xiulian", me);
        set("yinyang-shiertian/xiulian", sign, me);
        CLOSE_D->user_closed(me);
        me->start_busy(bind((: call_other, __FILE__, "mending" :), me),
                       bind((: call_other, __FILE__, "halt_mending" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s%s(%s)开始闭关修行，试图修炼阴阳九转十二重天的" + msg + "境界。",
                              ultrap(me) ? "大宗师" : "",
                              me->name(1),query("id", me)));

        return 1;
}

int continue_mending(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "mending" :), me),
                       bind((:call_other, __FILE__, "halt_mending" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n你继续闭关修行阴阳九转十二重天...\n" NOR);
        return 1;
}

private void stop_mending(object me)
{
        CLOSE_D->user_opened(me);
        if (! interactive(me))
        {
                me->force_me("chat* sigh");
                call_out("user_quit", 0, me);
        }
}

int mending(object me)
{
        string msg = "";

        if( query("potential", me) <= query("learned_points", me) )
        {
                tell_object(me, "你的潜能耗尽了。\n");
                message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
                msg = "退出";
        }
        
        switch(query("yinyang-shiertian/xiulian", me) )
        {
        case "shier":
        
                if( query("max_qi", me)<10000 || query("max_neili", me)<10000
                 || query("max_jingli", me)<2000 )
                {
                        tell_object(me, "你的状态不佳，无法继续修炼阴阳九转十二重天。\n");
                        message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
                        msg = "退出";
                }
                set("max_qi",query("max_qi",  me)-2, me);
                set("max_neili",query("max_neili",  me)-2, me);
                set("max_jingli",query("max_jingli",  me)-1, me);
                
                break;

        case "qiankun":
        
                if( query("max_jingli", me)<2000 )
                {
                        tell_object(me, "你的状态不佳，无法继续修炼阴阳九转十二重天。\n");
                        message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
                        msg = "退出";
                }
                set("max_jingli",query("max_jingli",  me)-1, me);
                
                break;

        case "yinyang":

                if( query("max_neili", me)<2000 )
                {
                        tell_object(me, "你的状态不佳，无法继续修炼。\n");
                        message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
                        msg = "退出";
                }
                set("max_neili",query("max_neili",  me)-1, me);
                
                break;
        }       

        if( query("neili", me)<query("max_neili", me) )
                set("neili",query("max_neili",  me), me);

        if( query("eff_jingli", me)<query("max_jingli", me) )
                set("eff_jingli",query("max_jingli",  me), me);

        if( query("eff_qi", me)<query("max_qi", me) )
                set("eff_qi",query("max_qi",  me), me);

        if (msg == "退出")
        {
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                        sprintf("听说%s(%s)闭关修炼阴阳九转十二重天结束，似乎没有太大的进展。",
                                me->name(1),query("id", me)));

                if (! interactive(me))
                {
                        me->force_me("chat* sigh");
                        call_out("user_quit", 0, me);
                }
                return 0;
        }
        
        addn("learned_points", 1, me);


        if (random(10) == 0)
                tell_object(me, "修炼阴阳九转十二重天中...\n");

        if (random(4000000) < me->query_skill("yinyang-shiertian", 1))
        {
                tell_object(me, HIR "恭喜你对阴阳九转十二重天有新的领悟，武学境界又有突破！\n" NOR);
 
                if( query("yinyang-shiertian/xiulian", me) == "shier" )
                {
                        addn("yinyang-shiertian/shier", 1, me);
                        if( query("yinyang-shiertian/shier", me) == 12 )
                        {
                                delete("yinyang-shiertian", me);
                                set("yinyang-shiertian/succeed", 1, me);
                                set("can_perform/yinyang-shiertian/tian", 1, me);
                                set("potential",query("learned_points",  me), me);
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                                sprintf("听说%s(%s)领悟到了阴阳九转十二重天的「十二重天」，窥视到了无上的武学境界。",
                                                                me->name(1),query("id", me)));
                                CHAR_D->setup_char(me);
                                stop_mending(me);
                                return 0;
                        }
                
                }

                if( query("yinyang-shiertian/xiulian", me) == "qiankun" )
                {
                        addn("yinyang-shiertian/jiu", 1, me);
                        if( query("yinyang-shiertian/jiu", me) == 9 )
                        {
                                delete("yinyang-shiertian", me);
                                set("can_perform/yinyang-shiertian/jiu", 1, me);
                                set("potential",query("learned_points",  me), me);
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                                sprintf("听说%s(%s)领悟到了阴阳九转十二重天的「九转乾坤」，武学境界又有突破。",
                                                        me->name(1),query("id", me)));
                                CHAR_D->setup_char(me);
                                stop_mending(me);
                                return 0;
                        }                
                }
        
                if( query("yinyang-shiertian/xiulian", me) == "yinyang" )
                {
                        switch(query("yinyang-shiertian/zhen", me) )
                        {
                        case "yinyang":
                                delete("yinyang-shiertian", me);
                                set("can_perform/yinyang-shiertian/zhen", 1, me);
                                set("potential",query("learned_points",  me), me);
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        sprintf("听说%s(%s)领悟到了阴阳九转十二重天「镇阴阳」，武学境界又有突破。",
                                                me->name(1),query("id", me)));
                                CHAR_D->setup_char(me);
                                stop_mending(me);
                                return 0;

                        case "yin":
                                delete("yinyang-shiertian/zhen", me);
                                set("yinyang-shiertian/zhen", "yinyang", me);
                                break;

                        default:
                                set("yinyang-shiertian/zhen", "yin", me);
                        }
                } 

                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("听说%s(%s)经过闭关苦修，对阴阳九转十二重天有新的领悟。",
                                              me->name(1),query("id", me)));

                me->improve_skill("yinyang-shiertian", 250000);
        }

        if( query("yinyang-shiertian/xiulian", me) == "shier" )
        {
                switch (random(4))
                {
                case 0:
                        msg = "随着时间的流逝，$N头顶蒸腾出阵阵白色烟霞，刹那间，"
                              "异香四散飘开，原来的浑浊污秽之气全被驱散，只留下心旷神怡的清新与芬芳。\n";
                        break;

                case 1:
                        msg = "$N顶上的那股白雾舒卷不定，仿佛什么都不是，但若仔细看时，"
                              "却是在不断地幻化成世间万物的种种神态，但其中好像有什么东西却是不变的。\n";
                        break;

                case 2:
                        msg = "那股白雾再度变换姿态，逐渐地沉了下去，裹住$N的身形，"
                              "不停地在$N的周围转动，速度越来越快，远远望去，像是一条白龙围着$N的身形撒欢。\n";
                        break;

                default:
                        msg = "$N的嘴角微微上翘，荡漾出一阵笑意在脸颊上，周围的白雾随着笑意"
                              "的流淌慢慢地变淡了，变没了，只是$N的眼神里平添了一分光华。\n";
                        break;
                }
        }
                
        if( query("yinyang-shiertian/xiulian", me) == "qiankun" )
        {
                switch (random(5))
                {
                case 0:
                        msg =  "$N想了想，说了一声“山”，然后便一动不动地伫立于天地间，"
                               "整个人从内到外都处于一种极静止的状态，任世间怎样的动荡，也决不动摇半分。\n";
                        break;

                case 1:
                        msg = "$N想了想，说了一声“水”，身形还是在那里不动分毫，但是旁人"
                              "看来$N好像是一朵雪花，一直在飘摇不定，竟无法"
                              "捕捉住$N的影子。\n";
                        break;

                case 2:
                        msg = "$N想了想，说了一声“风”，只见周围地上的落叶渐渐地被卷起，"
                              "无助的在半空中飘着，可是$N却感觉不出风自哪个方向"
                              "掠过$N的胸膛。\n";
                        break;

                case 3:
                        msg = "$N忽然长笑三声，一种看穿一切的自信流露在一投手、一举足之中，"
                              "显见得胸中自有丘壑，不与人同。\n";
                        break;

                default:
                        msg = "$N突然伸出手在半空中划了一道痕迹，那道痕迹仿佛山那般极静，"
                              "又如水那样极动，更像风似的极变，它蕴含了天地间的至理，一切都在循环变动"
                              "中往复。\n";
                        break;
                }
        }

        if( query("yinyang-shiertian/xiulian", me) == "yinyang" )
        {
                if( query("yinyang-shiertian/zhen", me) == "yin" )
                        msg = "$N脚下不丁不八，倚着浑厚的大地身形凝重如山，一股寒阴之气"
                              "自地底极深处传入$N的四经八脉。\n";
                else
                if( query("yinyang-shiertian/zhen", me) == "yinyang" )
                {
                        if (random(2) == 1)
                                msg = "$N脸色红白不定，双目颜色也变了样，一瞳含火，鲜红欲滴，"
                                      "一瞳含冰，秋霜不化，良久方自散去。\n"; 
                        else
                                msg = "$N周身中，寒阴之气盘旋于经脉之间，唯独心神处炽热不变，"
                                      "一个恍惚，玄阳之气却进入经脉，寒阴之气倒守护在心神左右。\n";
                }
                else
                        msg = "$N运目逼视光芒四射的红日，化神为虚，竟不觉如何的刺眼，"
                              "一道玄阳之气于头顶间散落于空中再复回到$N的心间。\n";                
        }

        message_vision(msg, me);
        return 1;
}

int halt_mending(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "你中止了修炼阴阳九转十二重天。\n");
        message_vision(HIY "$N" HIY "轻轻叹了一口气，缓缓的睁开眼。\n\n" NOR, me);
        addn("potential", (query("learned_points", me)-query("potential", me))/2, me);
        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "修炼阴阳九转十二重天中途突然复出。");
        return 1;
}

private void user_quit(object me)
{
        if (! me || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
指令格式 : xiulian

修炼境界乃是将自身的武学境界融入阴
阳九转十二重天当中，阴阳九转十二重
天在来世当中从某中意义上来说已经不
算是一种单纯的武学招式，而是一种武
学境界，因为其乃天下最厉害的几种武
学演练而成，其威力可想而知，所以不
能靠单纯的几招几式来体现出其整体，
所以需要修炼出几种特殊的境界，只有
拥有者将这几种境界修炼成功后，方能
将阴阳九转十二重天发挥自如。

HELP );
        return 1;
}