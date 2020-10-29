// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("秋月", ({"qiu yue"}));
        set("gender", "女性");
        set("age", 18);
        set("shen_type", -1);
        set("long", "青青的侍女，十七八的年纪。实际上是魔教天美宫主派在青青身边的卧底。\n"
                    "秋月的肌肤，比秋天的月亮还要皎洁、媚人。\n");
        set("attitude", "peaceful");

        set("per", 26);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 300);

        set("combat_exp", 1500000);
        set("score", 0);

        set_skill("force", 180);
        set_skill("moshen-xinfa", 180);
        set_skill("dodge", 180);
        set_skill("moshen-bufa", 180);
        set_skill("strike", 180);
        set_skill("moshen-zhangfa", 180);
        set_skill("cuff", 180);
        set_skill("moshen-quanfa", 180);
        set_skill("sword", 180);
        set_skill("moshen-jianfa", 180);
        set_skill("blade", 180);
        set_skill("moshen-daofa", 180);
        set_skill("parry", 150);
        set_skill("literate", 110);

        map_skill("force", "moshen-xinfa");
        map_skill("dodge", "moshen-bufa");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "moshen-jianfa");
        map_skill("blade", "moshen-daofa");
        map_skill("parry", "liuxing-jianfa");

        prepare_skill("strike", "moshen-zhangfa");
        
        create_family("魔教", 42, "弟子");

        set_temp("apply/attack", 180);
        set_temp("apply/damage", 180);
        set_temp("apply/unarmed_damage", 180);
        set_temp("apply/armor", 180);
                        
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangjian")->wield();
        add_money("silver",70);
}