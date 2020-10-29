// duanyu.c 段誉
// COOL@SJ,990827
// Modified by tangfeng 2004
// 这里的段誉涉及到三个场景，一个在无量玉像，一个在石屋里，一个在大伦寺暗室里
// By Spiderii@ty 加入时间限制
inherit F_MASTER;
#include <ansi.h>
inherit NPC;

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"
#define QUESTDIR6 "quest/天龙八部/武功/"

string tianlonghelp();
string askxiaofeng();
string askjiumozhi();
string ask_name();
int ask_home();
int ask_save();
void outroom(object me);
void dest(object me,object ob);
void greeting(object me);

void create()
{
        set_name("青年男子", ({"qingnian nanzi", "nanzi", "man"}));
        set("gender", "男性");
        set("age", 20);
        set("long", "这是一个青年男子，披头散发，赤裸着上身，下身只系着一条短裤，露出\n"
                    "了两条大腿，脸孔略尖，眼神似乎有些发狂。\n");
        set("attitude", "peaceful");
        set("str", 15);
        set("per", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("no_quest", 1);

        set("inquiry", ([
		"段誉" : (: ask_name :),
		"name" : (: ask_name :),
		"获救" : (: ask_save :),
		"救你" : (: ask_save :),
		"救段誉" : (: ask_save :),
		"救你们" : (: ask_save :),
		"搭救" : (: ask_save :),
		"解救" : (: ask_save :),
		"save" : (: ask_save :),
		"段延庆" : "就是他把我关进来的。\n",
		"拜师" : "嗯....，我的师傅是老子、孔子和庄子，他们的学问我还没学全呢。\n",
		"大理" : "大理是我家，我家在大理。",
		"天龙寺" : "天龙寺是大理段家武学的最高之地。",
		"天龙有难" : (: tianlonghelp :),
		"萧峰" : "我大哥萧峰啊，端得一条好汉。",
		"营救萧峰" : (: askxiaofeng :),
		"慕容复" : "慕容公子确是其江南文采，诗琴书画无所不精，武功更是冠绝天下。",
		"慕容博" : "我听说是，姑苏慕容不出的杰才，可惜英年早逝。",
		"鸠摩智" : (: askjiumozhi :),
		"六脉神剑" : "天龙寺最高绝学。",
		"段正淳" : "那是我爹爹。",
		"刀白凤" : "你找我妈妈有什么事情？",
		"段正明" : "你找我伯父有什么事情？",
		"虚竹" : "你找我三弟有什么事情？",

		"回家" : (: ask_home :),
		"go home" : (: ask_home :),

		//六脉神剑的quest好像有人做了一半，在枯荣长老身上有部分描述
        ]));

        set("jing", 10000);
        set("max_jing", 10000);
        set("jingli", 10000);
        set("eff_jingli", 10000);
        set("qi", 50000);
        set("max_qi", 20000);
        set("neili", 60000);
        set("max_neili", 40000);
        set("jiali",500);
        
        set("combat_exp", 15000000);
        set_skill("buddhism", 250);            
        set_skill("daode-jing", 250);                   
        set_skill("literate", 300);                
        set_skill("force", 600);                
        set_skill("beiming-shengong", 600);     
        set_skill("dodge", 600);                
        set_skill("lingbo-weibu", 600);         
        set_skill("parry", 300);
        set_skill("finger", 300);
        set_skill("yiyang-zhi", 200);
        set_skill("liumai-shenjian", 200);
        map_skill("parry", "yiyang-zhi");
        map_skill("finger", "yiyang-zhi");
        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
        setup();        
}
void init()
{
	object me;
	me = this_player();
	::init();
	if (interactive(me) && living(me) 
		&& !me->query_condition("killer")
		&& me->query(QUESTDIR1+"start") ) {
		me->start_busy(2);
        remove_call_out("greeting"); 
		call_out("greeting",2,me);
	} 
}
void greeting(object me)
{
	if(!me) return;
	if(environment(this_object())!=environment(me)) return;

	if(!me->query_condition("killer")&&me->query(QUESTDIR1+"start") 
			&& !me->query_temp(QUESTDIR1+"see_duanyu1")
			&& !me->query_temp(QUESTDIR1+"see_duanyu2")
			&& !me->query(QUESTDIR1+"wuliangover")
			&& me->query_temp(QUESTDIR1+"jianying"))
    {
		//玉像处
		  message_vision(HIC"\n$N一转身大吃一惊，却发现身旁却见一个男子站在玉像前，痴痴的呆看着，那表情竟然由爱生敬，由敬成痴。\n"NOR, me);  
		  log_file("quest/TLBB", sprintf("%s(%s) 凌波微步玉像处遇见段誉。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		  me->set_temp(QUESTDIR1+"see_duanyu2",1);
		  me->start_busy(1);
		  command("crazy");
		  command("say");
    }
	
	if(!me->query_condition("killer")
		&& me->query(QUESTDIR2+"start") 
		&& me->query_temp(QUESTDIR2+"pushdown") 
		&& !me->query(QUESTDIR2+"over"))
    {
		  message_vision(HIC"\n$N挤进暗室，发现一个中年男子，正炯炯有神地盯着你看，感觉不到一点被囚困的样子。\n\n"NOR, me);                      
		  command("ah "+me->query("id"));
		  command("look "+me->query("id"));
		  command("heng");
		  command("say");
		  command("say 真乃人不可貌相，这魔僧看似一代高僧，却妄为大轮明王。"); 
		  me->start_busy(1);
    }
}
string ask_name()
{
		set_name("段誉", ({ "duan yu", "duan","yu"}) );
		set("title",HIG"大理国镇南王世子"NOR);
		set("long", HIG"虽身处暗室，却依旧风采宜人，料想也是富贵子弟、世家豪杰。"NOR); 
		command("nod");
		return "在下便是段誉。";
}
int ask_home()
{
    object me,ob;
    ob=this_object();
	me=this_player();
	if(!me->query_condition("killer")
		&& me->query(QUESTDIR1+"start") 
		&& me->query_temp(QUESTDIR1+"see_duanyu2")
		&& !me->query_temp(QUESTDIR1+"gohome")
		&& !me->query_temp(QUESTDIR1+"see_duanyu1")
		&& !me->query(QUESTDIR1+"wuliangover")
		&& me->query_temp(QUESTDIR1+"jianying")
		&& ob->query("id")=="duan yu")
    {
		message_vision(HIY"\n$N轻轻道：“镇南王正在王府心急成忧，阁下还是回去看看。”\n"NOR, me, this_object());
		command("oh");
		command("consider");
		me->start_busy(1);
		command("say");
		me->set_temp(QUESTDIR1+"gohome",1);
		call_out("outroom",6,me);
		return 1;
    } 
	command("consider");
	me->start_busy(1);
	command("say");
	command("say 我也想回去，只是.......");
	command("shout");
    return 1;
}
void outroom(object me)
{
  object ob=this_object();
  if(!me) return;
  if(!me->query(QUESTDIR1+"start")) return;
  if(!me->query_temp(QUESTDIR1+"gohome")) return;
  if(me->query_temp(QUESTDIR1+"see_duanyu1")) return;
  if(me->query(QUESTDIR1+"wuliangover")) return;

  if(environment(ob)!=environment(me)) 
  {
  	command("say 人呢？"+me->name()+"刚才不是还在吗？");
	me->delete("quest/天龙八部/凌波微步篇");
  	command("say 我还是先回去了，爹爹和伯父一定着急了。");
  	command("sigh");
    me->set(QUESTDIR+"time",time());
 	me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
	destruct(ob);
  	return;
  }
  
  command("look "+me->query("id"));
 
  if(me->query("gender")=="女性")
  {
	  if(me->query("per")>26)
	  {
		  command("say 这位姐姐，竟然也这么漂亮，真是有得和这玉像一拼，不过这玉像精工也太神色动人了。");
		  command("points");
		  tell_object(me,HIC"\n你侧过身子看那玉像时，只见她眼光跟着转将过来，便似活了一般。你大吃一惊，侧头向右，玉像的眼光似乎也对着你移动。不论\n"
			  "你站在那一边，玉像的眼光始终向着你，眼光中的神色更是难以捉摸，似喜似爱，似是情意深挚，又似黯然神伤。\n"NOR);
		  tell_room(environment(me),HIC"转头却见"+me->query("name")+"也是一复神色怪怪的样子，也似乎被什么吸引住了似的。\n"NOR, ({ me })); 
		  tell_object(me,HIC"\n你又向玉像呆望良久，这才转头，见东壁上刮磨平整，刻着数十行字，都是“庄子”中的句子，大都出自“逍遥游”、“养生主”、\n"
			  "“秋水”、“至乐”几篇，笔法飘逸，似以极强腕力用利器刻成，每一笔都深入石壁几近半寸。文末题着一行字云：“逍遥子为秋\n"
			  "水妹书。洞中无日月，人间至乐也。”！\n"NOR);
		  tell_object(me,HIR"\n过了一会，禁不住脱口而出：“真是天仙下凡啊，这等姿色，别说是男子见了，心神不定，就是我身为女儿身，也是神色恍惚。”\n"
			  HIY"\n你突然竟然有双膝跪倒拜下去的冲动。 \n"NOR);
		  command("ah "+me->query("id"));
		  command("touch "+me->query("id"));	  
	  }
	  else
	  {
		  command("say "+me->query("name")+"，这位姐姐，你且仔细看看这玉像，真是太神色动人了。");
		  command("points");
		  tell_object(me,HIC"\n你侧过身子看那玉像时，只见她眼光跟着转将过来，便似活了一般。你大吃一惊，侧头向右，玉像的眼光似乎也对着你移动。不论\n"
			  "你站在那一边，玉像的眼光始终向着你，眼光中的神色更是难以捉摸，似喜似爱，似是情意深挚，又似黯然神伤。\n"NOR);
		  tell_room(environment(me),HIC"转头却见"+me->query("name")+"也是一复神色怪怪的样子，也似乎被什么吸引住了似的。\n"NOR, ({ me })); 
		  tell_object(me,HIC"\n你又向玉像呆望良久，这才转头，见东壁上刮磨平整，刻着数十行字，都是“庄子”中的句子，大都出自“逍遥游”、“养生主”、\n"
			  "“秋水”、“至乐”几篇，笔法飘逸，似以极强腕力用利器刻成，每一笔都深入石壁几近半寸。文末题着一行字云：“逍遥子为秋\n"
			  "水妹书。洞中无日月，人间至乐也。”！\n"NOR);
		  tell_object(me,HIR"\n过了一会，禁不住脱口而出：“真是天仙下凡啊，这等姿色，别说是男子见了，心神不定，就是我身为女儿身，看了真是自惭行愧啊。”\n"
			  HIY"\n你突然竟然有双膝跪倒拜下去的冲动。 \n"NOR);
		  command("ah "+me->query("id"));
		  command("shrug "+me->query("id"));	  
	  }
  }
  else
  {
 	  command("say "+me->query("name")+"，也是同道中人，你且仔细看看这玉像，真是太神色动人了。");
	  command("points");
	  tell_object(me,HIC"\n你侧过身子看那玉像时，只见她眼光跟着转将过来，便似活了一般。你大吃一惊，侧头向右，玉像的眼光似乎也对着你移动。不论\n"
	  "你站在那一边，玉像的眼光始终向着你，眼光中的神色更是难以捉摸，似喜似爱，似是情意深挚，又似黯然神伤。\n"NOR);
	  tell_room(environment(me),HIC"转头却见"+me->query("name")+"也是一复神色怪怪的样子，也似乎被什么吸引住了似的。\n"NOR, ({ me })); 
	  tell_object(me,HIC"\n你又向玉像呆望良久，这才转头，见东壁上刮磨平整，刻着数十行字，都是“庄子”中的句子，大都出自“逍遥游”、“养生主”、\n"
		  "“秋水”、“至乐”几篇，笔法飘逸，似以极强腕力用利器刻成，每一笔都深入石壁几近半寸。文末题着一行字云：“逍遥子为秋\n"
		  "水妹书。洞中无日月，人间至乐也。”！\n"NOR);
      if(me->query("gender")=="无性") tell_object(me,HIR"\n你暗想：“我要是真能做个女人，就是死一千遍，一万遍，也如身登极乐，欢喜无限。” \n"NOR);
	  tell_object(me,HIR"\n过了一会，禁不住脱口而出：“神仙姊姊，你若能活过来跟我说一句话，我便为你死一千遍，一万遍，也如身登极乐，欢喜无限。”\n"
		  HIY"\n你突然竟然有双膝跪倒拜下去的冲动。 \n"NOR);
	  command("ah "+me->query("id"));
	  command("touch "+me->query("id"));
  } 
  command("sigh");
  command("say 我还是先回去了，爹爹和伯父一定着急了。");
  command("chat* bye "+me->query("id"));	 
  command("wave "+me->query("id"));
  tell_room(environment(me),HIG"\n只见，段誉匆匆忙忙地离开，只是神色似乎很是留恋不舍。\n\n"NOR, ({}));
  me->set_temp(QUESTDIR1+"see_duanyu1",1);
  destruct(ob);
  return;
}


int ask_save()
{
    object me,ob,obj;
	int i, time;
    me=this_player();
    ob=this_object();
           
       //by Spiderii@ty 加入新标记,只为防止以前开lbwb的玩家可以连续fan bojuan
       time = time() - me->query("quest/天龙八部/武功/time");
       if ( me->query("quest/天龙八部/武功/time") && time < 86400 ) 
          {
		       message_vision("$N似乎不懂$n的意思。\n", ob,me);
	         return 1;
		 }


    if(ob->query("id")!="duan yu")
	{
		message_vision("$N似乎不懂$n的意思，道：$n要救谁，莫不是又来骗我的？。\n", ob, me);
		command("fear");
		return 1;
	}
	if (!me->query_condition("killer")
		&& me->query(QUESTDIR1+"start") 
		&& !me->query(QUESTDIR1+"over") 
		&& me->query_temp(QUESTDIR1+"kill_duan") 
		&& me->query(QUESTDIR1+"wuliangover"))
	{
		command("nod "+me->query("id"));
		message_vision(HIC"$N道：“今日相救无以回报，壮士是学武之人，我身上有卷帛卷，乃昔日\n"
			+"奇遇获得，今日赠于你，略表解救之谢意。”说完，$N从怀里摸出一团物事。\n"
			+"突然，$N大失惊色，“啊哟！怎么会变成这个样子？罢了！罢了！莫非天意？。”\n"
			+"拿去吧，能领会多少就看你的造化了。说完，$N把它交给$n。\n"NOR, ob, me);
		obj=new("/d/dali/obj/dodge_book");
              obj->set("owner", me->query("id"));//By Spiderii@ty 加个标记,防止BUG
              me->set("quest/天龙八部/武功/time", time()); //加个限制。禁止连续翻,只为防备以前开lbwb的玩家 By Spiderii@ty

		obj->move(me);
		//设定标志
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
		me->delete_temp("quest/天龙八部");
		me->set(QUESTDIR1+"over",1);//结束
		me->delete_temp("quest/busy");//任务冲突标志取消
		me->add_busy(4);
		i=10+random(10);
		me->add("max_neili",i);
		me->add("combat_exp",me->query_skill("force")+400);
		me->add("mana",me->query_skill("force")/3);
		command("thank "+me->query("id"));
		tell_object(me,HIY"\n你于"+NATURE_D->game_time()+"经过千辛万苦终于段誉从万劫谷解救出来，获得"+i+"点最大内力、"+(me->query_skill("force")+400)+"点经验和"+(int)me->query_skill("force")/3+"点声望。\n\n");
		log_file("quest/TLBB", sprintf("%s(%s) 凌波微步篇完成。奖励：%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), i,(me->query_skill("force")+400),me->query_skill("force")/3) );
		remove_call_out("dest");
		call_out("dest",5,me,ob);
		return 1;
	}
	if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"pushdown") && !me->query(QUESTDIR2+"over"))
	{
		command("say "+me->query("name")+"已经是第二次相救了，真的非常感激，我这里正好有块矿石，你且拿去。");
		obj=new("/d/zhiye/obj/kuangshi1");
		obj->set_level(5+random(3));
		obj->move(me);
		message_vision("$N给了$n一块"+obj->query("name")+"。\n", ob, me);
    	command("chat* thank "+me->query("id"));
    	command("wave "+me->query("id"));
    	command("bye "+me->query("id"));
		//设定标志
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
		me->set(QUESTDIR2+"over",1);  //结束 	
		me->delete_temp("quest/天龙八部");
		me->delete_temp("quest/busy");//任务冲突标志取消
		i=10+random(10);
		me->add("max_neili",i);
		me->add("combat_exp",(me->query_skill("force")+500));
		me->add("mana",me->query_skill("force")/3);
		tell_object(me,HIY"\n你于"+NATURE_D->game_time()+"经过千辛万苦终于段誉从天龙寺解救出来，获得"+i+"点最大内力、"+((int)me->query_skill("force")+500)+"点经验和"+(int)me->query_skill("force")/3+"点声望。\n\n");
		log_file("quest/TLBB", sprintf("%s(%s) 天龙营救篇完成。奖励：%d点最大内力，%d点经验，%d点声望和%s。\n", me->name(1),me->query("id"), i,(me->query_skill("force")+500),me->query_skill("force")/3,obj->query("name")) );
		destruct(this_object());
		return 1;
	}	
	if(random(2)) command("nod "+me->query("id"));
	else command("jump "+me->query("id"));
	return 1;
}

void dest(object me,object ob)
{
  if(!ob) return;
  if(!me || environment(ob)!=environment(me))
  {
	  destruct(ob);
	  return;
  }
  environment(ob)->set("exits/down","/d/dali/wuliang/midao1");
  message_vision(HIY"$n忽然看见角落里泥土翻飞，有三个身穿贴身紧靠的人从地里钻了出来 \n"
		+"$n仔细一看，原来是大理国的华赫艮、巴天石和范骅。范骅上前向段誉 \n"
		+"鞠了个躬,道：“公子，我们来救你来了。”眼角一瞥，看见了$n，道：\n"
		+"“敢问这位台兄？”，段誉道：“这位台兄也是来救我的，他杀了四大恶人\n"
		+"从前面推开巨石而入。”范、巴、华等人听了又惊又佩，，范骅道：“四。\n"
		+"大恶人党羽众多，恐怕还会有援兵来到，此地不宜久留，还是随我从地道。\n"
		+"赶紧离开吧。”众人点头称是，于是范、巴、华、段誉跳下地道离开了了\n"NOR, ob, me);
  destruct(ob);
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
  	  command("sigh "+me->query("id"));
		  return "真乃人不可貌相，这魔僧看似一代高僧，却妄为大轮明王。";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "鸠摩智妄为西域第一佛法高僧，所谓口生莲花，全是一派胡言。";
  }
  command("nod");
	return "大轮明王鸠摩智是吐蕃国的护国法王，但听说他具大智慧，精通佛法，好想见识一下。";
}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("nod");
  		return "我大哥萧峰如此英雄，何来援救之说。";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "听说这件事情，哼，我既可前往大辽。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
		  return "萧峰，难不是你所迫出中原，今日所谓搭救不知什么意思。假惺惺！";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("heng");
		  return "听说这件事情，哼，我既可前往大辽。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("heng");
		  return "听说这件事情，哼，我既可前往大辽。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "这一战真是痛快，"+me->query("name")+"更是威震武林，端得厉害啊。";
  }
  command("hoho");
	return "江湖人称南慕容、北萧峰，这萧峰正是我大哥，如此英雄好汉，何来援救之说。";
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
		  return "多谢"+RANK_D->query_respect(me) +"救我回国。";
  }
  command("hoho");
	return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
}
