// This program is a part of NT MudLIB
// cheng.c 成昆

inherit NPC;

void create()
{
        set_name("成昆",({"cheng kun","cheng","kun"}));
        set("long", "他就是成昆。\n");
        set("age", 60);
        set("attitude", "aggressive");
        set("class", "bonze");
        set("str", 27);
        set("int", 28);
        set("con", 27);
        set("dex", 26);
        set("max_qi", 2500);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("eff_jingli", 1500);
        set("jiali", 50);
        set("level", 20);
        set("combat_exp", 1300000);
        set("shen", -18000);

        set_skill("cuff", 160);
        set_skill("dodge", 160);
        set_skill("parry", 160);
        set_skill("force", 160);
        set_skill("blade", 160);
        set_skill("finger", 160);
        set_skill("shaolin-shenfa", 160);
        set_skill("hunyuan-yiqi", 160);
        set_skill("jingang-quan", 160);
        set_skill("xiuluo-dao", 160);
        set_skill("huanyin-zhi", 160);
        set_skill("literate", 160);

        map_skill("parry", "xiuluo-dao");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("force", "hunyuan-yiqi");
        map_skill("blade", "xiuluo-dao");
        map_skill("cuff", "jingang-quan");
        map_skill("finger", "huanyin-zhi");

        prepare_skill("finger", "huanyin-zhi");

        set("master_ob",1);
        setup();

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
}

