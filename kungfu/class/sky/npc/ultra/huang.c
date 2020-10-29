#include <ansi.h>

inherit NPC;

void create()
{
        object ob;
        set_name("黄裳", ({"huang shang", "huang", "shang"}));
        set("title", "大宗师");
        set("gender", "男性");
        set("age", 42);
        set("long", "此人气度闲雅，看不出武功高低。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        
            set("qi", 400000);
            set("max_qi", 400000);
            set("jing", 400000);
            set("max_jing", 400000);
            set("neili", 35000);
            set("max_neili", 35000);
            set("jiali", 400);
            set("combat_exp", 900000000);

        set_skill("unarmed", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("strike", 500);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("jiuyin-shengong", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 200);
        set_skill("qimen-xuanshu", 500);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "某家");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "claw.xin" :),
                (: perform_action, "claw.zhua" :),
                (: perform_action, "cuff.quan" :),
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

        carry_object("/d/taohua/obj/bupao")->wear();
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
        object guard1 = present ("huo shan", where);
        object guard2 = present ("kuihua taijian", where);
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
             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
     
        }

        set("qi", 400000);
        set("jing", 400000);
        set("neili", 35000);
        set("eff_qi", 400000);
        set("max_jing", 400000);
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