// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("铁燕夫人", ({"tie wife", "tie", "wife"}));
        set("title", "魔教长老");
        set("gender", "女性");
        set("age", 50);
        set("shen_type", -1);
        set("long", "一个又黑又瘦又小的老人婆，身青灰色的粗布衣服，站在那里，比别人坐着也高不了多少。\n"
                    "和铁燕站在一起看起来就像是一对刚从乡下来的老夫妻，完全没有一点特别的地方。\n");
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
        set_skill("yanzi-blade", 480);
        set_skill("parry", 450);
        set_skill("literate", 410);
        set_skill("medical", 400);
        set_skill("mojiao-medical", 400);
        set_skill("motun-tianxia", 400);

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
        command("say 你还是找我老公去吧！");
}

void kill_ob (object ob)
{
        object me = this_object();
        object where = environment(me);
        object guard = present("tie yan", where);

        ::kill_ob(ob);

        if (guard && ! guard->is_fighting())
        {
                message_vision(HIW "\n$N" HIW "大怒道：居然欺负到我们铁燕"
                               "头上来了，死吧！\n\n" NOR, guard);
                guard->kill_ob(ob);
        }
}