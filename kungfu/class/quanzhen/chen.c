// This program is a part of NT MudLIB
// chen.c 陈志益

inherit NPC;
inherit F_MASTER;

#include "quanzhen.h"

void create()
{
        set_name("陈志益", ({"chen zhiyi", "chen"}));
        set("gender", "男性");
        set("class", "taoist");
        set("age", 24);
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 28);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 1500);
        set("max_qi", 1500);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 60);
        set("level", 8);
        set("combat_exp", 180000);

        set_skill("force", 80);
        set_skill("quanzhen-xinfa", 80);
        set_skill("sword", 80);
        set_skill("quanzhen-jian",90);
        set_skill("dodge", 70);
        set_skill("jinyan-gong", 70);
        set_skill("parry", 80);
        set_skill("unarmed",80);
        set_skill("finger",80);
        set_skill("zhongnan-zhi", 80);
        set_skill("literate",60);
        set_skill("taoism",60);
        set_skill("array",80);
        set_skill("beidou-zhenfa", 80);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        prepare_skill("finger", "zhongnan-zhi");

        create_family("全真教", 3, "弟子");

        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
        ]) );

        set("master_ob",2);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greyrobe")->wear();

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 好吧，我就收下你这个徒弟了。");
        command("recruit "+query("id", ob));
}
