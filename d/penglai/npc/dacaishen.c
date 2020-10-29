inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
        set_name(HIY "大财神" NOR, ({ "da caishen", "da", "caishen" }));
        set("long", HIY "这是仙界的大财神，据说专门打理仙界和人间的一切帐务。\n" NOR);

        set("age", 9000);
        set("str", 80);
        set("dex", 120);
        set("max_qi", 18000000);
        set("max_jing", 1500000);
        set("max_jingli", 15000000);
        set("jingli", 15000000);
	set("max_neili", 200000);
	set("neili", 200000);		
        set("combat_exp", 200000000);
	set("no_nuoyi", 1);
	set("gift/exp", 1200);
	set("gift/pot", 800);
	set("oblist", ([
		"/clone/fam/gift/str3" : 2,
		"/clone/fam/gift/lan-feihun2" : 2,
		"/clone/armor/moling-zhiyi" : 10,
		"/clone/armor/moling-zhiyi2" : 6,
		"/clone/armor/moling-zhiyi3" : 3,			
		"/clone/armor/shenwu-xiangquan":60,
		"/clone/armor/shenwu-xiangquan2":40,
		"/clone/armor/shenwu-xiangquan3":30,					
		"/clone/armor/yinyang-erhuan":20,
		"/clone/armor/yinyang-erhuan2":10,
		"/clone/armor/yinyang-erhuan3":8,
	]));

	set_skill("force", 500);
	set_skill("dodge", 500);
	set_skill("unarmed", 500);
	set_skill("sword", 500);
	set_skill("parry", 500);
	set_skill("claw", 500);

        setup();
	add_money("gold", 30 + random(31));
}
void die()
{
	if (query("qi") > 200000)
	{
		revive();
		return;
	}
	::die();
}
