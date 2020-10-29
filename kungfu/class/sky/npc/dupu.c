#include <ansi.h>

inherit NPC;

void create()
{
        set_name("杜甫", ({ "du fu", "du", "fu"}));
        set("long", "这便是唐朝大诗人杜甫，只见他须垂三尺，\n"
                     "面如冠玉，双目炯炯有神。一手持青铜爵，\n"
                     "一手持长剑，正在独饮。\n"); 
        set("title", "唐朝大诗人");
        set("nickname", HIW "诗圣" NOR);
        set("gender", "男性");
        set("age", 37);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("per", 50);

        set("max_qi", 400000);
        set("max_jing", 460000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 450);
        set("combat_exp", 900000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.yujian" :),
                (: exert_function, "freeze" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),              
        }) );

        set_skill("dodge", 700);
        set_skill("parry", 700);
        set_skill("unarmed", 700);
        set_skill("unarmed", 700);
        set_skill("sword", 700);
        set_skill("yujian-shu", 700);
        set_skill("zuiquan-sanda", 700);
        set_skill("zuixian-bu", 700);
        set_skill("force", 700);
        set_skill("bingxin-jue", 700);
        set_skill("martial-cognize", 700);
        set_skill("literate", 700);
        set_skill("liquor", 700);
        set_skill("calligraphy", 700);

        map_skill("force", "bingxin-jue");
        map_skill("dodge", "zuixian-bu");
        map_skill("parry", "yujian-shu");
        map_skill("sword", "yujian-shu");
        map_skill("unarmed", "zuiquan-sanda");

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        //set_temp("handing", carry_object("/kungfu/class/sky/obj/shenjiu"));
}


void kill_ob (object ob)
{
        object me = this_object();
        object where = environment (me);
        object guard1 = present ("li bai", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);
        if (guard1 && ! guard1->is_fighting())guard1->kill_ob(ob);
        
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
                                 set("jing", 460000);
                                 set("neili", 35000);
                                 set("eff_qi", 400000);
                                 set("max_jing", 460000);
                                 set("max_neili", 35000);
                                 this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 8)
             {
                      ob->set("sky12/floor", 9);
                 command("say 阁下请便吧！");
             }
        }

        set("qi", 400000);
        set("jing", 460000);
        set("neili", 35000);
        set("eff_qi", 400000);
        set("max_jing", 460000);
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
