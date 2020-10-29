// tangyu.c 唐玉

#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("唐玉", ({ "tang yu", "tang", "yu" }));
        set("long", 
                "他是唐门第二代弟子中的杰出人物。\n");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "heroism");
        set("shen_type", 1);
        set("str", 32);
        set("int", 30);
        set("con", 30);
        set("dex", 32);
        
        set("max_qi", 1000);
        set("max_jing", 3000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 100);
        set("combat_exp", 2000000);
        set("level", 10);
        set("score", 200000);

        set_skill("force", 280);
        set_skill("throwing", 280);
        set_skill("dodge", 280);
        set_skill("parry", 280);
        set_skill("literate", 280);
        set_skill("hand", 280);
        set_skill("sword", 280);
        set_skill("boyun-suowu", 280);
        set_skill("biyun-xinfa", 280);
        set_skill("qiulin-shiye", 280);
        set_skill("wuzhan-mei", 280);
        set_skill("tangmen-throwing", 280);
        set_skill("poison", 280);
        set_skill("medical", 280);
        set_skill("tangmen-poison", 280);
        set_skill("tangmen-medical", 280);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "boyun-suowu");
        map_skill("sword", "wuzhan-mei");        
        map_skill("hand", "boyun-suowu");
        map_skill("medical", "tangmen-medical");
        map_skill("poison", "tangmen-poison");
        
        prepare_skill("hand", "boyun-suowu");

        
        create_family("唐门世家", 2, "嫡系高手");
        set("class", "tangmen");

        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),  
                (: exert_function, "powerup" :),  
                // ( : command("wield all") : ),
                (: perform_action, "throwing.san" :),                  
        }) );        
        
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);  

        set("master_ob", 3);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));  
        carry_object("/d/tangmen/obj/feidao");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  
                return;
                        
        if( query("shen", ob)<10000 )
         {
                command("say 我收徒最注重德行！");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否还做得不够？");
                return;
        }

        if ((int)ob->query_skill("biyun-xinfa", 1) < 120) {
                command("say 唐门虽然以暗器为主，但还是要辅以内力。"); 
                command("say " + RANK_D->query_respect(ob) + 
                        "是否还应该在碧云心法上多下点功夫？");
                return;
        }
        if( query("int", ob)<28){
                command("say 唐门历来注重弟子的文学修为。");
                command("say 本派功夫要能熟练运用，必须能体会其中所含深远意境，悟性差了是不行的。");
                command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
                return;
        }
        command("say 哈哈哈，我就收下你，记住以后要在江湖行侠仗义喔！");
        command("recruit "+query("id", ob));
}
