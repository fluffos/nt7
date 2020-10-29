// This program is a part of NT MudLIB

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("赵狗儿", ({"zhao gouer", "zhao", "gouer"}));
        set("title", "丐帮一袋弟子");
        set("gender", "男性");
        set("age", 16);
        set("long",
                "这是衣衫褴屡的小乞丐，老是缩在路边昏昏沉沉地打磕睡。\n");
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 18);
        set("int", 20);
        set("con", 20);
        set("dex", 23);
        set("max_qi", 120);
        set("max_jing", 120);
        set("neili", 150);
        set("max_neili", 150);
        set("jiali", 5);
        set("combat_exp", 2500);

        set_skill("force", 30);
        set_skill("huntian-qigong", 30);
        set_skill("dodge", 30);
        set_skill("feiyan-zoubi", 30);
        set_skill("hand", 30);
        set_skill("shexing-diaoshou", 30);
        set_skill("unarmed", 30);
           set_skill("cuff", 30);
        set_skill("changquan", 30);
        set_skill("strike", 30);
        set_skill("xiaoyaoyou", 30);
        set_skill("parry", 30);
        set_skill("staff", 30);
        set_skill("fengmo-zhang", 30);
        set_skill("blade", 30);
        set_skill("liuhe-dao", 30);
        set_skill("begging", 30);
        set_skill("checking", 20);
        set_skill("literate", 10);
        set_skill("martial-cognize", 10);

        map_skill("force", "huntian-qigong");
        map_skill("hand", "shexing-diaoshou");
        map_skill("blade", "liuhe-dao");
        map_skill("strike", "xiaoyaoyou");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "shexing-diaoshou");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("unarmed", "changquan");

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
