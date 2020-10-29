inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
        //set_name(HIR "年兽" NOR, ({ "nian shou", "nian", "shou" }));
        //set("long", HIR "传说中的年兽，打败它在新的一年能带给你好运。\n" NOR);

        set_name(HIM "幻兽" NOR, ({ "huan shou", "huan", "shou" }));
        set("long", HIM "神话故事中能令人产生幻觉的怪兽。\n" NOR);
        
        set("age", 190);
        set("str", 40);
        set("dex", 30);
        set("max_qi", 500000);
        set("max_jing", 150000);
        set("max_jingli", 15000000);
	set("max_neili", 200000);
	set("neili", 200000);		
        set("combat_exp", 20000000);
	set("no_nuoyi", 1);
	set("gift/exp", 400);
	set("gift/pot", 200);
	set("oblist", ([
		"/clone/fam/pill/blood" : 200,
		"/clone/herb/shedan" : 200,
		"/clone/fam/gift/lan-feihun2" : 2,
		"/clone/armor/moling-zhiyi" : 10,
		"/clone/armor/moling-zhiyi2" : 6,
		"/clone/armor/moling-zhiyi3" : 3,			
		"/clone/armor/lan-feihun":20,
		"/clone/armor/lan-feihun2":10,
		"/clone/armor/lan-feihun3":5,
		"/clone/armor/jinsi-beixin":20,
		"/clone/armor/jinsi-beixin2":10,
		"/clone/armor/jinsi-beixin3":8,	
		"/clone/tattoo/baichuantu": 40,
		"/clone/fam/pill/blood" : 200,		
		"/clone/herb/shedan" : 200,
		"/clone/fam/gift/lan-feihun2" : 2,
		"/clone/armor/moling-zhiyi" : 10,
		"/clone/armor/moling-zhiyi2" : 6,
		"/clone/armor/moling-zhiyi3" : 3,			
		"/clone/armor/lan-feihun":20,
		"/clone/armor/lan-feihun2":10,
		"/clone/armor/lan-feihun3":5,
		"/clone/armor/jinsi-beixin":20,
		"/clone/armor/jinsi-beixin2":10,
		"/clone/armor/jinsi-beixin3":8,	
		"/clone/tattoo/baichuantu": 40,				
	]));

	set_skill("force", 260);
	set_skill("dodge", 260);
	set_skill("unarmed", 100);
	set_skill("sword", 160);
	set_skill("parry", 160);
	set_skill("claw", 160);
	
        setup();
	add_money("silver", 12 + random(20));
}

void die()
{
	if (query("qi") > 50000)
	{
		revive();
		return;
	}
	::die();
}
