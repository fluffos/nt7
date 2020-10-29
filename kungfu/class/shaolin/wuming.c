// wuming.c 无名老僧

inherit NPC;
inherit F_COAGENT;

void create()
{
        set_name("无名老僧", ({ "wuming laoseng", "wuming" }));
        set("long",
                "他是一位须发花白的老僧，身着粗布衣衫，是"
                "少林寺里面打杂的僧人。\n"
        );

        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 98);
        set("shen_type", 1);
        set("str", 37);
        set("int", 42);
        set("con", 41);
        set("dex", 36);
        set("max_qi", 7000);
        set("max_jing", 3500);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 85);
        set("level", 60);
        set("combat_exp", 3000000);

        set_skill("buddhism", 450);
        set_skill("literate", 300);
        set_skill("martial-cognize", 400);

        set_skill("blade", 500);
        set_skill("claw", 500);
        set_skill("club", 500);
        set_skill("cuff", 500);
        set_skill("dodge", 500);
        set_skill("finger", 500);
        set_skill("force", 550);
        set_skill("hand", 500);
        set_skill("parry", 500);
        set_skill("staff", 500);
        set_skill("strike", 500);
        set_skill("sword", 500);
        set_skill("whip", 500);

        set_skill("banruo-zhang", 500);
        set_skill("cibei-dao", 500);
        set_skill("damo-jian", 500);
        set_skill("fengyun-shou", 500);
        set_skill("fumo-jian", 500);
        set_skill("hunyuan-yiqi", 500);
        set_skill("shaolin-xinfa", 500);
        set_skill("jingang-quan", 500);
        set_skill("longzhua-gong", 500);
        set_skill("luohan-quan", 500);
        set_skill("nianhua-zhi", 500);
        set_skill("pudu-zhang", 500);
        set_skill("qianye-shou", 500);
        set_skill("sanhua-zhang", 500);
        set_skill("riyue-bian", 500);
        set_skill("shaolin-shenfa", 500);
        set_skill("weituo-gun", 500);
        set_skill("wuchang-zhang", 500);
        set_skill("xiuluo-dao", 500);
        set_skill("yingzhua-gong", 500);
        set_skill("yijinjing", 550);
        set_skill("yizhi-chan", 500);
        set_skill("zui-gun", 500);

        map_skill("blade", "cibei-dao");
        map_skill("claw", "longzhua-gong");
        map_skill("club", "wuchang-zhang");
        map_skill("cuff", "luohan-quan");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("force", "yijinjing");
        map_skill("hand", "fengyun-shou");
        map_skill("parry", "nianhua-zhi");
        map_skill("staff", "weituo-gun");
        map_skill("strike", "sanhua-zhang");
        map_skill("sword", "fumo-jian");
        map_skill("whip", "riyue-bian");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        create_family("少林派", 0, "打杂僧人");

        setup();

        carry_object("/d/shaolin/obj/cheng-cloth")->wear();

}
