// xiaofeng.c
// Add by tangfeng 2004

inherit F_MASTER;
#include <ansi.h>
inherit NPC;

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"

int ask_truth();
int ask_yintui();
int ask_father();
void greeting(object me);
void xiaofeng_guiyin(object me);
void create()
{
	set_name("萧峰", ({"xiao feng", "xiao", "feng"}));
	set("gender", "男性");
	set("title",HIB"奇侠"NOR);
	set("age", 58);
	set("long", 
		"他就是丐帮前任帮主萧峰。\n"
		"他身高六尺有余，体格十分魁梧，长有一张线条粗旷、十\n"
		"分男性化的脸庞，双目如电，炯炯有神。\n");
	set("attitude", "peaceful");
	
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("qi", 40000);
	set("max_qi", 40000);
	set("jing", 15000);
	set("max_jing", 15000);
	set("eff_jing", 15000);
	set("neili", 60000);
	set("max_neili", 35000);
	set("jiali", 200);
  set("max_jingli", 15000);
  set("jingli", 15000);
	set("eff_jingli", 15000);
  set("combat_exp", 10000000);	 
	set_skill("force", 420);   
	set_skill("bangjue", 200);
	set_skill("literate", 200);        
	set_skill("medicine", 200);        
	set_skill("huntian-qigong", 420);
	set_skill("yijin-jing", 200);     
	set_skill("strike", 420);           
	set_skill("jingang-quan", 420);     
	set_skill("xianglong-zhang", 420);     
	set_skill("dodge", 420);      	     
	set_skill("xiaoyaoyou", 420);   
	set_skill("parry", 420);          
	set_skill("stick", 420);          
	set_skill("dagou-bang", 420);          
	set_skill("cuff", 420);          
	map_skill("cuff", "jingang-quan");
	map_skill("force", "huntian-qigong");
	map_skill("strike", "xianglong-zhang");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "xianglong-zhang");
	map_skill("stick", "dagou-bang");
	prepare_skill("strike","xianglong-zhang");
	prepare_skill("cuff","jingang-quan");
  set("chat_chance_combat", 99);
  set("chat_msg_combat", ({
          (: exert_function, "huntian" :),
          (: exert_function, "shentong" :),
          (: perform_action, "strike.paiyun" :),
          (: perform_action, "strike.xiao" :),
  }));
  set("inquiry", ([
		"段誉" : random(2)?"那是我二弟。\n":"我二弟一身内力震古烁今，六脉神剑更是天下无双。\n",
		"虚竹" : random(2)?"那是我三弟。\n":"我三弟现为缥缈宫宫主，只怕现在更是西夏国的驸马爷了。\n",
		"真相" : (: ask_truth :),
		"萧远山" : (: ask_father :),
		"拜师" : "嗯....，我注定一声漂泊，还是算了吧。\n",
		"丐帮" : "丐帮是我家，我家在丐帮。",
		"丐帮" : "我一身武功出自少林，也算是半个少林弟子。",
		"天龙寺" : "天龙寺是大理段家武学的最高之地。",
		"洪七公" : "恩，听说下一辈中也是他为人最为侠义，武功最高。",
		"阿朱" : "......怕是这一生我唯一的牵挂了。",
		"阿紫" : "恩，不提也罢，丁老怪的弟子，那个不是心狠手辣。",
		"阿碧" : "阿朱的妹妹，听说和慕容公子在一起。",
		"天龙寺" : "天龙寺是大理段家武学的最高之地。",
		"降龙十八掌" : "这是我行走江湖的吃饭的东西，哈哈。",
		"打狗棒" : "丐帮帮主之外不传之武功，确实精妙无比。",
		"归隐" : (: ask_yintui :),
		"隐退" : (: ask_yintui :),
		"洗手" : (: ask_yintui :),
		"隐退江湖" : (: ask_yintui :),
		"归隐江湖" : (: ask_yintui :),
		"慕容复" : "慕容公子确是其江南文采，诗琴书画无所不精，武功更是冠绝天下。",
		"慕容博" : "我听说是，姑苏慕容不出的杰才，可惜英年早逝。",
		"六脉神剑" : "天龙寺最高绝学。恐怕天下唯我二弟这身内力才能使得。",
    ]));

	setup();
  carry_object(ARMOR_D("changshan"))->wear();
  carry_object(ARMOR_D("shoes"))->wear();
}

void init()
{
	object me,room;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
  	if(!me->query_condition("killer")&&me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over"))
    {
	    this_object()->set("qi", this_object()->query("max_qi"));
	    this_object()->set("eff_qi", this_object()->query("max_qi"));
	    this_object()->set("neili", this_object()->query("max_neili")*2);
      tell_object(me,CYN"你惊讶地「啊！」了一声。\n"NOR);    
      message_vision(HIW"$N长长地舒了一口气，伤势看来基本全部恢复了。"NOR,this_object());                    
      tell_object(me,HIC"\n你没有料道，萧峰竟然恢复如此之迅速，果然是功夫了得。\n"NOR);  
      command("thank "+me->query("id"));
      //remove_call_out("greeting");
		  call_out("greeting",2,me);
    }
	 	if(!me->query_condition("killer")&& me->query(QUESTDIR4+"start") && me->query_temp(QUESTDIR4+"breakmen") && !me->query(QUESTDIR4+"over"))
    {
    	command("ah "+me->query("id"));
    	command("say 没想到，又是大侠舍命相救。"); 
    	command("thank "+me->query("id"));
      me->start_busy(2);
		  tell_object(me,HIC"\n你上前说道，“我们还是赶快离开此地，只怕这次为了营救你，江湖中人已全部出动，无论丐帮、少林、大理、\n"
		                      "还是远在西域的缥缈七十二宫。”\n"NOR);
		  command("sigh");
		  command("say 好，我们这就赶快一起闯出去。");
      if (!(room = find_object("/d/xingxiu/silk3")))
          room = load_object("/d/xingxiu/silk3");
      if(!room)
      { 
      	tell_object(me,HIR"\n赶快找wiz吧，竟然房间不存在!!!\n");
      }
      else
      {
                      me->set(QUESTDIR4+"over",1);
                      me->set(QUESTDIR+"time",time());
                      me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
                      me->delete_temp(QUESTDIR4+"dagouzhen");
                      me->delete_temp(QUESTDIR4+"shaolinzhen");
                      me->delete_temp(QUESTDIR4+"kill");
                      me->delete_temp(QUESTDIR4+"anhao");
                      me->delete_temp(QUESTDIR4+"count");
                      me->delete_temp(QUESTDIR4+"breakmen");
                      me->delete_temp(QUESTDIR4+"askxuanci");
                      me->delete_temp(QUESTDIR4+"askwu");
                  me->move("/d/xingxiu/daliao/shanlu3");
                  this_object()->move("/d/xingxiu/daliao/shanlu3");
                  me->move("/d/xingxiu/daliao/shanlu2");
                  this_object()->move("/d/xingxiu/daliao/shanlu2");
                  me->move("/d/xingxiu/daliao/shanlu1");
                  this_object()->move("/d/xingxiu/daliao/shanlu1");
                  "/cmds/std/look.c"->look_room(me,environment(me)); 
   		  me->move(room);
   		  this_object()->move(room);
   		  "/cmds/std/look.c"->look_room(me, room); 
        tell_object(me,HIG"\n你们边打边退，一路奔波，连续走过好几个地方，才来到一个断崖边。也巧，这里正是当年萧峰双亲双亡的地方。\n"NOR);
        message_vision(HIW"$N长长地舒了一口气。\n"NOR,this_object());
   		  command("whisper "+me->query("id")+" 也算终于脱险了，我与中原武林之间的恩恩怨怨叶一笔勾销。");
   		  command("chat* thank "+me->query("id"));
   		  command("wave "+me->query("id"));
   		  command("chat* byebye");
		    me->add("max_neili",me->query_skill("force")/2);
		    me->add("combat_exp",me->query_skill("force"));
		    me->add("shen",me->query_skill("force")*5);
		    me->add("mana",me->query_skill("force")/2);
        tell_object(me,HIY"\n你于"+NATURE_D->game_time()+"终于将萧峰从大辽解救出来，获得"+(int)me->query_skill("force")/2+"点最大内力、"+(int)me->query_skill("force")+"点经验和"+(int)me->query_skill("force")/2+"点声望。\n\n");
        log_file("quest/TLBB", sprintf("%s(%s) 终于将萧峰从大辽解救出来，时间 %s。获得%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2,me->query_skill("force"),me->query_skill("force")/2) );
                    destruct(this_object());
                    return;
 	    }
    }
	} 
}

void greeting(object me)
{
	if(!me) return;
  if(environment(this_object())!=environment(me)) 
  {
    command("chat "+me->name()+"怎么如此邋遢，竟然无端走开？");
    command("chat* heng "+me->query("id"));
    tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
    me->delete_temp(QUESTDIR3+"kill");
    me->delete_temp(QUESTDIR3+"lookcliff");
    me->delete(QUESTDIR3+"start");
    me->add("mana",-200);
    if(me->query("mana")<0) me->set("mana",0);
    return;
	}
	if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over"))
  {
    command("thank "+me->query("id"));
    command("say 再次感谢大侠救命之恩。");
    tell_object(me,HIG"\n\n你走过去看了看萧峰，还是将你看到的告诉了萧峰：智光大师所道的山壁上如今正中一大片尽是斧凿的印痕，\n"
                          "显而易见，是有人故意将留下的字迹削去了。\n"NOR);
	  tell_room(environment(me),HIG"\n"+me->name()+"走到萧峰跟前，低声说了些什么。\n"NOR, ({ me }));
    command("ah");
    message_vision(HIW"$N突然悲笑起来，喃喃道：“看来我真是契丹人，我真的不是汉人。”\n"NOR,this_object());
    command("say");
    message_vision(HIC"$N神色渐渐有些不正常，似乎已经有些发狂。\n"NOR,this_object());
    tell_object(me,HIW"\n突然之间，你脑子闪过两个念头。一个因为这萧峰已确是契丹人，他若公开反对大宋，只怕朝廷不知多少人因此\n"
                        "丧命，而且此时你趁他意乱伤神之际，正是扬你威名的大好时机；可是一个侠义之心告诉你，如此确似小人行为\n"
                        "一般不堪，这契丹人中也有好人坏人，也可以行侠仗义，何必执著于身份。\n"NOR);
    tell_object(me,HIR"\n一时间，你是劝其归隐（ask xiao about 归隐），还是为武林除害（kill xiao）？你一时委实难以决定。\n"NOR);
    me->set(QUESTDIR3+"over",1);
    me->start_busy(3);
	}
}
int ask_father()
{
    object me;
    me=this_player();
    if(me->query(QUESTDIR4+"over"))
    {
    	command("say 萧远山，正是我父亲。现已被少林高僧收为弟子。");
		  return 1;
	  }
    if(me->query(QUESTDIR3+"over"))
    {
    	command("heng");
    	command("say 萧远山，正是我父亲。此仇不能不报。");
		  return 1;
	  }
    if(!me->query(QUESTDIR3+"over"))
    {
    	command("? "+me->query("id"));
		  return 1;
	  }
    command("? "+me->query("id"));
		return 1;
}
int ask_truth()
{
    object me;
    me=this_player();
    if(me->query(QUESTDIR4+"over"))
    {
    	command("say 一切都已经过去，就重新开始吧。");
		  return 1;
	  }
    if(me->query(QUESTDIR3+"over"))
    {
    	command("heng");
    	command("say 此等大仇不能不报。");
		  return 1;
	  }
    if(!me->query(QUESTDIR3+"start"))
    {
    	command("? "+me->query("id"));
    	command("say 拜托，情节还没开始，不要clone我好不。");
    	command("heng "+me->query("id"));
		  return 1;
	  }
	  if(me->query_condition("killer"))
	  {
	  	command("heng");
	  	command("say 你还是处理好和官府的关系吧。");
	  	return 1;
	  }
    if(me->query(QUESTDIR3+"start")&&!me->query_temp(QUESTDIR3+"help"))
    {
    	command("? "+me->query("id"));
    	command("say 这么快你能找到我？BUG啊，靠，说：谁在帮你？");
		  return 1;
	  }
    if(me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"help")&&!me->query_temp(QUESTDIR3+"askxiao"))
    {
    	message_vision(HIY"$N听过$n的询问，顿时似乎苍老了很多。\n"NOR,this_object(),me);
    	command("say 我也不知道具体原委，这些日子以来，生不得安宁，朋友东分西裂，养父、师傅都无端被害。");
    	command("sigh");
    	command("say 我受伤未能远行，还请这位大侠去一次颂摩崖，那里据说有一块刻字记载当年事迹。");
    	command("thank "+me->query("id"));
    	me->set_temp(QUESTDIR3+"askxiao",1);
		  return 1;
	  }
    command("thank "+me->query("id"));
    command("say 一切有劳大侠了。");
		return 1;
}
int ask_yintui()
{
    object me;
    me=this_player();
    if(me->query(QUESTDIR4+"over"))
    {
    	command("say 一切都已经过去，就重新开始吧。");
		  return 1;
	  }
    if(me->query(QUESTDIR3+"good"))
    {
    	command("sigh");
    	command("say 也罢，天下何处不留人。这江湖中事我也不涉了，我既是契丹人，也该回我大辽。");
    	command("bye");
   		destruct(this_object());
		  return 1;
	  }
	  if(me->query_condition("killer"))
	  {
	  	command("heng");
	  	command("say 你还是处理好和官府的关系吧。");
	  	return 1;
	  }
    if(!me->query(QUESTDIR3+"good") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"bad"))
    {
    	tell_object(me,HIW"你见萧峰呆呆发蒙，知道他正为这契丹人的身份伤神，却听萧峰越来越暴躁，大声号叫：“我不是汉人，我不是汉人！\n"
    	                  "我是契丹胡虏，我是契丹胡虏！”提起手来，一掌掌往山壁上劈去，壁上石屑四溅。乔峰心中郁怒难伸，仍是一掌掌的\n"
    	                  "劈去，似要将这一个多月来所受的种种委屈，都要向这块石壁发泄，到得后来，手掌出血，一个个血手印拍上石壁，他\n"
    	                  "兀自不停。\n\n"NOR);
    	message_vision(HIY"$N渐渐发起狂来，神色却是越来越是悲痛。\n"NOR,this_object());
    	tell_object(me,HIW"你知道似萧峰这等武功若不及时劝说，这等悲愤只怕内功大有损伤，当即哈哈大笑一声。果然，萧峰怒视于你。你且自\n"
    	                  "顾说道：“大丈夫提得起、放得下，汉人中有好人坏人，契丹人中，自然也有好人坏人。你生为契丹人又当如何，只要\n"
    	                  "行侠仗义，这天下还不是要去要来”。\n\n"NOR);          	 
    	command("ah "+me->query("id"));
    	command("consider");
    	remove_call_out("xiaofeng_guiyin");
    	call_out("xiaofeng_guiyin",5,me);
		  return 1;
	  }
	  if(me->query(QUESTDIR3+"over")&& me->query(QUESTDIR3+"bad"))
	  {
   	  command("heng "+me->query("id"));
   	  kill_ob(me);
   	  return 1;
   	}
 	  command("heng "+me->query("id"));
		return 1;
}
void xiaofeng_guiyin(object me)
{
	if(!me) return;
  if(environment(this_object())!=environment(me)) 
  {
    command("chat "+me->name()+"怎么如此邋遢，竟然无端走开？");
    command("chat* heng "+me->query("id"));
    tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
    me->delete_temp(QUESTDIR3+"kill");
    me->delete_temp(QUESTDIR3+"lookcliff");
    me->delete(QUESTDIR3+"start");
    me->delete(QUESTDIR3+"over");
    me->add("mana",-200);
    if(me->query("mana")<0) me->set("mana",0);
    return;
  }
  if(!me->query(QUESTDIR3+"good") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"bad"))
  {
    command("nod "+me->query("id"));
    tell_object(me,HIG"\n却见萧峰脸色大见缓和，以萧峰原本的大智慧，也定能明白这其中的道理。你也放下心来。\n"NOR);
    command("say 也罢，我这就回我大辽，做我自己，还自行侠仗义，怎能这般自甘消沉。");
    command("thank "+me->query("id"));
    command("bye");                     
    me->set(QUESTDIR3+"good",1);
		me->add("mana",me->query_skill("force")/2);
		me->add("shen",me->query_skill("force")*5);
    tell_object(me,HIY"\n\n你于"+NATURE_D->game_time()+"选择劝说萧峰归隐江湖，也算功德无量，获得"+(int)me->query_skill("force")/2+"点声望的奖励。\n\n");
    log_file("quest/TLBB", sprintf("%s(%s) 选择劝说萧峰归隐江湖，时间 %s。获得%d点声望。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2) );
	  destruct(this_object());
	}
}
void die()
{
	object me,ob=this_object();
	me=ob->query_temp("last_damage_from");
        if(userp(me=ob->query_temp("last_damage_from")) 
	  && me->query(QUESTDIR3+"over")
	  && !me->query(QUESTDIR3+"good")
	  && !me->query(QUESTDIR3+"bad"))
	{
 	  me->set(QUESTDIR3+"bad",1);
 	  command("chat* heng");
    command("chat 好好，"+me->name()+"竟然趁我不注意偷袭我，等我武功恢复之日，当是中原武林血洗之时！");
		me->add("max_neili",me->query_skill("force")/2);
		me->add("shen",-me->query_skill("force")*5);
    tell_object(me,HIY"\n\n你于"+NATURE_D->game_time()+"选择为武林除害，击败萧峰，获得"+(int)me->query_skill("force")/2+"点内力的奖励。\n\n");
    log_file("quest/TLBB", sprintf("%s(%s) 选择击败萧峰，时间 %s。获得%d点内力。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2) );
	  destruct(this_object());
  }
  else if(this_object()->query("no_death"))
  {
	ob->set("qi", 20000);
	ob->set("eff_qi", 20000);
	ob->set("jing", 15000);
	ob->set("max_jing", 15000);
	ob->add("neili", 8000);
  ob->set("jingli", 15000);
	ob->set("jing", 15000);
  command("heng");
  message_vision(HIR "\n$N微一凝神，运起混天气功，全身骨节发出一阵爆豆般的声响。\n" NOR, ob);
	}
   ::die();
}
void unconcious()
{
  die();
}
