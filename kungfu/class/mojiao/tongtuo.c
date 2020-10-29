// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "mojiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("铜驼", ({"tong tuo", "tong", "tuo"}));
        set("title", "魔教长老");
        set("gender", "男性");
        set("age", 52);
        set("shen_type", -1);
        set("long", "身材高出别人两个头，宽出别人一倍。身着铜甲，整个人不威而怒。\n");
        set("attitude", "peaceful");

        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 10000);
        set("max_jing", 10000);
        set("neili", 130000);
        set("max_neili", 130000);
        set("jiali", 3000);

        set("combat_exp", 150000000);
        set("score", 0);

        set_skill("force", 600);
        set_skill("moshen-xinfa", 600);
        set_skill("chiyou-kuangzhanjue", 600);
        set_skill("dodge", 600);
        set_skill("moshen-bufa", 600);
        set_skill("jiutian-xiaoyaobu", 600);
        set_skill("strike", 600);
        set_skill("moshen-zhangfa", 600);
        set_skill("cuff", 600);
        set_skill("moshen-quanfa", 600);
        set_skill("nuquan", 600);
        set_skill("sword", 600);
        set_skill("moshen-jianfa", 600);
        set_skill("blade", 600);
        set_skill("moshen-daofa", 600);
        set_skill("parry", 600);
        set_skill("moshen-zhenshen", 600);
        set_skill("literate", 600);
        set_skill("medical", 600);
        set_skill("mojiao-medical", 600);
        set_skill("motun-tianxia", 600);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "nuquan");
        map_skill("sword", "moshen-jianda");
        map_skill("blade", "moshen-daofa");
        map_skill("parry", "moshen-zhenshen");

        prepare_skill("cuff", "nuquan");
        
        create_family("魔教", 40, "长老");
  
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({
                (: perform_action, "sword.kuang" :), 
                (: exert_function, "recover" :),
        }) );

        set_temp("apply/attack", 280);
        set_temp("apply/damage", 280);
        set_temp("apply/unarmed_damage", 280);
        set_temp("apply/armor", 280);
                        
        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
        add_money("silver",70);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  return;

        if ((int)ob->query_skill("moshen-xinfa", 1) < 120) 
        {
                command("say 本教的内功心法你还没练好，还要多下苦功才行！");
                return;
        }
        
        command("recruit "+query("id", ob));
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

        case "一怒杀佛" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/nuquan/nu",
                           "name"    : "一怒杀佛",
                           "sk1"     : "nuquan",
                           "lv1"     : 200,
                           "dodge"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "无法无天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/moshen-zhenshen/wu",
                           "name"    : "无法无天",
                           "sk1"     : "moshen-zhenshen",
                           "lv1"     : 200,
                           "dodge"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;
                
        default:
                return 0;
        }
}