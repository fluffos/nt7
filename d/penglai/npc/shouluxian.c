// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIY "守路仙人" NOR, ({ "shoulu xian", "shoulu", "xian" }));

        set("long", HIY "这是守护南山路口的仙人，要进入南山非得守路仙人的指引不可。\n" NOR);

        set("gender", "男性");
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
        set_skill("sword", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);
        set_skill("medical", 2500);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
		"蓬莱仙岛"               :   "这不是你该来的地方，我看你还是快走吧。\n",
		"南山入口"               :   "呵呵，如果你能给我一瓶青梅酒，我便指引你入口所在。\n",
		"青梅酒"                 :   "你不知道么，这岛上仙人都爱喝，不过酿制方法只有酒剑仙知道，哈哈　……",
        ]));
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

void init()
{
	object me = this_player();
	
	if (objectp(present("penglai qingmeijiu", me)))
		command("say 好香~~，是谁的青梅酒快快拿出来让本仙人品尝品尝。");
}

void unconcious()
{
        die();
}

int accept_object(object me, object obj)
{			
	
	if( query("penglai/nanshan_quest/ok", me) )
	{
		command("hehe");
		return 0;
	}
	
	if( query("id", obj) == "penglai qingmeijiu" && 
	    base_name(obj) == "/d/penglai/obj/qingmeijiu")
	{
		command("wa");
		message_vision(HIC "$N" HIC "接过" + obj->name() + HIC "，一口便喝了个精光 ……\n" NOR, this_object());
		command("haha");
		command("say 好，实在是好~~~~");
		command("say 既然你解了本仙人的酒瘾，进入南山的方法我自然会教给你 ……");
		message_vision("\n$N" NOR "对着$n" NOR "窃窃私语，似乎在传授什么口诀。\n\n" NOR, this_object(), me);
		tell_object(me, HIG "守路仙人在你耳边说道：#%&$#%@%&%$&#$%@#@$\n" NOR);
		command("say 你可记好了，这入山的方法就在这里面。");
set("penglai/nanshan_quest/ok", 1, 		me);
		destruct(obj);
		return 1;
	}
	else
	{
		command("say 本仙人只要青梅酒，其他什么都不要。");
		return 0;
	}	

}
