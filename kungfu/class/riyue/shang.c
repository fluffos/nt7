//shang.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("桑三娘", ({ "sang sanniang", "sang", "sanniang"}) );
        set("gender", "女性" );
        set("age", 45);
        set("title", "日月神教天香堂长老");
        set("long", "神情古怪，面无丝毫微笑，面容却相当清秀。 \n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 24);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 29);

        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("combat_exp", 350000);
        set("score", 30000);
        set("jiali", 200);

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
        set_skill("throwing", 150);
        set_skill("xinghui-canlan", 150);

        map_skill("force", "riyue-xinfa");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("hand", "huanmo-longtianwu");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("sword", "riyue-jian");
        map_skill("parry", "riyue-jian");
        map_skill("throwing", "xinghui-canlan");

        prepare_skill("hand", "huanmo-longtianwu");
        prepare_skill("cuff", "xuwu-piaomiao");

        create_family("日月神教",2,"弟子 天香堂长老");

        set("master_ob",2);
        setup();
        carry_object("/d/heimuya/npc/obj/changjian")->wield();
        carry_object("/d/heimuya/npc/obj/cloth")->wear();
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
    set("title", HIM"日月神教"HIG"天香堂教众"NOR, ob);
}
