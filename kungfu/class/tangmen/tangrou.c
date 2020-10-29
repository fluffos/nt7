// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "tangmen.h"  

int ask_job();

#include "/d/tangmen/npc/job.h";

void create()
{
        set_name("唐柔", ({ "tang rou", "tang" }));
        set("nickname", HIG "锦江老四" NOR);
        set("long", "这是锦江四公子的老四，一身的功夫却是不凡。\n");
        set("gender", "男性");
        set("age", 25);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 25);
        set("con", 24);
        set("dex", 28);
        set("max_qi", 8000);
        set("max_jingli", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);
        set("shen", 2000);
        set("combat_exp", 100000);
        set("level", 8);
        set("score", 7000);

        set_skill("force", 80);
        set_skill("throwing", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_skill("literate", 80);
        set_skill("hand", 80);
        set_skill("sword", 80);
        set_skill("boyun-suowu", 80);
        set_skill("biyun-xinfa", 80);
        set_skill("qiulin-shiye", 80);
        set_skill("wuzhan-mei", 80);
        set_skill("poison", 80);
        set_skill("medical", 80);
        set_skill("tangmen-throwing", 80);
        set_skill("tangmen-poison", 80);
        set_skill("tangmen-medical", 80);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "boyun-suowu");
        map_skill("sword", "wuzhan-mei");        
        map_skill("hand", "boyun-suowu");
        map_skill("medical", "tangmen-medical");
        map_skill("poison", "tangmen-poison");
        
        prepare_skill("hand", "boyun-suowu");

        
        create_family("唐门世家", 3, "弟子");

        set("inquiry", ([
                "job" : ( : ask_job  : ),
        ]));
        
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

        set("master_ob", 2);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));  
        carry_object("/d/tangmen/obj/feidao");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  
                return;
                
        /*
        if( query("shen", ob)>1000 || query("shen", ob)<1000
         || query("combat_exp", ob)>10000 )
        {
                command("say “我唐门世家乃是武林世家，你已是武林中人，我不能收你为徒！”\n");
                return;
        }
        if( query("dex", ob)<30 )
        {
                command("say “你的身法太差了，不要误了自己啊！”\n");
                return;    
        }
        if( query("int", ob)<28){
                command("say 唐门历来注重弟子的文学修为。");
                command("say 本派功夫要能熟练运用，必须能体会其中所含深远意境，悟性差了是不行的。");
                command("say " + RANK_D->query_respect(ob) + "的悟性还大有潜力可挖，还是请回吧。");
                return;
        }
        if( query("str", ob)<30){
                command("say " + RANK_D->query_respect(ob) + "的先天膂力不够，还是请回吧。");
                return;
        }
        */

        if( query("family/family_name", ob) == "唐门世家"
         && query("family/master_name", ob) != "唐柔" )
        {
                command("say “你已是我唐门人，我的功夫不是太高的，你还是找我大师兄吧!”\n");
                return;
        }                    
        command("say “好吧，从今天起你就是唐门的弟子了。”\n");
        set("tangmen/yanli", 1, ob);
        command("recruit "+query("id", ob));
}
