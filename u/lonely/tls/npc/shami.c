inherit NPC;
void create()
{
        set_name("小沙弥", ({ "xiao shami", "xiao","shami" }));
	set("gender", "男性");
	set("age", 15);
        set("long", "他是一位天龙寺里的小沙弥。\n");	
	set("combat_exp", 1000);
        set("shen", 10);
	set("attitude", "peaceful");
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);
	setup();
	carry_object("/clone/misc/cloth")->wear();
}
