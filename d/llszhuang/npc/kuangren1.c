#include <ansi.h>
inherit NPC;
#include <random_name.h>
void create()
{
        string name,nickname;
        name = comm_man_name();
        nickname = comm_man_nick();
        set_name(name, ({ "kuang ren"}) );
        set("nickname",nickname);
        set("long",@LONG
他眼神凶狠无比，狠狠瞪视着你。
LONG
         );
        set("max_jing", 7000);
        set("max_qi", 7000);                    
        set("max_sen", 7000);
        set("max_neili",7000); 
        set("neili",7000);
        set("jiali",200);     
        set("combat_exp",5800000);
        set("cor",150);
        set("age",65);
        set_skill("pixie-jian", 520);
        set_skill("force", 500);
        set_skill("hamagong", 800);
        set_skill("dodge", 580);
        set_skill("unarmed", 550);
        set_skill("xingxiu-duzhang", 500);
        set_skill("parry", 550);
        set_skill("zhaixing-gong",500);
        set_skill("tianshan-zhang", 515);
        map_skill("force", "hamagong");
        map_skill("dodge", "zhaixing-gong");
        map_skill("unarmed", "xingxiu-duzhang");
        map_skill("parry", "pixie-jian");
        map_skill("sword","pixie-jian");
        set("chat_chance_combat",10);
        set("chat_msg_combat", ({
                (: exert_function,"powerup" :),
        }) );

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player())) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}
