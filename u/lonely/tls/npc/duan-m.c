

inherit NPC;

void create()
{
	int name_no = random(4); 
	string *name_string = ({"邦","雨","永","刚","清","龙","方","言"});

	set_name("段"+name_string[name_no], ({"nan dizi", "nan", "dizi"}) );
	set("long", "他大理段氏的家人，从小被送到天龙学艺。\n");
	set("gender", "男性" );
	set("age", 26);
	set("attitude", "peaceful");
	set("str",22);
	set("int",28);
	set("con",18);
	set("dex",20);
    set("qi", 700);
	set("max_qi", 700);
	set("max_jing", 270);
	set("neili", 500);
	set("max_neili", 340);
	set("jiali", 12);
	set("combat_exp", 45000+random(10000));
	set("shen", 3000+random(2000));

	set_skill("force", 70);
	set_skill("qiantian-yiyang", 60);
	set_skill("dodge", 70);
	set_skill("tianlong-xiang", 70);
	set_skill("parry", 60);
	set_skill("cuff", 50);
	set_skill("duanjia-quan", 55);
	set_skill("sword", 40);
	set_skill("literate", 40);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
	map_skill("cuff", "duanjia-quan");
	map_skill("force", "qiantian-yiyang");
	prepare_skill("finger","yiyang-zhi");

	set("shen_type", 1);
	create_family("天龙寺", 15, "弟子");
	set("inquiry", ([
		"name": "在下姓段，名唤" + name_string[name_no] + "，从十六岁起便投在这里学艺。",
			]) );

	setup();

	carry_object("/clone/misc/cloth.c")->wear();
}
