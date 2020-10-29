//xtong1.c 小童

inherit NPC;

void create()
{
	set_name("小童", ({ "xiao tong", "xiao","tong"}) );
	set("gender", "男性" );
	set("age", 15);
	set("long",
		"这个小童正坐在正中的一个凳子上打着瞌睡。\n");
	set("combat_exp", 50000);
	set("attitude", "friendly");
	setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver",random(50));
}