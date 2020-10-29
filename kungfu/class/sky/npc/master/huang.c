#include <ansi.h>

inherit NPC;

void create()
{
        object ob;
        set_name("黄药师", ({"huang yaoshi", "huang", "yaoshi"}));
        set("title", "东海桃花岛岛主");
        set("nickname", HIC "东邪" NOR );
        set("gender", "男性");
        set("age", 42);
        set("long", "他就是桃花岛主。行事好恶全由己心，因此被\n"
                    "人称作「东邪」。\n");
        set("attitude", "peaceful");
        set("class", "scholar");
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        
            set("qi", 500000);
            set("max_qi", 500000);
            set("jing", 500000);
            set("max_jing", 500000);
            set("neili", 35000);
            set("max_neili", 35000);
            set("jiali", 500);
            set("combat_exp", 900000000);

        set_skill("force", 650);
        set_skill("bibo-shengong", 650);
        set_skill("luoying-xinfa", 650);
        set_skill("hand", 650);
        set_skill("finger", 650);
        set_skill("canglang-zhi", 650);
        set_skill("tanzhi-shentong", 650);
        set_skill("unarmed", 650);
        set_skill("strike", 650);
        set_skill("pikong-zhang", 650);
        set_skill("luoying-shenzhang", 650);
        set_skill("xuanfeng-tui", 650);
        set_skill("dodge", 650);
        set_skill("anying-fuxiang",650);
        set_skill("parry", 650);
        set_skill("sword", 650);
        set_skill("throwing", 650);
        set_skill("luoying-shenjian", 650);
        set_skill("yuxiao-jianfa", 650);
        set_skill("lanhua-shou", 650);
        set_skill("qimen-wuxing", 650);
        set_skill("count", 650);
        set_skill("jingluo-xue", 650);
        set_skill("mathematics", 650);
        set_skill("literate", 650);
        set_skill("chuixiao-jifa", 650);
        set_skill("bihai-chaosheng", 650);
        set_skill("taohua-yuan", 650);
        set_skill("drawing", 650);
        set_skill("chess", 650);
        set_skill("calligraphy", 650);
        set_skill("medical", 650);
        set_skill("taohua-yaoli", 650);
        set_skill("martial-cognize", 650);

        map_skill("force", "bibo-shengong");
        map_skill("finger", "tanzhi-shentong");
        map_skill("hand", "lanhua-shou");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("strike", "luoying-shenzhang");
        map_skill("dodge", "anying-fuxiang");
        map_skill("parry", "tanzhi-shentong");
        map_skill("sword", "yuxiao-jianfa");
        map_skill("chuixiao-jifa", "bihai-chaosheng");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("medical", "taohua-yaoli");

        prepare_skill("finger" , "tanzhi-shentong");

        create_family("桃花岛", 1, "岛主");

                set("chat_chance_combat", 120);
                set("chat_msg_combat", ({
                (: perform_action, "sword.bihai" :),
                (: perform_action, "sword.qing" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "finger.ding" :),
                (: perform_action, "finger.xiao" :),
                (: perform_action, "finger.po" :),
                (: perform_action, "finger.zhuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),  
        }));

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
        object guard1 = present ("yideng dashi", where);
        object guard2 = present ("hong qigong", where);
        object guard3 = present ("ouyang feng", where);

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
                                 set("neili", 35000);
                                 set("eff_qi", 500000);
                                 set("max_jing", 500000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 6)
             {
                      ob->set("sky12/floor", 7);
                 command("say 阁下请便！");
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
