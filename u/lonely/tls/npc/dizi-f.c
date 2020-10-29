// /d/dali/npc/dizi-f.c
// By jpei
//update bye cool

inherit NPC;

void create()
{
    int name_no = random(2); 
	string *name_string = ({"闪电","小小胖"});

	set_name("女弟子", ({"nv dizi", "nv", "dizi"}) );
	set("long", "她正在专心致志地练习功夫。\n");
	set("gender", "女性" );
	set("age", 23);
	set("attitude", "peaceful");
	set("str",18);
	set("int",28);
	set("con",19);
	set("dex",22);
	set("max_qi", 650);
	set("max_jing", 250);
	set("neili", 500);
	set("max_neili", 320);
	set("jiali", 10);
	set("combat_exp", 15000);

	set_skill("force", 30);
	set_skill("qiantian-yiyang", 27);
	set_skill("dodge", 30);
	set_skill("tianlong-xiang", 28);
	set_skill("parry", 32);
	set_skill("cuff", 32);
	set_skill("duanjia-quan", 30);
	set_skill("sword", 30);
	set_skill("literate", 35);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
	map_skill("cuff", "duanjia-quan");
	map_skill("force", "qiantian-yiyang");
	prepare_skill("cuff","duanjia-quan");

	set("shen_type", 0);
	create_family("天龙寺", 16, "弟子");

	set("inquiry", ([
		"name": "奴家叫做" + name_string[name_no] + "，从小被寺里的师傅收养。",
		"寒雨": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
		"jpei": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
	]) );

	setup();

	carry_object("/clone/misc/cloth.c")->wear();
}
