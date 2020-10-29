inherit NPC;

void create()
{
        set_name("江湖豪杰", ({ "jianghu haojie","haojie" }) );
        set("nickname", "市井豪杰");
        set("gender", "男性");
        set("age", 24);
        set("long",
                "江湖豪杰。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("neili", 900000);
        set("max_neili", 900000);
        set("jiali", 1000);
        set("combat_exp", 300000000);
        set("score", 20000);
        set("shen_type", 0);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("literate", 300);

        set_skill("huashan-jianfa", 500);
        set_skill("huashan-xinfa", 500);
        set_skill("huashan-quanfa", 500);
        set_skill("feiyan-huixiang", 500);

        map_skill("sword", "huashan-jianfa");
        map_skill("parry", "huashan-jianfa");
        map_skill("force", "huashan-xinfa");
        map_skill("unarmed", "huashan-quanfa");
        map_skill("dodge", "feiyan-huixiang");

        set("auto_perform", 1);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

