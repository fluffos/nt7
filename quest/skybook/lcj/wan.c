//wanzhenshan.c 

inherit NPC;
#include <ansi.h>

int ask_liguan(); 
string ask_diyun();
string ask_qi();
#include "/d/suzhou/npc/lchj.h";

void create()
{
	set_name("万震山", ({ "wan zhenshan","wan","zhenshan", "guanzhu" }));
	set("title", "襄阳武馆馆主");
	set("nickname", "五云手");
	set("gender", "男性");
	set("age", 62);
	set("str", 30);
	set("dex", 26);
	set("long", "这人紫金脸庞，面带威严，威武有力，站在那里就象是一座铁塔。\n");
	set("combat_exp", 100000);
	set("shen_type", 1);
	set("attitude", "peaceful");
	set("unique", 1);
         
	set_skill("force", 90);
	set_skill("strike", 90);  
	set_skill("dodge", 90);
	set_skill("parry", 90);     
	set_skill("shenzhao-jing", 90);
	map_skill("force","shenzhao-jing");

	set("inquiry", ([
		"工作" : "呵呵，你去找我的大徒弟吧，他会安排你的!",
		"练功" : "东西练武场都可以练的，你去那儿练吧!",
		"离馆" : (:ask_liguan:),  
		"狄云" : (: ask_diyun:),	
		"戚长发" : (: ask_qi:),	
		"唐诗选辑" : "唐诗选辑？......我没听说过。",
		"连城诀" : "连城决？......我没听说过。",
		"连城剑法" : "什么连城剑法？我没听说过。",
		"言达平" : "他是我师弟。",
		"梅念笙" : "铁骨墨萼梅念笙老先生啊，正是我师傅。",
		"落花流水":"你说的可是南四奇！",
		"花铁干":"“中平枪花铁干”！",
		"刘乘风":"“柔云剑刘乘风”！",
		"陆天抒":"“仁义陆大刀”！",
		"水岱":"“冷月剑水岱”！",
	]));

	setup();
	carry_object(ARMOR_D("jinduan"))->wear();
}

int ask_liguan()
{
	object ob;
	object letter;
	
	ob = this_player();
	if(! ob->query("enter_wuguan")){
		command("say 你不是已经来打听过了么？");
		return 1;
	}
	if(ob ->query("combat_exp") >= 3000 && objectp(letter = new(__DIR__"obj/letter")) ) {
		command("nod "+ob->query("id"));
		command("say 这位" + RANK_D->query_respect(ob)+"可以出去闯荡江湖了，江湖险恶，可千万小心啊。去和我"+
			"四徒弟孙均去说一声吧，他会安排的。");
		            command("say 江湖险恶，若要防身，非有几件利器坚甲不可。");
            
            	command("say 老夫当年云游江南，曾与一位奇人相交甚好，你可前往寻访，求得冶铁煅造之术。");
            	command("say 如果你不解冶铁煅造之术，可以使用 help dazao 获得详细信息。");
                letter->move(ob);
                message_vision("$n给$N一封「"+letter->query("name")+"」。\n",ob,  this_object());        
                   command("say 我看你基础武功还不够扎实，就让我再指点你几招，你可要看仔细了。");
ob->set_skill("force", 32);
ob->set_skill("dodge", 32);
ob->set_skill("parry", 32);
ob->set_skill("cuff", 32);
ob->set_skill("strike", 32);
ob->set_skill("leg", 32);
ob->set_skill("finger", 32);
ob->set_skill("blade", 32);
ob->set_skill("sword", 32);
ob->set_skill("staff", 32);
ob->set_skill("hand", 32);
ob->set_skill("club", 32);
ob->set_skill("whip", 32);
ob->set_skill("stick", 32);
ob->set_skill("throwing", 32);
ob->set_skill("claw", 32);
ob->set_skill("yeqiu-quan", 10);
                ob->delete("enter_wuguan");
		ob->delete("wgjob");
		return 1;
	}
	else {
		command("pat "+ob->query("id"));
		command("say 这位" + RANK_D->query_respect(ob)+"的经验还太差，江湖太危险，你还是乖乖在武馆练功吧。");
		return 1;
	}
}
string ask_diyun()
{
	object me,ob;
	me = this_player();
	ob = this_object();
    if(me->query("combat_exp")<10000)
   {
    command("killair");
       return "你问这个干什么？";
}
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎么进来这里的？";
	}
	if(me->query_temp(QUESTDIR2+"askwan_diyun" ))
	{
	   command("hehe");
	   return "嘿嘿，现在狄云应该老死在监狱吧！";
	}
	message_vision(HIY"$N脸上露出警惕的神色。\n", ob);
	command("look "+me->query("id"));
	command("heng");
	command("say 恩，当年他师傅妄想刺杀我，而狄云更是和贱女桃红苟合，送他去监狱已经是优待他了。");
	command("haha");
	me->set_temp(QUESTDIR2+"askwan_diyun",1);
	if(me->query_temp(QUESTDIR2+"askwan_qi" ))
		tell_object(me,HIG"你总感觉这话中有问题。你更发现万震山似乎眼神神经兮兮的。\n"NOR);
	return "";
}
string ask_qi()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(!me->query(QUESTDIR1+"over") || !me->query_temp(QUESTDIR2+"start" ))
	{
	   call_out("outwuguan",1,me);
	   return "你怎么进来这里的？";
	}
	if(me->query_temp(QUESTDIR2+"askwan_qi" ))
	{
	   command("say");
	   return "嘿嘿，在哪里我也不知道......！";
	}
	command("look "+me->query("id"));
	command("haha");
	command("say 当年戚长发妄想刺杀我，幸亏我发现得及时。这些年，也不知道他哪里去了。");
	message_vision(HIY"$N脸上露出得意的神色。\n", ob);
	command("haha");
	me->set_temp(QUESTDIR2+"askwan_qi",1);
	if(me->query_temp(QUESTDIR2+"askwan_diyun" ))
		tell_object(me,HIG"你总感觉这话中有问题。你更发现万震山似乎眼神神经兮兮的。\n"NOR);
	return "";
}
void outwuguan(object me)
{
	object ob=this_object();
	object *inv;
        if(!me) return;
   if( me->query("combat_exp") <3000 ) return;
	command("?");
	message_vision(HIY"$N脸上露出疑惑的神色。\n", ob);
	command("say 你怎么进来这里的？");
	message_vision(HIR"只听见一声来人啊，$N被一阵棍棒给打晕了。\n"NOR, me);
	me->delete("enter_wuguan");
	inv = filter_array(deep_inventory(me), (: userp :));
	if( sizeof(inv))
		inv->move(environment(ob));
	me->unconcious();
if(me->query("combat_exp")>3000)         me->move("/d/xiangyang/damen");
	me->delete_temp("quest/busy");//
	me->delete_temp("quest/连城诀");
}
