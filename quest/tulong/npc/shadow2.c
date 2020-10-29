#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("欧阳锋--影", ({ "ouyang feng-shadow", "shadow" }));
        set("long", "他是白驼山庄主，号称“西毒”的欧阳锋。\n"
                   +"由于习练「九阴真经」走火入魔，已变得精\n"
                   +"神错乱，整日披头散发。不过，看来也不是\n"
                   +"真人呢。\n");
        set("title", "白驼山庄主");
        set("gender", "男性");
        set("age", 53);
        set("nickname", HIR "西毒" NOR);
        set("shen_type",-1);
        set("shen", -150000);
        set("attitude", "peaceful");

        set("str", 130);
        set("int", 129);
        set("con", 130);
        set("dex", 128);

        set("qi", 251100);
        set("max_qi", 251100);
        set("jing", 90111);
        set("max_jing", 91100);
        set("neili", 20100);
        set("max_neili", 20100);
        set("jiali", 550);

        set("combat_exp", 151100000);
        set("score", 20001100);

        set_skill("force", 2110);
        set_skill("unarmed", 1510);
        set_skill("dodge", 1810);
        set_skill("parry", 1810);
        set_skill("hand",1710);
        set_skill("training",1510);
        set_skill("staff", 1810);
        set_skill("hamagong", 2010);
        set_skill("chanchu-bufa", 1810);
        set_skill("shexing-diaoshou", 1810);
        set_skill("lingshe-zhangfa", 1810);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("unarmed", "shexing-diaoshou");
        map_skill("hand", "shexing-diaoshou");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa"); 
        set("chat_chance_combat", 60);  
        set("chat_msg_combat", ({ 
               (: exert_function, "recover" :),
                (: exert_function, "reserve" :),
                (: exert_function, "powerup" :),                (: perform_action, "staff.shoot" :),  
                (: perform_action, "staff.shoot" :), 
                (: perform_action, "staff.shoot" :), 
                (: perform_action, "staff.shoot" :), 
                (: perform_action, "staff.shoot" :),         }) );

        create_family("白驼山派",1, "开山祖师");
        setup();
    carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

int accept_fight(object ob)
{
        ob=this_player();   
        if( !query("fighter", ob)){
        command("heihei");
        command("say 好，就让我超度你吧！\n");
        set("fighter", 1, ob);
        set_temp("m_success/幻影", 1, ob);
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob);
        return 1;
        }
        else
        write(query("name", ob)+"，你已经上过场了！\n");
     }
void die()
{
        object ob;
        message_vision("\n$N一晃，变为一缕轻烟消失了。\n", this_object());
        ob = new("/quest/tulong/npc/shadow3");
        ob->move(environment(this_object()));
        destruct(this_object());
} 

