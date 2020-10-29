#include <ansi.h>
inherit NPC;

void create()
{
        set_name("铁传甲", ({ "tie chuanjia", "tie", "chuanjia" }) );
        set("nickname", WHT "铁甲金刚" NOR);
        set("title", "忠心护卫");
        set("gender", "男性");
        set("age", 42);
        set("long", "一个身材魁梧的汉子。\n");
        set("attitude", "peaceful");

        set("str", 40);
        set("con", 30);
        set("int", 20);
        set("dex", 30);

        set("max_qi", 160000);
        set("qi", 160000);
        set("max_jing", 60000);
        set("neili", 35000);
        set("max_neili", 35000);
        set("jiali", 150);

        set("combat_exp", 900000000);
        set("shen_type", 1);
        set("score", 5000);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),             
        }) );

        set_skill("unarmed", 620);
        set_skill("force", 620);
        set_skill("parry", 680);
        set_skill("dodge", 680);
        set_skill("cuff", 620);
        set_skill("literate", 600);
        set_skill("yijinjing", 620);
        set_skill("tiexian-quan", 620);
        set_skill("feiyan-huixiang", 680);
        set_skill("martial-cognize", 600);

        map_skill("parry", "tiexian-quan");
        map_skill("force", "yijinjing");
        map_skill("unarmed", "tiexian-quan");
        map_skill("cuff", "tiexian-quan");
        map_skill("dodge", "feiyan-huixiang");

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 600);
                set_temp("apply/parry", 600);

        setup();

        //carry_object("/kungfu/class/sky/obj/miji1");
        carry_object("/clone/cloth/cloth")->wear();
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
                                 set("qi", 160000);
                                 set("jing", 60000);
                                 set("neili", 35000);
                                 set("eff_qi", 160000);
                                 set("max_jing", 60000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 1)
             {
                      ob->set("sky12/floor", 2);
                 command("say 阁下请便吧！");
             }
        }

        set("qi", 160000);
        set("jing", 60000);
        set("neili", 35000);
        set("eff_qi", 160000);
        set("max_jing", 60000);
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
