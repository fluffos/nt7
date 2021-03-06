// Npc: /wu.c
// Date: Oct.18 1999 by Lonely

inherit NPC;
void create()
{
        set_name("吴光胜", ({ "wu guangsheng", "wu", "guangsheng"}));
        set("gender", "男性");
        set("attitude", "friendly");

        set("age", 20);
        set("shen_type", -1);
        set("per", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 500);
        set("max_jing", 500);
        set("neili", 550);
        set("max_neili", 550);
        set("jiali", 40);
        set("combat_exp", 50000);
        set("score", 100);

        set_skill("force", 40);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        set_skill("changquan", 40);
        set_skill("parry", 40);
        set_skill("damo-jian", 40);
        set_skill("sword", 40);

        map_skill("unarmed", "changquan");
        map_skill("sword", "damo-jian");
        map_skill("parry", "damo-jian");

        set("inquiry", ([
                "无量玉壁"  : "那是本派禁地，任何外人不得擅入。干犯禁忌，可叫你死葬身之地。",
        ]));

        create_family("无量剑东宗", 5, "弟子");
        setup();

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
