//qi.c 戚芳 by river

inherit NPC;

#include <ansi.h>
int ask_xuexi4();
string ask_diyun();
string ask_tangshi();
string ask_xieyang();
void outwuguan(object me);
#include "/d/suzhou/npc/lchj.h";

void create()
{
	set_name("戚芳", ({ "qi fang","qi","fang", "woman" }));        
	set("gender", "女性");
	set("age", 21); 
	set("long", "圆圆的脸蛋，一双大眼黑溜溜的。\n");
	set("combat_exp", 3000);
	set("shen_type", 1);
	set("attitude", "friendly");        

	set_skill("force", 30);
	set_skill("strike", 30);
	set_skill("sword", 30);
	set_skill("shenzhao-jing",30);
	map_skill("force", "shenzhao-jing");         
 
	set("inquiry", ([
		"万圭" : "他是我的夫君啊。",
		"学习" : (: ask_xuexi4 :),
		"狄云" : (: ask_diyun:),	
		"唐诗选辑" : (: ask_tangshi:),	
		"鞋样" : (: ask_xieyang:),	

		"连城诀" : "连城决？......我没听说过。",
		"连城剑法" : "什么连城剑法？我只学过躺尸剑法。",
		"万震山" : "他是我师伯。",
		"言达平" : "他是我师伯。",
		"戚长发" : "他是我爹爹。",
		"梅念笙" : "铁骨墨萼梅念笙老先生啊。",
		"落花流水":"你说的可是南四奇！",
		"花铁干":"“中平枪花铁干”！",
		"刘乘风":"“柔云剑刘乘风”！",
		"陆天抒":"“仁义陆大刀”！",
		"水岱":"“冷月剑水岱”！",
	]));

	setup();
	carry_object(ARMOR_D("cloth"))->wear();
	add_money("silver", 3);
}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if ( ob ->query_temp("jobask") == 4) {
		command("wanfu "+ob->query("id"));
		command("say 这位" + RANK_D->query_respect(ob) +",你可以 "HIY HBCYN"ask qi about 学习"CYN" 来向我了解聊天的情况。"NOR);
	}
}                               

int ask_xuexi4()
{
	object ob = this_player();
	if(ob->query_temp("jobask") == 4) {
		command("say  这位" + RANK_D->query_respect(ob) +"来武馆多久啦？在这儿练功之余可和别人闲聊 "HIY HBCYN"chat"CYN"\n"+
			"来交流交流感情。还可以散布些谣言 "HIY HBCYN" rumor"CYN" ,同一门派的还可以用 "HIY HBCYN" party"CYN"。\n"+
			"闲聊和散布谣言时可用些已经有的动作。你可以试试 "HIY HBCYN"chat* hi"CYN" 。用 "HIY HBCYN"semote"CYN"\n"+
			"可以查出哪些是已有了的动作。若你话太多惹人厌就会被人投票关闭交谈频\n"+
			"道 "HIY HBCYN"vote chblk xxx"CYN" 。频道被关了后只有等别人投票打开 "HIY HBCYN"vote unchblk\n"+
			"xxx"CYN" 。如果你想找人聊天而不想让其他人听到，你可以告诉 "HIY HBCYN"tell"CYN" 他(她)。有\n"+
			"人告诉你什么事，你可以用 "HIY HBCYN"reply"CYN" 来回答他（她）。你还可以跟某一位与你\n"+
			"在同一房间的人讲悄悄话 "HIY HBCYN"whisper"CYN" 。江湖上不少人沉迷在武功之中，喜欢打\n"+
			"打杀杀的，然而我觉得还是闲聊交友更有趣。你好自为之吧。"NOR);
		ob->delete_temp("jobask");
		if(ob->query_temp("jobover") != 4) {
			ob->set_temp("jobover", 4);
			command("say 听说我师兄还有点事情找你，你最好去看一下。"NOR);
			if ( ob->query("combat_exp") < 400 ) {
				ob->add("potential", 20);
				ob->add("combat_exp", 100);
				tell_object(ob,HIW"你听了戚芳的讲解，增加了一百点实战经验和二十点潜能，对江湖又多了一分了解。\n"NOR);
			}
		}
		return 1;
	}
	if ( ob->query_temp("jobover") == 4) {
		command("say 我不是都和你说了么，我师兄有事找你，快去看下吧。");
		return 1;
	}
}
string ask_diyun()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎么进来这里的？";
	}
	if(!me->query_temp(QUESTDIR2+"waqiang" ))
	   return "也不知道狄云现在怎么样啊！";
	if(me->query_temp(QUESTDIR2+"askqi" ))
	{
	   command("sigh");
	   command("say");
	   return "也不知道狄云现在怎么样啊！";
	}
	command("say");
	message_vision(HIY"$N脸上露出怀念的神色。\n", ob);
	command("look "+me->query("id"));
	command("say 恩，当年的事情发生的确太突然了，其实我也觉得狄云不象那种人。");
	command("sigh");
	command("say 也不知道现在狄云怎么样了。");
	me->set_temp(QUESTDIR2+"askqi_diyun",1);
	return "";
}
string ask_tangshi()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎么进来这里的？";
	}
	if(!me->query_temp(QUESTDIR2+"askqi_diyun" ))
	{
	   command("doubt");
	   return "你说什么唐诗选辑？";
	}
	if(me->query_temp(QUESTDIR2+"asktangshi" ))
	{
	   command("say");
	   return "好像在.....！真的忘记了！";
	}
	if(me->query_temp(QUESTDIR2+"askxieyang" ))
	{
	   command("say");
	   return "好像在书房！";
	}
	command("consider");
	message_vision(HIY"$N仔细在脑海里搜索“唐诗选辑”。\n", ob);
	command("look "+me->query("id"));
	command("say 恩，好像有这么个名字。可是我有点忘记在哪里了。");
	me->set_temp(QUESTDIR2+"asktangshi",1);
	return "";
}

string ask_xieyang()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎么进来这里的？";
	}
	if(!me->query_temp(QUESTDIR2+"asktangshi" ))
	{
	   command("doubt");
	   return "你说什么鞋样？";
	}
	if(me->query_temp(QUESTDIR2+"askxieyang" ))
	{
	   command("say");
	   return "好像在书房！";
	}
	command("en");
	message_vision(HIY"$N慢慢在脑海里搜索“唐诗选辑”、“鞋样”，突然似乎想了起来。\n", ob);
	command("look "+me->query("id"));
	command("say 恩，好像有这么个名字。我记得给狄云用来做过鞋样的。");
	command("say 我好像顺手隔在书房里。只是也不知道现在狄云怎么样了。");
	me->set_temp(QUESTDIR2+"askxieyang",1);
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
