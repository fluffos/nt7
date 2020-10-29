// This program is a part of NT MudLIB

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("江上游", ({"jiang shangyou", "jiang shangyou", "jiang"}));
        set("title", "丐帮五袋弟子");
        set("gender", "男性");
        set("age", 28);
        set("long",
                "他是远近闻名的潜水好手，被人起了个外号就叫「浪里鱼」江上游。\n");

        set("attitude", "peaceful");
        set("class", "beggar");
        set("str", 20);
        set("int", 24);
        set("con", 20);
        set("dex", 28);
        set("max_qi", 550);
        set("max_jing", 550);
        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 40);
        set("level", 6);
        set("combat_exp", 100000);

        set_skill("force", 55);
        set_skill("huntian-qigong", 55);
        set_skill("dodge", 55);
        set_skill("feiyan-zoubi", 55);
        set_skill("unarmed", 50);
           set_skill("cuff", 50);
        set_skill("changquan", 50);
        set_skill("hand", 55);
        set_skill("shexing-diaoshou", 55);
        set_skill("strike", 55);
        set_skill("xiaoyaoyou", 55);
        set_skill("parry", 55);
        set_skill("staff", 55);
        set_skill("fengmo-zhang", 55);
        set_skill("jiaohua-bangfa", 55);
        set_skill("blade", 55);
        set_skill("liuhe-dao", 55);
        set_skill("begging", 55);
        set_skill("checking", 55);
        set_skill("literate", 55);
        set_skill("martial-cognize", 40);

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "changquan");
        map_skill("hand", "shexing-diaoshou");
        map_skill("blade", "liuhe-dao");
        map_skill("strike", "xiaoyaoyou");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "shexing-diaoshou");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("丐帮", 20, "弟子");

        set("master_ob",1);
        setup();

        carry_object(__DIR__"obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "男性" )
                return;

        if( query("shen", ob)<0 )
        {
                command("say 你身为丐帮弟子，竟然不做好事？");
                return;
        }
        command("nod");
        command("say 我便收你为徒，日后可得行侠仗义，莫损我丐帮名声。");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}
