// cool 980310
// duan1.c
// Modify By River 98/11
//COOL@SJ,990828
// tangfeng@SJ 2004

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"
#define QUESTDIR6 "quest/天龙八部/武功/"

string ask_join();
string ask_duan();
string strike();
string fenglu();
string ask_save();
string tianlonghelp();
string askxiaofeng();
string askjiumozhi();

void create()
{
	set_name("段正淳", ({ "duan zhengchun", "duan", "master" }) );
	set("title", "镇南王");
	set("nickname","风流王爷");
	set("gender", "男性" );
	set("age", 44);
	set("str", 22);
	set("con", 23);
	set("dex", 23);
	set("int", 25);
	set("per", 28);
	set("attitude", "friendly");


	set("max_qi", 3000);
	set("max_jing", 1800);
	set("eff_jingli", 1800);
	set("neili", 3000);
	set("qi", 3000);
	set("jingli", 1800);
	set("max_neili", 3000);
	set("jiali", 50);

	set("rank_info/respect", "风流王爷");
	create_family("天龙寺", 13, "俗家弟子");

	set("long",
	"段正淳是个相当高大的中年儒生，若不是跟随在他左右的铁甲卫士成群，\n"
	"你大概猜不到眼前这个温文儒雅的中年人竟是大理王爷。\n");

	set("combat_exp", 1100000);
	set("score", 50000);

	set("chat_chance_combat", 30);
	set("chat_msg_combat",({
		(: perform_action, "sword.fenglei" :),
		(: exert_function, "qi" :)
	}));

	set_skill("parry", 150);
	set_skill("dodge", 150);
	set_skill("force", 150);
	set_skill("cuff", 150);
	set_skill("literate", 120);
	set_skill("sword", 160);
	set_skill("duanjia-jianfa", 160);
	set_skill("strike", 150);
	set_skill("qingyan-zhang", 150);
	set_skill("qiantian-yiyang", 150);
	set_skill("duanjia-quan", 150);
	set_skill("tianlong-xiang", 150);
	set_skill("finger", 150);
	set_skill("yiyang-zhi", 160);
	set_skill("buddhism", 100);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "qingyan-zhang");
	map_skill("sword", "duanjia-jianfa");
	map_skill("cuff", "duanjia-quan");
	map_skill("force", "qiantian-yiyang");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger", "yiyang-zhi");
	prepare_skill("strike","qingyan-zhang");
	prepare_skill("cuff","duanjia-quan");

	set("inquiry", ([
		"段誉" : (: ask_duan :),
		"name": "你问这干嘛，我就是段正淳，难道你又是我情人生的孩子？",
		"here": "这里便是镇南王府。",
		"天龙寺" : "天龙寺是我段家武学的最高之地，不过，想拜天龙寺可不是那么容易的.",
		"拜天龙" : (: ask_join :),
		"拜天龙寺" : (: ask_join :),
		"掌法诀要" : (: strike :),
		"练掌法" : (: strike :),
	//	"俸禄" :  (: fenglu :),
		"营救" : (: ask_save :),
		"解救" : (: ask_save :),
		"援救" : (: ask_save :),
		"救援" : (: ask_save :),
		"save" : (: ask_save :),
		"搭救" : (: ask_save :),		
		"大理" : "这里便是大理。",
		"天龙寺" : "天龙寺是我段家武学的最高之地，不过，想拜天龙寺可不是那么容易的.",
		"天龙有难" : (: tianlonghelp :),
		"萧峰" : "江湖人称南慕容、北萧峰，端得一条好汉。",
		"营救段誉" : (: ask_save :),
		"救援段誉" : (: ask_save :),
		"援救段誉" : (: ask_save :),
		"救援萧峰" : (: askxiaofeng :),
		"援救萧峰" : (: askxiaofeng :),
		"解救萧峰" : (: askxiaofeng :),
		"营救萧峰" : (: askxiaofeng :),
		"慕容复" : "江湖人称南慕容、北萧峰，听说慕容公子年级轻轻，却无所不精。",
		"慕容博" : "姑苏慕容不出的杰才，可惜英年早逝。",
		"鸠摩智" : (: askjiumozhi :),
         "六脉神剑" : "传说的我天龙寺最高绝学，我也未能得见。",          
	]));

	setup();
	carry_object("/d/dali/npc/obj/huangpao")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}
void init()
{
	object ob,me;
	ob =this_object();
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
		if(this_player()->query("quest/dali"))
		{
			tell_object(me,HIY"\n鉴于新Quest，系统自动转换标志搜索：\n"NOR);
			if(this_player()->query("quest/dali/fail"))
			{
				this_player()->set(QUESTDIR6+"fail",this_player()->query("quest/dali/fail"));
				tell_object(me,HIY"原有"+chinese_number(this_player()->query("quest/dali/fail"))+"次失败纪录转换成功！\n"NOR); 
				this_player()->delete("quest/dali/fail");
			}
			if(this_player()->query("quest/dali/time"))
			{
				this_player()->set(QUESTDIR+"time",this_player()->query("quest/dali/time"));
				tell_object(me,HIY"上次解密时间标志转换成功！\n"NOR);  
				this_player()->delete("quest/dali/time");
			}
			if(this_player()->query("quest/dali/shanlu"))
			{
				this_player()->set(QUESTDIR1+"pass_shanlu",1);
				tell_object(me,HIY"成功通过荆棘林标志转换成功！\n"NOR);  
				this_player()->delete("quest/dali/shanlu");
			}
			if(this_player()->query("quest/dali/yuxiang"))
			{
				this_player()->set(QUESTDIR6+"yuxiang",1);
				tell_object(me,HIY"磕头玉像标志转换成功！\n"NOR);
				this_player()->delete("quest/dali/yuxiang");
			}
			if(this_player()->query("quest/dali/pass"))
			{
				this_player()->set(QUESTDIR6+"pass",1);
				this_player()->set(QUESTDIR6+"yuxiang",1);
				tell_object(me,HIY"凌波微步标志转换成功！\n\n"NOR);
				this_player()->delete("quest/dali/pass");
			}
			this_player()->delete("quest/dali");
			tell_object(me,HIY"\n新旧系统自动转换结束！\n\n"NOR);
		}
		if(this_player()->query(QUESTDIR6+"pass") && !this_player()->query(QUESTDIR1+"wuliangover"))
					this_player()->set(QUESTDIR6+"yuxiang",1);
		if(me->query(QUESTDIR1+"over"))
			command("thank "+me->query("id"));
		if(!me->query_condition("killer")&& me->query_temp(QUESTDIR1+"see_duanyu1")&&!me->query(QUESTDIR1+"wuliangover"))
		{
			command("look "+me->query("id"));
			tell_object(me,HIY"\n你上前告诉"+ob->name()+"，说在无量山发现段誉，大可放心！\n"NOR);
			command("oh");
			command("jump "+me->query("id"));
			message_vision(HIC"$n向$N表示真诚的感谢。\n", me, this_object());
			command("touch "+me->query("id"));
			command("say 那我也完全放心了，想来这几天犬子就会回来的。"); 
			me->delete_temp("quest/busy");//任务系统冲突标志
			me->delete_temp("quest/天龙八部");   
			me->set(QUESTDIR1+"wuliangover",1);   
			//设定标志
			me->set(QUESTDIR+"time",time());
			me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		}
	} 
}

string ask_duan()
{
	object me;
	object *obj;
	int x;
	me = this_player();
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
           return "小儿和中原官府应该没有半点关系，"+RANK_D->query_respect(me) +"还是自我小心通缉！";
	}
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  { 
      message_vision(HIC"$N脸上露出气愤的神色。\n", this_object());
  	  command("heng");
	  obj = users();
	  x = sizeof(obj);
	  while(x--) {
		  if ( (obj[x]->query_temp(QUESTDIR1+"jianying")
                          ||obj[x]->query_temp(QUESTDIR1+"start"))
			  && obj[x]!=me) 
			  return "不过，"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已经在帮我了，"+RANK_D->query_respect(me) +"不用那么着急！";		  
	  }
  	  //设定标志
  	  me->set(QUESTDIR+"time",time());
  	  me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
  	  me->set(QUESTDIR1+"start",1);
      me->set_temp(QUESTDIR1+"start",1);
	  me->set_temp("quest/busy",1);//与任务系统冲突标志
	  log_file("quest/TLBB", sprintf("%s(%s) 开始天龙八部第一部分。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return "小儿不爱学武，和我吵了几句就离家出走了，唉......家门不幸啊！";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
	  message_vision(HIC"$N脸上露出气愤的神色。\n", this_object());
  	  command("sigh");
  	  command("shrug "+me->query("id"));
	  return "前段时间有人说在无量山附近看到小儿，不知道现在身在何处。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
 
  	  command("sigh");
  	  message_vision(HIC"$N脸上露出担心的神色。\n", this_object());
  	  //时间一天
  	  if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
	  {
		  if(random(2)) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
		  else return "誉儿这几天就可能回来了，"+RANK_D->query_respect(me) +"先行休息去吧！";
	  }
	  me->set_temp(QUESTDIR1+"2_start",1);
	  return "小儿日前被四大恶人的南海鳄神掳走了，我们正在设法营救他，有来报目前就在无量山附近的一座石屋内。";
	}
	if (me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"2_start") && !me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  message_vision(HIC"$N脸上露出担心的神色。\n", this_object());
  	  command("shrug "+me->query("id"));
	  return "刚有探报，小儿确实就在无量山附近的一座石屋内，不得已只怕要走一次了。";
  }
  if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("look "+me->query("id"));
  	  command("nod "+me->query("id"));
  	  message_vision(HIC"$n向$N表示真诚的感谢。\n", me, this_object());
	  return "刚有探报，小儿确实就在无量山附近的一座石屋内，不过，有"+RANK_D->query_respect(me) +"相助，料无大碍。";
  }
  if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
  	  message_vision(HIC"$n向$N表示真诚的感谢。\n", me, this_object());
	  return "多谢"+RANK_D->query_respect(me) +"搭救小儿，只是这万劫谷之后，身体一直不调，才被送往天龙寺求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小儿自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "竟然惹出鸠摩智这等高手，但愿小儿吉人天相啊。";
  }
  command("nod "+me->query("id"));
	return "段誉正是犬子，不知道找他何事。";
}

string ask_save()
{
	object me;
	object *obj;
	int i,j,x;
	i=random(5)+2;
	j=random(4)+3;
	me=this_player();

  if(!me->query(QUESTDIR1+"start" ))
  {
  	  command("?");
  		return "小儿向来只爱佛法已经，平易近人，援救之说何来之说？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("shrug "+me->query("id"));
		  return "前段时间有人说在无量山附近看到小儿，这等贪玩，就让他去吧。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"wuliangover")&& !me->query_temp(QUESTDIR1+"2_start")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
		  return "小儿最近收了个莫名其妙的弟子，好像叫什么南海鳄鱼？我总是担心啊，千万不要出什么乱子。";
  }
	if (me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"2_start") && !me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
		if ( me->query("shen") < 0)
		           return ("我看" + RANK_D->query_respect(me) +"面带阴邪之气，恐怕是四大恶人一伙的奸细。");
    	if ( me->query("combat_exp") < 1500000)
		           return ("四大恶人都是绝顶高手,"+RANK_D->query_respect(me) +"似乎武功不够，和四大恶人相斗会有性命之忧。");
  		me->set_temp(QUESTDIR1+"step",i);
	  	me->set_temp(QUESTDIR1+"steps",j);
  	  command("look "+me->query("id"));
   	  //增加时间和经验间隔限制
  	  //时间一天
  	  if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
	  {
		  if(random(2)) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
		  else return "誉儿被那四大恶人擒走，这件事还需从长计议，"+RANK_D->query_respect(me) +"千万不得鲁莽。";
	  }
	  //考虑很多限制，这里经验差距变得少一点
	  if(me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<100000)
		  return "以"+RANK_D->query_respect(me) +"目前的经验就算目前有情况，也帮不上什么忙，还是抓紧练功吧！";

	  obj = users();
	  x = sizeof(obj);
	  while(x--) {
		  if ( obj[x]->query_temp(QUESTDIR1+"yingjiu")&& obj[x]!=me) 
			  return ""+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已经在帮我了，"+RANK_D->query_respect(me) +"还是抓紧练功吧！";		  
	  }

  	  //设定标志
  	  me->set(QUESTDIR+"time",time());
  	  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
  	  command("touch "+me->query("id"));
  	  me->set_temp(QUESTDIR1+"yingjiu",1);
	  me->set_temp("quest/busy",1);//与任务系统冲突标志
	  log_file("quest/TLBB", sprintf("%s(%s) 开始准备营救段誉（第一章）。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return ("既然"+ RANK_D->query_respect(me) +"有意相助，定会如虎添翼。居我得知，誉儿被四大恶人之首\n"+
			"段延庆囚在正在无量山附近的一座石屋内，只是路上十分险恶，之前为了探明路线，\n"+
			"我已损失好几名手下。你先去大理北面去无量山路上的一个小溪那里，向北行五里，\n"+
			"再向西行"+chinese_number(j)+"里，再向北行"+chinese_number(i)+"里，然后会到一座高山，再往后就要见机行事了。\n\n"+
			"段正淳说道：好了，准备一下，为了不惊动对方，切记要在晚上行动，路上小心。");
  }
  if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("look "+me->query("id"));
  	  command("touch "+me->query("id"));
                  return "有"+RANK_D->query_respect(me) +"相助，料无大碍。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多谢"+RANK_D->query_respect(me) +"搭救小儿，只是这万劫谷之后，身体一直不调，才被送往天龙寺求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "小儿自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
  	  command("look "+me->query("id"));
		  return "竟然惹出鸠摩智这等高手，但愿小儿吉人天相啊。";
  }
  command("nod "+me->query("id"));
	return "小儿向来只爱佛法已经，平易近人，援救之说何来之说？";
}
string askjiumozhi()
{
	object me;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "听说，大轮寺第一高僧鸠摩智将来我天龙寺佛法交流，真是我大理之幸啊。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧，所谓口生莲花，全是一派胡言。";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "鸠摩智妄为西域第一佛法高僧，所谓口生莲花，全是一派胡言。";
  }
   command("nod");
	return "大轮明王鸠摩智是吐蕃国的护国法王，但听说他具大智慧，精通佛法，想来武功也是惊人。";
}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("hoho");
  		return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是涉及到大辽与大宋之争，实在不好插手。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
                  return "萧峰，难不是你所迫出中原，今日所谓搭救不知何意。";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是涉及到大辽与大宋之争，实在不好插手。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "萧峰乃小儿之义兄，自然要救。这位"+RANK_D->query_respect(me) +"可先行一步，大理段家弟子随后援到。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "这一战真是痛快，"+me->query("name")+"更是威震武林，端得厉害啊。";
  }
	return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
}
string tianlonghelp()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"over"))
  {
  	  command("haha");
  		return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
  }
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "听说，大轮寺高僧鸠摩智不日将来我天龙寺，不知是喜是祸。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
	  return "多谢"+RANK_D->query_respect(me) +"化解这场天龙危机，还将我侄子得以解救。";
  }
  command("hoho");
	return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
}
string strike()
{
	mapping fam = this_player()->query("family");
	object ob;
	if(!fam || fam["family_name"] != "天龙寺")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
	if(this_player()->query_skill("strike",1) > 30)
		return "你的掌法已经有一定基础了，这本书对你没什么用，还是留给别的弟子吧";
	ob = unew("/d/dali/obj/book-strike");
	if(!clonep(ob))
		return "你来晚了，本派的「掌法诀要」不在此处。";
	if(clonep(ob) && ob->violate_unique()){
		destruct(ob);
		return "你来晚了，本派的「掌法诀要」不在此处。";
	}
	ob->move(this_player());
	return "好吧，这本「掌法诀要」你拿回去好好钻研。";
}

string ask_join()
{
	object me;
	object ob;
	ob=this_player();
	me=this_object();
	if (ob->query("tls"))
		return "你已经是天龙寺出家弟子了，何故还要问此事？";

//	if (ob->query("combat_exp") > 100000)
//		return "大理段氏在大理还需要你这样的人才，就不要去天龙寺出家吧。";

	if(ob->query_temp("tls_app"))
		return "我不是已经推荐你去天龙寺了吗？怎么还不去啊？";

	if((string)ob->query("gender") == "女性" )
		return "天龙寺武功需要纯阳之体，小姑娘可不收啊! ";

	if((int)ob->query_skill("qiantian-yiyang",1) < 120  )
		return RANK_D->query_respect(ob) +"，你乾天一阳功太差,不能学习高等级的功夫!";

	if ( ob->query("job_time/大理") + ob->query("job_time/送信")  < 50)
		return "我看你为镇南王府做事做的还不够啊，努力做吧！";

	if ( ob->query_int() < 30 )
		return "天龙寺武学深奥，我看你的悟性似乎不够，恐怕无法领会这么高的功夫!";

	if( ob->query("marry"))
		return "你都已经结婚了，要去出家，叫你夫人怎么办？";

	ob->set_temp("tls_app",1);
	command ("say 哈哈！好样的！这位兄弟既然为我大理段氏做了这么多事,今天就推荐你去天龙寺！");
	return "我即刻修书一封，快马送到天龙寺了惑禅师那里，你速速赶去吧!";
}

string fenglu()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	int gold = 0, fenglu;

	if (!fam || fam["family_name"] != "天龙寺")
		return "这位"+ RANK_D->query_respect(ob) +"不是我大理国的臣民，难道也想来拿大理的俸禄？";

	if( ob->query("tls"))
		return "这位"+ RANK_D->query_respect(ob) +"已经出家了，还要这俸禄做甚？";

	switch (fam["generation"]) {
		case 13:
			gold += 500;
		case 14:
			gold += 800;
			break;
		default:
			return "这位"+ RANK_D->query_respect(ob) +"在大理时间还太短，等过段时间才来拿吧。";
	}
	fenglu = ob->query("age") * 12 + ob->query("month");
	if (ob->query("fenglu") >= fenglu)
		return "这位"+RANK_D->query_respect(ob) +"本月不是已经拿过俸禄了，怎么还想来拿？";
	gold *= ob->query_skill("qiantian-yiyang", 1);
        if (ob->query_skill("force", 1) < 216)  return "你这个月没有俸禄。";
	ob->set("fenglu", fenglu);
	command ("pat " + ob->query("id"));
	message_vision("$N给了$n"+MONEY_D->money_str(gold)+"。\n", this_object(), ob);
	MONEY_D->pay_player(ob, gold);
	return "这是你本月的俸禄，这位"+ RANK_D->query_respect(ob) +"好好干啊！";
}

void attempt_apprentice(object ob)
{
	object me=this_object();
	mapping fam = ob->query("family");
	if( (string)ob->query("gender") == "女性" ){
		command ("say 我天龙寺武功需要纯阳之体，小姑娘我可不收啊!");
		return;
	}
	if (ob->query("tls")){
		command ("say 你已经是天龙寺出家弟子了，我不能再收你了！\n");
		return;
	}
	if( (int)ob->query_skill("qiantian-yiyang",1) < 80  ){
		command ("hmm");
		command ("say 你乾天一阳功如此之差，我可不收你?");
		return;
	}
	if(ob->query_int() < 30){
		command("say 学一阳指之人必须悟性奇高，依我看" + RANK_D->query_respect(ob) + "的资质似乎不够？");
		return;
	}
	if(fam["master_name"] == "段正明"){
		command("haha");
		command("say "+RANK_D->query_respect(ob)+"已是兄长身前的侍卫，"+RANK_D->query_self(me)+"怎能再收你为徒？");
		return;
	}
	command("smile");
	command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
	command("recruit " + ob->query("id") );
	if (!ob->query("qinwang")) {
		this_object()->set("title",HIC "大理国镇南王府家将" NOR);}
	else
		{
		this_object()->set("title", HIW "大理国"+ ob->query("qinwang")+NOR);}
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	 ob->set("class", "officer");
}
