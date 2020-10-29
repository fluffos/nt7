#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_COAGENT;

void create()
{
        set_name("华英雄", ({ "hua yingxiong", "hua", "yingxiong"}));
        set("long", "一个俊俏的中年男子，衣着长衫，他就是华英雄。\n"
                    "传说他命犯天煞孤星，一生漂泊，落于异地。尔后\n"
                    "习得一身绝技，兼修炼「中华傲决」，大败「东洋\n"
                    "战神」无敌。\n"); 
        set("nickname", HIW "中华英雄" NOR);
        set("title", HIY "大宗师" NOR);
        set("gender", "男性");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 40);

        set("max_qi", 280000);
        set("max_jing", 60000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 250);
        set("combat_exp", 900000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.aojue" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }) );

        set_skill("dodge", 560);
        set_skill("strike", 560);
        set_skill("parry", 560);
        set_skill("unarmed", 560);
        set_skill("force", 560);
        set_skill("sword", 560);
        set_skill("siji-jianfa", 560);
        set_skill("zhonghua-aojue", 560);
        set_skill("martial-cognize", 560);
        set_skill("literate", 500);

        map_skill("force", "zhonghua-aojue");
        map_skill("sword", "zhonghua-aojue");
        map_skill("dodge", "zhonghua-aojue");
        map_skill("parry", "zhonghua-aojue");
        map_skill("strike", "zhonghua-aojue");
        map_skill("unarmed", "zhonghua-aojue");

        prepare_skill("strike", "zhonghua-aojue");

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
        set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
        set_temp("apply/parry", 600);

        setup();

        carry_object(__DIR__"obj/cloth3")->wear();
        carry_object(__DIR__"obj/chijian")->wield();
        carry_object("/kungfu/class/sky/obj/miji2");
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
                                 set("qi", 280000);
                                 set("jing", 60000);
                                 set("neili", 35000);
                                 set("eff_qi", 280000);
                                 set("max_jing", 60000);
                                 set("max_neili", 350000);
                                 this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 3)
             {
                      ob->set("sky12/floor", 4);
                 command("say 阁下请便吧！");
             }
        }

        set("qi", 280000);
        set("jing", 60000);
        set("neili", 35000);
        set("eff_qi", 280000);
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
