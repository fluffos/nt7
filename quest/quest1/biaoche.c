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
        set_name(HIW "镖车" NOR, ({ "biao che", "cart", "che" }));
        set_weight(300000);
        set("no_get", 1);
        set("unit", "辆");
        set("value", 0);
        set("long", 
                HIW "一辆福威镖局的镖车，一干镖头正准备赶车(drive)起程呢。" NOR); 
        set("no_clean_up",1);
        setup();
        call_out("destroy1", 1, this_object());
}

void init()
{
        if( query("id", this_player()) == query("owner", this_object()) )
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
        object me;
        if (objectp(ob))
        {
                /*
                message("channel:rumor", MAG "【镖局传闻】由于" + query("owner_name") +
                        "护送的镖车未能如期抵达，福威镖局已派人前去接管镖车！\n" NOR, users());
                */
                tell_object(all_inventory(environment(ob)),
                            HIW "忽然，远远走来一群人，原来是总镖头派人前来了，为首的镖师\n" +
                            "边走嘴里还边骂道：“他奶奶的！等了这么久也还没到，总镖头\n" +
                            "还以为让人给劫了，害老子白跑一趟！”说完，一干人等拉起镖\n" +
                            "车，扬长而去！\n" NOR);

                remove_call_out("destroy1");
                remove_call_out("destroy2");

                me=present(query("owner", ob),environment(ob));
                if (objectp(me))
                {
                        delete_temp("apply/short", me);
                        delete_temp("quest_yunbiao/have_task", me);
                        set_temp("quest_yunbiao/finished_time", time(), me);
                }
                destruct(ob);
        }
        return 1;
}


int do_gan(string arg)
{        
        object me, ob, env, obj, robber, *killer;
        string item, dir, dest, target;
        int reward_exp, reward_pot, reward_score, flag, i;
        int lvl;

        mapping exit;
        me = this_player();
        ob = this_object();

        if (! arg) return notify_fail("你要赶什么？\n");

        if( query("id", me) != query("owner", ob) )
                return notify_fail("你赶的不是自己的镖车吧？\n"); 

        if (sscanf(arg, "%s to %s", item, dir) != 2 
        ||  item != "biao che" && item != "che")
                return notify_fail("指令：gan 镖车 to 方向 \n");        
                        
        if (me->is_busy())
                return notify_fail("你现在正忙着哩。\n");

        flag = 0;
        killer = all_inventory(environment(me));
        for (i = 0; i < sizeof(killer); i++)
        {
                if (objectp(killer[i]) 
                 && query("want_kill", killer[i]) == query("id", me) )
                flag = 1;
        }

        if (flag)   
                return notify_fail(CYN "你还是先把眼前的敌人解决了再说吧！\n" NOR);
        
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
                if (ob->move(obj) && me->move(obj)) 
                {
                        all_inventory(env)->follow_me(me, dir);
                        message_vision(HIG "$N赶着镖车驶了过来。\n" NOR, me);
                        lvl = me->query_skill("driving"); 
                        if (random(lvl + 100) < 50) 
                        me->start_busy(random(2) + 2);
                        else me->start_busy(1);
                        if (me->can_improve_skill("driving")) 
                                me->improve_skill("driving", 1); 
                }

                if( random(12)<2 && !query("no_fight", environment(ob)) )
                {
                        robber = new(__DIR__"robber");
                        set("want_kill",query("id",  me), robber);
                        robber->move(environment(ob));  
                        robber->kill_ob(me);
                        robber->check_me();  
                        me->start_busy(1);
                        robber->start_busy(1);
                }
        } else
        {
                reward_exp=query("combat_exp", me)/3000;
                if( reward_exp > 40000 ) reward_exp = 40000;
                reward_exp=reward_exp+query_temp("quest_yunbiao/bonus", me)*500;
                reward_exp = reward_exp / 2 + random(reward_exp);
                if (reward_exp > 60000) reward_exp = 60000;

                reward_pot = reward_exp/2;
                reward_score = reward_exp / 40;

/*
                message("channel:rumor",HIM"【镖局】"+query("name", me)+
                        "运送的镖车历经千辛万苦，终于顺利抵达！\n" NOR,
                        users());
*/
                
                /*
                addn("combat_exp", reward_exp, me);
                addn("potential", reward_pot, me);
                addn("score", reward_score, me);
                
                tell_object(me, HIW "在此次运镖中你获得了" +
                            CHINESE_D->chinese_number(reward_exp) + "点实战经验、" +
                            CHINESE_D->chinese_number(reward_pot) + "点潜能及\n" +
                            CHINESE_D->chinese_number(reward_score) + "点综合评价奖励！\n" NOR);
                */
                GIFT_D->delay_bonus(me, ([ "prompt" : "在此次运镖中",
                                           "exp"    : reward_exp,
                                           "pot"    : reward_pot,
                                           "mar"    : reward_exp/10,
                                           "score"  : reward_score, ]));
                                           
                addn("quest_yunbiao/reward_exp", reward_exp, me);
                addn("quest_yunbiao/reward_potential", reward_pot, me);
                
                delete_temp("quest_yunbiao/have_task", me);
                set_temp("quest_yunbiao/finished_time", time(), me);
                delete_temp("apply/short", me);
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        }   
        return 1;
}

int destroy1(object ob)
{
        object me;

        if (! objectp(ob) || ! environment(ob))
                return 1;

        if (objectp(ob) && ! present(query("owner", ob), environment(ob)))
        {
                me=find_player(query("owner", ob));
                if( !me)me=find_living(query("owner", ob));
                if (objectp(me))
                {
                        delete_temp("quest_yunbiao", me);
                        delete_temp("apply/short", me);
                        me->apply_condition("yunbiao_busy", 8);
                }

/*
                message("channel:rumor", HIB "【镖局】" + query("owner_name") +
                        HIB"护送的镖车在半路让人给劫了！\n" NOR, users());
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
