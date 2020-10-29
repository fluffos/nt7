// huoshan 霍山

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("霍山", ({ "huo shan", "huo", "shan" }) );
        set("title", HIW "大宗师" NOR);
        set("gender", "男性");
        set("age", 91);
        set("long", "他身着奇装异服，相貌平平，便似一般的西域人士。\n");
        set("attitude", "peaceful");
        set("class", "fighter");
        set("str", 30);
        set("int", 37);
        set("con", 39);
        set("dex", 33);

        set("max_qi", 400000);
        set("qi", 400000);
        set("max_jing", 400000);
        set("jing", 400000);
        set("neili", 35000);
        set("max_neili", 35000);
        set("jiali", 400);

        set("combat_exp", 900000000);

        set_skill("unarmed", 650);
        set_skill("parry", 650);
        set_skill("dodge", 650);
        set_skill("force", 650);
        set_skill("sword", 650);
        set_skill("jiuyang-shengong", 650);
        set_skill("qiankun-danuoyi", 650);
        set_skill("martial-cognize", 650);
        set_skill("literate", 650);

        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "qiankun-danuoyi");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("sword", "jiuyang-shengong");

        prepare_skill("unarmed", "jiuyang-shengong");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.xi" :),
                (: perform_action, "unarmed.hun" :),
                (: perform_action, "unarmed.jiu" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),                     
        }) );

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "本座");

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
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
        object guard2 = present ("dugu qiubai", where);
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
             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
        }


        set("qi", 400000);
        set("jing", 400000);
        set("eff_qi", 400000);
        set("max_jing", 400000);
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