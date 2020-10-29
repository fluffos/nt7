inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
        set_name(NOR + YEL "松鼠" NOR, ({ "song shu", "song", "shu" }));
        set("long", YEL "这是一只可爱的松鼠，看起来很机灵。\n" NOR);

        set("age", 1);
        set("str", 1);
        set("dex", 20);
        set("max_qi", 5000);
        set("max_jing", 20000);
	set("max_neili", 2000);
	set("neili", 2000);		
        set("combat_exp", 1000000);

	set("gift/exp", 100);
	set("gift/pot", 50);
	set("oblist", ([
		"/clone/fam/gift/str2" : 200,
		"/clone/fam/gift/str3" : 5,
		"/clone/armor/shangu-zhixing" : 50,
		"/clone/armor/shangu-zhixing2" : 30,
		"/clone/armor/shangu-zhixing3" : 20,			
		"/clone/armor/huangtoujin":60,
		"/clone/armor/huangtoujin2":40,
		"/clone/armor/huangtoujin3":30,					
		"/clone/armor/jinsi-beixin":20,
		"/clone/armor/jinsi-beixin2":10,
		"/clone/armor/jinsi-beixin3":8,	
	]));

        setup();
	add_money("silver", 2 + random(4));
	
	if (random(3) == 1)carry_object("/d/penglai/obj/songye");
}
