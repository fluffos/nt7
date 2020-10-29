// animaout.c

#include <ansi.h>

inherit F_CLEAN_UP;

int outing(object me);
int halt_outing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;

        seteuid(getuid());
        where = environment(me);

        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( !query("breakup", me) )
                return notify_fail("你还没有打通大小周天，谈什么元婴出世？\n");

        if( query("animaout", me) )
                return notify_fail("你已经练成元婴出世了，没有必要再来一遍！\n");

/*
        if( query("reborn/times", me) < 1 )
                return notify_fail("你还没有转世过，如何能领悟出修炼元婴出世？\n");
*/

        if (wizardp(me))
                return notify_fail("巫师也要修炼元婴出世？有毛病了？\n");

        if( !query("no_fight", where) )
                return notify_fail("在这里修炼元婴出世？不太安全吧？\n");

        if( !query("sleep_room", where) )
                return notify_fail("你得找一个能够休息的地方闭关修行。\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if( query("potential", me)-query("learned_points", me)<1000 )
                return notify_fail("你的潜能不够，没法闭关修行以修炼元婴出世。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你现在的气太少了，无法静心闭关。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你现在的精太少了，无法静心闭关。\n");

        if( query("max_jingli", me)<2000 )
                return notify_fail("你觉得精力颇有不足，看来目前还难以"
                                   "修炼元婴出世。\n");

        if( query("jingli", me)*100/query("max_jingli", me)<90 )
                return notify_fail("你现在的精力太少了，无法静心闭关。\n");

        message_vision("$N盘膝坐下，开始冥神运功，闭关修行。\n", me);
        set("startroom", base_name(where), me);
        set("doing", "animaout", me);
        CLOSE_D->user_closed(me);
        me->start_busy(bind((:call_other, __FILE__, "outing" :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s%s(%s)开始闭关修行，苦心修炼元婴出世。",
                              ultrap(me) ? "大宗师" : "",
                              me->name(1),query("id", me)));

        return 1;
}

int continue_outing(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "outing" :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n你继续闭关修行以修炼元婴出世...\n" NOR);
        return 1;
}

protected void stop_outing(object me)
{
        CLOSE_D->user_opened(me);
        if (! interactive(me))
        {
                me->force_me("chat* sigh");
                call_out("user_quit", 0, me);
        }
}

int outing(object me)
{
        string msg;

#ifndef NO_FEE
        if (! interactive(me) &&
               !MEMBER_D->is_valid_member(query("id", me)) && 
            query("online_time", me) <= query("offline_time", me)*3 )
        {
                CLOSE_D->user_opened(me);
                call_out("user_quit", 0, me);
                return 0;
        }
#endif

        if( query("potential", me) <= query("learned_points", me) )
        {
                tell_object(me, "你没有办法继续领悟下去了。\n");
                message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("听说%s(%s)闭关结束，似乎没有什么成果。",
                                      me->name(1),query("id", me)));
                if (! interactive(me))
                {
                        me->force_me("chat* sigh");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        addn("learned_points", 1, me);

        if (random(10))
                return 1;

        if( random(40000)<query("con", me) )
        {
                message_vision(HIY "只见$N" HIY "头上现出万朵金莲，光"
                               "华四射，一时间麝香扑鼻、氤氲遍地！\n" NOR, me);
                tell_object(me, HIM "你觉得精力源源而生，忽然心如止水，如身出"
                            "天际，无源无尽、登时大彻大悟。\n" NOR);
                set("animaout", 1, me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("听说%s(%s)经过闭关苦修，终"
                                      "于修成正果，练得元婴出世。",
                                      me->name(1),query("id", me)));
                addn("max_jingli", 1500, me);
                CHAR_D->setup_char(me);
                stop_outing(me);
                return 0;
        }

        switch (random(4))
        {
        case 0:
                msg = "你练精还虚，不住的提升自己的精力。\n";
                break;

        case 1:
                msg = "你将精力化回元神，试图神游三界。\n";
                break;

        case 2:
                msg = "你试图将元神逼出七窍，然后周游四处复又收回。\n";
                break;

        default:
                msg = "你缓缓呼吸吐纳，将空气中水露皆收为己用。\n";
                break;
        }

        tell_object(me, msg);
        return 1;
}

int halt_outing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "你中止了闭关。\n");
        message_vision(HIY "$N" HIY "轻轻叹了一口气，缓缓的睁开眼。\n\n" NOR, me);
        addn("potential", (query("learned_points", me)-query("potential", me))/2, me);
        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "闭关中途突然复出。");
        return 1;
}

protected void user_quit(object me)
{
        if (! me || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
指令格式 : animaout

档你打通任督二脉以后，并且具有非常高深的精力修行时，可以用这
条指令修炼元婴出世。如果成功可以大大的增加你的精和精力上限。

HELP );
        return 1;
}
