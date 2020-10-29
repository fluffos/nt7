// JieYinShi
// pal 1997.05.11

#include "ansi.h"

inherit NPC;
inherit F_UNIQUE;

string ask_for_join();

void create()
{
        set_name("接引使", ({"jieyin shi","jieyin","shi",}));
        set("long",
                "他是一位精明的中年人，身穿一件白布长袍。\n"
                "他正在上下打量着你。\n"
                );

        set("title", HIG "明教" NOR);

        set("gender", "男性");
        set("attitude", "friendly");

        set("inquiry",([
                "明教"        : (: ask_for_join :),
                ]));

        set("age", 30);
        set("shen_type", 1);
        set("str", 25);
        set("int", 17);
        set("con", 50);
        set("dex", 21);
        set("max_qi", 450);
        set("max_jing", 200);
        set("neili", 350);
        set("max_neili", 350);
        set("jiali", 30);
        set("combat_exp", 5000);
        set("score", 100);

        set_skill("force", 30);
        set_skill("hunyuan-yiqi", 30);
        set_skill("dodge", 50);
        set_skill("shaolin-shenfa", 50);
        set_skill("cuff", 50);
        set_skill("jingang-quan", 50);
        set_skill("parry", 30);
        set_skill("buddhism", 30);
        set_skill("literate", 30);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("parry", "jingang-quan");

        prepare_skill("cuff", "jingang-quan");

        setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}


void init()
{
        ::init();
}

string ask_for_join()
{
        return "有介绍信就可以找光明左使加入我明教。\n";
}

int accept_object(object ob, object obj)
{
        object me ;
//      string men;
        mapping family;

        me = this_object ();
        ob = this_player ();

        if( query("id", obj) == "tuijian xin1" && 
            query_temp("have_letter", ob) )
        {
                if( query("can_apprentice_menzhu", ob) )
                        return notify_fail("还不赶快去找风字门门主拓跋学我光明圣教的入门武功!\n");

                   if( !mapp(family=query("family", ob)) || !ob->query_family() )
                   {
                        delete_temp("have_letter", ob);

                        if( query("gender", ob) == "女性" )
                                command("say 我明教又得一女中豪杰，真是可"
                                        "喜可贺！");
                        else 
                                command("say 我明教又得一英雄好汉，真是可"
                                        "喜可贺！");

                        set("can_apprentice_menzhu", "风字门", ob);

                        command("smile");
                        tell_object(ob,"接引使者对你说道：光明圣教光明左使手下有天、地、风、雷四门，你先到风字门门主拓跋那里学入门武功吧！\n");
                        destruct(obj);
                        return 1;
                }

                if (family["family_name"] != "明教")
                {
                        message_vision("$N对$n摇摇头，说道：你已经加入"
                                       "其他门派了，不能再入我明教。\n",
                                       me, ob);
                        return 1;
                } else
                        message_vision("$N摇摇头，对$n说道：你已经是我明教"
                                       "的人了。\n", me, ob);
        }
        command("?");
        command("say 这东西给我可没有什麽用。");
        return 0;
}