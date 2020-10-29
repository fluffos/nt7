
inherit NPC;

void create()
{
        set_name("游坦之", ({ "you tanzhi", "you"}));
        set("nickname", "铁丑");
        set("long",
                      "此人一张脸凹凹凸凸，一块红，一块黑，满是创伤痕痕，\n"
                      "五官糜烂，丑陋可怖已极，无不骇然。\n");
        set("gender", "男性");
        set("age", 25);
        set("attitude", "peaceful");
//        set("shen_type", -1);
        set("str", 35);
        set("str", 35);
        set("int", 20);
        set("con", 30);
        set("dex", 20);
        set("no_get", 1);

        set("max_qi", 6500);
        set("qi",6500);
        set("max_jing", 4500);
        set("jing",4500);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jingli",6000);
        set("max_jingli",6000);
        set("jiali", 250);
        set("combat_exp", 3500000);
        set("shen", -400000);
        set("apply/armor", 90);
        set("PKS", 1000000);

        set_skill("force", 200);
        set_skill("huagong-dafa", 200);
        set_skill("dodge", 200);
        set_skill("dodge", 200);
        set_skill("strike", 200);
        set_skill("claw", 200);
        set_skill("sanyin-wugongzhao", 200);
        set_skill("poison", 200);
        set_skill("chousui-zhang", 200);
        set_skill("parry", 200);
        set_skill("tianshan-zhang", 200);
        set_skill("feixing-shu", 200);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("sword", "tianshan-zhang");

        prepare_skill("strike", "chousui-duzhang");
        prepare_skill("claw", "sanyin-wugongzhao");

        set("auto_perform",1);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}