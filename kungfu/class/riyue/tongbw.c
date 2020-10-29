//tongbw.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

string ask_zijinchui();
string ask_zijinchuifa();

void create()
{
        set_name("童百熊", ({ "tongbai xiong","xiong"}) );
        set("gender", "男性" );
        set("age", 75);
        set("title", "日月神教风雷堂长老");
        set("long", "他白发披散, 银髯戟张, 脸上的肌肉牵动, \n"
                    "圆睁双眼, 身上的鲜血已然凝结, 神情甚是可怖。\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 21);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);
        set("combat_exp", 350000);
        set("score", 30000);

        set_skill("force", 130);
        set_skill("riyue-xinfa", 130);
        set_skill("dodge", 130);
        set_skill("piaomiao-shenfa", 130);
        set_skill("hand", 130);
        set_skill("huanmo-longtianwu", 130);
        set_skill("cuff", 130);
        set_skill("xuwu-piaomiao", 130);
        set_skill("parry", 130);
        set_skill("literate", 80);
        set_skill("sword", 130);
        set_skill("riyue-jian", 130);
        set_skill("blade", 150);
        set_skill("tianmo-dao", 150);

        map_skill("force", "riyue-xinfa");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("hand", "huanmo-longtianwu");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("sword", "riyue-jian");
        map_skill("parry", "tianmo-dao");
        map_skill("blade", "tianmo-dao");

        prepare_skill("hand", "huanmo-longtianwu");
        prepare_skill("cuff", "xuwu-piaomiao");

        create_family("日月神教",2,"弟子 风雷堂长老");

        set("chat_chance", 2);
        set("chat_msg", ({
            "童百熊怒瞪双眼道: “我没错, 我没有叛教! 东方兄弟你不能冤枉我呀! ”\n",
            "童百熊叹了一口气说：“我和东方兄弟出生入死, 共历患难的时候, 你们还没生下来哪!”\n"
        }));

        set("inquiry",([
            "紫金锤"   : (: ask_zijinchui :),
            "紫金锤法" : (: ask_zijinchuifa :),
            "秘籍"     : (: ask_zijinchuifa :),
        ]));
        set("zijin_book", 1);

        set("master_ob",2);
        setup();
        carry_object("/d/heimuya/npc/obj/zijinchui");
        carry_object("/d/heimuya/npc/obj/dadao")->wield();
        carry_object("/d/heimuya/npc/obj/cloth")->wear();
        carry_object("/d/heimuya/npc/obj/card1");
}

void attempt_apprentice(object ob)
{
    if(! permit_recruit(ob))  return;

    if((int)ob->query_skill("riyue-xinfa", 1) < 80)
    {
         command("say 你的内功心法尚欠火候，多练练去吧！");
         return;
    }

    command("recruit "+query("id", ob));
    set("title", HIM"日月神教"HIY"风雷堂教众"NOR, ob);
}

string ask_zijinchui()
{
    set_temp("zijin_chuifa", 1, this_player());
    message_vision("童百熊叹了口气，说道：“这柄紫金锤是当年一位"
                   "武林前辈送给我的。”\n", this_object());
    return "唉，只可惜我未能将锤法练成。";
}

string ask_zijinchuifa()
{
    object ob = new("/clone/book/zijin_book");
    object me = this_player();
    string msg;

    if( query_temp("zijin_chuifa", me) && !query("couple", me) && 
        query("combat_exp", me)>10000 )
    {
        if (query("zijin_book"))
        {
            message_vision("童百熊叹了口气，说道：“我习练紫金锤法多年，仍不能"
                           "悟出其中要领，只习得十之一二。”\n", me);
            msg = "这位" + RANK_D->query_respect(me) + "，你我一见如故，这" +
                  "本书我就送你吧，希望你能领悟其中精要。";
            ob->move(this_object());
            set("zijin_book", 0);
            command("givezijin_bookto"+query("id", me));
        }
        else   msg = "你来晚了，《紫金锤法》一书我已送人。";

        delete_temp("zijin_chuifa", me);
        return msg;
    }
    else
        return "紫金锤法我只传有缘之人，可惜你不太适合。";
}

void reset()
{
    set("zijin_book", 1);
}
