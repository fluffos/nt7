// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// wu.c 武眠风

inherit NPC;

string ask_me_2(string name);
void create()
{
        set_name("武眠风", ({ "wu mianfeng", "wu" }));
        set("long","
他是黄药师的五弟子武眠风，他身材瘦小，沉默寡言，在江湖
上名声不响，但却极得黄药师信任，顾而命他掌管桃花岛药房
重地。他在桃花弟子中尤精剑法。\n");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 25);
        set("int", 30);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);
        set("level", 10);
        set("combat_exp", 400000);

        set_skill("force", 120);
        set_skill("bibo-shengong", 120);
        set_skill("dodge", 120);
        set_skill("luoying-shenfa", 120);
        set_skill("strike", 120);
        set_skill("luoying-shenzhang", 120);
        set_skill("unarmed", 120);
        set_skill("luoying-shenjian", 120);
        set_skill("qimen-wuxing", 120);
        set_skill("xuanfeng-tui", 120);
        set_skill("hand", 120);
        set_skill("lanhua-shou", 120);
        set_skill("sword",120);
        set_skill("yuxiao-jianfa", 120);
        set_skill("literate", 80);

        map_skill("force", "bibo-shengong");
        map_skill("dodge", "luoying-shenfa");
        map_skill("strike", "luoying-shenzhang");
        map_skill("parry", "yuxiao-jianfa");
        map_skill("hand", "lanhua-shou");
        map_skill("unarmed", "xuanfeng-tui");
        map_skill("sword","yuxiao-jianfa");

        prepare_skill("strike", "luoying-shenjian");

        create_family("桃花岛", 2, "弟子");
        setup();
        set("inquiry", ([
                    "九花玉露丸" : (: ask_me_2, "yulu-wan" :)
        ]));

        set("drug_count", 3);
        set("yulu_count", 1);

        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/d/taohua/obj/tiexiao")->wield();
}

string ask_me_2(string name)
{
        mapping fam; 
        object ob;
        
        if( !(fam=query("family", this_player())) || fam["family_name"] != "桃花岛" )
                return RANK_D->query_respect(this_player()) + 
                "与本派素无来往，不知此话从何谈起？";

        if( query("family/master_name", this_player()) != "黄药师" )
                return "你功夫不够，还是不要为妙。";                

        if (query("yulu_count") < 1)
                return "抱歉，你来得不是时候，已经发完了。";

        if (this_player()->query_condition("work") > 0)
                return "我不是才给过你药吗？怎麽又来要了，真是贪得无厌！";

        ob = new("/d/taohua/obj/"+name);
        ob->move(this_player(), 1);
        this_player()->apply_condition("work", 45);

        addn("yulu_count", -1);

        message_vision("武眠风给$N一粒"+query("name", ob)+"。\n",this_player());

        return "拿去吧。小心别弄丢了。";
}

int accept_kill(object me)
{
        if( query("family/family_name", me) == "桃花岛"){
        command("say 你我本是同门，如何要加害于我！\n");
        set("th_killer", 1, me);
        kill_ob(me);
        return 1;
        }
        return 0;
}
void unconcious()
{
        object ob, me=this_object();

        if( objectp(ob=query_temp("last_damage_from", me) )
         && query("family/family_name", ob) == "桃花岛" )
        set("th_killer", 1, ob);

        ::unconcious();
}