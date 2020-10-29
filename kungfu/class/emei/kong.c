// This program is a part of NT MudLIB
// kong.c 静空师太

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("静空师太", ({ "jingkong shitai","jingkong","shitai"}));
        set("long",
        "她是峨嵋派三师姐，一位中年出家道姑，道冠高拢，慈眉善目。\n");
        set("gender", "女性");
        set("age", 45);
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
        set("per", 30);

        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jingli", 1500);
        set("max_jingli", 1500);
        set("level", 10);
        set("combat_exp", 250000);
        set("score", 1000);
        set_skill("persuading", 80);
        set_skill("force", 100);
        set_skill("throwing", 80);
        set_skill("dodge", 90);
        set_skill("finger", 90);
        set_skill("parry", 80);
        set_skill("strike", 100);
        set_skill("blade", 90);
        set_skill("literate", 90);
        set_skill("mahayana", 100);
        set_skill("jinding-zhang", 90);
        set_skill("tiangang-zhi", 95);
        set_skill("yanxing-dao", 80);
        set_skill("zhutian-bu", 100);
        set_skill("emei-xinfa", 100);
        set_skill("linji-zhuang", 100);
        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("blade","yanxing-dao");
        map_skill("parry","yanxing-dao");

        create_family("峨嵋派", 4, "弟子");

        set("master_ob", 3);
        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
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

        message("vision", "静空师太对着"+me->name()+"讲了几句话。\n",
                        environment(me), ({me}) );

        switch(random(3)) {
                case 0:
                write("静空师太说：白水禅师曾住在我们万年庵，那时叫白水寺。
            有个僧人问他：什么是祖师西来意？　白水禅师是怎样回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 + random(5)) {
                        write("你想起在一部经书里读到过这个故事。\n");
                        write("你说：四溟无窑宅，一滴润乾坤。\n\n");
                        message("vision", me->name()+"想了一下，跟静空师太说了几句话。\n",
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
                write("静空师太说：白水禅师曾住在我们万年庵，那时叫白水寺。
            有个僧人问他：禅宗六祖一路，应谈何事？　白水禅师是怎样回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 + random(5)) {
                        write("你想起在一部经书里读到过这个故事。\n");
                        write("你答道：涧松千载鹤来聚，月中香桂凤凰归。\n\n");
                        message("vision", me->name()+"想了一下，跟静空师太说了几句话。\n",
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

                case 2:
                write("静空师太说：白水禅师曾住在我们万年庵，那时叫白水寺。
            有个僧人问他：什么是此经，即佛性？　白水禅师是怎样回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 ) {
                        write("你想起在一部经书里读到过这个故事。\n");
                        write("你答道：抛梭石女辽空响，海底泥牛夜叫频。\n\n");
                        message("vision", me->name()+"想了一下，跟静空师太说了几句话。\n",
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

        command("say 阿弥陀佛，善哉！善哉！在本庵修行，我要先考考你的佛法。");
        set_temp("pending/kao", 1, ob);
        command("say 你要准备好了，就告诉(nod)我吧。\n");
        add_action("do_nod", "nod");
        return;
}
