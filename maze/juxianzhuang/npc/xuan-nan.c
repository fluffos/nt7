// Npc: /kungfu/class/shaolin/xuan-nan.c
// Date: YZC 96/01/19

inherit NPC;

void create()
{
        set_name("玄难大师", ({
                "xuannan dashi",
                "xuannan",
                "dashi",
        }));
        set("long",
                "他是一位白须白眉的老僧，身穿一袭银丝棕黄袈裟。他身材极瘦，\n"
                "两手更象鸡爪一样。他双目微闭，一副没精打采的模样。\n"
        );


        set("nickname", "般若堂首座");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 2800);
        set("max_jing", 1000);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 50);
        set("combat_exp", 1100000);

        set_skill("force", 1250);
        set_skill("hunyuan-yiqi", 1250);
        set_skill("shaolin-xinfa", 1250);
        set_skill("dodge", 1250);
        set_skill("shaolin-shenfa", 1250);
        set_skill("parry", 1250);
        set_skill("cuff", 1250);
        set_skill("club", 1250);
        set_skill("finger", 1250);
        set_skill("strike", 1250);
        set_skill("jingang-quan", 1250);
        set_skill("wuchang-zhang", 1250);
        set_skill("yizhi-chan", 1250);
        set_skill("banruo-zhang", 1250);
        set_skill("buddhism", 1250);
        set_skill("literate", 1250);
        set_skill("medical", 180);
        set_skill("shaolin-yishu", 180);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("finger", "yizhi-chan");
        map_skill("strike", "banruo-zhang");
        map_skill("club", "wuchang-zhang");
        map_skill("parry", "wuchang-zhang");

        prepare_skill("finger", "yizhi-chan");
        prepare_skill("strike", "banruo-zhang");

        create_family("少林派", 36, "弟子");


        //set("master_ob",4);
        set("auto_perform", 1);
        setup();

        carry_object("/d/shaolin/obj/chanzhang")->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

