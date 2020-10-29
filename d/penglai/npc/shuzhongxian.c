// 
//

#include <ansi.h>

inherit NPC;

string ask_nanti1();
string ask_nanti2();
string ask_nanti3();
string ask_nanti4();
string ask_nanti5();
string ask_nanti6();

void create()
{
        set_name(HIW "书中仙" NOR, ({ "shuzhong xian", "shuzhong", "xian" }));
        	
        set("long", HIW "这位仙人乃大名鼎鼎的书中仙，据说天上地下之事他无所不知，神通广大。\n" NOR);

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
                "如何不被仙气困扰"       :   "这仙气的困扰对于你们凡人来说是无可避免的，不过只要你能回答我的几个难题，\n"
                                             "本仙人到是可以教你如何减少仙气对你的困扰。\n",
                "难题"                   :   "我这里总共有六道难题，如果你能按顺序逐一解决，我便教你如何减少被仙气困扰的方法。\n",                            
                "解决难题"               :   "你想好了就在这里找我吧，按照顺序如第一道题你就 ask xian about 难题一 。\n",
                "如何答复"               :   "每道题目都是一首诗的一部分，答案是一样物品，你找到这个物品交给我就行了。\n",
		"蓬莱仙岛"               :   "这不是你该来的地方，我看你还是快走吧。\n",
		"难题一"                 :   (: ask_nanti1 :),
		"难题二"                 :   (: ask_nanti2 :),
		"难题三"                 :   (: ask_nanti3 :),
		"难题四"                 :   (: ask_nanti4 :),
		"难题五"                 :   (: ask_nanti5 :),
		"难题六"                 :   (: ask_nanti6 :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

string ask_nanti1()
{
	object me;
	string str;
	
	me = this_player();
	str = HIC "“悠然见南山。”" NOR;
	
	if( query("penglai/go_quest/ok", me) )
		return "我的六道难题你都解决了，不错，不错。";
		
	if( query("penglai/go_quest/step", me)>1 )
		return "这道难题你已经解答过了。";	
	
	tell_object(me, HIG "题目是：" + str + HIG "\n " NOR);
set("penglai/go_quest/step", 1, 	me);
	me->save();
	
	return "我等你的好消息了。";
}

string ask_nanti2()
{
	object me;
	string str;
	
	me = this_player();
	str = HIC "“碧草生在幽谷中，沐日浴露姿从容。”\n“天赐神香自悠远，引来蝴蝶弄清风。”" NOR;
	
	if( query("penglai/go_quest/ok", me) )
		return "我的六道难题你都解决了，不错，不错。";
		
	if( query("penglai/go_quest/step", me)>2 )
		return "这道难题你已经解答过了。";	
	
	if( query("penglai/go_quest/step", me)<2 )
		return "你还是先解答前面的难题吧。";
			
	tell_object(me, HIG "题目是：\n" + str + HIG "\n " NOR);
set("penglai/go_quest/step", 2, 	me);
	me->save();
	
	return "我等你的好消息了。";
}

string ask_nanti3()
{
	object me;
	string str;
	
	me = this_player();
	str = HIC "“彩衣天授浮生梦，粉翅风怜浪客诗。”\n“独步寻花花谢早，相思寄月月难知。”" NOR;
	
	if( query("penglai/go_quest/ok", me) )
		return "我的六道难题你都解决了，不错，不错。";
		
	if( query("penglai/go_quest/step", me)>3 )
		return "这道难题你已经解答过了。";	
	
	if( query("penglai/go_quest/step", me)<3 )
		return "你还是先解答前面的难题吧。";
			
	tell_object(me, HIG "题目是：\n" + str + HIG "\n " NOR);
set("penglai/go_quest/step", 3, 	me);
	me->save();

	return "我等你的好消息了。";
}

string ask_nanti4()
{
	object me;
	string str;
	
	me = this_player();
	str = HIC "“若非一番寒澈骨。”\n" NOR;
	
	if( query("penglai/go_quest/ok", me) )
		return "我的六道难题你都解决了，不错，不错。";
		
	if( query("penglai/go_quest/step", me)>4 )
		return "这道难题你已经解答过了。";	
	
	if( query("penglai/go_quest/step", me)<4 )
		return "你还是先解答前面的难题吧。";
			
	tell_object(me, HIG "题目是：\n" + str + HIG "\n " NOR);
set("penglai/go_quest/step", 4, 	me);
	me->save();

	return "我等你的好消息了。";
}

string ask_nanti5()
{
	object me;
	string str;
	
	me = this_player();
	str = HIC "“长昼风雷惊虎豹，半空鳞甲舞蛟龙。”" NOR;
	
	if( query("penglai/go_quest/ok", me) )
		return "我的六道难题你都解决了，不错，不错。";
		
	if( query("penglai/go_quest/step", me)>5 )
		return "这道难题你已经解答过了。";	
	
	if( query("penglai/go_quest/step", me)<5 )
		return "你还是先解答前面的难题吧。";
			
	tell_object(me, HIG "题目是：\n" + str + HIG "\n " NOR);
set("penglai/go_quest/step", 5, 	me);
	me->save();

	return "我等你的好消息了。";
}

string ask_nanti6()
{
	object me;
	string str;
	
	me = this_player();
	str = HIC "“劝君莫嗟叹，精神可胜兵；”\n“充塞天和地，怀抱浪与星。”" NOR;
	
	if( query("penglai/go_quest/ok", me) )
		return "我的六道难题你都解决了，不错，不错。";
		
	if( query("penglai/go_quest/step", me)>6 )
		return "这道难题你已经解答过了。";	
	
	if( query("penglai/go_quest/step", me)<6 )
		return "你还是先解答前面的难题吧。";
			
	tell_object(me, HIG "题目是：\n" + str + HIG "\n " NOR);
set("penglai/go_quest/step", 6, 	me);
	me->save();

	return "我等你的好消息了。";
}
int accept_object(object me, object obj)
{			
	
	if( query("penglai/go_quest/ok", me) )
	{
		command("say 阁下智慧超群，佩服佩服。");
		return 0;
	}
	
	switch(query("penglai/go_quest/step", me) )
	{
		// 菊花
		case 1:
			if( query("id", obj) == "penglai juhua" && 
	    		    base_name(obj) == "/d/penglai/obj/juhua")
	    		{
	    			command("nod");
	    			command("say 很好，很好，你可以开始解答下一道难题了。");
	    			destruct(obj);
set("penglai/go_quest/step", 2, 				me);
	    			me->save();
	    			return 1;
	    		}
	    		command("say 本仙人从不乱收别人东西。");
	    		return 0;
			break;
		// 兰草	
		case 2:
			if( query("id", obj) == "penglai lancao" && 
	    		    base_name(obj) == "/d/penglai/obj/lancao")
	    		{
	    			command("nod");
	    			command("say 很好，很好，你可以开始解答下一道难题了。");
	    			destruct(obj);
set("penglai/go_quest/step", 3, 				me);
	    			me->save();
	    			return 1;
	    		}
	    		command("say 本仙人从不乱收别人东西。");
	    		return 0;		
			break;		
		// 蝴蝶标本
		case 3:
			if( query("id", obj) == "hudie biaoben" && 
	    		    base_name(obj) == "/d/penglai/obj/biaoben")
	    		{
	    			command("nod");
	    			command("say 很好，很好，你可以开始解答下一道难题了。");
	    			destruct(obj);
set("penglai/go_quest/step", 4, 				me);
	    			me->save();
	    			return 1;
	    		}
	    		command("say 本仙人从不乱收别人东西。");
	    		return 0;		
			break;		
		// 梅花
		case 4:
			if( query("id", obj) == "penglai meihua" && 
	    		    base_name(obj) == "/d/penglai/obj/meihua")
	    		{
	    			command("nod");
	    			command("say 很好，很好，你可以开始解答下一道难题了。");
	    			destruct(obj);
set("penglai/go_quest/step", 5, 				me);
	    			me->save();
	    			return 1;
	    		}
	    		command("say 本仙人从不乱收别人东西。");
	    		return 0;		
			break;		
		// 松叶
		case 5:
			if( query("id", obj) == "penglai songye" && 
	    		    base_name(obj) == "/d/penglai/obj/songye")
	    		{
	    			command("nod");
	    			command("say 很好，很好，你可以开始解答下一道难题了。");
	    			destruct(obj);
set("penglai/go_quest/step", 6, 				me);
	    			me->save();
	    			return 1;
	    		}
	    		command("say 本仙人从不乱收别人东西。");
	    		return 0;		
			break;		
		// 竹叶
		case 6:
			if( query("id", obj) == "penglai zhuye" && 
	    		    base_name(obj) == "/d/penglai/obj/zhuye")
	    		{
	    			command("nod");
	    			command("say 很好，很好，阁下智慧超群，将老仙难题逐一解答。");
	    			destruct(obj);
	    			command("say 本仙人便教你如何减少仙气的困扰，你可记好了 ……");
	    			tell_object(me, HIG "恭喜你，已经学会了如何减少岛上仙气对你的困扰。\n" NOR);
set("penglai/go_quest/ok", 1, 				me);
	    			me->save();
	    			return 1;
	    		}
	    		command("say 本仙人从不乱收别人东西。");
	    		return 0;		
			break;	
		default :
			command("say 本仙人从不乱收别人东西。");
			return 0;
			break;			
	}
	
	return 0;

}
void unconcious()
{
        die();
}
