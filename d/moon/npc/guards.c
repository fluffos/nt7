// ken 1999.12.11
inherit NPC;
void create()
{
	string *order=({"少年", "青年", "中年", "壮年", "老年"});
        set_name((order[random(5)]) +"庄丁", ({ "guards"}) );
        set("gender", "男性" );
        set("title", "圆月山庄");
        set("age", 22);
        set("long", "这是圆月山庄的一个庄丁。\n");
        set("combat_exp", 300000+random(100000));
        set("attitude", "friendly");
        set_skill("unarmed", 50);
	set_skill("moon-steps",random(50)+50);
	set_skill("dodge", random(50)+50);
	set_skill("moon-blade",random(50)+50);
        set_skill("parry",random(50)+50);
        set_skill("blade",random(50)+50);
	map_skill("dodge","moon-steps");
        map_skill("blade","moon-blade");
        map_skill("parry","moon-blade");
        set("force",1500);
        set("force_factor",random(30)+10);
        set("max_force",300);
        set("chat_chance", 3);
        set("chat_msg", ({
                "庄丁警惕地喝道；站住！你是干什么的？\n",
		(: random_move :),
        }) );
	
	setup();
        carry_object(__DIR__"obj/sblade")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
        
}

