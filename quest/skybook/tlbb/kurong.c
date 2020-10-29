//update by cool 98.2.18
//added by tangfeng 2004
inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"
#define QUESTDIR6 "quest/天龙八部/武功/"

string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();

int ask_xingyue(object who);
//string ask_liumai1();
string ask_liumai2();
int ask_dudan(object who);   

void create()
{
	object ob;
        set_name("枯荣长老", ({ "kurong zhanglao","kurong","zhanglao"}) );
        set("nickname", "天龙寺长老");
	set("long", 
" 枯荣长老面容奇特之极，左边的一半脸色红润，
皮光肉滑，有如婴儿，右边的一半却如枯骨，除了
一张焦黄的面皮之外全无肌肉，骨头突了出来，宛
然便是半个骷髅骨头。他在天龙寺中辈份最高，在
这里独参枯禅已数十年，天龙寺诸僧众，谁也没见
过他真面目。\n");
        set("gender", "男性" );
        set("class","bonze");   
        set("unique", 1);
        set("age", 99);
        set("str", 30);
        set("cor", 27);
        set("cps", 32);
        set("int", 35);
        set("per",23);

        set("max_jing",5000);
        set("eff_jingli", 6500);
        set("max_qi", 9500);
        set("jiali",100);
        set("neili",17000);
        set("max_neili",17000); 
        set("rank_info/respect", "高僧");
        create_family("天龙寺", 12, "僧侣");
        set("combat_exp", 4350000);
        set("score", 0);

        set("chat_chance_combat", 80);
        set("chat_msg_combat",({ 
                (: exert_function, "ku" :),
                (: perform_action, "finger.sanmai" :),
                (: perform_action, "finger.sandie" :),
        }));
        set_skill("parry", 340);
        set_skill("dodge", 340);
        set_skill("force", 360);
        set_skill("finger", 350);
        set_skill("whip", 320);
        set_skill("liumai-jianzhen",200);
        set_skill("cihang-bian", 320);
        set_skill("duanjia-jianfa", 300);
        set_skill("sword", 300);
        set_skill("strike", 340);
        set_skill("buddhism", 200);
        set_skill("literate", 200);
        set_skill("qiantian-yiyang", 220);
        set_skill("liumai-shenjian", 40);
        set_skill("kurong-changong", 360);
        set_skill("qingyan-zhang", 280);
        set_skill("yiyang-zhi", 340);
        set_skill("tianlong-xiang", 340);

        map_skill("whip", "cihang-bian");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "kurong-changong");
        map_skill("finger", "yiyang-zhi");
        map_skill("strike","kurong-changong");
        map_skill("force", "kurong-changong");
        prepare_skill("finger","yiyang-zhi"); 

        set_temp("apply/armor", 60);
        set_temp("apply/attack", 60);
        set_temp("apply/damage", 60);

        set("inquiry", ([
		"name": "贫僧就是枯荣",
		"菩提" : (: ask_xingyue :),
		"毒丹" : (: ask_dudan :),
		"普云洞" : (: ask_liumai2 :),
		//"段誉" : (: ask_liumai1 :),
            		"段誉" : (: askduanyu :),
		            "大理" : "这里便是大理。",
		            "天龙寺" : "这里正是天龙寺，大理段家武学的最高之地。",
		            "天龙有难" : (: tianlonghelp :),
		            "营救" : (: asksave :),
		            "搭救" : (: asksave :),
		            "萧峰" : "江湖人称南慕容、北萧峰，端得一条好汉。",
		            "营救段誉" : (: asksave :),
		            "营救萧峰" : (: askxiaofeng :),
		            "慕容复" : "江湖人称南慕容、北萧峰，听说慕容公子年级轻轻，却无所不精。",
		            "慕容博" : "我听说是，姑苏慕容不出的杰才，可惜英年早逝。",
		            "鸠摩智" : (: askjiumozhi :),
		            "六脉神剑" : "传说的我天龙寺最高绝学，需要极深内力才能运用。",
	]));

        set("env/一阳指", 3);
        setup();
        
        if (clonep(this_object())) {
		if (ob = carry_object("/clone/weapon/xingyue"))
		ob->wield(); 
	}
	carry_object("/d/tls/obj/jiasha")->wear();
	carry_object("/d/tls/obj/sengxie")->wear();
}

void reset()
{
	object ob;
	if (clonep() && (ob = unew(BINGQI_D("xingyue")))) {
		ob->move(this_object());
		command("wield xingyue puti");
        }
}

#include "kurong.h"

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
		  return "这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧。";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "鸠摩智妄为西域第一佛法高僧，所谓口生莲花，全是一派胡言。";
  }
  /*
  大轮明王鸠摩智是吐蕃国的护国法王，但只听说他具大智慧，精通佛法，每隔五年，开坛讲经说法，西域天竺各地的高僧大德，
  云集大雪山大轮寺，执经问难，研讨内典，闻法既毕，无不欢喜赞叹而去。
  */
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
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
		  return "乔峰，难不是你所迫出中原，今日所谓搭救不知何意！";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "听说那一战，"+me->query("name")+"更是威震武林，端得厉害啊。";
  }
  command("hoho");
	return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
}
string asksave()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start") &&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "小王子素来不喜武学，只爱佛法易经，平易近人，何来援救之说？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说，前段时间小王子和镇南王又是吵架一番，至今未有回家，不知"+RANK_D->query_respect(me) +"可否帮助打听一下。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "我佛慈悲。只是自从万劫谷回来，小王子精神恍惚，不知所中何毒还是受何种内伤。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。小王子自万劫谷回来，总是气血不定，内力怪异，才被送往我天龙寺求救来了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。竟然惹出鸠摩智这等高手，但愿王子吉人天相啊。";
  }
  command("hoho");
	return "小王子素来不喜武学，只爱佛法易经，平易近人，何来援救之说？";
}
string askduanyu()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "你问誉儿啊，他是镇南王正淳的公子，听说天资聪明，生性淳厚，只是素来不喜武学，只爱佛法易经。";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说，前段时间小王子和镇南王又是吵架一番，至今未有回家。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "我佛慈悲。多谢"+RANK_D->query_respect(me) +"搭救小王子。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。小王子自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救来了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。竟然惹出鸠摩智这等高手，但愿王子吉人天相啊。";
  }
  command("hoho");
	return "你问誉儿啊，他是镇南王正淳的公子，听说天资聪明，生性淳厚。";
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
  	  command("heng");
		  return "我佛慈悲。这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "我佛慈悲。多谢"+RANK_D->query_respect(me) +"化解这场天龙危机，还将我大理小王子得以解救。";
  }
  command("hoho");
	return "我佛慈悲。天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
}
/*
string ask_liumai1()
{
        object ob;
        ob=this_player();

	if( ob->query("dali/meet_dy1")||ob->query("liumai_update")){
		ob->set_temp("liumai/update",1);
		return "唉，求佛祖保佑,誉儿前日被大雪山大轮明王鸠摩智给抓走了，\n"+
			"誉儿生性淳厚，定能逢凶化吉。阿弥陀佛! \n";
	}
	else if( ob->query("dali/meet_dy2")){
		return "听说誉儿已经被人搭救回来了，真是万幸啊！阿弥陀佛！ \n";
	}
	return "你问誉儿啊，他是镇南王正淳的公子，听说天资聪明，生性淳厚。 \n";
}
*/