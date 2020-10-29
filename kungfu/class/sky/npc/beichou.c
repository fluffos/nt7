#include <ansi.h>
inherit NPC;

void create()
{
        set_name("北丑", ({ "bei chou", "bei", "chou", "xizi" }) );
        set("nickname", HIW "北戏子" NOR);
        set("title", HIC "武林泰斗" NOR);
        set("gender", "男性" );
        set("age", 68);
        set("long", HIC "这是一个身着戏子打扮的瘦小老头，长得尖\n"
                        "嘴猴腮，天生一副奸相。这便是当今武林中\n"
                        "号称「" HIR "南贤北丑" HIC "」戏子北丑。"
                        "\n" NOR);
        set("attitude", "friendly");
        set("max_jing", 250000);
        set("max_qi", 400000);
        set("max_jingli", 250000);
        set("jingli", 250000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 300);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 900000000);

        set_skill("dodge", 650);
        set_skill("unarmed", 650);
        set_skill("force", 650);
        set_skill("parry", 650);
        set_skill("sword", 650);
        set_skill("poison", 650);
        set_skill("medical", 650);
        set_skill("hand", 650);
        set_skill("strike", 650);
        set_skill("staff", 650);
        set_skill("finger", 650);
        set_skill("claw", 650);
        set_skill("blade", 650);
        set_skill("pixie-jian", 650);
        set_skill("literate", 650);
        set_skill("taoism", 650);
        set_skill("buddhism", 650);
        set_skill("jiuyang-shengong", 650);
        set_skill("lingbo-weibu", 650);
        set_skill("qiankun-danuoyi", 650);
        set_skill("xuanming-zhang", 650);
        set_skill("jiuyin-baiguzhao",650);
        set_skill("dugu-jiujian", 650);
        set_skill("liumai-shenjian", 650);
        set_skill("qianzhu-wandushou", 650);
        set_skill("ranmu-daofa", 650);
        set_skill("dagou-bang", 650);
        set_skill("shaolin-yishu", 650);
        set_skill("wudu-qishu", 650);
        set_skill("throwing", 650);
        set_skill("martial-cognize", 800);
        set_skill("mantian-xing", 650);
        set_skill("idle-force", 650);

        map_skill("unarmed", "pixie-jian");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("finger", "liumai-shenjian");
        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");

        prepare_skill("finger", "liumai-shenjian");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: perform_action, "blade.zhenyan" :),
                (: perform_action, "blade.huo" :),
                (: perform_action, "staff.wugou" :),
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.ban" :),
                (: perform_action, "unarmed.cimu" :),
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),
                (: perform_action, "throwing.shan" :),
                (: perform_action, "hand.zhugu" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "finger.zong" :),
                (: perform_action, "finger.zong" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
                
        }) );

        set("dugu-jiujian/nothing", 1);

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

        setup();
        carry_object("d/city/obj/cloth")->wear();
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
                                 set("jing", 150000);
                                 set("neili", 35000);
                                 set("max_jing", 150000);
                                 set("eff_qi", 400000);
                                 set("qi", 400000);
                                 set("max_jingli", 500000);
                                 set("jingli", 500000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }
             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 5)
             {
                      ob->set("sky12/floor", 6);
                 command("say 阁下请便吧！");
             }
        }

        set("qi", 400000);
        set("jing", 150000);
        set("neili", 35000);
        set("max_jing", 150000);
        set("eff_qi", 400000);
                set("qi", 400000);
        set("max_jingli", 500000);
        set("jingli", 500000);
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
