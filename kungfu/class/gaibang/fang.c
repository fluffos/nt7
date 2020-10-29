// fang.c

#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("方舵主", ({"fang duozhu", "fang", "duozhu"}));
        set("long",
                "这是位衣著邋塌，蓬头垢面的丐帮八袋弟子，现任大仁分舵舵主。\n");
        set("gender", "男性");
        set("nickname", HIG"大仁分舵"HIY"舵主"NOR);
        set("title", "丐帮八袋弟子");
        set("age", 25);
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 8);
        set("str", 23);
        set("int", 22);
        set("con", 18);
        set("dex", 25);

        set("max_qi", 360);
        set("max_jing", 300);
        set("neili", 710);
        set("max_neili", 710);
        set("jiali", 36);

        set("combat_exp", 69000);

        set_skill("force", 75);
        set_skill("huntian-qigong", 72);
        set_skill("hand", 75);
        set_skill("suohou-hand", 75);
        set_skill("dodge", 68);
        set_skill("xiaoyaoyou", 70);
        set_skill("parry", 70);
        set_skill("staff", 75);
        set_skill("fengmo-zhang", 75);
        set_skill("begging", 70);
        set_skill("training", 60);
        set_skill("strike",70);

        set_skill("lianhua-zhang",70);
        set_skill("sunze-youfu",70);
        map_skill("strike","sunze-youfu");
        prepare_skill("strike", "sunze-youfu");
        map_skill("force", "huntian-qigong");
        map_skill("hand", "suohou-hand");
        map_skill("parry", "fengmo-zhang");
        map_skill("staff", "fengmo-zhang");
        map_skill("dodge", "xiaoyaoyou");

        //set("party/party_name", HIC"丐帮"NOR);
        //set("party/rank", HIG"大仁分舵"HIY"八袋舵主"NOR);
        //set("party/level", 8);
        create_family("丐帮", 19, "弟子");

        setup();

        carry_object(__DIR__"obj/cloth")->wear();
        carry_object("/clone/weapon/gangzhang")->wield();
}

void attempt_apprentice(object ob)
{
        command("hmm");
        command("say 走开，我不收徒。");
}
