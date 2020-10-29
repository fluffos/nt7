// This program is a part of NT MudLIB
// ding.c 丁敏君

#include "emei.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("丁敏君", ({ "ding minjun","ding","minjun"}));
        set("long",
                "她是峨嵋派的第四代俗家弟子。是天下最恶心，无赖的人。\n");
        set("gender", "女性");
        set("age", 22);
        set("attitude", "peaceful");
        set("shen_type", -2);
        set("class", "fighter");

        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("per", 10);

        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jingli", 1500);
        set("max_jingli", 1500);
        set("level", 10);
        set("combat_exp", 150000);
        set("score", 1000);
        set_skill("force", 60);
        set_skill("throwing", 30);
        set_skill("dodge", 80);
        set_skill("finger", 70);
        set_skill("parry", 70);
        set_skill("strike", 70);
        set_skill("sword", 80);
        set_skill("hand", 60);
        set_skill("jieshou-jiushi", 60);
        set_skill("jinding-zhang", 70);
        set_skill("tiangang-zhi", 70);
        set_skill("emei-jian", 80);
        set_skill("huifeng-jian", 80);
        set_skill("zhutian-bu", 80);
        set_skill("linji-zhuang", 70);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        set("inquiry", ([
                "出家"     : "你去本山的庵堂里找我静字辈师姐吧。她们在福寿庵、千佛庵、\n万年庵、万行庵和卧云庵修行。\n",
                "灭绝师太" : "她是本派掌门人，在华藏庵修行。\n",
        ]));

        create_family("峨嵋派", 4, "弟子");

        set("master_ob", 2);
        set("master_ob", 2);
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"female-cloth")->wear();
        carry_object(CLOTH_DIR"female-shoe")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_hit","hit");
        add_action("do_kill","kill");
}

void greeting(object ob)
{
          if( !ob || environment(ob) != environment() ) return;
          command("chat"+query("name", ob)+"我好喜欢你啊！\n");
}
int do_hit(string arg)
{
          command("chat"+query("name", this_player())+"要非礼我了！\n");
          return 1;
}
int do_kill(string arg)
{
          command("chat"+query("name", this_player())+"这个混蛋要强奸我了！快来人哪！\n");
          return 1;
}
int accept_fight(object me)
{
          command("chat"+query("name", this_player())+"要强奸我了，救命啊！\n");
          return 0;
}

void attempt_apprentice(object ob)
{
        command ("say 阿弥陀佛！贫尼不收弟子。\n");
        return;
}
