//ren.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
// inherit F_QUESTER;

string ask_linghuchong();

void create()
{
        set_name("任盈盈", ({ "ren yingying","ren","ying"}) );
        set("gender", "女性" );
        set("age", 20);
        set("shen_type", 1);
        set("combat_exp", 500000);

        set("per", 30);
        set("str", 16);
        set("dex", 27);
        set("con", 17);
        set("int", 18);

        set("attitude", "friendly");
        set("chat_chance", 3);
        set("chat_msg",({
        "任盈盈说道：不知令狐冲他，怎样了，是否又和那小贱人在一起......\n",
        "任盈盈说道：也不知蓝凤凰见没见到他，可真急死我了.......\n",
        }) );

        create_family("日月神教",2,"弟子 圣姑");

        set_skill("force", 120);
        set_skill("riyue-xinfa", 120);
        set_skill("dodge", 120);
        set_skill("piaomiao-shenfa", 120);
        set_skill("hand", 120);
        set_skill("huanmo-longtianwu", 120);
        set_skill("cuff", 120);
        set_skill("xuwu-piaomiao", 120);
        set_skill("parry", 120);
        set_skill("literate", 120);
        set_skill("sword", 120);
        set_skill("riyue-jian", 120);

        map_skill("force", "riyue-xinfa");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("hand", "huanmo-longtianwu");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("sword", "riyue-jian");
        map_skill("parry", "riyue-jian");

        prepare_skill("hand", "huanmo-longtianwu");
        prepare_skill("cuff", "xuwu-piaomiao");

        set("inquiry",([
            "令狐冲" : (: ask_linghuchong:),
        ]) );
        set("letter",1);

        set("master_ob",2);
        setup();
        carry_object("/clone/cloth/female5-cloth")->wear();
        carry_object("/d/heimuya/npc/obj/jin")->wear();
        carry_object("/d/heimuya/npc/obj/changjian")->wield();
        carry_object("/d/heimuya/npc/obj/letter");
}

void attempt_apprentice(object ob)
{
    if(! permit_recruit(ob))  return;

    if( query("shen", ob)>0 )
    {
         command("say 我倒是想收你，可是教主会不答应的！");
         return;
    }

    command("recruit "+query("id", ob));
    set("title", HIM"日月神教教众"NOR, ob);
}

string ask_linghuchong()
{
    object me = this_player();
    object ob;

    message_vision("任盈盈说道：去年上华山一去就再无音信，他不会忘记我吧......\n", me );
    if(! query("letter"))
        return "这位" + RANK_D->query_respect(me) + "，我已经派" +
               "蓝凤凰去寻找了，也不知道怎么样了。";
    message_vision("任盈盈又说道：这位"+ RANK_D->query_respect(me)+"，我这里有"
                   "信，你要是找到令狐冲，就把信交给他，他会明白的。\n" , me);
    ob=new("/d/heimuya/npc/obj/letter");
    ob->move(me);
    set("letter", 0);
    set_temp("ren_qingxin", 1, me);
    return "这封信烦你交给令狐冲。\n";
}

void reset()
{
     set("letter", 1);
}
