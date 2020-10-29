inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
	object ob;
	
        set_name(HIY "猕猴" NOR, ({ "mi hou", "mi", "hou" }));
        set("long", HIY "这是一只猕猴，正盯着你看，似乎存有戒心。\n" NOR);

        set("age", 4);
        set("str", 20);
        set("dex", 30);
        set("max_qi", 50000);
        set("max_jing", 50000);
        set("max_jingli", 50000);
	set("max_neili", 5000);
	set("neili", 5000);		
        set("combat_exp", 2000000);

	set_skill("force", 20);
	set_skill("dodge", 20);
	set_skill("unarmed", 20);
	set_skill("sword", 20);
	set_skill("parry", 20);
	set_skill("claw", 20);
	
	set("gift/exp", 100);
	set("gift/pot", 80);
	set("oblist", ([
		"/clone/fam/gift/int2" : 200,
		"/clone/fam/gift/int3" : 5,
		"/clone/armor/feima-xue2" : 4,
		"/clone/armor/feima-xue3" : 2,
		"/clone/armor/biyu-chai" : 30,
		"/clone/armor/biyu-chai2" : 20,
		"/clone/armor/biyu-chai3" : 10,
		"/clone/armor/huangtoujin":60,
		"/clone/armor/huangtoujin2":40,
		"/clone/armor/huangtoujin3":30,					
		"/clone/armor/tie-shoutao":60,
		"/clone/armor/tie-shoutao2":40,
		"/clone/armor/tie-shoutao3":30,	
	]));

        setup();
	add_money("silver", 4 + random(8));
	
	if (random(20) == 1)carry_object("/d/penglai/obj/pantao");

}
