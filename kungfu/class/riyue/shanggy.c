//shanggy.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("上官云", ({ "shangguan yun","shangguan","yun"}) );
        set("gender", "男性" );
        set("age", 40);
        set("title" , "日月神教白虎堂长老");
        set("long", "他长手长脚, 双目精光灿然, 若有威势。\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 21);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 30);

        set("max_qi", 800);
        set("max_jing",800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);
        set("combat_exp", 360000);
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
        set_skill("pili-daofa", 150);

        map_skill("force", "riyue-xinfa");
        map_skill("dodge", "piaomiao-shenfa");
        map_skill("hand", "huanmo-longtianwu");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("sword", "riyue-jian");
        map_skill("parry", "pili-daofa");
        map_skill("blade", "pili-daofa");

        prepare_skill("hand", "huanmo-longtianwu");
        prepare_skill("cuff", "xuwu-piaomiao");

        create_family("日月神教",2,"弟子 白虎堂长老");

        set("master_ob",2);
        setup();
        carry_object("/d/heimuya/npc/obj/gangzhang");
        carry_object("/d/heimuya/npc/obj/dadao")->wield();
        carry_object("/d/heimuya/npc/obj/cloth")->wear();
        carry_object("/d/heimuya/npc/obj/zhenzhu")->wear();
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
    set("title", HIM"日月神教"HIW"白虎堂教众"NOR, ob);
}
