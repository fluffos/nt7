// tanggan.c

#include <ansi.h>
inherit NPC;
inherit F_GUARDER; 

int permit_pass(object me, string dir); 

void create()
{
        set_name("唐刚", ({ "tang gang", "tang", "gang"}));
        set("nickname", HIR "嫡系死士" NOR); 
        set("long", "这是嫡系死士之一，一身的功夫却是不凡。\n");
        set("gender", "男性");
        set("age", 55);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 18);
        set("int", 25);
        set("con", 24);
        set("dex", 28);

        set("max_qi", 600);
        set("max_jingli", 500);
        set("max_douzhi", 600);
        set("douzhi", 600);
        set("neili", 600);
        set("max_neili", 500);
        set("jiali", 10);
        set("combat_exp", 30000);
        set("score", 5000);
        set("level", 15);

        set_skill("force", 180);
        set_skill("throwing", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("literate", 180);
        set_skill("hand", 180);
        set_skill("sword", 180);
        set_skill("boyun-suowu", 180);
        set_skill("biyun-xinfa", 180);
        set_skill("qiulin-shiye", 180);
        set_skill("wuzhan-mei", 180);
        set_skill("tangmen-throwing", 180);
        set_skill("tangmen-poison", 180);
        set_skill("tangmen-medical", 180);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        
        prepare_skill("hand", "boyun-suowu");

        create_family("唐门世家", 3, "弟子");
        
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),  
                (: exert_function, "powerup" :),  
                // ( : command("wield all") : ),
                (: perform_action, "throwing.qian" :),  
                
        }) );        
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);  

        set("coagents", ({ 
                ([ "startroom" : "/d/tangmen/tangltt", 
                   "id"        : "tang laotai" ]), 
        })); 

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangjian")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/qianqian"));  
}

int permit_pass(object me, string dir)
{
        object *inv;
        int i;

        if (! living(this_object()))
                return 1;
                
        if( !query("family", me) )
        {
                message_vision("$N对$n道：要学艺的话到镇上找唐柔？！\n", this_object(), me);
                return notify_fail("唐刚不想让你过去。\n"); 
        }
        
        notify_fail("看来" + name() + "不打算让你过去。\n");

        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i])) continue;
                if( query("family/family_name", inv[i]) != "唐门世家" )
                {
                        message_vision("$N对$n喝道：你背的是谁？还不快快放下！\n",
                                       this_object(), me);
                        return 0;
                }
        }

        if( query("family/family_name", me) && 
            query("family/family_name", me) != "唐门世家" )
        {
                message_vision("$N对$n道：对不起，不是我们唐门世家的人"
                               "请勿入唐门。\n", this_object(), me);
                return 0;
        }
        
        if( !query("tangmen/upshan", me) )
        {
                message_vision("$N对$n道：对不起，你的武功还没有练到家，不可进唐门的！\n",
                               this_object(), me);
                return 0;
        }              

             
                      
    
        return 1;
}