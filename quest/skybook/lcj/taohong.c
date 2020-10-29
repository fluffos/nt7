// taohong.c

inherit NPC;
#include <ansi.h>
#include "/d/suzhou/npc/lchj.h";
void outwuguan(object me);
string ask_qiqiang();
string ask_gaotou();
void create()
{
	set_name("中年乞妇", ({ "zhongnian qifu","qifu","zhongnian" }) ); 
	set("gender", "女性" );
	set("age", 33);
	set("long", "一个中年乞妇，低头弓背，披头散发，衣服污秽破烂。\n"); 
	set("combat_exp", 1000);
 
	setup();

	set("chat_chance", 3);
	set("chat_msg", ({
		"中年乞妇喃喃地道：老爷晚上见鬼，要砌墙，怎么怪得我？又....又不是我瞎说。\n",
		"中年乞妇惊恐万分：除了这里，我什么地方都不认得，叫我到哪里去？\n",
		"中年乞妇道：老爷又不是不信，可是...可是....我又没说，老爷却赶了我出来。\n",	 
	}));
	set("inquiry", ([
		"狄云" : "我不认识他，我真的不认识！！",	
		"戚长发" :  "我不认识他，我真的不认识！！",	
		"砌墙" : (:ask_qiqiang:),  
		"镐头" : (:ask_gaotou:),  
	]));
	carry_object(ARMOR_D("cloth"))->wear();
}
string ask_qiqiang()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎么进来这里的？";
	}
	if(me->query_temp(QUESTDIR2+"askqiqiang" ))
	{
	   command("say");
	   return "我真的....真的不是瞎说！";
	}
	command("look "+me->query("id"));
	message_vision(HIY"$N脸上露出恐惧的神色。\n", ob);
	command("say 老爷晚上见鬼，拎着镐头，要砌墙，怎么怪得我？");
	command("say 当年肯定是老爷亏心事做多了，又是杀害戚老头，又是陷害狄什么云。");
	command("fear");
	me->set_temp(QUESTDIR2+"askqiqiang",1);
	return "";
}
string ask_gaotou()
{
	command("look "+this_player()->query("id"));
	command("say 吴坎那里应该有吧。");
	return "";
}
void outwuguan(object me)
{
	object ob=this_object();
	object *inv;
	if(!me) return;
	command("?");
	message_vision(HIY"$N脸上露出疑惑的神色。\n", ob);
	command("say 你怎么进来这里的？");
	message_vision(HIR"只听见一声来人啊，$N被一阵棍棒给打晕了。\n"NOR, me);
	me->delete("enter_wuguan");
	inv = filter_array(deep_inventory(me), (: userp :));
	if( sizeof(inv))
		inv->move(environment(ob));
	me->unconcious();
	me->move("/d/xiangyang/damen");
	me->delete_temp("quest/busy");//
	me->delete_temp("quest/连城诀");
}
