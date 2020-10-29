inherit NPC;
#include <ansi.h>;

void create()
{
        set_name("岳不群--空", ({ "yue buqun shadow", "shadow" }) );
        set("title", "华山派掌门");
        set("nickname", "君子剑");
        set("gender", "男性");
        set("class", "swordsman");
        set("age", 55);
        set("long",
                "岳不群自幼执掌华山派，乃当今武林中一等一的高手。不过面前这个\n"
    +"岳不群，似乎让人有些不真实感。\n");
        set("attitude", "peaceful");
        set("str", 126);
        set("con", 130);
        set("dex", 130);
        set("int", 128);

        set("neili", 21400);
        set("max_neili", 21400);
        set("jiali", 330);
        set("max_qi",23000);
        set("max_jing",13200);

        set("combat_exp", 13300000);
        set("shen", -200000);
        set("xunshan", 1);
        set("apprentice_available", 3);

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :), 
                (: perform_action, "sword.cimu" :),  
                (: perform_action, "sword.cimu" :), 
                (: perform_action, "sword.cimu" :), 
                (: perform_action, "sword.cimu" :), 
                (: perform_action, "sword.cimu" :),         }) );
        set("inquiry", ([
            "过关": "要想过关，得先打败我。\n",
        ]) );

        set_skill("unarmed", 820);
        set_skill("sword", 850);
        set_skill("force", 850);
        set_skill("parry", 640);
        set_skill("dodge", 820);
        set_skill("literate", 800);
        set_skill("huashan-sword", 860);
        set_skill("zixia-shengong", 850);
        set_skill("huashan-quan", 820);
        set_skill("feiyan-huixiang", 820);
        set_skill("pixie-jian",850);

        map_skill("sword", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("force", "zixia-shengong");
        map_skill("unarmed", "huashan-quan");
        map_skill("dodge", "feiyan-huixiang");

        create_family("华山派", 13, "掌门");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_fight(object ob)
{
        ob=this_player();   
        if( !query("fighter", ob)){
        command("say 来得好！我可是不会手下留情的。\n");
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
          if( objectp(ob = find_object("/d/dragon/dragoncave")) )
                  destruct(ob);
        ob = new("/quest/tulong/npc/shadow1");
        ob->move(environment(this_object()));
        destruct(this_object());
} 
