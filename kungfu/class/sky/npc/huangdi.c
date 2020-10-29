#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIY "黄帝" NOR, ({ "huang di", "huang", "di"}));
        set("long", HIY "    此人身穿黄色龙袍，气宇轩昂，乃远古传说中的炎帝。\n" NOR);

        set("gender", "男性");
        set("age", 40);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 60);
        set("int", 60);
        set("con", 60);
        set("dex", 60);

        set("max_qi", 500000);
        set("max_jing", 500000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 300);
        set("combat_exp", 900000000);

        set_skill("dodge", 600);
        set_skill("parry",600);
        set_skill("sword", 600);
        set_skill("unarmed", 600);
        set_skill("yinyang-shiertian", 600);
        set_skill("force", 600);
        set_skill("martial-cognize", 600);
        set_skill("literate", 600);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("sword", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: perform_action, "sword.zhen" :),
                (: perform_action, "unarmed.zhen" :),
                (: perform_action, "sword.tian" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),                
        }) );

        set_temp("apply/damage", 500);
        set_temp("apply/armor", 600);
                set_temp("apply/attack", 2000);
        set_temp("apply/dodge", 400);
                set_temp("apply/parry", 500);

                set("yinyang-shiertian/yinyang", 1);

        setup();

        carry_object(__DIR__"obj/longpao")->wear();
        carry_object("/clone/weapon/xuanyuan-jian")->wield();
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
                                  set("neili", 35000);
                                 set("eff_qi", 500000);
                                 set("max_jing", 500000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("haha");
             if (ob->query("sky12/floor") == 10)
             {
                      ob->set("sky12/floor", 11);
                 command("say 后生可畏啊！");
             }
        }

        set("qi", 500000);
        set("jing", 500000);
        set("neili", 35000);
        set("eff_qi", 500000);
        set("max_jing", 500000);
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
