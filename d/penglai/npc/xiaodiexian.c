inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
        set_name(HIM "小蝶仙" NOR, ({ "xiao diexian", "xiao", "diexian" }));
        set("long", HIM "还未完全修炼成人形的小蝶仙。\n" NOR);

        set("age", 80);
        set("str", 40);
        set("dex", 30);
        set("max_qi", 300000);
        set("max_jing", 150000);
        set("max_jingli", 150000);
	set("max_neili", 20000);
	set("neili", 20000);		
        set("combat_exp", 20000000);

	set("gift/exp", 200);
	set("gift/pot", 150);
	set("oblist", ([
		"/clone/herb/shedan" : 200,
		"/clone/fam/gift/hong-feihun" : 2,
		"/clone/armor/fenghuang-chai" : 20,
		"/clone/armor/fenghuang-chai2" : 10,
		"/clone/armor/fenghuang-chai3" : 6,			
		"/clone/armor/zhanshen-toukui":60,
		"/clone/armor/zhanshen-toukui2":40,
		"/clone/armor/zhanshen-toukui3":30,					
		"/clone/armor/haizhi-xin":20,
		"/clone/armor/haizhi-xin2":10,
		"/clone/armor/haizhi-xin3":8,	
	]));

	set_skill("force", 260);
	set_skill("dodge", 260);
	set_skill("unarmed", 60);
	set_skill("sword", 60);
	set_skill("parry", 60);
	set_skill("claw", 60);
	
        setup();
	add_money("silver", 6 + random(12));
	
	if (random(20) == 1)carry_object("/d/penglai/obj/biaoben");
}
