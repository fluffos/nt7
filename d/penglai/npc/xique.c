inherit __DIR__"pld_npc.c";
#include <ansi.h>

int is_pld_npc(){return 1;}

void create()
{
        set_name(HIW "喜鹊" NOR, ({ "xi que", "xi", "que" }));
        set("long", HIW "这是一只可爱的喜鹊，看起来很机灵，最喜欢吃青梅。\n" NOR);

        set("age", 1);
        set("str", 1);
        set("dex", 20);
        set("max_qi", 5000);        
        set("max_jing", 20000);
        set("max_jingli", 20000);
        set("jingli", 20000);
	set("max_neili", 2000);
	set("neili", 2000);		
        set("combat_exp", 1000000);

	set("gift/exp", 100);
	set("gift/pot", 50);
	set("oblist", ([
		"/clone/fam/gift/dex2" : 200,
		"/clone/fam/gift/dex3" : 2,
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
        
        if (random(400) == 1)
        {
       	       set_name(HIM "喜鹊仙子" NOR, ({ "xique xianzi", "xique", "xianzi" }));
       	       set("long", HIM "这是传说中喜鹊化作的仙子，着一身喜鹊羽衣，美貌无比，令人心醉。\n" NOR);       
       	       set("gift/exp", 100);
	       set("gift/pot", 50); 	
               set("str", 30);                  
               set("dex", 80);                 
               set("max_qi", 150000);      
               set("eff_qi", 150000); 
               set("jingli", 20000);
               set("qi", 150000);       
               set("max_jing", 200000);         
               set("eff_jing", 200000);
               set("jing", 200000);
      	       set("max_neili", 50000);         
      	       set("neili", 50000);		
               set("combat_exp", 100000000);  
               add_money("gold", 200 + random(400));   	       
        }
        else
	{
		add_money("silver", 2 + random(4));
	}
	
	if (random(100) == 1)carry_object("/d/penglai/obj/qingmei");
	if (random(100) == 1)carry_object("/d/penglai/obj/meihua");
}
