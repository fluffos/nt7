// This program is a part of NT MudLIB
// hui.c 静慧师太

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("静慧师太", ({ "jinghui shitai","jinghui","shitai"}));
        set("long",
           "她是峨嵋派四师姐，只见她两眼烁烁有神，不停的扫视着四周。。\n");
        set("gender", "女性");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("shen", 10000);
        set("class", "bonze");
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
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
        set_skill("dodge", 90);
        set_skill("finger", 100);
        set_skill("parry", 90);
        set_skill("strike", 100);
        set_skill("sword", 95);
        set_skill("literate", 90);
        set_skill("mahayana", 100);
        set_skill("hand", 100);
        set_skill("jieshou-jiushi", 100);
        set_skill("emei-xinfa", 100);
        set_skill("jinding-zhang", 100);
        set_skill("tiangang-zhi", 90);
        set_skill("huifeng-jian", 90);
        set_skill("zhutian-bu", 100);
        set_skill("linji-zhuang", 100);
        set_skill("emei-jian", 90);

        map_skill("hand", "jieshou-jiushi");
        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("sword","huifeng-jian");
        map_skill("parry","huifeng-jian");

        create_family("峨嵋派", 4, "弟子");

        set("master_ob", 3);
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

        message("vision", "静慧师太对着"+me->name()+"讲了几句话。\n", environment(me), ({me}) );

        switch(random(2)) {
                case 0:
                write("静慧师太说：赵州从谂，乃是禅宗著名高师。
            有一次一个官员曾问他：和尚还入地狱吗？　赵州从谂答：我马上就入。
            那官员颇有些幸灾乐祸，说：大善知识为什么还入地狱呢？
            赵州从谂是怎样回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 +random(5)) {
                        write("你忽然想起在一部经书里读到过这个故事。\n");
                        write("你说：赵州从谂回答他道：我不入地狱，谁去教化你？\n\n");
                        message("vision", me->name()+"想了一下，跟静慧师太说了几句话。\n",
                                environment(me), ({me}) );

                        command("say 阿弥陀佛，善哉！善哉！好吧，我就收下你了。");
                        command("say 希望你能以慈悲之心，以智慧之力，努力行善，济度众生。\n");
                        command("recruit "+query("id", me));
                }
                else {
                        write("你想了许久，也不明白其中的道理。\n");
                        command("say 阿弥陀佛，你多学些佛法后再来找我吧。\n");
                }
                break;

                case 1:
                write("静慧师太说：赵州从谂，乃是禅宗著名高师。
            有一次一个僧人问他：狗子还有佛性没有？　赵州说：无。　
            僧人说：上至诸佛，下至蝼蚁，都有佛性，为什么狗子却没有？
            赵州从谂是怎样回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 60 +random(5)) {
                        write("你灵机一动，想起这个典故。\n");
                        write("你说：赵州从谂回答道：因为他有业识，即识神之业力在。\n\n");
                        message("vision", me->name()+"想了一下，跟静慧师太说了几句话。\n",
                                environment(me), ({me}) );

                        command("say 阿弥陀佛，善哉！善哉！好吧，我就收下你了。");
                        command("say 希望你能以慈悲之心，以智慧之力，努力行善， 济度众生。\n");
                        command("recruit "+query("id", me));
                }
                else {
                        write("你想了许久，也不明白其中的道理。\n");
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
