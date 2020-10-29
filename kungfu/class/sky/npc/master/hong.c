#include <ansi.h>

inherit NPC;

void create()
{
        object ob;
        set_name("洪七公", ({ "hong qigong", "hong", "qigong" }));
        set("long", @LONG
他就是丐帮第十七任帮主，号称九指神丐的洪
七公老爷子。只见他须眉皆白，周身上下邋遢
不已，模样甚是龌龊。可是他目光如电，显得
正义凛然，不怒而自威。
LONG);
        set("nickname", HIW "北丐" NOR);
        set("gender", "男性");
        set("class", "beggar");
        set("age", 75);
        set("attitude", "peaceful");

        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);

            set("qi", 300000);
            set("max_qi", 300000);
            set("jing", 300000);
            set("max_jing", 300000);
            set("neili", 35000);
            set("max_neili", 35000);
            set("jiali", 300);
            set("combat_exp", 900000000);

        set("score", 4000000);
        set("shen_type", 1);

        set_skill("force", 650);
        set_skill("jiaohua-neigong", 650);
        set_skill("huntian-qigong", 650);
        set_skill("yijin-duangu", 650);
        set_skill("dodge", 650);
        set_skill("feiyan-zoubi", 650);
        set_skill("xiaoyaoyou", 650);
        set_skill("unarmed", 650);
        set_skill("changquan", 650);
        set_skill("jueming-tui", 650);
        set_skill("hand", 650);
        set_skill("chansi-shou", 650);
        set_skill("claw", 650);
        set_skill("suohou-gong", 650);
        set_skill("strike", 650);
        set_skill("xianglong-zhang", 650);
        set_skill("tongchui-zhang", 650);
        set_skill("liuhe-zhang", 650);
        set_skill("parry", 650);
        set_skill("staff", 650);
        set_skill("dagou-bang", 650);
        set_skill("jiaohua-bangfa", 650);
        set_skill("fengmo-zhang", 650);
        set_skill("fumo-zhang", 650);
        set_skill("throwing", 650);
        set_skill("pomie-jinzhen", 650);
        set_skill("begging", 650);
        set_skill("checking", 650);
        set_skill("literate", 650);
        set_skill("martial-cognize", 650);

        map_skill("throwing", "pomie-jinzhen");
        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "changquan");
        map_skill("hand", "chansi-shou");
        map_skill("claw", "suohou-gong");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("staff", "dagou-bang");
        map_skill("strike", "xianglong-zhang");

        prepare_skill("strike", "xianglong-zhang");

        create_family("丐帮", 17, "帮主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.qu" :),
                (: perform_action, "strike.zhen" :),
                (: perform_action, "strike.fei" :),
                (: perform_action, "dodge.xian" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.chuo" :),
                (: perform_action, "staff.feng" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "staff.tian" :),
                (: exert_function, "recover" :),
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
        object guard1 = present ("yideng dashi", where);
        object guard2 = present ("huang yaoshi", where);
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
