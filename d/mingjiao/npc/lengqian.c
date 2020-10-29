// LengQian.c
// pal 1997.05.11

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;
#include <ansi.h>
#include "tangzhu.h"

void create()
{
        set_name("冷谦", ({ "leng qian", "leng", "qian", }));
        set("long",
        "他是一位冷冷的老者，身穿一件白布长袍。\n"
        "他说话极为简捷，便是杀了他的头也不肯多说半句废话。\n"
        );

        set("title", HIG "明教" NOR "五散人");
        set("nickname", "冷面先生");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "fighter");

        set("age", 54);
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
        set_skill("pili-quan", 150);
        set_skill("shenghuo-quan", 150);
        set_skill("guangming-zhang", 150);
        set_skill("liehuo-jian", 150);
        set_skill("martial-cognize", 100);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "shenghuo-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("sword", "liehuo-jian");
        map_skill("cuff", "pili-quan");
        map_skill("parry", "pili-quan");

        prepare_skill("cuff", "pili-quan");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform cuff.jin") :),
        }) );

        create_family("明教", 36, "五散人");
        set("inherit_title",HIG"明教"NOR"光明掌旗使"NOR);

        /*
        set_temp("apply/attack", 120);
        set_temp("apply/damage", 120);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 120);
        */
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

int accept_ask(object me, string topic)
{
        switch (topic)
        {

        case "紫雷劲" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pili-quan/jin",
                           "name"    : "紫雷劲",
                           "sk1"     : "pili-quan",
                           "lv1"     : 40,
                           "gongxian": 80,
                           "shen"    : 500, ]));
                break;

        default:
                return 0;
        }
}
