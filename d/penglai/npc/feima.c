inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
        set_name(HIW "飞马" NOR, ({ "fei ma", "fei", "ma" }));
        set("long", HIW "这是一只长着翅膀的骏马，模样甚是威风。\n" NOR);

        set("age", 190);
        set("str", 40);
        set("dex", 30);
        set("max_qi", 4200000);
        set("max_jing", 150000);
        set("max_jingli", 1500000);
	set("max_neili", 200000);
	set("neili", 200000);		
        set("combat_exp", 20000000);
	set("no_nuoyi", 1);
	set("gift/exp", 800);
	set("gift/pot", 520);
	set("oblist", ([
		"/clone/fam/gift/str3" :1,
		"/clone/fam/gift/con3" :1,			
		"/clone/armor/feima-xue2" :400,			
		"/clone/armor/feima-xue3":200,
		"/clone/armor/feima-xue" :500,
	]));

	set_skill("force", 560);
	set_skill("dodge", 560);
	set_skill("unarmed", 500);
	set_skill("sword", 560);
	set_skill("parry", 560);
	set_skill("claw", 560);

        setup();
	add_money("gold", 5 + random(10));
}
void init()
{
	// 随机攻击玩家
	if (userp(this_player()) && random(5) == 1)
	{
		kill_ob(this_player());
	}
}

void die()
{
	if (query("qi") > 150000)
	{
		revive();
		return;
	}
	::die();
}
