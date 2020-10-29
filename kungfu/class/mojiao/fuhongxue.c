// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("傅红雪", ({"fu hongxue", "fu", "hongxue"}));
        set("gender", "男性");
        set("age", 26);
        set("shen_type", -1);
        set("long", "一身很普通的装束，让人很难把他和大名鼎鼎的傅红雪联系在一起。\n");
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

        set_skill("force", 480);
        set_skill("moshen-xinfa", 480);
        set_skill("chiyou-kuangzhanjue", 450);
        set_skill("dodge", 480);
        set_skill("moshen-bufa", 480);
        set_skill("jiutian-xiaoyaobu", 450);
        set_skill("strike", 480);
        set_skill("moshen-zhangfa", 480);
        set_skill("cuff", 480);
        set_skill("moshen-quanfa", 480);
        set_skill("sword", 480);
        set_skill("moshen-jianfa", 480);
        set_skill("blade", 480);
        set_skill("moshen-daofa", 480);
        set_skill("mingyue-blade", 480);
        set_skill("parry", 450);
        set_skill("literate", 410);
        set_skill("medical", 400);
        set_skill("mojiao-medical", 400);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "moshen-jianfa");
        map_skill("blade", "mingyue-blade");
        map_skill("parry", "mingyue-blade");

        prepare_skill("strike", "moshen-zhangfa");
        
        create_family("魔教", 40, "弟子");
  
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({
                (: perform_action, "blade.zhan" :), 
                (: perform_action, "blade.tianya" :),                 
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
        command("say 我不收徒，你还是另找他人吧！");
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "天涯明月" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/mingyue-blade/tianya",
                           "name"    : "天涯明月",
                           "sk1"     : "mingyue-blade",
                           "lv1"     : 200,
                           "dodge"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "斩诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/mingyue-blade/zhan",
                           "name"    : "斩诀",
                           "sk1"     : "mingyue-blade",
                           "lv1"     : 200,
                           "dodge"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;
                
        default:
                return 0;
        }
}

int recognize_apprentice(object ob, string skill)
{
        if (ob->query_skill(skill, 1) >= 400)
        {
                command("say 够了！我就教你到这里吧，武功还是"
                        "要靠自己多研究才是！");
                return -1;
        }
                
        if( query_temp("can_learn/fuhongxue/mingyue-blade", ob) && 
            skill == "blade")
                return 1;

        if( query_temp("can_learn/fuhongxue/mingyue-blade", ob) && 
            skill == "mingyue-blade")
                return 1;             

        if (skill == "mingyue-blade")
        {
                if( query("family/family_name", ob) != "魔教" )
                {
                        command("say 你和我素无渊源，我为什么要教你武功？");
                        return -1;
                } 
                                               
                message_vision("$N看了看$n，点点头道：天涯明月刀也没有什么难学的。\n",
                               this_object(), ob);
                set_temp("can_learn/fuhongxue/mingyue-blade", 1, ob);
                return 1;
        }

        command("say 我只懂得一点天涯明月刀，你可不要为难我。");
        return -1;
}