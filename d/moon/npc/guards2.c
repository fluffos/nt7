// ken 1999.12.11
inherit NPC;
void create()
{
        set_name("护庄守卫", ({ "guards"}) );
        set("gender", "男性" );
        set("title", "圆月山庄第三代弟子");
        create_family("圆月山庄", 3, "弟子");
        set("class", "moon");
        set("age", 22);
        set("long", "这是圆月山庄庄主丁鹏门下的弟子。\n");
        set("combat_exp", 500000+random(300000));
        set("attitude", "friendly");
        set_skill("unarmed", 150);
	set_skill("moon-steps",random(100)+80);
	set_skill("dodge", random(100)+80);
	set_skill("moon-blade",random(100)+80);
        set_skill("parry",random(100)+80);
        set_skill("blade",random(100)+80);
	map_skill("dodge","moon-steps");
        map_skill("blade","moon-blade");
        map_skill("parry","moon-blade");
        set("force",2500);
        set("force_factor",random(30)+20);
        set("max_force",500);
        set("chat_chance", 3);
        set("chat_msg", ({
                "护庄守卫警惕地喝道；站住！你是干什么的？\n",
        }) );
	
	setup();
        carry_object(__DIR__"obj/lblade")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
        
}

