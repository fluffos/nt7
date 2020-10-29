#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_COAGENT;

void create()
{
        set_name("李逍遥", ({ "li xiaoyao", "li", "xiaoyao"}));
        set("long", "仙剑奇侠传中的传奇人物，少年得蜀山剑派\n" 
                    "高人授艺，兼习家传绝学飞龙探云手以及冰\n"
                    "心决，乃一代不世的剑侠。\n"); 
        set("nickname", HIW "蜀山剑神" NOR);
        set("title", HIY "大宗师" NOR);
        set("gender", "男性");
        set("age", 24);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set("max_qi", 290000);
        set("max_jing", 290000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 250);
        set("combat_exp", 900000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.fei" :),
                (: exert_function, "freeze" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),              
        }) );

        set_skill("dodge", 560);
        set_skill("parry", 560);
        set_skill("unarmed", 560);
        set_skill("hand", 560);
        set_skill("sword", 560);
        set_skill("yujian-shu", 560);
        set_skill("feilong-shou", 560);
        set_skill("zuixian-bu", 560);
        set_skill("force", 560);
        set_skill("bingxin-jue", 560);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "bingxin-jue");
        map_skill("dodge", "zuixian-bu");
        map_skill("parry", "yujian-shu");
        map_skill("sword", "yujian-shu");
        map_skill("unarmed", "feilong-shou");
        map_skill("hand", "feilong-shou");

        prepare_skill("hand", "feilong-shou");

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

        setup();

        carry_object(__DIR__"obj/pangukai")->wear();
        carry_object(__DIR__"obj/chiyoujian")->wield();
        //carry_object("/kungfu/class/sky/obj/miji3");
        //set_temp("handing", carry_object("/kungfu/class/sky/obj/shenjiu"));
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
                                 set("qi", 290000);
                                 set("jing", 90000);
                                 set("neili", 35000);
                                 set("eff_qi", 290000);
                                 set("max_jing", 90000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 2)
             {
                      ob->set("sky12/floor", 3);
                 command("say 阁下请便吧！");
             }            
        }

        set("qi", 290000);
        set("jing", 90000);
        set("neili", 35000);
        set("eff_qi", 290000);
        set("max_jing", 90000);
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
