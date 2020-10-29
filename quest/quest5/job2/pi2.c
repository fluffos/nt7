// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// pi.c 裨将 玄武内门

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("裨将", ({ "pi jiang", "pi", "jiang" }));
        set("gender", "男性");
        set("age", random(10) + 30);
        set("str", 25);
        set("dex", 16);
        set("long", "这是一个大宋年轻将领，满脸征尘。\n");
        set("combat_exp", 45000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("unarmed", 60);
        set_skill("force", 60);
        set_skill("sword", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);

        set("neili", 400); 
        set("max_neili", 400);
        set("jiali", 10);

        setup();
        carry_object("/d/city/obj/changjian")->wield();
        carry_object("/d/city/obj/tiejia")->wear();
}

void init()
{       
        object ob;

        ::init();

        if (objectp(ob = this_player()) && ! is_fighting()) 
        {
                // remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) 
                return;

        if( query_temp("guo_shoucheng/start_job", ob) == 1 )
                say("裨将皱了皱眉：这位" + RANK_D->query_respect(ob) + "，你还是安心守城吧。\n");
        else 
        if( query_temp("guo_shoucheng/mark_shadi", ob) == 2
         && !query_temp("guo_shoucheng/job_over", ob) )
        {
                say("裨将拱手说道：这位" + RANK_D->query_respect(ob) + "，你来得正是时候，蒙古靼子已经快攻上城了。\n");
                
                set("env/combatd", 4, ob);
                ob->apply_condition("jobshadi_limit", 10 + random(5));
                set_temp("guo_shoucheng/start_job", 1, ob);
                set_temp("guo_shoucheng/where", environment(ob), ob);
                // remove_call_out("to_rob");
                call_out("to_rob", 10, ob);
        } else
        if( query_temp("guo_shoucheng/job_over", ob) )
        {
                say("裨将拱手说道：这位" + RANK_D->query_respect(ob) + "，你已经可以回去复命了。\n");
                return;
        } 

}

void to_rob(object ob)
{
        object /**target,*/ robber, room;              
//      int i;
        
        if (! ob || environment(ob) != environment()) 
                return;

        room = environment(ob);
        
        if( query("short", environment(ob)) == "青龙内门" )
        {
                robber = new(__DIR__"robber1");
                robber->do_change(ob);
                set("want_kill", ob, robber);
                robber->move(room);
                message_vision(HIR "突然城下爬上来一个蒙古兵士。\n" NOR, this_player()); 
                robber->kill_ob(ob);
                ob->kill_ob(robber);
        }
}

int accept_kill(object me) 
{
        message_vision(CYN "$N" CYN "大怒道：“给我滚！”说罢一掌把$n" CYN "劈倒在地。\n" NOR, this_object(), me); 
        me->unconcious(); 
        return -1; 
}

int accept_ansuan(object who) 
{
        return notify_fail("你刚想暗算，可是眼前一花，看不太清楚。\n"); 
}

int accept_hit(object me) 
{

        message_vision(CYN "$N" CYN "大怒道：“给我滚！”说罢一掌把$n" CYN "劈倒在地。\n" NOR, this_object(), me); 
        me->unconcious(); 
        return -1; 
}

int accept_fight(object who) 
{
        command("say 没兴趣。"); 
        return 0; 
}

void fight_ob(object ob) 
{
        message_vision(CYN "$N" CYN "大怒道：“给我滚！”说罢一掌把$n" CYN "劈倒在地。\n" NOR, this_object(), ob); 
        ob->unconcious(); 
        return; 
}


void unconcious()
{
        return;
}

void die()
{
        return;
}