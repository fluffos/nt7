#include <ansi.h>
inherit SKYBOOKNPC;

void create()
{
        set_name("戚长发", ({ "qi changfa", "qi", "changfa" }));
        set("nickname", HIR "铁索横江" NOR);
        set("gender", "男性" );
        set("class", "swordman");
        set("attitude", "peaceful");
        set("shen_type", 1);
        
        set("skybook", "lianchengjue");

        set("age", 45);
        set("str", 28);
        set("con", 26);
        set("int", 28);
        set("dex", 28);
        set("jing", 50000000);  
        set("max_jing", 50000000);
        set("jingli", 50000000);        
        set("max_jingli", 50000000);            
        set("max_qi", 1000000000);
        set("max_jing", 50000000);
        set("neili", 1000000);
        set("max_neili", 1000000);
        set("jiali", 15000);
        set("combat_exp", 500000000);

        set_skill("force", 2200);
        set_skill("henshan-xinfa", 2200);
        set_skill("dodge", 2200);
        set_skill("henshan-shenfa", 2200);
        set_skill("cuff", 2200);
        set_skill("henshan-quan", 2200);
        set_skill("sword", 2400);
        set_skill("tangshi-jian", 2400);
        set_skill("strike", 2200);
        set_skill("liuyun-zhang" , 2200);
        set_skill("parry", 2200);
        set_skill("literate", 260);
        set_skill("martial-cognize", 700);

        map_skill("strike", "liuyun-zhang");
        map_skill("sword", "tangshi-jian");
        map_skill("force", "zhenyue-jue");
        map_skill("dodge", "henshan-shenfa");
        map_skill("parry", "tangshi-jian");

        prepare_skill("strike", "liuyun-zhang");
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.luo" :),
                (: perform_action, "strike.pai" :),
                (: perform_action, "strike.ying" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 500000);
        set_temp("apply/damage", 400000);
         set_temp("apply/armor", 2000000);
        set_temp("apply/unarmed_damage", 400000);
        
        create_family("衡山支派", 16, "弟子");

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}


void attempt_apprentice(object ob)
{
        command("haha");
        command("say 孺子可教，孺子可教。");
        command("say 你以后定要勤和芳儿切磋武艺。");
        return;
}


void die(object killer)
{
        if (! objectp(killer))return;
        
        if (userp(killer) && environment(killer) == environment(this_object())) 
        {
                command("haha");
                command("say 想不到我一世英名，竟命丧于此！");
                return;
        }
        
        revive();
}

void unconcious()
{
         // 防止直接call_die()
         if (query("qi") > 200000)
         {
                revive();
                return;
         }

        die(query_last_damage_from());
}
