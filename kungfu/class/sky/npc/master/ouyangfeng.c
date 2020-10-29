// ouyangfeng.c

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("欧阳锋", ({ "ouyang feng", "ouyang", "feng" }));
        set("long", "他就是白驼山庄主，号称“西毒”的欧阳锋。脸型瘦削，\n"
                    "身形剽悍，虽然受到郭靖欺骗误学习了「九阴真经」而走\n"
                    "火入魔，一度变得精神错乱，但是现在已然恢复，功力犹\n"
                    "胜往昔。\n");
        set("title", "西域白驼山庄主");
        set("gender", "男性");
        set("age", 53);
        set("nickname", HIR "西毒" NOR);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set("str", 32);
        set("int", 34);
        set("con", 34);
        set("dex", 32);

            set("qi", 300000);
            set("max_qi", 300000);
            set("jing", 300000);
            set("max_jing", 300000);
            set("neili", 35000);
            set("max_neili", 35000);
            set("jiali", 300);
            set("combat_exp", 900000000);

        set_skill("force", 650);
        set_skill("unarmed", 650);
        set_skill("dodge", 650);
        set_skill("parry", 650);
        set_skill("cuff", 650);
        set_skill("finger", 650);
        set_skill("staff", 650);
        set_skill("poison", 650);
        set_skill("shedu-qiqiao", 650);
        set_skill("hamagong", 650);
        set_skill("baituo-xinfa", 650);
        set_skill("chanchu-bufa", 650);
        set_skill("lingshe-quan", 650);
        set_skill("lingshe-zhangfa", 650);
        set_skill("baibian-daxue", 650);
        set_skill("guzheng-jifa", 650);
        set_skill("xiyu-tiezheng", 650);
        set_skill("wushe-qu", 650);
        set_skill("literate", 650);
        set_skill("medical", 650);
        set_skill("baituo-michuan", 650);
        set_skill("martial-cognize", 650);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("cuff", "lingshe-quan");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("medical", "baituo-michuan");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

        create_family("欧阳世家", 5, "掌门");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.qian" :),
                (: perform_action, "staff.wuji" :),
                (: perform_action, "cuff.rou" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: exert_function, "tui" :),
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

        set("music_book", 1);

        setup();
        carry_object("/d/baituo/obj/shezhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("d/baituo/obj/tiezheng");
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
        object guard2 = present ("huang yaoshi", where);
        object guard3 = present ("hongqi gong", where);

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

        set("qi", 300000);
        set("jing", 300000);
        set("neili", 35000);
        set("eff_qi", 300000);
        set("max_jing", 300000);
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
