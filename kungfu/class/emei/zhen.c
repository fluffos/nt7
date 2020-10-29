// This program is a part of NT MudLIB
// zhen.c 静真师太

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("静真师太", ({ "jingzhen shitai","jingzhen","shitai"}));
        set("long",
          "她是一位中年出家道姑，身穿道袍，正端坐在蒲团上，眉目之间有一股祥和之气。\n");
        set("gender", "女性");
        set("age", 42);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("shen", 10000);
        set("class", "bonze");
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "还俗"  : "峨嵋弟子，不能还俗。你找掌门师太吧。",
        ]));

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 20);

        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jingli", 1500);
        set("max_jingli", 1500);

        set("combat_exp", 150000);
        set("score", 1000);
        set_skill("persuading", 80);
        set_skill("throwing", 60);
        set_skill("force", 60);
        set_skill("dodge", 70);
        set_skill("finger", 75);
        set_skill("parry", 70);
        set_skill("strike", 60);
        set_skill("sword", 80);
        set_skill("literate", 70);
        set_skill("mahayana", 60);
        set_skill("emei-xinfa", 70);
        set_skill("jinding-zhang", 60);
        set_skill("tiangang-zhi", 65);
        set_skill("emei-jian", 70);
        set_skill("huifeng-jian", 60);
        set_skill("zhutian-bu", 60);
        set_skill("linji-zhuang", 60);
        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        create_family("峨嵋派", 4, "弟子");

        set("master_ob", 2);
        setup();
         carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));
}
