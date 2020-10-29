// lao-denuo.c

#include <ansi.h>
inherit NPC;
inherit F_GUARDER;
inherit F_MASTER;

#include "qizong.h"

string ask_me(object who);
void create()
{
        set_name("劳德诺", ({ "lao denuo","lao","denuo" }) );
        set("nickname", "老好人");
        set("gender", "男性");
        set("age", 61);
        set("long", "劳德诺是岳不群的二弟子，武艺也是不凡。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 3400);
        set("max_jing", 1700);
        set("neili", 2800);
        set("max_neili", 2800);

        set("combat_exp", 150000);
        set("shen_type", -1);
        set("score", 5000);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.lao" :),
                (: perform_action, "cuff.song" :),
                (: perform_action, "sword.feng" :),
                (: perform_action, "sword.lian" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("unarmed", 120);
        set_skill("sword", 140);
        set_skill("force", 140);
        set_skill("cuff", 120);
        set_skill("strike", 120);
        set_skill("parry", 120);
        set_skill("dodge", 120);
        set_skill("literate", 100);
        set_skill("martial-cognize", 100);

        set_skill("huashan-sword", 140);
        set_skill("huashan-neigong", 140);
        set_skill("huashan-quan", 120);
        set_skill("huashan-zhang", 120);
        set_skill("huashan-shenfa", 120);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("cuff", "huashan-quan");
        map_skill("strike", "huashan-zhang");
        map_skill("dodge", "huashan-shenfa");

        prepare_skill("strike", "huashan-zhang");
        prepare_skill("claw", "huashan-quan");

        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);

        set("inquiry", ([
                "岳不群"     :  "他是我尊师，你找他有事吗？\n",
                "宁中则"     :  "她是我师母！\n",
                "紫霞秘籍" : (: ask_me :),
        ]));

        set("apply/dodge", 100);

        set("coagents", ({
                ([ "startroom" : "/d/huashan/qunxianguan",
                   "id"        : "yue buqun" ]),
        }));

        create_family("华山派", 14, "弟子");
        set("master_ob",4);
        set("master_ob",2);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if( !permit_recruit(ob) )
                return;

        if( query("shen", ob)<0 )
        {
             command("shake");
             command("say 我华山派乃名门正派，不收你这种心术不正之徒！");
             return;
        }

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));
}


int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "截手式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/jie",
                           "name"    : "截手式",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 30,
                           "gongxian": 60,
                           "shen"    : 500, ]));
                break;

        case "飞絮飘渺" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-zhang/piao",
                           "name"    : "飞絮飘渺",
                           "sk1"     : "huashan-zhang",
                           "lv1"     : 30,
                           "gongxian": 60,
                           "shen"    : 600, ]));
                break;

        case "苍松式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-quan/song",
                           "name"    : "苍松式",
                           "sk1"     : "huashan-quan",
                           "lv1"     : 40,
                           "gongxian": 100,
                           "shen"    : 800, ]));
                break;

        case "剑掌五连环" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/lian",
                           "name"    : "剑掌五连环",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 50,
                           "force"   : 100,
                           "gongxian": 150,
                           "shen"    : 1200, ]));
                break;

        default:
                return 0;
        }
}


string ask_me(object who)
{
        int i;
        object *ob, book;

        if ((random(10) < 8) || is_fighting())
                return "对不起，这件事，我不清楚，你还是问我师傅去吧！\n";

        set_temp("apply/attack",  50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage",  50);

        message("vision",
                YEL "看来这件事你都知道了？臭贼，去死吧！\n"
                "劳德诺使开长剑，招数精奇，狠辣无比，一改整日笑咪咪的模样。\n" NOR,
                environment(), this_object());


        ob = all_inventory(environment());
        for (i = sizeof(ob) - 1; i >= 0; i--)
        {
                if (! userp(ob[i])) continue;

                if( query_temp("hs/askzixia", ob[i]) )
                {
                        delete_temp("hs/askzixia", ob[i]);
                        book = new("/clone/book/zixia_book");
                        book->move(environment(this_object()));
                }
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }

        return "我带师投艺，忍辱负重，你竟敢打我的主意！\n";
}

