inherit NPC;
#include <ansi.h>

void create()
{
        set_name("毒郎中", ({ "du langzhong", "langzhong" }));
        set("long", 
                "一个面目凶神恶刹的中年人，现在在到处收集毒药。\n");
        set("gender", "男性");
        set("age", 50);
        set("attitude", "peaceful");
        set("class", "fighter");
        set("str", 35);
        set("int", 28);
        set("con", 30);
        set("dex", 28);
        
        set("max_qi", 600);
        set("max_jing", 600);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 20);
        set("combat_exp", 50000);

        /*
        set_skill("blade",50);
        set_skill("ruyi-dao",50);
        set_skill("force", 50);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_skill("feiyan-zoubi", 50);
        set_skill("beiming-shengong",50);
        set_skill("changquan", 50);

        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("force", "beiming-shengong");
        map_skill("blade", "ruyi-dao");
        */

        set("title","五毒教教众");
        setup();
        carry_object("/d/beijing/npc/obj/cloth1")->wear();
        carry_object("/d/beijing/npc/obj/blade2")->wield();

}

void init()
{
        object ob;

        ::init();

        ob = this_player();

        command("grin");
        command("say 嘿嘿，今天真不巧，让你遇见了本爷，本爷今天要财要命！\n");
        remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob); 
}
