// This program is a part of NT MudLIB

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("静玄师太", ({ "jingxuan shitai","jingxuan","shitai"}));
        set("long", "她是峨嵋派大师姐，跟随灭绝师太二十余载，"
                    "峨嵋派的功夫已尽得所传。\n");
        set("gender", "女性");
        set("age", 42);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "还俗"  : "峨嵋弟子，不能还俗。你找掌门师太吧。",
        ]));

        set("str", 22);
        set("int", 20);
        set("con", 24);
        set("dex", 23);

        set("max_qi", 3100);
        set("max_jing", 1600);
        set("neili", 3300);
        set("max_neili", 3300);
        set("level", 20);
        set("combat_exp", 800000);

        set_skill("force", 180);
        set_skill("emei-xinfa", 180);
        set_skill("linji-zhuang", 150);
        set_skill("dodge", 160);
        set_skill("zhutian-bu", 160);
        set_skill("strike", 160);
        // set_skill("sixiang-zhang", 160);
        set_skill("jinding-zhang", 160);
        set_skill("finger", 160);
        set_skill("tiangang-zhi", 160);
        set_skill("hand", 160);
        set_skill("jieshou-jiushi", 160);
        set_skill("parry", 160);
        set_skill("sword", 180);
        set_skill("emei-jian", 180);
        set_skill("huifeng-jian", 180);
        set_skill("blade", 180);
        set_skill("yanxing-dao", 180);
        set_skill("literate", 200);
        set_skill("mahayana", 200);
        set_skill("buddhism", 200);
        set_skill("martial-cognize", 100);

        map_skill("force","emei-xinfa");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("hand", "jieshou-jiushi");
        map_skill("sword", "huifeng-jian");
        map_skill("strike", "jinding-zhang");
        map_skill("blade", "yanxing-dao");
        map_skill("parry","yanxing-dao");

        prepare_skill("hand", "jieshou-jiushi");
        prepare_skill("finger", "tiangang-zhi");

        set("no_teach", ([
                "linji-zhuang" : "临济十二庄需得我师父灭绝师太亲自传授。",
        ]));

        create_family("峨嵋派", 4, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: perform_action, "finger.ling" :),
                (: perform_action, "blade.huan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("master_ob", 4);
        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}

/*
void init()
{
        ::init();
        add_action("do_nod","nod");
}
*/

int do_nod(string arg)
{
        object me = this_player();

        if( !query_temp("pending/kao", me) )
                return 0;

        command("smile");
        command("say 我讲个故事你听：\n");

        message("vision", "静玄师太对着"+me->name()+"讲了几句话。\n",
                        environment(me), ({me}) );

        switch(random(2)) {
                case 0:
                write("静玄师太说：罗汉和尚曾住在峨嵋山延福院里。
            有僧人问他：什么是西来大意？　他说；井中红焰，日里浮沤。
            僧人问：这怎么领会？　罗汉和尚是怎样回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 + random(10)) {
                        write("你想起在一部书里读到过这个典故。\n");
                        write("你说：遥指扶桑日那边。\n\n");
                        message("vision", me->name()+"想了一下，跟静玄师太说了几句话。\n",
                                environment(me), ({me}) );

                        command("say 阿弥陀佛，善哉！善哉！好吧，我就收下你了。");
                        command("say 希望你能以慈悲之心，以智慧之力，努力行善，济度众生。\n");
                        command("recruit "+query("id", me));
                }
                else {
                        write("你想了许久，也解不明白其中的禅理。\n");
                        command("say 阿弥陀佛，你多学些佛法后再来找我吧。\n");
                }
                break;

                case 1:
                write("静玄师太说：密印安民曾在华藏寺开法。
            密印安民有一次请教名僧圆悟：什么是古帆未挂？
            圆悟说：庭前柏树子。密印安民大悟彻悟后说了什么？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 + random(10)) {
                        write("你想起在一部经书里读到过这个典故。\n");
                        write("你答道：古人说“一滴投于巨壑”，殊不知大海也投于一滴！。\n\n");
                        message("vision", me->name()+"想了一下，跟静玄师太说了几句话。\n",
                                environment(me), ({me}) );

                        command("say 阿弥陀佛，善哉！善哉！好吧，我就收下你了。");
                        command("say 希望你能以慈悲之心，以智慧之力，努力行善，济度众生。\n");
                        command("recruit "+query("id", me));
                }
                else {
                        write("你想了许久，也解不明白其中的禅理。\n");
                        command("say 阿弥陀佛，你多学些佛法后在来找我吧。\n");
                }
                       break;
        }
        return 1;

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<1000 )
        {
                command("say " + RANK_D->query_respect(ob) +
                        "你行侠仗义之事还做的不够。");
                return;
        }

        if ((int)ob->query_skill("mahayana",1) < 50)
        {
                command("say 你大乘涅磐功的修为还不够，提高些再来吧。");
                return;
        }

        command("say 阿弥陀佛，善哉！善哉！在本庵修行，我要先考考你的佛法。");
        set_temp("pending/kao", 1, ob);
        command("say 你要准备好了，就告诉(nod)我吧。\n");
        add_action("do_nod", "nod");
        return;
}
