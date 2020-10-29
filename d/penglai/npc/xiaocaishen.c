inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
        set_name(HIY "小财神" NOR, ({ "xiao caishen", "xiao", "caishen" }));
        set("long", HIY "这是仙界的小财神，据说专门打理仙界的金库。\n" NOR);

        set("age", 4000);
        set("str", 20);
        set("dex", 30);
        set("max_qi", 200000);
        set("max_jing", 150000);
        set("max_jingli", 150000);
	set("max_neili", 200000);
	set("neili", 200000);		
        set("combat_exp", 20000000);
	set("no_nuoyi", 1);
	set("gift/exp", 150);
	set("gift/pot", 120);
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

	set_skill("force", 20);
	set_skill("dodge", 20);
	set_skill("unarmed", 20);
	set_skill("sword", 20);
	set_skill("parry", 20);
	set_skill("claw", 20);
	
        setup();
	add_money("gold", 1 + random(1));
}
