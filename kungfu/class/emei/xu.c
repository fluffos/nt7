// This program is a part of NT MudLIB
// xu.c 静虚师太

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_MASTER;
int peiyao();
int liandan();
void create()
{

        set_name("静虚师太", ({ "jingxu shitai","jingxu","shitai"}));
        set("long",
          "她是峨嵋派二师姐，峨嵋门下多年，一套峨嵋掌法名动江湖。。\n");
        set("gender", "女性");
        set("age", 43);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("shen", 10000);
        set("class", "bonze");
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "配药"  : ( : peiyao :),
                "霹雳弹": ( : liandan : ),
                "还俗"  : "峨嵋弟子，不能还俗。你找掌门师太吧。",
        ]));

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 20);

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
        set_skill("throwing", 80);
        set_skill("force", 100);
        set_skill("dodge", 90);
        set_skill("finger", 100);
        set_skill("parry", 90);
        set_skill("strike", 80);
        set_skill("blade", 100);
        set_skill("literate", 90);
        set_skill("mahayana", 100);
        set_skill("jinding-zhang", 100);
        set_skill("tiangang-zhi", 90);
        set_skill("yanxing-dao", 100);
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

        message("vision", "静虚师太对着"+me->name()+"讲了几句话。\n",
                        environment(me), ({me}) );

        switch(random(2)) {
                case 0:
                write("静虚师太说：大承和尚曾住在峨嵋山。
            有个僧人问他：什么是胜峰？　大承说；直耸烟岚。
            僧人又问：向上事（即脱俗之事）如何？　他答：立地三尺五。
            僧人又问：什么是佛法？　他就说：兴义门前咚咚鼓。
            那僧说：这我不懂。　大承和尚是怎样回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 50 + random(8)) {
                        write("你想起在一部经书里读到过这个故事。\n");
                        write("你说：朝打三千，暮打八百。\n\n");
                        message("vision", me->name()+"想了一下，跟静虚师太说了几句话。\n",
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
                write("静虚师太说：慧真广悟曾在峨嵋山出家。
            慧真广悟开堂那天，有个僧人出来问：什么是佛法大意？
            慧真广悟说：日出方知天下朗，无油哪点佛前灯？
            僧人又问：什么是双峰境？　慧真广悟是怎样回答他的呢？\n\n");

                if ((int)me->query_skill("mahayana", 1) > 50 + random(8)) {
                        write("你想起在一部经书里读到过这个典故。\n");
                        write("你答道：夜听水流庵后竹，昼起看云面前山。\n\n");
                        message("vision", me->name()+"想了一下，跟静虚师太说了几句话。\n",
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
int peiyao()
{
        object me = this_player();
        object ob = this_object();
        object obj;
        int i;

        if(!objectp(present("caoyao 3",me)))
        {
                command("say 你的身上没有那么多草药。");
                return 1;
        }
        for(i=0;i<3;i++)
        {
                obj=present("caoyao",me);
                destruct(obj);
        }
        command("smile");
        command("say 好吧，我就给你配药了。");
        obj=new("/d/emei/obj/zhongyao");
        obj->move(me);
        message_vision("静慈师太给$N一包中药。\n",me);
        return 1;
}
int liandan()
{
        object me = this_player();
        object ob = this_object();
        object obj;
        int i;
        if(!objectp(present("liuhuang",me)))
        {
                command("say 你的身上没有炼制霹雳弹用的硫磺。");
                return 1;
        }
        obj=present("liuhuang",me);
        destruct(obj);
        command("smile");
        command("say 好吧，我就给你炼制一粒霹雳弹。");
        obj=new("/d/emei/obj/pilidan");
        obj->move(me);
        message_vision("静慈师太给$N一粒霹雳弹。\n",me);
        return 1;
}
