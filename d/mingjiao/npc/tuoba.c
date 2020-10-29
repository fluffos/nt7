// TuoBa.c
// pal 1997.05.14

#include "ansi.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

void create()
{
        set_name("拓跋", ({ "tuoba", }));
        set("long",
        "他是一位带发修行的头陀，身穿一件白布长袍。\n"
        "他个子不高，但很结实，看上去颇为纯朴。可是脸上经常浮现出奇怪的笑容，让\n"
        "人有些摸不着头脑。\n"
        );

        set("title",HIG "明教" NOR "风字门门主");
        set("level",5);

        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 22);
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 450);
        set("max_jing", 300);
        set("neili", 600);
        set("max_neili", 600);
        set("jiali", 50);
        set("combat_exp", 50000);
        set("score", 100);

        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("cuff", 80);
        set_skill("strike", 80);
        set_skill("literate", 100);

        set_skill("shenghuo-xinfa", 80);
        set_skill("shenghuo-bu", 80);
        set_skill("shenghuo-quan", 80);
        set_skill("guangming-zhang", 80);
        set_skill("liehuo-jian", 80);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "shenghuo-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("cuff", "shenghuo-quan");

        prepare_skill("cuff", "shenghuo-quan");
        prepare_skill("strike", "guangming-zhang");

        set("mingjiao_party","风字门");
        set("inherit_title",HIG"明教"NOR"风字门教众"NOR);
        create_family("明教", 38, "风字门门主");
        setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}

#include "menzhu.h"
