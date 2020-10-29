// guxu.c 谷虚

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("谷虚道长", ({ "guxu daozhang", "guxu", "daozhang" }));
        set("long","他就是俞岱岩的弟子谷虚道长。\n他今年四十岁，主管武当派的俗事。\n");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 22);
        set("int", 25);
        set("con", 26);
        set("dex", 23);

        set("max_qi", 2800);
        set("max_jing", 1400);
        set("neili", 3300);
        set("max_neili", 3300);
        set("jiali", 50);

        set("combat_exp", 500000);
        set("score", 28000);

        set_skill("force", 120);
        set_skill("yinyun-ziqi", 120);
        set_skill("dodge", 100);
        set_skill("tiyunzong", 100);
        set_skill("strike", 110);
        set_skill("wudang-zhang", 110);
        set_skill("parry", 120);
        set_skill("sword", 100);
        set_skill("wudang-jian", 100);
        set_skill("taoism", 70);
          set_skill("literate", 80);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        set("env/wimpy", 60);
        create_family("武当派", 3, "弟子");
        set("inquiry", ([
                "道德经" : (: ask_me :),
                "jing"   : (: ask_me :),
                "book"   : (: ask_me :),
        ]));

        set("book_count", 1);

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}

/*
void init()
{
        object me = this_player();

        ::init();

        if( query("family/family_name", me) == "武当派" && 
                query("wudang/offerring", me)>query("age", me)*2 )
                set_temp("mark/谷虚", 1, me);
}
*/

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否还做得不够？");
                return;
        }
        command("say 好吧，贫道就收下你了。即入武当门来，勿忘行善！");
        command("recruit "+query("id", ob));
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "武当派")
                return RANK_D->query_respect(this_player()) +"与本派素无来往，不知此话从何谈起？";
        if (query("book_count") < 1)
                return "你来晚了，本派的道德真经不在此处。";
        addn("book_count", -1);
        ob = new(BOOK_DIR"daodejing-ii");
        ob->move(this_player());
        return "好吧，这本「道德经」你拿回去好好钻研。";
}

void reset()
{
        set("book_count", 1);
}
