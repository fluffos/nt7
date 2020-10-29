// dugu qiubai

#include <ansi.h>

inherit NPC;

void check_weapon();

void create()
{
        set_name("独孤求败", ({ "dugu qiubai", "dugu" }) );
        set("title", HIC "大宗师" NOR);
        set("gender", "男性");
        set("age", 48);
        set("long", "此人诚恳敦厚，眉目菱角分明，气宇轩昂。\n");
        set("attitude", "peaceful");
        set("str", 38);
        set("int", 39);
        set("con", 32);
        set("dex", 33);

        set("max_qi", 500000);
        set("qi", 500000);
        set("max_jing", 500000);
        set("jing", 500000);
        set("neili", 35000);
        set("max_neili", 35000);
        set("jiali", 400);

        set("combat_exp", 900000000);

        set_skill("unarmed", 650);
        set_skill("sword", 1000);
        set_skill("blade", 650);
        set_skill("staff", 650);
        set_skill("hammer", 650);
        set_skill("club", 650);
        set_skill("whip", 650);
        set_skill("dagger", 650);
        set_skill("throwing", 650);
        set_skill("parry", 650);
        set_skill("dodge", 650);
        set_skill("force", 650);
        set_skill("never-defeated", 650);
        set_skill("dugu-jiujian", 1000);
        set_skill("martial-cognize", 650);

        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "never-defeated");
        map_skill("dodge", "never-defeated");
        map_skill("force", "never-defeated");

        set("opinion/ultra",  1);
        set("opinion/master", 1);
        set("dugu-jiujian/nothing", 1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: check_weapon :),
        }) );

        set("rank_info/self", "在下");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "sword.jian" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),                  
        }) );

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield();
}

void check_weapon()
{
        object ob;
        
        if (objectp(query_temp("weapon")))
                return;

        ob = new("/clone/weapon/zhujian");
        ob->move(this_object());
        command("wield jian");
}
void start_kill(object guard, object ob)
{
        if (! objectp(guard) || ! objectp(ob))return;

        guard->kill_ob(ob);        
}

void delay_kill(object guard, object ob)
{
        remove_call_out("start_kill");
        call_out("start_kill", 2, guard, ob);
}
void kill_ob (object ob)
{
        object me = this_object();
        object where = environment (me);
        object guard1 = present ("huang shang", where);
        object guard2 = present ("huo shan", where);
        object guard3 = present ("kuihua taijian", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);
        if (guard1 && ! guard1->is_fighting())delay_kill(guard1, ob);
        if (guard2 && ! guard2->is_fighting())delay_kill(guard2, ob);
        if (guard3 && ! guard3->is_fighting())delay_kill(guard3, ob);
        
}

void unconcious()
{
        die();
}

void die()
{
        object ob;

        ob = query_last_damage_from();

        if (objectp(ob) && ob->is_fighting(this_object()))
        {
                         if (arrayp(ob->query_team()))
                         {
                                 command("heng");
                                 command("say 胜之不武！");
                                 set("qi", 500000);
                                 set("jing", 500000);
                                 set("eff_qi", 500000);
                                 set("max_jing", 500000);
                                 set("neili", 35000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 7)
             {
                      ob->set("sky12/floor", 8);
                 command("say 阁下请便吧！");
             }
        }


        set("qi", 500000);
        set("jing", 500000);
        set("eff_qi", 500000);
        set("max_jing", 500000);
        set("neili", 35000);
        set("max_neili", 35000);

        this_object()->clear_condition();

        return;
}



// 气血小于1000则死亡，避免他人协助帮忙转世
void heart_beat()
{
        if (this_object()->query("qi") < 1000 || this_object()->query("eff_qi") < 1000)
        {
                die();
        }
        ::heart_beat(); 
        keep_heart_beat(); 
}