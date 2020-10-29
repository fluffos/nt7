// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit "/inherit/char/punisher"; 

void create()
{
        set_name("白袍老人", ({"baipao laoren", "laoren"}));
        set("gender", "男性");
        set("age", 21);
        set("shen_type", -1);

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

        set_skill("force", 4800);
        set_skill("moshen-xinfa", 4800);
        set_skill("chiyou-kuangzhanjue", 4800);
        set_skill("dodge", 4800);
        set_skill("moshen-bufa", 4800);
        set_skill("jiutian-xiaoyaobu", 4800);
        set_skill("strike", 4800);
        set_skill("moshen-zhangfa", 4800);
        set_skill("cuff", 4800);
        set_skill("moshen-quanfa", 4800);
        set_skill("sword", 4800);
        set_skill("moshen-jianfa", 4800);
        set_skill("blade", 4800);
        set_skill("moshen-daofa", 4800);
        set_skill("moon-blade", 4800);
        set_skill("parry", 4800);
        set_skill("literate", 410);
        set_skill("medical", 400);
        set_skill("mojiao-medical", 400);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "moshen-jianfa");
        map_skill("blade", "moon-blade");
        map_skill("parry", "moon-blade");

        prepare_skill("strike", "moshen-zhangfa");
        
        create_family("魔教", 0, "教主");
  
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({
                (: perform_action, "blade.ting" :),
                (: perform_action, "blade.yue" :),  
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
