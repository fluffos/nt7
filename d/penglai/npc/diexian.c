// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
	if (random(2))
        	set_name(HIM "蝶仙" NOR, ({ "die xian", "die", "xian" }));
        else
        	set_name(HIM "彩蝶仙子" NOR, ({ "caidie xianzi", "caidie", "xianzi" }));
        	
        set("long", HIM "这便是传说中的蝶仙，一身彩衣打扮，背上还有一对彩色的翅膀，样貌比天仙更胜三分。\n" NOR);

        set("gender", "女性");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "蝴蝶标本"   :   "做好的蝴蝶标本都都交给小蝶仙了，不过我正需要这个，能否帮帮忙。\n",
		"蓬莱仙岛"               :   "这不是你该来的地方，我看你还是快走吧。\n",
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

void unconcious()
{
        die();
}

int accept_object(object me, object obj)
{				
	object ob;
	
        if( query("id", obj) == "hudie biaoben" && 
	    base_name(obj) == "/d/penglai/obj/biaoben")
	{
		command("nod");
		message_vision(HIC "$N" HIC "接过" + obj->name() + HIC "，道：目前我正需要这个，谢谢 ……\n" NOR, this_object());
		message_vision(NOR + CYN "\n$N" NOR "拿出十两白银给" + me->name() + NOR + CYN "。\n" NOR, this_object(), me);
		ob = new("/clone/money/silver");
		ob->set_amount(10);
		ob->move(me, 1);
		destruct(obj);
		return 1;
	}
	return 0;	

}
