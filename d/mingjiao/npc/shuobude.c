// ShuoBuDe.c
// pal 1997.05.11

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;
#include <ansi.h>
#include "tangzhu.h"

void create()
{
        set_name("说不得", ({ "shuo bude", "shuo", "bude", }));
        set("long",
        "他是一位笑嘻嘻的僧人，身穿一件白布长袍。\n"
        "\n"
        );

        set("title", HIG "明教" NOR "五散人");
        set("nickname", "布袋和尚");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 50);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 5000);

        set_skill("force", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("sword", 150);
        set_skill("cuff", 150);
        set_skill("strike", 150);
        set_skill("literate", 100);

        set_skill("shenghuo-xinfa", 150);
        set_skill("shenghuo-bu", 150);
        set_skill("shenghuo-quan", 150);
        set_skill("guangming-zhang", 150);
        set_skill("liehuo-jian", 150);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "shenghuo-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("cuff", "shenghuo-quan");

        prepare_skill("cuff", "shenghuo-quan");
        prepare_skill("strike", "guangming-zhang");

        create_family("明教", 36, "五散人");
        set("inherit_title",HIG"明教"NOR"光明掌旗使"NOR);
        setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}

void init()
{
        ::init();

        if( interactive(this_player()) && query_temp("fighting", this_player()) )
        {
                COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon") );
                addn_temp("beat_count", 1, this_player());
        }       
}
