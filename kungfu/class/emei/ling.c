// This program is a part of NT MudLIB
// ling.c 赵灵珠

inherit NPC;
inherit F_MASTER;

#include "emei.h"
#include <ansi.h>

void create()
{
        set_name("赵灵珠", ({ "zhao lingzhu","zhao","lingzhu"}));
        set("long",
                "她是峨嵋派的第四代俗家弟子。\n");
        set("gender", "女性");
        set("age", 22);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("shen", 10000);
        set("class", "fighter");

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
        set("combat_exp", 150000);
        set("score", 1000);
        set_skill("throwing", 30);
        set_skill("persuading", 50);
        set_skill("force", 70);
        set_skill("dodge", 80);
        set_skill("finger", 60);
        set_skill("parry", 80);
        set_skill("strike", 60);
        set_skill("blade", 90);
        set_skill("emei-xinfa", 90);
        set_skill("jinding-zhang", 60);
        set_skill("tiangang-zhi", 60);
        set_skill("yanxing-dao", 90);
        set_skill("zhutian-bu", 80);
        set_skill("linji-zhuang", 70);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("blade","yanxing-dao");
        map_skill("parry","yanxing-dao");
        create_family("峨嵋派", 4, "弟子");

        set("master_ob", 2);
        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(CLOTH_DIR"female-cloth")->wear();
        carry_object(CLOTH_DIR"female-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say 好吧，我就收下你了。");
        command("recruit "+query("id", ob));
}
