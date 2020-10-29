// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

string ask_jiu();

void create()
{
        set_name(HIW "酒剑仙" NOR, ({ "jiujian xian", "jiujian", "xian" }));

        set("long", HIW "这人好生面熟，难道蜀山派的酒剑仙，他怎会在这里？。\n" NOR);

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
        set_skill("sword", 2500);
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
		"蜀山派"                 :   "你也听说过吗，看不出来啊，呵呵。\n",
		"青梅酒"                 :   (: ask_jiu :),
        ]));
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

string ask_jiu()
{
	object me = this_player();
        object ob_xy, ob_xnj, ob_hbk, ob_qmj;
        object ob_xy2;
	int i;

	// 需要材料
	/*
	 青梅     2
         蓬莱蟠桃 1
         菊花     1
       */
        command("nod");
        command("say 既然是为了青梅酒而来，我酒剑仙当然义不容辞。");
        command("say 不过酿制青梅酒需要一些特殊的材料：");
        message_vision(HIM  + "\n"
                       "青梅     2 颗 \n"
                       "蓬莱蟠桃 1 个\n"
                       "菊花     1 朵\n\n" NOR, this_object());
        command("say 如果你这些材料都备齐了的话就来找我吧！");
        command("say 忘记提醒你了，如果你是第一次找本剑仙酿制青梅酒，嘿嘿 ……");
        
        if( !query_temp("want_make_qingmeijiu", me) )
        {
        set_temp("want_make_qingmeijiu", 1, 	me);
        	return "怎么样？如果你考虑好了，再来找我！\n";
        }
        	
                        
	// 需要青梅
	if (! objectp(ob_xy = present("penglai qingmei", me)))
		return "你好象还没备齐青梅吧？\n";			
	if (base_name(ob_xy) != "/d/penglai/obj/qingmei")
		return "你好象还没备齐青梅吧？\n";
	
        if (! objectp(ob_xy2 = present("penglai qingmei 2", me)))
		return "你好象还没备齐青梅吧？\n";			
        if (base_name(ob_xy2) != "/d/penglai/obj/qingmei")
		return "你好象还没备齐青梅吧？\n";
	
	// 需要蓬莱蟠桃
	if (! objectp(ob_xnj = present("penglai pantao", me)))
		return "你好象还没备齐蓬莱蟠桃吧？\n";			
	if (base_name(ob_xnj) != "/d/penglai/obj/pantao")
		return "你好象还没备齐蓬莱蟠桃吧？\n";

	// 需要菊花
	if (! objectp(ob_hbk = present("penglai juhua", me)))
		return "你好象还没备齐菊花吧？\n";			
	if (base_name(ob_hbk) != "/d/penglai/obj/juhua")
		return "你好象还没备齐菊花吧？\n";

        // 消耗材料      
        ob_xy =  present("penglai qingmei", me);
        destruct(ob_xy);
        ob_xy =  present("penglai qingmei", me);
        destruct(ob_xy);
        ob_xnj = present("penglai pantao", me);
        destruct(ob_xnj);
        ob_hbk = present("penglai juhua", me);        
        destruct(ob_hbk);
        
       
        
        command("say 既然你材料都备齐了，这青梅酒就由本剑仙酿制吧。");
        
        message_sort(HIR "\n$N" HIR "从腰间取出一个葫芦，将各种材料放进葫芦中，然后闭上眼睛，口中"
                     "默念着什么，似乎正在施展法术 …… 顷刻，一股酒香从葫芦中飘出。看来这青梅酒已成。\n\n" NOR, this_object(), me);

	command("say 好了好了，很久没有闻到这青梅酒的香味了。");
	
	if( !query("penglai/qingmeijiu_quest/ok", me) )
	{
		command("say 本剑仙忘记告诉你了，凡是第一次找我酿制青梅酒后，这酒都由本剑仙代为品尝了 ……");
		message_vision(HIC "说罢，$N" HIC "脖子一仰，将葫芦里的青梅酒喝了个精光。\n" NOR, this_object());
		command("haha");
		command("say 好酒，好酒啊。");
set("penglai/qingmeijiu_quest/ok", 1, 		me);
delete_temp("want_make_qingmeijiu", 		me);
		me->save();
		return "不过你不用担心，下次酿制好后我便将酒送你了，哈哈 ~~~";
	}
	else
	{
		ob_qmj = new("/d/penglai/obj/qingmeijiu");
		ob_qmj->move(me, 1);
		message_vision("$N" NOR "拿出一瓶青梅酒给$n。\n" NOR, this_object(), me);
		log_file("penglai_quest",query("id", me)+"制作青梅酒成功！\n");
	}
	
        tell_object(me, HIG "恭喜你，获得了青梅酒，赶紧交给守路仙人吧！\n" NOR);        
        
        delete_temp("want_make_qingmeijiu", me);
        
        me->save();
        
        return "小心，别洒了，这酒可是凡间品尝不到的！\n";
}

void unconcious()
{
        die();
}
