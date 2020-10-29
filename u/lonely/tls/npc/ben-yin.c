//cool@SJ,990605
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
void new_happen(object me);
string ask_kurong();

void create()
{
        set_name("本因大师", ({ "benyin dashi","benyin","dashi"}) );
        set("nickname", "天龙寺主持");
	set("long", "一位白须白眉的老僧，身穿一袭金丝木棉袈裟。\n"+
			"若以俗家辈份排列，本因大师应是当今大理国保定帝的俗家叔父。\n");
	set("gender", "男性" );
        set("attitude", "friendly");
        set("age", 69);
        set("str", 25);
        set("int", 26);
        set("con", 28);
        set("dex", 26);
	set("unique", 1);

	set("class", "bonze");
	set("shen", 10);
        set("jing", 2000);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 100);
        set("qi", 3000);
        set("max_qi", 3000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("combat_exp", 1350000);

        set_skill("qiantian-yiyang", 165);
        set_skill("tianlong-xiang", 165);
        set_skill("yiyang-zhi", 150);
        set_skill("duanjia-jianfa",170);
        set_skill("buddhism", 165);
        set_skill("literate", 120);
        set_skill("parry", 160);
        set_skill("finger", 165);
        set_skill("sword", 160);
        set_skill("dodge", 165);
        set_skill("kurong-changong", 100);
        set_skill("force", 160);
        set_skill("liumai-shenjian", 120);
        set_skill("medicine", 110);
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "yiyang-zhi");
        map_skill("sword", "duanjia-jianfa");
        map_skill("finger", "yiyang-zhi");
        prepare_skill("finger","yiyang-zhi");
        create_family("天龙寺", 13, "方丈");
	set("inquiry", ([
		"name": "贫僧就是本因",
		"龙树院" : "龙树院在雨花阁后面的松树林中",
		"枯荣" : "枯荣大师在龙树院参悟",
		"枯荣大师" : "枯荣大师在龙树院参悟",
		"松树林" : (: ask_kurong :),
		"龙树院" : (: ask_kurong :),
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
        ]) );
        set("chat_chance_combat", 30);
        set("chat_msg_combat",({
              (: perform_action, "finger.sandie" :),
        }));
        setup();
        carry_object(BINGQI_D("changjian"))->wield();
        carry_object("/d/tls/obj/nianzhu")->wear();
        carry_object("/d/tls/obj/jiasha")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();
}

string ask_kurong()
{
	object me,ob;
	mapping ob_fam,my_fam;
	ob=this_player();
	me=this_object();
	ob_fam = (mapping)ob->query("family");
	my_fam = (mapping)me->query("family");

	if ((ob_fam && ob_fam["family_name"] != "天龙寺")||ob->query("class") != "bonze")
		return ("对不起，你不能去打扰枯荣大师！\n");
	if (ob_fam["generation"] == (my_fam["generation"] + 1)){
		return ("松林很密，容易迷路，你一进林，向北走四步，向西走三步，再向北走一步，西走三步就到了 \n");
	} 
	else return ("你辈分不够，不能去拜见枯荣大师。 \n");
}

#include "ben.h";

void init()
{
	object me,obj1,obj2;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
	 	if(me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"kill_dizi"))
    {
    	command("look "+me->query("id"));
    	command("touch "+me->query("id"));
    	command("say 有这位"+RANK_D->query_respect(me) +"帮忙，本寺当可高枕无忧了。"); 
    }
	 	if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"caught") && !me->query(QUESTDIR2+"over"))
    {
    	command("sigh");
    	command("say 段王子被抓，这如何是好，我佛慈悲，但愿王子吉人天相啊。"); 
    }
	
	if(me->query(QUESTDIR2+"start") 
		&& !me->query_temp(QUESTDIR2+"caught_") 
		&& !me->query_temp(QUESTDIR2+"caught") 
		&& !me->query(QUESTDIR2+"over")
		&& me->query_temp(QUESTDIR2+"kill_dizi"))
    {
    	command("look "+me->query("id"));
    	command("touch "+me->query("id"));
    	command("say 多些这位"+RANK_D->query_respect(me) +"帮忙，本寺当可高枕无忧了。"); 
      tell_object(me,HIG"\n你走进大厅，却发现这里更是热闹非凡，场中两人正都在一起，那身受僧衣的怕就是鸠摩智了，另外一个竟然正是大理王子段誉，\n"
                          "武功之高，世上罕见。\n"NOR);
      if(!(obj1=present("duan yu",this_object()))||!(obj1=present("zhongnian nanzi",this_object())))
      {
  	     obj1=new("/d/dali/wuliang/npc/dy");
		 obj1->set_name("段誉", ({ "duan yu", "duan","yu"}) );
		 obj1->set("title",HIB"大理国镇南王世子"NOR);
		 obj1->set("long", "大理国镇南王之子。");	
  	     obj1->move(environment(me));
      }
      if(!(obj2=present("jiumo zhi",this_object())))
      {
  	     obj2=new("/kungfu/class/xueshan/jiumozhi");
  	     obj2->move(environment(me));
      }
      message_vision(HIC"只见斗室中剑气纵横，刀劲飞舞，便似有无数迅雷疾风相互冲撞激荡。鸠摩智只觉得段誉内劲越来越强，剑法也是变化莫测，\n"
                        "随时自创新意，与适才本因、本相等人的拘泥剑招大不相同，令人实难捉摸。他自不知段誉记不明白六路剑法中这许多繁复的\n"
                        "招式，不过危急中随指乱刺，那里是什么自创新招了？心下既惊且悔：“天龙寺中居然伏得有这样一个青年高手，今日当真是\n"
                        "自取其辱。”突然间嗤嗤嗤连砍三刀，叫道：“且住！” \n\n"NOR,me);   
         
      message_vision(HIM"\n段誉当即收招，只是你却发现他真气竟然不能随意收发，只将手指一抬向怀顶指去，$N不禁暗叫不好，抬眼望去鸠摩智似已有觉悟。\n\n"NOR,me);   
	  me->start_busy(1);
	  remove_call_out("new_happen");
	  me->set_temp(QUESTDIR2+"caught_",1);
      call_out("new_happen",6, me);
    }
	} 
}
void new_happen(object me)
{
  object obj1,obj2,ob;
  ob = this_object();
  if(!me) 
  {
	  command("?");
	  if((obj1=present("duan yu",environment(ob))))
		  destruct(obj1);
	  if((obj1=present("zhongnian nanzi",environment(ob))))
		  destruct(obj1);
	  if((obj1=present("jiumo zhi",environment(ob))))
		  destruct(obj1);
	  return;
  }
  if(environment(ob)!=environment(me)) 
  {
	  command("say 怎么关键时候，"+me->name()+"在何处？");
	  me->delete(QUESTDIR2+"start");
	  me->delete_temp("quest/天龙八部");
	  me->delete_temp("quest/busy");//任务冲突标志取消 
	  command("heng");
	  return;
  }
  
  if(!(obj1=present("duan yu",environment(ob)))&& !(obj1=present("zhongnian nanzi",environment(ob))))
  {
	  command("ah");
	  command("say 段誉呢？这么快，除了鸠摩智，谁将他抢走呢？");
	  me->delete(QUESTDIR2+"start");
	  me->delete_temp("quest/天龙八部");
	  me->delete_temp("quest/busy");//任务冲突标志取消 
	  command("?");
	  tell_object(me,HIR"段誉不知所踪，任务失败。\n"NOR);
	  if((obj2=present("jiumo zhi",environment(ob))))
	  {
		  message_vision(HIG"\n$N似乎也感到莫名其妙，转身离开了。\n"NOR,obj2);
		  destruct(obj2);
	  }
	  return;
  }
  
  if(!(obj2=present("jiumo zhi",environment(this_object()))))
  {
	  command("ah");
	  command("say 鸠摩智呢？竟然莫名其妙退走了？");
	  me->delete(QUESTDIR2+"start");
	  me->delete_temp("quest/天龙八部");
	  me->delete_temp("quest/busy");//任务冲突标志取消 
	  command("?");
	  tell_object(me,HIR"继续情节无法展开。\n"NOR);
	  if((obj1=present("duan yu",environment(ob))))
	  {
		  message_vision(HIG"\n$N高兴地跳了起来，转身离开了。\n"NOR,obj1);
		  destruct(obj1);
	  }
	  return;
  }
  
  if(me->query(QUESTDIR2+"start") 
	  && me->query_temp(QUESTDIR2+"caught_") 
	  && !me->query_temp(QUESTDIR2+"caught") 
	  && !me->query(QUESTDIR2+"over")
	  && me->query_temp(QUESTDIR2+"kill_dizi"))
  {
 
    message_vision(HIY"\n果然，鸠摩智见段誉脸有迷惘之色，收敛真气时手忙脚乱，全然不知所云，心念微动，便即纵身而上，挥拳向他脸上击去。他见鸠\n"
                        "摩智挥拳打到，便即毛手毛脚的伸臂去格。鸠摩智右掌翻过，已抓住了他胸口‘神封穴’。段誉立时全身酸软，动弹不得。鸠摩智\n"
                        "立即伸指又点他‘极泉’、‘大椎’、‘京门’数处大穴。鸠摩智倒退三步，说道：“这位小施主心中记得六脉神剑的图谱。原来\n"
                        "的图谱已被枯荣大师焚去，小施主便是活图谱，在慕容先生墓前将他活活的烧了，也是一样。”左掌扬处，向前急连砍出五刀，抓\n"
                        "住段誉退出了牟尼堂门外。\n\n"NOR,me);  
   	command("@@");
    message_vision(HIY"\n这生变化实在出乎意料之外，你虽已瞧出段誉武学之中隐伏有大大的破绽，却也决计料想不到，竟能如此轻而易举的手到擒来。等\n"
                        "鸠摩智拿人走人之时，已经来不及了。本因等纵前想要夺人，均被他这连环五刀封住，无法抢上。\n\n"NOR,me);  
   	command("wah");
    message_vision(HIC"\n鸠摩智长笑说道：“烧了死图谱，反得活图谱。慕容先生地下有人相伴，可不觉寂寞了！”右掌斜劈，喀喇喇一声响，将牟尼堂的\n"
                        "两根柱子劈倒，身形微幌，便如一溜轻烟般奔入林中，刹那间不知去向。你和本因双双抢出，见鸠摩智已然走远。却听内堂枯荣长\n"
                        "老道：“快追！”衣襟带风，一飘数丈。似是本参大师和他并肩齐行，向北追赶。 \n\n"NOR,me);
    me->set_temp(QUESTDIR2+"caught",1);
	destruct(obj1);
	destruct(obj2);
   	return;
  }
}
string askjiumozhi()
{
	object me;
	object *obj;
	int x;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "听说，大轮寺第一高僧鸠摩智将来我天龙寺佛法交流，真是我大理之幸啊。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query_temp(QUESTDIR2+"jiumozhi")&&!me->query(QUESTDIR2+"over"))
	{
      //增加时间和经验间隔限制
      //时间一天，经验500K
      if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
   	                 return "感谢"+RANK_D->query_respect(me) +"如此仗义。今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
      if(me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000)
  	                return "以"+RANK_D->query_respect(me) +"目前的经验就算目前有情况，也帮不上什么忙，还是抓紧练功吧！";
      //设定标志
	  tell_object(me,HIW"\n你素知大轮明王鸠摩智是吐蕃国的护国法王，但只听说他具大智慧，精通佛法，想来武功也是超高。只是这等\n"NOR);
  	  tell_object(me,HIW"明抢之事，确实不通情理。‘六脉神剑经’更是天龙寺镇寺之宝，这等上门要书的做法摆明就是欺负他人。\n"NOR);
  	  tell_object(me,HIC"你打定主意道：这等欺负人的行径，确是武林不齿，在下不才，也要管上一管。\n\n"NOR);
	  command("touch "+me->query("id"));
  	  obj = users();
	  x = sizeof(obj);
	  while(x--) {
		  if ( obj[x]->query_temp(QUESTDIR2+"jiumozhi") && obj[x]!=me) 
			  return "不过，有"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已经在帮我了，"+RANK_D->query_respect(me) +"还是抓紧练功吧！";		  
	  }
	  me->set(QUESTDIR+"time",time());
	  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));        

  	  me->set_temp(QUESTDIR2+"jiumozhi",1);
	  me->set_temp("quest/busy",1);//与任务系统冲突标志
	  log_file("quest/TLBB", sprintf("%s(%s) 开始天龙八部天龙寺救援篇。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return "这大轮明王也算是举世闻名的高僧了，怎能恁地不通情理，胆敢向本寺强要此经？只怕善意者不来，来者不善，\n"
		         "此事后果非小，我作不得主，请枯荣师叔出来主持大局。不过，这次有"+RANK_D->query_respect(me) +"相助，只怕是明王的失算了。\n"
		         "\n"NOR+HIG+me->name()+"点头道：有枯荣师叔出来主持大局最好。我且先到天龙寺门口一看。"NOR;
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "多谢"+RANK_D->query_respect(me) +"相助。只是这魔僧妄为吐蕃国第一佛法高僧。";
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
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
                  return "萧峰，难不是你所迫出中原，今日所谓搭救不知何意！";
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
		  return "我佛慈悲。小王子自万劫谷回来，总是气血不定，才被送往我天龙寺枯荣长老那里求救来了。";
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
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   return "天龙寺和中原官府应该没有半点关系，"+RANK_D->query_respect(me) +"还是自我小心通缉！";
	}
  if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("sigh");
	  tell_object(me,HIY"只见本因方丈从怀中取出一封金光灿烂的信笺，递在你手中。你接了过来，着手重甸甸地，但见这信奇异之极。\n"NOR);
  	  tell_object(me,HIY"你识得写的是：“书呈崇圣寺住侍”，从金套中抽出信笺，也是一张极薄的金笺，上用梵文书写，大意说：“\n"NOR);
  	  tell_object(me,HIG"当年与姑苏慕容博先生相会，订交结友，谈论当世武功。慕容先生言下对贵寺‘六脉神剑’备致推崇，深以未\n"NOR);
  	  tell_object(me,HIG"得拜观为憾。近闻慕容先生仙逝，哀痛无已，为报知己，拟向贵寺讨求该经，焚化于慕容先生墓前，日内来取，\n"NOR);
  	  tell_object(me,HIG"勿却为幸。贫僧自当以贵重礼物还报，未敢空手妄取也。”信末署名‘大雪山大轮寺释子鸠摩智合十百拜’。\n"NOR);
  	  command("heng");

  	  command("look "+me->query("id"));
  	  if(me->query("combat_exp")<3000000)		  return ""+RANK_D->query_respect(me) +"好意心领了，只是只怕那鸠摩智武功高强，你也无法帮忙多少。";
  	  if(me->query("shen")<0)		  return ""+RANK_D->query_respect(me) +"好意心领了，只是......。";

  	  me->set(QUESTDIR2+"start",1);
	  return "如果能有"+RANK_D->query_respect(me) +"帮忙，只怕我天龙寺这次当高枕无忧了。";
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
