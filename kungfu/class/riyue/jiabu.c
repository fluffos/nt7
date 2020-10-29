//jiabu.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("贾布", ({ "jia bu", "jia", "bu"}) );
        set("gender", "男性" );
        set("age", 45);
        set("title", "日月神教青龙堂长老");
        set("long", "他蜡黄瘦脸，两边太阳穴高高鼓起，便如藏了一枚核桃似的。\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 15);
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
        set_skill("strike", 150);
        set_skill("tianmo-zhang", 150);

        map_skill("force", "riyue-xinfa");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("hand", "huanmo-longtianwu");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("sword", "riyue-jian");
        map_skill("parry", "tianmo-zhang");
        map_skill("strike", "tianmo-zhang");

        create_family("日月神教",2,"弟子 青龙堂长老");

        set("chat_chance", 1);
        set("chat_msg", ({
               "贾布叹道: “攘外必先安内，堂中令牌被盗若是被教主知道，我命休矣。”\n"
        }) );
        set("master_ob",2);
        setup();
        carry_object("/d/heimuya/npc/obj/dadao");
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
    set("title", HIM"日月神教"HIC"青龙堂教众"NOR, ob);
}
