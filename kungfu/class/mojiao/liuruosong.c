// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "mojiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("柳若松", ({"liu ruosong", "liu", "ruosong"}));
        set("nickname", HIW "青松剑客" NOR );
        // set("title", "岁寒三友");
        set("gender", "男性");
        set("age", 42);
        set("shen_type", -1);
        set("long", "“岁寒三友”中的”青松剑客”，万松山庄的主人。\n"
                    "武当山玄真观，天一真人门下唯一的俗家弟子。\n");
        set("attitude", "peaceful");

        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 300);

        set("combat_exp", 1500000);
        set("score", 0);

        set_skill("force", 180);
        set_skill("moshen-xinfa", 180);
        set_skill("wudang-xinfa", 150);
        set_skill("dodge", 180);
        set_skill("moshen-bufa", 180);
        set_skill("strike", 180);
        set_skill("moshen-zhangfa", 180);
        set_skill("wudang-zhang", 150);
        set_skill("cuff", 180);
        set_skill("moshen-quanfa", 180);
        set_skill("sword", 180);
        set_skill("moshen-jianfa", 180);
        set_skill("wudang-jian", 150);
        set_skill("liuxing-jianfa", 180);
        set_skill("blade", 180);
        set_skill("moshen-daofa", 180);
        set_skill("parry", 150);
        set_skill("literate", 110);

        map_skill("force", "moshen-xinfa");
        map_skill("dodge", "moshen-bufa");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "liuxing-jianfa");
        map_skill("blade", "moshen-daofa");
        map_skill("parry", "liuxing-jianfa");
        
        prepare_skill("strike", "moshen-zhangfa");
        
        create_family("魔教", 41, "弟子");

        set("no_teach", ([
                "wudang-xinfa"          : "此乃武当武功，我不能轻易传授于你。",
                "wudang-zhang"      : "此乃武当武功，我不能轻易传授于你。",
                "wudang-jian"         : "此乃武当武功，我不能轻易传授于你。",
        ]));
  
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({
                (: perform_action, "sword.liuxing" :), 
                (: exert_function, "recover" :),
        }) );

        set_temp("apply/attack", 180);
        set_temp("apply/damage", 180);
        set_temp("apply/unarmed_damage", 180);
        set_temp("apply/armor", 180);
                        
        set("master_ob", 3);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangjian")->wield();
        add_money("silver",70);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  return;

        command("recruit "+query("id", ob));
        command("say 好，好，好，日后一定要光大我魔教。"); 
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "天外流星" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/liuxing-jianfa/liuxing",
                           "name"    : "天外流星",
                           "sk1"     : "liuxing-jianfa",
                           "lv1"     : 150,
                           "dodge"   : 150,
                           "gongxian": 420,
                           "shen"    : -10000, ]));
                break;

        default:
                return 0;
        }
}