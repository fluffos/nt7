// This program is a part of NT MudLIB

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("马俱为", ({"ma juwei", "ma", "juwei"}));
        set("title", "丐帮七袋弟子");
        set("gender", "男性");
        set("age", 35);
        set("long",
                "这是位武艺精强，却沉默寡言的丐帮八袋弟子。\n");
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 23);
        set("int", 22);
        set("con", 18);
        set("dex", 25);
        set("max_qi", 800);
        set("max_jing", 500);
        set("neili", 710);
        set("max_neili", 710);
        set("jiali", 60);
        set("level", 10);
        set("combat_exp", 200000);

        set_skill("force", 80);
        set_skill("huntian-qigong", 80);
        set_skill("dodge", 80);
        set_skill("feiyan-zoubi", 80);
        set_skill("unarmed", 80);
           set_skill("cuff", 80);
        set_skill("changquan", 80);
        set_skill("hand", 80);
        set_skill("shexing-diaoshou", 80);
        set_skill("strike", 80);
        set_skill("xiaoyaoyou", 80);
        set_skill("parry", 80);
        set_skill("staff", 80);
        set_skill("fengmo-zhang", 80);
        set_skill("blade", 80);
        set_skill("liuhe-dao", 80);
        set_skill("begging", 80);
        set_skill("checking", 80);
        set_skill("literate", 80);
        set_skill("martial-cognize", 60);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("blade", "liuhe-dao");
        map_skill("strike", "xiaoyaoyou");
        map_skill("staff", "fengmo-zhang");
        map_skill("unarmed", "changquan");
        map_skill("parry", "shexing-diaoshou");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("丐帮", 19, "弟子");
        set("master_ob",1);
        setup();

        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say 你身为丐帮弟子，竟然不做好事？");
                return;
        }
        command("nod");
        command("say 你拜我为师，可要做好吃苦的准备，好好做个丐帮弟子！");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}
