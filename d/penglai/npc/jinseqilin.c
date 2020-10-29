inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
        set_name(HIY "金色麒麟" NOR, ({ "jinse qilin", "jinse", "qilin" }));
        set("long", HIY "这是一只浑身长满了金毛的麒麟，金光射的你有些睁不开眼睛。\n" NOR);

        set("age", 190);
        set("str", 40);
        set("dex", 30);
        set("max_qi", 24000000);
        set("max_jing", 1500000);
        set("max_jingli", 15000000);
        set("jingli", 15000000);
	set("max_neili", 200000);
	set("neili",200000);		
        set("combat_exp", 800000000);
	set("no_nuoyi", 1);
	set("gift/exp", 3000);
	set("gift/pot", 1500);
	set("oblist", ([
		"/clone/fam/gift/str4" :2,
		"/clone/fam/gift/con4" :2,
		"/clone/fam/gift/dex4" :2,
		"/clone/fam/gift/int4" :2,							
		"/clone/armor/moling-zhiyi3" : 3,			
		"/clone/armor/zhanhun-xue3":20,
		"/clone/armor/xingyue-erhuan3":20,
		"/clone/fam/item/wannian-hong":30,
                "/clone/fam/max/xunhuang":30,  
	]));

	set_skill("force", 960);
	set_skill("dodge", 960);
	set_skill("unarmed", 900);
	set_skill("sword", 960);
	set_skill("parry", 960);
	set_skill("claw", 960);
	
        set_temp("apply/dodge", 520);
        set_temp("apply/defense", 520);
        set_temp("apply/unarmed_damage", 580);
        set_temp("apply/armor", 2200);
        	
        setup();
	add_money("gold", 30 + random(20));
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
	if (query("qi") > 200000)
	{
		revive();
		return;
	}
	::die();
}
