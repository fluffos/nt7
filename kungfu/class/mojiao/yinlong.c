// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "mojiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("银龙", ({"yin long", "yin", "long"}));
        set("title", "魔教长老");
        set("gender", "男性");
        set("age", 52);
        set("shen_type", -1);
        set("long", "银色衣装、戴着银色面具的人，面具下飘着银白色的长衫，因此，可以知道这是\n"
                    "一个男人，一个老人。身上有股无形的、慑人的威力透射出来，使人不敢冒犯他。\n");
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
        set_skill("yinlong-shou", 600);
        set_skill("cuff", 600);
        set_skill("moshen-quanfa", 600);
        set_skill("sword", 600);
        set_skill("moshen-jianfa", 600);
        set_skill("blade", 600);
        set_skill("moshen-daofa", 600);
        set_skill("longteng-daofa", 600);
        set_skill("parry", 600);
        set_skill("literate", 600);
        set_skill("medical", 600);
        set_skill("mojiao-medical", 600);
        set_skill("motun-tianxia", 600);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "yinlong-shou");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "moshen-jianfa");
        map_skill("blade", "longteng-daofa");
        map_skill("parry", "longteng-daofa");

        prepare_skill("strike", "yinlong-shou");
        
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

        case "夺命" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinlong-shou/duo",
                           "name"    : "夺命",
                           "sk1"     : "yinlong-shou",
                           "lv1"     : 200,
                           "dodge"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "腾诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/longteng-daofa/teng",
                           "name"    : "腾诀",
                           "sk1"     : "longteng-daofa",
                           "lv1"     : 200,
                           "dodge"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;
                
        default:
                return 0;
        }
}