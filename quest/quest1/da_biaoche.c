// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ITEM;

mapping default_dirs = ([
        "north"     : "北面",
        "south"     : "南面",
        "east"      : "东面",
        "west"      : "西面",
        "northup"   : "北边",
        "southup"   : "南边",
        "eastup"    : "东边",
        "westup"    : "西边",
        "northdown" : "北边",
        "southdown" : "南边",
        "eastdown"  : "东边",
        "westdown"  : "西边",
        "northeast" : "东北",
        "northwest" : "西北",
        "southeast" : "东南",
        "southwest" : "西南",
        "up"        : "上面",
        "down"      : "下面",
        "enter"     : "里面",
        "out"       : "外面",
]);

int can_drive_by(object me)
{
        if( query("owner") == query("id", me) ) return 1;
        return 0;
}



void create()
{       
        seteuid(getuid());
        set_name(HIM "福威大镖车" NOR, ({ "da biaoche", "biaoche", "che" }));
        set_weight(500000);
        set("no_get", 1);
        set("unit", "辆");
        set("value", 0);
        set("long", 
                HIM "一辆福威镖局的大镖车，上面结结实实盖着蓬布，一群镖头赶(drive)着车，牢牢地护在一边。" NOR); 
        set("no_clean_up", 1);
        setup();
        call_out("destroy1", 1, this_object());
}

void init()
{
        if( query("id", this_player()) == query("owner", this_object() )
         || query("id", this_player()) == query("parter", this_object()) )
        {
                add_action("do_gan", "gan"); 
                add_action("do_gan", "drive");
        }
}

void start_escape_me()
{
        call_out("destroy2", (int)query("time"), this_object());
}

int destroy2(object ob)
{
        object me, parter;
        
        if (objectp(ob))
        {
                /*
                message("channel:rumor", MAG "【镖局传闻】由于" + query("owner_name") +
                        "率领的镖队未能如期抵达，福威镖局已派人前去接管镖队！\n" NOR, users());
                */
                
                tell_object(all_inventory(environment(ob)),
                            HIW "忽然，远远走来一群人，原来是总镖头派人前来了，为首的镖师\n" +
                            "边走嘴里还边骂道：“他奶奶的！等了这么久也还没到，总镖头\n" +
                            "还以为让人给劫了，害老子白跑一趟！”说完，一干人等拉起镖\n" +
                            "车，扬长而去！\n" NOR);

                remove_call_out("destroy1");
                remove_call_out("destroy2");

                me=present(query("owner", ob),environment(ob));
                if( !me)me=find_living(query("owner", ob));
                if (objectp(me))
                {
                        delete_temp("apply/short", me);
                        delete_temp("quest_yunbiao/have_task", me);
                        set_temp("quest_yunbiao/finished_time", time(), me);
                        delete_temp("quest_yunbiao/bandit_killed", me);
                }
                parter=present(query("parter", ob),environment(ob));
                if( !parter)parter=find_living(query("parter", ob));
                if (objectp(parter))
                {
                        delete_temp("apply/short", parter);
                        delete_temp("quest_yunbiao/have_task", parter);
                        set_temp("quest_yunbiao/finished_time", time(), parter);
                        delete_temp("quest_yunbiao/bandit_killed", parter);
                }
                destruct(ob);
        }
        return 1;
}


int do_gan(string arg)
{        
        object me, parter, ob, env, obj, robber, *killer;
        string item, dir, dest, target;
        int reward_exp1, reward_pot1, reward_score1, flag, i, num, reward_exp2, reward_pot2, reward_score2;
        int lvl;

        mapping exit;
        
        ob = this_object();
        me=present(query("owner", ob),environment(ob));
        parter=present(query("parter", ob),environment(ob));

        if (! arg) return notify_fail("你要赶什么？\n");

        if (! objectp(me) || ! objectp(parter)) 
                return notify_fail("护镖要两个人齐心协力，你的同伴不在，不要轻举妄动！\n"); 

        if (sscanf(arg, "%s to %s", item, dir) != 2 
        ||  item != "biaoche" && item != "che" && item != "da biaoche")
                return notify_fail("指令：gan 镖车 to 方向 \n");        
                        
        if (me->is_busy())
                return notify_fail("你现在正忙着哩。\n");

        flag = 0;
        killer = all_inventory(environment(me));
        for (i = 0; i < sizeof(killer); i++)
        {
                if (objectp(killer[i]) 
                 && (query("want_kill1", killer[i]) == query("id", me )
                 || query("want_kill2", killer[i]) == query("id", me)) )
                flag = 1;
        }

        if (flag)   
                return notify_fail(CYN"你还是先把眼前的敌人解决了再说吧！\n"NOR);
        
        env = environment(me);
        if (! env) return notify_fail("你要去那里？\n");

        if( !mapp(exit=query("exits", env)) || undefinedp(exit[dir]) )
                return notify_fail("这个方向过不去。\n");
        
        dest = exit[dir];

        if (! (obj = find_object(dest)))
                call_other(dest, "???");
        if (! (obj = find_object(dest)))
                return notify_fail("那里好象过不去。\n");

        if (! undefinedp(default_dirs[dir]))
                target = default_dirs[dir];
        else
                target=query("short", obj);

        message_vision(HIG "$N赶着镖车往" + target + "驶去。\n" NOR, me);  
        
        if( file_name(obj) != query("file", ob) )
        {
                if (ob->move(obj) && me->move(obj) && parter->move(obj)) 
                {
                        all_inventory(env)->follow_me(me, dir);
                        message_vision(HIG "$N赶着镖车驶了过来。\n" NOR, me);
                        lvl = me->query_skill("driving"); 
                        if (random(lvl + 100) < 50) {
                        me->start_busy(random(2) + 1);
                           if (! parter->is_busy())
                        parter->start_busy(random(2) + 1);
                        } else
                        {
                        me->start_busy(1);
                           if (! parter->is_busy())
                        parter->start_busy(1);
                        }
                        if (me->can_improve_skill("driving")) 
                                me->improve_skill("driving", 1); 
                        if (parter->can_improve_skill("driving")) 
                                parter->improve_skill("driving", 1); 
                }

                if( random(10)<2 && !query("no_fight", environment(ob)) )
                {
                        num = random(2) + 1;
                        for (i = 0; i < num; i++)
                        {
                                robber = new(__DIR__"bandit");
                                set("want_kill1",query("id",  me), robber);
                                set("want_kill2",query("id",  parter), robber);
                                robber->move(environment(ob));  
                                robber->kill_ob(me);
                                robber->kill_ob(parter);
                                robber->check_me();  
                                robber->start_busy(1);
                        }
                        me->start_busy(1);
                        parter->start_busy(1);   
                }
        } else
        {
                reward_exp1=query("combat_exp", me)/3000;
                if( reward_exp1 > 20000 ) reward_exp1 = 20000;
                reward_exp1=reward_exp1+query_temp("quest_yunbiao/bonus", me)*150;
                reward_exp1=reward_exp1+query_temp("quest_yunbiao/bandit_killed", me)*200;
                reward_exp1 = reward_exp1 / 2 + random(reward_exp1 / 2);
                if (reward_exp1 > 60000) reward_exp1 = 60000;
                reward_pot1 = reward_exp1/2;
                reward_score1 = reward_exp1 / 40;
                
                reward_exp2=query("combat_exp", parter)/3000;
                if( reward_exp2 > 20000 ) reward_exp2 = 20000;
                reward_exp2=reward_exp2+query_temp("quest_yunbiao/bonus", parter)*120;
                reward_exp2=reward_exp2+query_temp("quest_yunbiao/bandit_killed", parter)*200;
                reward_exp2 = reward_exp2 / 2 + random(reward_exp2 / 2);
                if(reward_exp2 > 60000) reward_exp2 = 60000;
                reward_pot2 = reward_exp1/2;
                reward_score2 = reward_exp1 / 40;

/*
                message("channel:rumor",HIM"【镖局】"+query("name", me)+
                        "率领的镖队历经千辛万苦，终于顺利抵达！\n" NOR,
                        users());
*/
                
                GIFT_D->delay_bonus(me, ([ "prompt" : "在此次运镖中",
                                           "exp"    : reward_exp1,
                                           "pot"    : reward_pot1,
                                           "mar"    : reward_exp1/10,
                                           "score"  : reward_score1, ]));
                
                GIFT_D->delay_bonus(parter, ([ "prompt" : "在此次运镖中",
                                           "exp"    : reward_exp2,
                                           "pot"    : reward_pot2,
                                           "mar"    : reward_exp2/10,
                                           "score"  : reward_score2, ]));
                /*                                                 
                tell_object(me, HIW "在此次运镖中你获得了" +
                            CHINESE_D->chinese_number(reward_exp1) + "点实战经验、" +
                            CHINESE_D->chinese_number(reward_pot1) + "点潜能\n及" +
                            CHINESE_D->chinese_number(reward_score1) + "点综合评价奖励！\n" NOR);

                tell_object(parter, HIW "在此次运镖中你获得了" +
                            CHINESE_D->chinese_number(reward_exp2) + "点实战经验、" +
                            CHINESE_D->chinese_number(reward_pot2) + "点潜能\n及" +
                            CHINESE_D->chinese_number(reward_score2) + "点综合评价奖励！\n" NOR);
                
                addn("combat_exp", reward_exp1, me);
                addn("potential", reward_pot1, me);
                addn("score", reward_score1, me);
                
                addn("combat_exp", reward_exp2, parter);
                addn("potential", reward_pot2, parter);
                addn("score", reward_score2, parter);
                */
                addn("quest_yunbiao/reward_exp", reward_exp1, me);
                addn("quest_yunbiao/reward_potential", reward_pot1, me);                
       
                addn("quest_yunbiao/reward_exp", reward_exp2, parter);
                addn("quest_yunbiao/reward_potential", reward_pot2, parter);
                
                delete_temp("quest_yunbiao/have_task", me);
                set_temp("quest_yunbiao/finished_time", time(), me);
                delete_temp("quest_yunbiao/have_task", parter);
                set_temp("quest_yunbiao/finished_time", time(), parter);
                delete_temp("quest_yunbiao/bandit_killed", me);
                delete_temp("apply/short", me);
                delete_temp("quest_yunbiao/bandit_killed", parter);
                delete_temp("apply/short", parter);
              
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        }   
        return 1;
}

int destroy1(object ob)
{
        object me, parter;

        if (! objectp(ob) || !environment(ob))
                return 1;

        if (objectp(ob) && ! present(query("owner", ob), environment(ob)) 
        &&  ! present(query("parter"), environment(ob)))
        {
                me=find_player(query("owner", ob));
                if( !me)me=find_living(query("owner", ob));
                
                parter=find_player(query("parter", ob));
                if( !parter)parter=find_living(query("parter", ob));
                
                if (objectp(me))
                {
                        delete_temp("quest_yunbiao", me);
                        delete_temp("apply/short", me);
                        me->apply_condition("yunbiao_busy", 8);
                }
                if (objectp(parter))
                {
                        delete_temp("quest_yunbiao", parter);
                        delete_temp("apply/short", parter);
                        parter->apply_condition("yunbiao_busy", 8);
                }

/*
                message("channel:rumor", HIB "【镖局】" + query("owner_name") +
                        HIB"率领的镖队在半路让人给劫了！\n" NOR, 
                        users());
*/
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        } else
        {
                remove_call_out("destroy1");
                call_out("destroy1", 1, ob);
                return 1;
        }
}
