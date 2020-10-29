#include <ansi.h>
inherit NPC;
void create()
{        
        set_name("商人", ({ "shang ren", "shang", "ren" }));
        set("gender", "男性");
        set("age", 20+random(40));
        set("str", 25);        
        set("int",25);
        set("con",25);
        set("dex",25);
        set("max_qi", 400);        
        set("max_jing", 100);        
        set("max_neili", 400);
        set("jiali", 15);
        set("combat_exp", 60000);
        set_skill("force", 40); 
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set("apply/attack", 15);
        set("apply/defense", 15);
        set("apply/damage", 5);
        set("combat_exp", 1500);
        setup();
        add_money("silver", 1);
        carry_object("/clone/weapon/gangjian")->wield();
}
