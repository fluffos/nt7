// fangsheng.c

inherit "/inherit/char/punisher";

void create()
{
        set_name("方生", ({ "fang sheng", "fang" }));
        set("long", "他面目慈和，显然是一得道高僧。\n");

        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 40);
        set("shen_type", 1);
        set("str", 35);
        set("int", 31);
        set("con", 37);
        set("dex", 32);
        set("max_qi", 60000);
        set("max_jing", 30000);
        set("neili", 75000);
        set("max_neili", 75000);
        set("jiali", 150);
        set("combat_exp", 24500000);
        set("score", 10000000);

        set_skill("force", 2700);
        set_skill("hunyuan-yiqi", 2700);
        set_skill("dodge", 2600);
        set_skill("shaolin-shenfa", 2600);
        set_skill("finger", 2700);
        set_skill("strike", 270);
        set_skill("hand", 2600);
        set_skill("claw", 2600);
        set_skill("parry", 2600);
        set_skill("nianhua-zhi", 2700);
        set_skill("sanhua-zhang", 2700);
        set_skill("fengyun-shou", 2600);
        set_skill("longzhua-gong", 2600);
        set_skill("buddhism", 2600);
        set_skill("literate", 1200);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("hand", "fengyun-shou");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "nianhua-zhi");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        create_family("少林派", 0, "高僧");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.san" :),
                (: perform_action, "hand.qinna" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
