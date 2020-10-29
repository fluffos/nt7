// This program is a part of NT MudLIB

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;

#include "fight.h"

void create()
{
        set_name("莫不收", ({"mo bushou", "mo", "bushou"}));
        set("title", "丐帮三袋弟子");
        set("gender", "男性");
        set("age", 21);
        set("long",
                "这是个蓬头垢面的青年乞丐，整天端着个破碗哼哼：“你不收，他不收，谁也不愿收 ...”\n");
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 25);
        set("int", 22);
        set("con", 18);
        set("dex", 25);
        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 150);
        set("max_neili", 150);
        set("jiali", 25);
        set("level", 4);
        set("combat_exp", 29000);

        set_skill("force", 30);
        set_skill("huntian-qigong", 30);
        set_skill("dodge", 30);
        set_skill("feiyan-zoubi", 30);
        set_skill("unarmed", 40);
           set_skill("cuff", 40);
        set_skill("changquan", 40);
        set_skill("hand", 30);
        set_skill("shexing-diaoshou", 30);
        set_skill("strike", 30);
        set_skill("xiaoyaoyou", 30);
        set_skill("parry", 30);
        set_skill("staff", 30);
        set_skill("fengmo-zhang", 30);
        set_skill("blade", 30);
        set_skill("liuhe-dao", 30);
        set_skill("begging", 30);
        set_skill("checking", 30);
        set_skill("literate", 30);
        set_skill("martial-cognize", 20);

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
        carry_object("/clone/weapon/gangzhang")->wield();
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
