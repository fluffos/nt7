// This program is a part of NT MudLIB
// fang.c 方碧琳

#include <ansi.h>
#include "emei.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("方碧琳", ({ "fang bilin","fang","bilin"}));
        set("long",
                "她是峨嵋派的第四代俗家弟子。\n");
        set("gender", "女性");
        set("age", 20);
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

        set_skill("persuading", 40);
        set_skill("throwing", 30);
        set_skill("force", 60);
        set_skill("dodge", 80);
        set_skill("finger", 50);
        set_skill("parry", 70);
        set_skill("strike", 80);
        set_skill("blade", 60);
        set_skill("emei-xinfa", 60);
        set_skill("jinding-zhang", 80);
        set_skill("tiangang-zhi", 50);
        set_skill("yanxing-dao", 60);
        set_skill("zhutian-bu", 80);
        set_skill("linji-zhuang", 60);

        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("blade","yanxing-dao");
        map_skill("parry","yanxing-dao");

        set("inquiry", ([
                "出家"     : "你去本山的庵堂里找我静字辈师姐吧。她们在福寿庵、千佛庵、\n万年庵、万行庵和卧云庵修行。\n",
                "灭绝师太" : "她是本派掌门人，在华藏庵修行。\n",
        ]));

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
