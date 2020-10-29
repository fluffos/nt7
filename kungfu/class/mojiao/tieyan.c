// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "mojiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("铁燕", ({"tie yan", "tie", "yan"}));
        set("title", "魔教长老");
        set("gender", "男性");
        set("age", 52);
        set("shen_type", -1);
        set("long", "一个又黑又瘦又小的老头，身青灰色的粗布衣服，站在那里，比别人坐着也高不了多少。\n"
                    "和铁燕夫人站在一起看起来就像是一对刚从乡下来的老夫妻，完全没有一点特别的地方。\n");
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
        set_skill("sword", 600);
        set_skill("moshen-jianfa", 600);
        set_skill("blade", 600);
        set_skill("moshen-daofa", 600);
        set_skill("yanzi-blade", 600);
        set_skill("parry", 600);
        set_skill("literate", 600);
        set_skill("medical", 600);
        set_skill("mojiao-medical", 600);
        set_skill("motun-tianxia", 600);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "moshen-jianda");
        map_skill("blade", "yanzi-blade");
        map_skill("parry", "yanzi-blade");

        prepare_skill("strike", "moshen-zhangfa");
        
        create_family("魔教", 40, "长老");
  
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({
                (: perform_action, "blade.he" :), 
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

        case "双刀合壁" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yanzi-blade/he",
                           "name"    : "双刀合壁",
                           "sk1"     : "yanzi-blade",
                           "lv1"     : 200,
                           "dodge"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "魔神魅影" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jiutian-xiaoyaobu/ying",
                           "name"    : "魔神魅影",
                           "sk1"     : "jiutian-xiaoyaobu",
                           "lv1"     : 200,
                           "dodge"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "神刀化血" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/chiyou-kuangzhanjue/hua",
                           "name"    : "神刀化血",
                           "sk1"     : "chiyou-kuangzhanjue",
                           "lv1"     : 200,
                           "force"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "蚩尤回魂" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/chiyou-kuangzhanjue/hui",
                           "name"    : "蚩尤回魂",
                           "sk1"     : "chiyou-kuangzhanjue",
                           "lv1"     : 200,
                           "force"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;                                
        default:
                return 0;
        }
}

void kill_ob (object ob)
{
        object me = this_object();
        object where = environment(me);
        object guard = present("tie wife", where);

        ::kill_ob(ob);

        if (guard && ! guard->is_fighting())
        {
                message_vision(HIW "\n$N" HIW "大怒道：居然欺负到我们铁燕"
                               "头上来了，死吧！\n\n" NOR, guard);
                guard->kill_ob(ob);
        }
}