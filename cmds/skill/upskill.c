// upgrade

#include <ansi.h>

inherit F_CLEAN_UP;

#define PERIOD          864
#define PERIOD_POT      20000
#define PERIOD_MAR      12000

int clossing(object me);
int halt_closing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;
        
        seteuid(getuid());
        where = environment(me);
        
        if (! arg)
               return notify_fail("你要闭关钻研什么武功？\n");
        
        if (! me->query_skill(arg) || 
            file_size(SKILL_D(arg) + ".c") < 0)    
               return notify_fail("你要钻研的武功不存在或你不会该武功。\n");
        
        //if (! SKILL_D(arg)->is_invent_skill())
        if (me->query_skillo(arg, 1) < 4600 )
               return notify_fail("你对" + to_chinese(arg) + "的领悟还不够，无法提升其COMBAT威力。\n");  
               
        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( !query("no_fight", where) )
                return notify_fail("在这里闭关钻研？不太安全吧？\n");

        if( !query("sleep_room", where) )
                return notify_fail("你得找一个能够休息的地方闭关钻研。\n");

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");
                        
        if( query("combat_exp", me)<10000000000 )
                return notify_fail("你的经验不够，没法闭关钻研。\n");

        if( query("potential", me)-query("learned_points", me)<1000000 )
                return notify_fail("你的潜能不够，没法闭关钻研。\n");

        if( query("experience", me)<query("learned_experience", me)+600000 )
                return notify_fail("你现在积累的实战体会还太少。\n"); 
        
        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你现在的气太少了，无法静心钻研。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你现在的精太少了，无法静心钻研。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你觉得内力颇有不足，看来目前还难以"
                                   "进行长时间的闭关钻研。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你现在的内力太少了，无法静心钻研。\n");

        message_vision("$N盘膝坐下，开始冥神运功，闭关钻研" + to_chinese(arg) + "。\n", me);
        set("startroom", base_name(where), me);
        set("doing", "invent", me);
        set("upgrade", arg, me);
        CLOSE_D->user_closed(me, "invent");
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("大宗师%s(%s)开始闭关修炼钻研%s。",
                              me->name(1),query("id", me),to_chinese(arg)));

        return 1;
}

int continue_uping(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me,HIR"\n你继续闭关修炼钻研"+to_chinese(query("upgrade", me))+"...\n"NOR);
        return 1;
}

int closing(object me)
{
        int t;
        int tn;
        mixed pot, mar;
        int r;
        int exp_inc;
        string skill;
        
        skill=query("upgrade", me);
        pot=query("potential", me);
        mar=query("experience", me);

#ifdef DB_SAVE
        if (! interactive(me) && 
            !MEMBER_D->is_valid_member(query("id", me)) && 
            query("online_time", me) <= query("offline_time", me)*3 )
        {
                CLOSE_D->user_opened(me);
                call_out("user_quit", 0, me);
                return 0;
        }
#endif

        if( pot <= query("learned_points", me )
         || mar <= query("learned_experience", me) )
        {
                tell_object(me, "你的潜能或体会耗尽了。\n");
                message_vision("$N睁开双目，缓缓吐了一口气，站了起来。\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("听说%s(%s)修炼钻研%s功德圆满。",
                                      me->name(1),query("id", me),to_chinese(skill)));
                if (! interactive(me))
                {
                        me->force_me("chat* haha");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        if( me->add("learned_points",PERIOD_POT/2+random(PERIOD_POT))>pot )
                set("learned_points", pot, me);

        if( me->add("learned_experience",PERIOD_MAR/2+random(PERIOD_MAR))>mar )
                set("learned_experience", mar, me);
                
        t=query_temp("last_closing", me);
        tn = time();
        if (tn - t < 0)
        {
                set_temp("last_closing", tn, me);
                return 1;
        }

        if (tn - t < PERIOD && query("id", me) != "lonely")
                return 1;

        set_temp("last_closing", tn, me);
                
        if (random(10) == 0)
                //tell_object(me, "闭关修炼" + to_chinese(skill) + "中...\n");
                tell_object(me, "你闭关钻研" + to_chinese(skill) + "，似有所思。\n");
        
        /*
        if ((random(100) < 3) && me->can_improve_neili())
        {
                tell_object(me, HIR "你对内功有所领悟，感到内力进步了！\n" NOR);
                addn("improve/neili", 1, me);
                me->improve_neili(10 + random(20));
        }

        if ((random(100) < 3) && me->can_improve_jingli())
        {
                tell_object(me, HIM "你对神通有所领悟，感到精力进步了！\n" NOR);
                addn("improve/jingli", 1, me);
                me->improve_jingli(5 + random(10));
        }
        */

        exp_inc = 50 + random(100);
        exp_inc = exp_inc * (100 + me->query_skill("martial-cognize", 1)) / 500;
        exp_inc=exp_inc*(100+query("int", me))/100;
        addn("combat_exp", exp_inc, me);
        me->improve_skill("martial-cognize", 800 + random(800));

        tell_object(me, HIM "你脑中突然灵光一闪，你对" + to_chinese(skill) + "有了更深的领悟！\n" NOR); 
        me->improve_skill(skill, 5000 + random(1000));
        SKILLS_D->upgrade_skill_power(skill); 
        CHANNEL_D->do_channel(find_object(SKILLS_D), "rumor", 
                              "江湖传言，武学大宗师" + me->name(1) + "闭关修炼钻研" + 
                              to_chinese(skill) + "，终于完善其破绽之处，并广为流传。"); 

        return 1;
}

int halt_closing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me,"你中止了闭关修炼"+to_chinese(query("upgrade", me))+"。\n");
        message_vision(HIY "$N" HIY "大喝一声，睁开眼来，一股气流登时"
                       "将众人迫退四步。\n\n" NOR, me);

        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                              "修炼"+to_chinese(query("upgrade", me))+"中途突然复出。");
        return 1;
}

protected void user_quit(object me)
{
        if (! objectp(me) || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
指令格式 : upskill

闭关修炼研究武功，只有你武功达到4600级以后才能够闭关修炼研究提升你的武功
的COMBAT数值，要求必须在一个安全并且可以休息的地方才能修炼，修炼前需要有
一百万点潜能及六十万体会，闭关开始以后，玩家离线以后其角色将仍然在线修行，
直到玩家中止修炼(halt)或是潜能或体会耗尽。期间内玩家的经验、修炼武功、武
学修养、以及修炼武功威力将会提升。

HELP );
        return 1;
}
