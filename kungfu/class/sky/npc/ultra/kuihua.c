// kuihua 葵花太监

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("葵花太监", ({ "kuihua taijian", "kuihua", "taijian" }) );
        set("title", HIR "大宗师" NOR);
        set("gender", "男性");
        set("age", 39);
        set("long", "此人脸型瘦削，满是阴骛，不知是喜是怒。\n");
        set("attitude", "peaceful");
        set("str", 31);
        set("int", 39);
        set("con", 34);
        set("dex", 36);

        set("max_qi", 400000);
        set("qi", 400000);
        set("max_jing", 200000);
        set("jing", 200000);
        set("neili", 35000);
        set("max_neili", 35000);
        set("jiali", 300);

        set("combat_exp", 900000000);

        set_skill("unarmed", 650);
        set_skill("finger", 650);
        set_skill("parry", 650);
        set_skill("dodge", 650);
        set_skill("force", 650);
        set_skill("sword", 650);
        set_skill("kuihua-mogong", 650);
        set_skill("martial-cognize", 650);
        set_skill("literate", 650);

        map_skill("parry", "kuihua-mogong");
        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("finger", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");

        prepare_skill("finger", "kuihua-mogong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "本宫");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "finger.tian" :),
                (: perform_action, "finger.hui" :),
                (: perform_action, "finger.fenshen" :),
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
        carry_object("/clone/misc/spin")->wield();
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
        object guard3 = present ("dugu qiubai", where);

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
                                 set("qi", 400000);
                                 set("jing", 200000);
                                 set("eff_qi", 400000);
                                 set("max_jing", 200000);
                                 set("neili", 35000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
        }

        set("qi", 400000);
        set("jing", 200000);
        set("eff_qi", 400000);
        set("max_jing", 200000);
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