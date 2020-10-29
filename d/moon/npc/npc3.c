// ken 1999.12.11
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("银龙", ({ "yinlong"}) );
        set("gender", "男性" );
        set("title", "圆月山庄");
        set("nickname", HIR"大护法"NOR);
        set("age", 42);
        set("long", "银龙是圆月山庄庄主丁鹏手下四大护法之一。\n");
        set("combat_exp", 600000+random(400000));
        set("attitude", "friendly");
        set_skill("unarmed", 150);
	set_skill("moon-steps",random(120)+80);
	set_skill("dodge", random(120)+80);
	set_skill("moon-blade",random(120)+80);
        set_skill("parry",random(120)+80);
        set_skill("blade",random(120)+80);
	map_skill("dodge","moon-steps");
        map_skill("blade","moon-blade");
        map_skill("parry","moon-blade");
        set("force",2500);
        set("force_factor",random(40)+20);
        set("max_force",1500);
        set("max_mana",1500);
        set("max_atman",1500);
	setup();
        carry_object(__DIR__"obj/blade3")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
        
}

