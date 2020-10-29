inherit NPC;

void create()
{
        set_name("王老板", ({ "wang laobang", "publisher", "wang"}));
        set("long", "这是一位白白胖胖的中年人，身子微微发福，是个富商豪绅模样。\n"
                "他手中提着一个小箱子，正笑眯眯地上下打量着你。\n"
                "据说他曾经试过科举，但几次不中后便改行以贩书为业了。\n");
        set("gender", "男性");
        set("age", 45);
        set("str", 25);
        set("dex", 25);
        set("attitude", "peaceful");

        set("combat_exp", 75000);
        set("shen_type", 0);

        set_skill("unarmed", 60);
        set_skill("force", 60);
        set_skill("literate", 300);

        set("neili", 4000); 
        set("max_neili", 4000);
        set("jiali", 500);

        setup();
        carry_object("/clone/cloth/cloth")->wear();

}
