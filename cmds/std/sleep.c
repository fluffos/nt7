// sleep.c
// Updated by Lonely

#include <ansi.h>
#include <command.h>

void wakeup(object me);

int main(object me, string arg)
{
//      object obj,old_target;
        int i;
//      object *inv;
        mapping fam;
        mapping cnd;
        string *kc;
        object where = environment(me);
        object bag;
        int qi, jing;

        seteuid(getuid());

        if (! where) return 1;

        if( (!(fam=query("family", me)) || fam["family_name"] != "丐帮" )
              && !(query("sleep_room", where) )
             && !objectp(bag = present("sleepbag", me))
              || (query("no_sleep_room", where)) )
             return notify_fail("这里不是你能睡的地方！\n");


        if (me->is_busy())
                return notify_fail("你正忙着呢！\n");

        if( me->is_fighting() )
                return notify_fail("战斗中不能睡觉！\n");

        if( query("hotel", where) && !(query_temp("rent_paid", me)) )
        {
                message_vision("店小二从门外对$N大叫：把这里"
                               "当避难所啊！先到一楼付钱后再来睡！\n",me);
                return 1;
        }

        jing=query("jing", me);
        qi=query("qi", me);
        if (jing < 0 || qi < 0)
                return notify_fail("你现在接近昏迷，睡不着觉。\n");
        cnd = me->query_condition();
        if (cnd && sizeof(cnd))
        {
                kc   = keys(cnd);
                for (i = 0; i < sizeof(kc); i++)
                {
                        if (CONDITION_D(kc[i])->min_qi_needed(me) > qi ||
                            CONDITION_D(kc[i])->min_jing_needed(me) > jing)
                        {
                                message("vision", me->name() + "看样子是想睡觉，"
                                        "可是辗转反侧，就是睡不着。\n",
                                        environment(me), me);
                                tell_object(me, "你想合上眼睛好好睡上一觉，可是" +
                                            to_chinese(kc[i]) + "不断折磨着你，"
                                            "让你辗转难眠。\n");
                                return 1;
                        }
                }
        }

        if( query("sleep_room", where) )
        {
            write("你往床上一躺，开始睡觉。\n");
            write("不一会儿，你就进入了梦乡。\n");
            set_temp("block_msg/all", 1, me);
            message_vision("$N一歪身，倒在床上，不一会"
                           "便鼾声大作，进入了梦乡。\n",me);
        } else
        if (objectp(bag = present("sleepbag", me)))
        {
                write("你展开一个睡袋，钻了进去，开始睡。\n");
            write("不一会儿，你就进入了梦乡。\n");
            set_temp("block_msg/all", 1, me);
            message_vision("$N展开一个睡袋，钻了进去，不一会就进入了梦乡！\n",me); 
        } else
        {
            write("你往地下角落一躺，开始睡觉。\n");
            write("不一会儿，你就进入了梦乡。\n");
            set_temp("block_msg/all", 1, me);
            message_vision("$N往地下角落屈身一躺，不一"
                           "会便鼾声大作，做起梦来。\n",me);
        }

        set("no_get", 1, me);
        set("no_get_from", 1, me);

        set_temp("sleeped", 1, me);
        if( query("hotel", where) )
            delete_temp("rent_paid", me);

        me->disable_player(" <睡梦中>");
        me->start_call_out(bind((: call_other, __FILE__, "wakeup", me :), me),
                           3 + random(120/me->query_con()));

        return 1;
}

void wakeup(object me)
{
        if( !me || !query_temp("sleeped", me) )
                return;

        if (living(me))
        {
                delete_temp("sleeped", me);
                return;
        }

        me->enable_player();
        set_temp("block_msg/all", 0, me);
        delete("no_get", me);
        delete("no_get_from", me);
        delete_temp("sleeped", me);

        // if (time() - me->query("last_sleep") >= 30)
        if (time())
        {
                set("qi",query("eff_qi",  me), me);
                set("jing",query("eff_jing",  me), me);
                if( query("neili", me)<query("max_neili", me) )
                        set("neili", query("max_neili", me), me);
                /*
                me->add("neili",query("max_neili", me)/2-
                                 query("neili", me)/2);
                */
                message("vision", me->name() + "一觉醒来，精力充沛"
                                  "地活动了一下筋骨。\n",
                        environment(me), ({ me }));
                write("你一觉醒来，只觉精力充沛。该活动一下了。\n");
                set("last_sleep", time(), me);
        } else
        {
                message("vision", me->name() + "迷迷糊糊的睁开眼睛，"
                                  "懒散无神的爬了起来。\n",
                        environment(me), ({ me })); 
                write("你迷迷糊糊的睁开双眼，爬了起来。\n");
        }
        me->write_prompt();
}

int help(object me)
{
        write(@HELP
指令格式 : sleep
 
顾名思义，这个指令是用来睡觉的。
HELP );
        return 1;
}