//hufei.c
//by tangfeng@SJ

inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR "quest/雪山飞狐/"
#define QUESTDIR1 "quest/雪山飞狐/两页刀法篇/"
#define QUESTDIR2 "quest/雪山飞狐/复仇篇/"
#define QUESTDIR3 "quest/雪山飞狐/解药篇/"
#define QUESTDIR4 "quest/雪山飞狐/武功/"
int do_halt1(string arg);
void greeting(object me);
void unconcious();
void kill_ob(object me);
int do_hit(string arg);
void do_halt(object me);
void die();
int ask_biwu();
int ask_cheng();
int ask_yaowu();
int ask_hujiadaofa();
int ask_huyidao();
int ask_jiachou();
int ask_liangyedaofa();
int ask_zhiliao();
int ask_yanji();
int ask_miaoruolan();
int ask_tian();
int ask_miaorenfeng();
int ask_jiaoliang();
int hufei_fight(object me, object ob);
int thinking(object me, object ob);
int try_fight(object me, object ob);
int start_condition(object ob);
int power_condition(object me,object ob,int p);
int busy_pass(object ob);

void create()
{
	set_name("胡斐", ({ "hu fei", "hu", "fei" }) );
	set("gender", "男性" );
	set("title", HIW"雪山飞狐"NOR);
	set("age", 26);
	set("long",
	    HIR"辽东大侠胡一刀的儿子。"NOR);
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("unique", 1);

	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("blade", 300);
	set_skill("cuff",300);
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("xuantian-wuji",300);
	set_skill("hujia-daofa",300);
	map_skill("force","lengquan-shengong");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("blade","hujia-daofa");
	map_skill("parry","hujia-daofa");
  prepare_skill("cuff", "zhentian-quan");
	set("combat_exp", 2000000);
	set("max_qi", 30000);
	set("max_jing", 3000);
	set("max_neili", 5000);
	set("eff_jingli",3000);
	set("qi",30000);
	set("jing",3000);
	set("jingli",3000);
	set("neili", 5000);

        set("inquiry", ([
        "胡一刀" : (: ask_huyidao :),
        "胡家刀法" : (: ask_hujiadaofa :),
        "两页刀法" : (: ask_liangyedaofa :),
        "较量" : (: ask_jiaoliang :),
        "比武" : (: ask_biwu :),
        "治疗" : (: ask_zhiliao :),
        "苗若兰" : (: ask_miaoruolan :),
//    "苗人风" : (: ask_miaorenfeng :),
        "苗人凤" : (: ask_miaorenfeng :),
        "苗人风" : (: ask_miaorenfeng :),
        "阎基" : (: ask_yanji :),
        "程灵素" : (: ask_cheng :),
        "田归农" : (: ask_tian :),
        "家仇" : (: ask_jiachou :),
	]));
	setup();
	set("chat_chance", 1);
	set("chat_msg", ({
		"胡斐跪在坟前拜了又拜。\n",
	}));
	carry_object("/clone/weapon/blade/blade.c")->wield();
	carry_object("/clone/weapon/blade/blade.c");
	carry_object("/clone/armor/baihu-qiu.c")->wear();
}

void init()
{
  object ob;
	::init();
  ob = this_player();
  if (interactive(ob = this_player()) ) {
       remove_call_out("greeting");
       call_out("greeting", 1, ob);
  }
	add_action("do_answer","answer");
	add_action("do_halt1","halt");
  add_action("do_hit", "hit");
}
int do_halt1(string arg)
{
         object me,ob;
         me=this_player();
         ob=this_object();
	       command("sneer");
         remove_call_out("do_halt");
         remove_call_out("try_fight");
  	     ob->reset_action();
	       ob->delete("quest/try_fight");
	       ob->delete("quest/try_fight_id");
	       me->delete_temp(QUESTDIR+"较量/hu_fighting");
	       start_condition(ob);
	       command("halt");
         ob->remove_all_killer();
         me->remove_all_killer();
         return 1;

}
void greeting(object me)
{
  int shen,i;
  if(!me) return;
  if(environment(me)!=environment(this_object())) return;
  shen = me->query("shen");
	if(me->query_temp(QUESTDIR2+"over"))
	{
/*
　胡斐喘了口气，面对著这个自己生平想过几千几万遍之人，一时之间竟尔没了主意：“他是我杀父仇人，可是他又是若兰的父亲”。
　　“他害得我一生孤苦，但听平四叔说，他豪侠仗义，始终没对不起我的爹妈”。
　　“他号称打遍天下无敌手，武功艺业，举世无双，但我偏不信服，倒要试试是他强呢还是我强？”
*/
	 if(me->query_condition("killer"))
	 {
	   command("fear "+me->query("id"));
     command("say 小心官府通缉！");
	   return;
	 }
		tell_object(me,CYN"\n你急忙将真相告诉胡斐，胡斐闻言更是泣不成声....\n"NOR);
  	command("cry");
    me->delete_temp(QUESTDIR2+"over");
        tell_object(me,HIW"\n“田归农！”胡斐悲笑起来，仇恨似乎更是沉积，算是万幸，天龙门早已灭门，这恩怨也算是了解。\n\n"NOR);
    me->set(QUESTDIR2+"over",1);
    me->delete_temp(QUESTDIR2+"over");
  	tell_object(me,HIG"你不知道是喜是悲，想想这个结果对胡斐来说也许也是个园结。\n"NOR);
  	command("say 苗大侠，不知道毒发如何？");
  	tell_object(me,CYN"你点头道：我马上去苗家庄，你心情不定，还是先歇息为妙。\n"NOR);
   	me->add("max_neili",me->query_skill("force")/2);
   	me->add("combat_exp",me->query_skill("force"));
   	i=180+random(40);
   	me->add("mana",i);
  	tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解开雪山飞狐复仇篇，获得"+(int)me->query_skill("force")/2+"点最大内力、"+(int)me->query_skill("force")+"点经验奖励、"+i+"点声望。\n\n"NOR);
          log_file("quest/FEIHU", sprintf("%s(%s) 揭开雪山飞狐Quest复仇篇,时间 %s。获得%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2,me->query_skill("force"),i ) );
	}
	else
	{
	  if(shen <0 ) command("look "+me->query("id"));
	  else command("say");
  }
}

int ask_cheng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("say 真的感谢程姑娘，要不是她恐怕我抱憾终生。");
	  command("think");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"getjieyao"))
  {
	  command("suicide1");
	  command("say 真的感谢程姑娘，我们还是赶快去救治苗大侠吧。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& (me->query_temp(QUESTDIR3+"jieyao2")||me->query_temp(QUESTDIR3+"qixinghaitang")))
  {
	  command("suicide1");
	  command("say 我们快点赶到程姑娘那里，苗大侠的毒如此凶猛，只怕......");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao1"))
  {
	  command("sigh");
	  command("say 我们快点去找到七星海棠。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
	  command("blush");
	  command("say 程姑娘当年我与她有过一面之交，只是现在身在何处，不很清楚......");
	  command("sigh");
	  return 1;
  }
  command("say 你也认识程姑娘，这些年来，其实我一直在找她。");
	command("sigh");
	return 1;
}

int ask_biwu()
{
	object me = this_player();
  if(me->query(QUESTDIR3+"marry"))
  {
	  command("say 20年前的比武，现在已经完全明了，胡苗两家今天能够再次重归于好，多亏大侠帮忙。");
  	command("thank "+me->query("id"));
	  command("say 还要多谢大侠能够撮合在下与苗姑娘的婚姻。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 20年前的比武，现在已经完全明了。苗大侠如此正气，我竟然怀疑他，还好毒也解了，没能铸成大错。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 确实没有想到事情如此复杂。恨我自己，苗大侠如此正气，我竟然怀疑他，这毒如此凶猛，只怕......");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("shout");
	  command("say 20年前的比武，的确还有疑点，但是既然知道杀害我爹的凶手，就算我这身武功不济，也决不苟生。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("say 20年前的比武，知道真相的人都不复人世，这些年来我一直在寻找杀害爹妈的凶手。");
	  command("shout");
	  command("say 而且，可惜我武功未能圆通，不能为报父仇，这胡家刀法总是不能返璞归真。");
	  return 1;
  }
	command("say 当年我爹爹和号称“打遍天下无敌手”的苗人凤在此比武，苗人凤以毒刀\n将我爹爹害死，我娘自刎殉夫。待我遇见那杀父仇人，定将他碎尸万断......不过，\n"
          "他二人豪气相侔，相敬相重，苗人凤怎么会下如此黑手？");
	command("consider");
	command("doubt");
	return 1;
}

int ask_hujiadaofa()
{
	object me = this_player();
	object ob = this_object();
	int i;
	if(me->query_condition("killer"))
	 {
	   command("fear "+me->query("id"));
     command("say 小心官府通缉！");
	   return 1;
	}
	if(me->query(QUESTDIR2+"start") && !me->query(QUESTDIR3+"over"))
  {
	  command("shake "+me->query("id"));
	  command("say 现在时间紧急，这刀法还是以后切磋吧。");
	  return 1;
  }
  if(me->query(QUESTDIR4+"hujiadaofa_fail")>=3 && me->query("registered")<3)
  {
	  command("shake "+me->query("id"));
	  command("say 这刀法还是以后切磋吧。");
	  return 1;
	}

  if(me->query(QUESTDIR4+"hujiadaofa"))
  {
   if(me->query("potential")<= 5)
   {
	  command("? "+me->query("id"));
	  if(random(2)) command("say 胡什么刀，什么法啊？");
	  else command("say 潜能不够学什么刀法！");
    return 1;
   }
   else
   {
    message_vision("$N向$n请教有关胡家刀法的奥妙。\n", me, this_object());
    me->receive_damage("jing", 30);
    tell_object(me,"你听了胡斐的指点，对胡家刀法的奥妙似乎有些心得。\n");
    me->add("potential",-(random(3)+2));
    if( me->query("potential")<0)
        me->set("potential",0);
    me->improve_skill("hujia-daofa", 10+random(me->query_int()));
    me->improve_skill("blade", random(me->query_int())/2);
    return 1;
   }
  }
	if(me->query(QUESTDIR4+"time") && (time() - me->query(QUESTDIR4+"time"))<86400)
	{
	  command("hehe "+me->query("id"));
	  command("say 现在时间紧急，这刀法还是明天再来吧。");
	  return 1;
	}
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 不是刚学完吗，这刀法还是以后切磋吧。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("nod "+me->query("id"));
	  if(me->query(QUESTDIR4+"combat_exp") && (me->query("combat_exp") - me->query(QUESTDIR4+"combat_exp"))<1000000)
	  {
	    command("shake "+me->query("id"));
	    command("say 你还是专门练功去吧，你武功未有长进，只怕还是难以领悟。");
	    return 1;
	  }
    message_vision(HIB"\n$n突然运起独门内功冷泉神功，只感觉刀势无风自起。\n"NOR, me, ob);
    ob->set_temp("quest/雪山飞狐/武功/lengquan",1);
    ob->set_temp("busy",1);
    power_condition(me,ob,300+random(100));
	  for ( i = 0; i < 6+random(8);i++){
	     hufei_fight(me, ob);
    }
    ob->delete_temp("quest/雪山飞狐/武功/lengquan");
    start_condition(ob);
    tell_object(me,CYN"\n\n\n一晃数招已过，胡斐笑说道：「刚才我使用的招数可看清楚了？」\n"NOR);
    command("smile "+me->query("id"));
    remove_call_out("busy_pass");
    remove_call_out("thinking");
    me->set(QUESTDIR4+"time",time());
    me->set(QUESTDIR4+"combat_exp",me->query("combat_exp"));
    ob->set_temp("busy",1);
		call_out("busy_pass",600, ob);
		call_out("thinking",3, me, ob);
    tell_object(me,CYN"你开始认真考虑。\n"NOR);
    me->start_busy(3+random(i));
	  return 1;
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("shout");
	  if(random(2)) command("say 可惜我武功未能圆通，不能为报父仇，这胡家刀法总是不能返璞归真。");
	  else command("say 苗人风听说武功号称打遍天下，自是厉害，可惜我胡家刀法秘籍竟有残缺，因此在下武功终未大成。");
	  return 1;
  }
  if(me->query_temp(QUESTDIR1+"jiachou"))
  {
 	  command("heng");
	  command("say 我胡家刀法确是一等一的武功，只是爹爹留给我秘籍竟然缺了两页，缺了扎根基的入门功夫，缺了拳法刀法的总诀。");
	  command("say 这些年来，无论怎么用功，总是难以融会贯通，听说苗人风号称打遍天下无敌手，可惜我胡家刀法秘籍竟有残缺，不是对手。");
 	  command("sigh");
    command("say 我听平四叔说，这两页好像被一个江湖郎中夺去，前一段时间有人说在苗疆看到他。");
    me->set(QUESTDIR1+"start",1);
    me->delete_temp(QUESTDIR1+"jiachou");
	  return 1;
  }
	command("sneer");
	if(random(2)) command("say 想和我比试？看好了！");
  power_condition(me,ob,250+random(200));
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  if(random(2)) COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  if(random(2)) COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  start_condition(ob);
	command("sneer");
	return 1;
}
int hufei_fight(object me, object ob)
{
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  if (!present(me,environment(ob)) || me->query("qi") <= me->query("max_qi")/50 || me->query("jing") <= 10 || me->query("jingli") <= 10)  {
	command("sneer");
	command("say 这位大侠武功未能返璞归真，只怕难以领悟胡家刀法的绝技！");
	return 0;
  }
  return 1;
}
int busy_pass(object ob)
{
	if(!ob) return 0;
	if(ob->query_temp("busy")) ob->delete_temp("busy");
  return 1;
}

int thinking(object me, object ob)
{
	int i;
  if(environment(me)!=environment(this_object()))
  {
  	start_condition(ob);
  	return 1;
  }
	if(!me->query_temp(QUESTDIR4+"thinking"))
	{
		me->set_temp(QUESTDIR4+"thinking",1);
    tell_object(me,HIG"你努力地回忆刚才的每一招每一式......\n"NOR);
    tell_object(me,CYN"你努力地回忆刚才的每一招每一式......\n"NOR);
		call_out("thinking",4, me, ob);
	}
	else
	{
	  if(random(me->query("pur"))>28 && random(me->query("int"))>28)
    {
       tell_object(me,HIG"\n你明悟其中，突然间明白了一切。\n"NOR);
       tell_object(me,CYN"你「哈哈哈」大笑几声。\n"NOR);
       tell_object(me,CYN"你说道：「"NOR+HIR"我明白了。"NOR+CYN"」\n"NOR);
       command("nod");
       command("congra");
       tell_object(me,HIR"你听了胡斐的指点，对胡家刀法的奥妙似乎有些心得。\n"NOR);
       tell_object(me,HIR"只是你发现这胡家刀法还需要冷泉神功才能发挥全效。\n"NOR);
       me->set(QUESTDIR4+"hujiadaofa",1);
       me->delete(QUESTDIR4+"hujiadaofa_fail");
   	   i=180+random(40);
   	   me->add("mana",i);
  	   tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解开雪山飞狐胡家刀法篇，并获得"+i+"点声望。\n\n"NOR);
	     log_file("quest/FEIHU", sprintf("%s(%s) 揭开雪山飞狐胡家刀法,时间 %s，并获得%d点声望。\n", me->name(1),me->query("id"), ctime(time()),i ) );
    }
    else
    {
       tell_object(me,HIG"\n你似乎抓住了什么，可是依然不是很明白。\n"NOR);
       tell_object(me,CYN"你摇了摇头，道：好像还是很困难的。\n"NOR);
       tell_object(me,HIY"你深深地叹了口气。\n"NOR);
       me->add(QUESTDIR4+"hujiadaofa_fail",1);
      if(me->query(QUESTDIR4+"hujiadaofa_fail")>=3 && me->query("registered")<3)
       {
      	tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"最后一次尝试揭开雪山飞狐胡家刀法，却没有成功。\n\n"NOR);
   		  log_file("quest/FEIHU", sprintf("%s(%s) 最后一次尝试揭开雪山飞狐胡家刀法，却没有成功。时间 %s。\n", me->name(1),me->query("id"), ctime(time()) ) );
       }
    }
    me->delete_temp(QUESTDIR4+"thinking");
  }
  return 1;
}

int ask_huyidao()
{
	object me = this_player();
  if(me->query(QUESTDIR2+"over"))
  {
  	command("nod "+me->query("id"));
  	command("say 不错不错，当年的关东大侠胡一刀正是我父亲！");
   	message_vision(HIB"$N说完这句话，满脸尽是得意之色！\n"NOR,this_object());
	  return 1;
  }
  if(me->query(QUESTDIR2+"start"))
  {
  	command("heng");
  	command("say 当年的关东大侠胡一刀正是我父亲！");
  	command("say 爹爹的死我这就去找苗人风算账去！");
  	return 1;
  }
  command("nod "+me->query("id"));
  command("say 当年的关东大侠胡一刀正是我父亲！");
  command("say 可惜爹爹的仇，还未报！");
	return 1;
}

int ask_jiachou()
{
	object me = this_player();
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
     command("say 小心官府通缉！");
	   return 1;
	}
  if(me->query(QUESTDIR3+"marry"))
  {
	  command("say 家仇已了，胡苗两家今天能够再次重归于好，也多亏大侠帮忙。");
  	command("thank "+me->query("id"));
	  command("say 还要多谢大侠能够撮合在下与苗姑娘的婚姻。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
	  command("say 胡苗两家今天能够再次重归于好，也多亏大侠帮忙。苗大侠如此正气，我竟然怀疑他，还好毒也解了，没能铸成大错。");
	  command("sigh "+me->query("id"));
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 确实没有想到事情如此复杂。恨我自己，苗大侠如此正气，我竟然怀疑他，这毒如此凶猛，只怕......");
	  return 1;
  }
  if(me->query(QUESTDIR2+"start"))
  {
	  command("say 正所谓父仇不两立，既然知道杀害我爹的凶手，就算我这身武功不济，也决不苟生。");
	  if(!me->query(QUESTDIR2+"answer")){
	     command("look "+me->query("id"));
       command("sigh");
	     command("say 这位大侠，武功超绝，不知道是否愿意帮忙？");
       tell_object(me,HIG"回答命令answer yes 或者answer no\n"NOR);
       me->set_temp(QUESTDIR2+"answer_",1);
    }
    else
    {
	     command("look "+me->query("id"));
       command("thank");
	     command("say 只要这位大侠能够帮忙，在下不胜感激。其实我也不能确认这事情原委。");
    }
  	return 1;
  }
  if(me->query(QUESTDIR+"time") && (time() - me->query(QUESTDIR+"time"))<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 没看见我很忙，明天再来。");
	  return 1;
	}
  if(me->query(QUESTDIR1+"over"))
  {
	  command("say 我一直怀疑他就是杀害我爹的凶手，只是苗家素有侠名，所以不敢确认，如今真相大白。");
	  command("say 正所谓父仇不两立，既然知道杀害我爹的凶手，就算我这身武功不济，也决不敢偷生了。");
    command("sigh");
    me->set(QUESTDIR+"time",time());
	  command("look "+me->query("id"));
	  command("say 这位大侠，武功超绝，不知道是否愿意帮忙？");
    tell_object(me,HIG"回答命令answer yes 或者answer no\n"NOR);
    me->set_temp(QUESTDIR2+"answer_",1);
    me->set(QUESTDIR2+"start",1);
	  return 1;
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("shout");
	  command("say 我一直怀疑苗人风就是杀害我爹的凶手，只是他素有侠名，所以不敢确认。");
	  return 1;
  }
  if(me->query_temp(QUESTDIR1+"jiachou"))
  {
	  command("shout");
	  command("consider");
	  command("say 我真的不明白，想不通这其中的变化，只可惜我爹妈死得不明不白。");
	  return 1;
  }
	command("say 当年我爹爹和号称“打遍天下无敌手”的苗人凤在此比武，苗人凤以毒刀\n"
"  将我爹爹害死，我娘自刎殉夫。待我遇见那杀父仇人，定将他碎尸万断......不过，\n"
"  他二人豪气相侔，相敬相重，苗人凤怎么会下如此黑手？");
	command("consider");
	command("doubt");
  me->set(QUESTDIR+"time",time());
	me->set_temp(QUESTDIR1+"jiachou",1);
	return 1;
}

int do_answer(string arg)
{
	object me = this_player();
	if(!me->query_temp(QUESTDIR2+"answer_")) return 0;
	if(!arg ||(arg!="yes" && arg!="no")) return 0;
	if(arg=="yes")
	{
    tell_object(me,CYN"\n你深深地叹了口气，说道：恩，这段公案也应该有个水落石出！我就帮你去一次苗家庄吧。\n"NOR);
	  me->set_temp(QUESTDIR2+"answer","yes");
	}
	else
	{
    tell_object(me,CYN"\n你惊异地说道：我却有些怀疑，苗大侠怎么可能是凶手呢！不是算为你，我也要去一次苗家庄吧！\n"NOR);
	  me->set_temp(QUESTDIR2+"answer","no");
	}
	return 1;
}

int ask_jiaoliang()
{
	object me = this_player();
	object ob = this_object();
	if(me->query_condition("killer"))
	 {
	   command("fear "+me->query("id"));
     command("say 小心官府通缉！");
	   return 1;
	}
  if(!me->query(QUESTDIR3+"over") && me->query(QUESTDIR2+"start"))
  {
	  command("shake "+me->query("id"));
	  command("say 现在时间紧急，还是以后切磋吧。");
	  return 1;
  }
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 刚切磋完，以后切磋吧。");
	  return 1;
  }
  if(random(me->query("combat_exp"))<random(ob->query("combat_exp")*2/3) && !wizardp(me))
  {
	  command("say 危险，太危险了！");
    COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	  command("fear "+me->query("id"));
    COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	  command("say 危险，太危险了！");
    COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	  command("fear "+me->query("id"));
    return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("nod "+me->query("id"));
    message_vision(HIY"\n$n突然运起独门内功冷泉神功，只感觉刀势无风自起。\n"NOR, me, this_object());
    me->set_temp(QUESTDIR+"较量/hu_fighting",1);
    power_condition(me,ob,300+random(100));
	  ob->set("quest/try_fight",1);
	  ob->set("quest/try_fight_id",me->query("id"));
    ob->kill_ob(me);
	  command("sneer");
    remove_call_out("busy_pass");
    remove_call_out("do_halt");
    remove_call_out("try_fight");
    ob->set_temp("busy",1);
		call_out("busy_pass",600, ob);
    call_out("do_halt", 150,me);
		call_out("try_fight", 2, me, ob);
    me->start_busy(1);
    ob->start_busy(1);
	  return 1;
  }

	command("say 想和我比试？看好了！");
	command("sneer");
  power_condition(me,ob,250+random(200));
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
	command("sneer");
	start_condition(ob);
	return 1;
}

int try_fight(object me, object ob)
{
	int i;
	if (!me->is_fighting(ob)|| !ob->is_fighting(me)||!present(me,environment(ob)) || me->query("eff_qi") <= 1000|| me->query("qi") <= 0 || me->query("jing") <= 10 || me->query("jingli") <= 10)  {
	   command("sneer");
	   command("say 这位大侠武功未能返璞归真，只怕难以抵挡胡家刀法的进攻！");
     remove_call_out("do_halt");
     remove_call_out("try_fight");
  	 ob->reset_action();
	   ob->delete("quest/try_fight");
	   ob->delete("quest/try_fight_id");
	   me->delete_temp(QUESTDIR+"较量/hu_fighting");
	   start_condition(ob);
	   command("halt");
     ob->remove_all_killer();
     me->remove_all_killer();
  	 return 1;
  }
  if (!present("blade",ob))
	    carry_object(BINGQI_D("blade"))->wield();
	else command("wield blade");

  i=me->query_temp(QUESTDIR+"较量/fight_times");

  if(i<(2+random(me->query("int")/20))) i++;
  else
  {
  	if(ob->query_busy())
  	{
  		if(ob->query_busy()>2) ob->start_busy(me->query_busy()/2);
  		else ob->start_busy(random(2));
      message_vision(HIR"\n$N"MAG"逆转冷泉神功，瞬间化解原本束缚$N行动的困境，手脚顿时灵活了许多！\n"NOR, ob);
      if(random(2))
      {
            message_vision(HIW"\n$N"HIW"轻舒猿臂，手中的钢刀吞吞吐吐，变化莫测，笼罩了$n"HIW"周身要害！\n" NOR, this_object(),me);
            ob->command("haha");
            if(random(3))
            {
            	message_vision(HIY"\n$n"HIY"见来招实在是变幻莫测，不由得心生惧意，招式登时出了破绽！\n" NOR, this_object(),me);
              me->add_busy(3+random(4));
              COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            }
            else
            {
            	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            }
	    }
    }
    else
    {
     switch(random(6))
     {
     	case 0:
            message_vision(HIW"\n$N"HIW"轻舒猿臂，手中的钢刀吞吞吐吐，变化莫测，笼罩了$n"HIW"周身要害！\n" NOR, this_object(),me);
            ob->command("haha");
            if(random(3))
            {
            	message_vision(HIY"\n$n"HIY"见来招实在是变幻莫测，不由得心生惧意，招式登时出了破绽！\n" NOR, this_object(),me);
              me->add_busy(3+random(4));
              COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            }
            else
            {
            	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            }
            break;
     	case 1:
     	case 2:
            message_vision(HIC"\n突然之间，本就快捷绝伦的刀法骤然变得更加凌厉！就在这一瞬之间，$N已劈出七刀！\n"NOR, this_object(),me);
            ob->command("haha");
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            break;
     	case 3:
     	case 4:
     		    message_vision(HIR"\n$N手中的钢刀幻出漫天刀云，雷霆霹雳般的击向$n！\n" NOR, this_object(),me);
	          ob->add_temp("apply/attack", ob->query_skill("blade"));
	          ob->add_temp("apply/damage", ob->query_skill("blade"));
          	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
	          ob->add_temp("apply/attack", -ob->query_skill("blade"));
	          ob->add_temp("apply/damage", -ob->query_skill("blade"));
            ob->command("haha");
            break;
     	default:
      	    message_vision(HIB"\n$n突然运起独门内功冷泉神功，只感觉刀势无风自起。\n"NOR, me, this_object());
            ob->command("heng");
	          ob->add_temp("apply/attack", ob->query_skill("blade")/4);
            break;
     }
    }
     i=0;
  }
  me->set_temp(QUESTDIR+"较量/fight_times",i);
	call_out("try_fight", 1, me, ob);
  return 1;
}
int ask_liangyedaofa()
{
	object me = this_player();
  if(me->query(QUESTDIR1+"over"))
  {
  	command("thank "+me->query("id"));
	  command("say 感谢大侠帮我找到这两页刀法，我才能将胡家刀法融会贯通。");
	  return 1;
  }
	command("?");
  command("say 两页刀法？不是很明白。");
	return 1;
}
int ask_yanji()
{

	object me = this_player();
  if(me->query(QUESTDIR2+"over"))
  {
	  command("say 一切都结束了，也多亏他告诉我这一切恩恩怨怨。");
	  command("zxx2 "+me->query("id"));
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("heng");
	  command("say 这小人竟然乘乱偷走我家秘籍，待我见到必不可饶！");
	  return 1;
  }
 	command("?");
	command("say 我好像不认识这个人。");
	command("consider");
	return 1;
}
int ask_zhiliao()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("?");
	  command("say 我不是医生，呵呵，问我什么治疗？ ");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
	  command("sigh "+me->query("id"));
	  command("say 治疗苗大侠恐怕只有程姑娘了，好歹也让求她了，只是不知道现在程姑娘人在哪里。");
	  return 1;
  }
  command("?");
	command("say 我不是医生，呵呵，问我什么治疗？");
	return 1;
}
int ask_miaoruolan()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"marry"))
  {
  	command("blush");
  	command("thank "+me->query("id"));
	  command("say 小兰最近很好。还要多谢大侠能够撮合在下与苗姑娘的婚姻。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
	  command("say .............");
	  command("blush "+me->query("id"));
	  return 1;
  }
	command("say .............");
	command("blush "+me->query("id"));
	if(random(2)) command("zxx2");
	else command("sigh");
	return 1;
}
int ask_miaorenfeng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
  	command("thank "+me->query("id"));
	  command("say 苗大侠最近很好。还要多谢大侠能够化解苗胡两家的恩怨。");
  	command("thank "+me->query("id"));
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("blush "+me->query("id"));
	  command("say 果真一代大侠，可惜之前我一直冤枉了他。");
	  return 1;
  }
	command("say .............");
	command("consider");
	command("say 我不明白苗大侠与我爹爹如此交好，为何使出如此毒手，而他平常为人却有光明磊落！");
	return 1;
}
int ask_tian()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 天龙门现在一门尽亡，也算是天网恢恢阿。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("heng");
	  command("say 确实没有想到事情如此复杂。不知道这天龙门现在还有余人......");
    tell_object(me,CYN"你缓缓地摇了摇头，叹气道：恩恩怨怨何时了。\n"NOR);
	  return 1;
  }
	command("say 听说是上任天龙门掌门，很久不知下落了。现在天龙门大不如以前了。");
	return 1;
}

int accept_object(object who, object ob,object me)
{
	 if(ob->query("id")=="liangye daofa")
   {
   	 command("ah "+(string)who->query("id"));
     if(who->query_temp(QUESTDIR1+"liangye") && who->query(QUESTDIR1+"start"))
     {
     	/*
     	因为他父亲曾遗给他记载着武林绝学的一本拳经刀谱，那便是胡家拳法和刀法的精义。
     	这本拳经刀谱本来少了头上两页，缺了扎根基的入门功夫，缺了拳法刀法的总诀，于是不论他多么聪明用功，总是不能入门。
     	现下机缘巧合，给阎基偷去的总诀找回来了，于是一加融会贯通，武功进境一日千里。
     	*/
     	command("jump "+(string)who->query("id"));
        tell_object(who,HIY"\n你把两页刀法将给胡斐。胡斐仔细地看了两遍，不由惊叫起来，“正是这两页刀法，不是大侠何处得来？”\n"NOR);
        tell_object(who,HIG"你简单说了一下你去苗疆；却见胡斐傻傻地盯着这两页刀法，不由自主地演练起来，全然忘记你的存在。\n\n"NOR);
     	who->start_busy(4);
      remove_call_out("telltruth");
      call_out("telltruth", 4, who);
     }
     else  command("thank "+(string)who->query("id"));
   }
    else
   {
     command("? "+(string)who->query("id"));
   }
   call_out("destroying", 1, ob);
   return 1;
}
void destroying(object obj)
{
        if(obj) destruct(obj);
        return;
}
void telltruth(object me)
{
	    int i;
	    if(!me) return;
	    if(environment(me)!=environment(this_object()))   	return;
      if(!me->query_temp(QUESTDIR1+"liangye")) return;
      write("\n\n");
     	command("haha");
     	command("say 不错就是它，正是我胡家刀法无法圆通的缺陷所在！");
     	tell_object(me,YEL"\n你看胡斐练得差不多，同时把从阎基那里听来的关于20年前比武的一些信息告诉胡斐，从比武到最后，最\n"NOR);
     	tell_object(me,YEL"后因为胡一刀妄想破解“提撩剑白鹤舒翅”结果不敌而自杀。说了好一会，才说完。\n\n"NOR);

     	command("bite");
     	command("say");
     	command("say 无论如何，看来爹爹死在苗人风手下千真万确。我的胡家刀法终于能够返璞归真，既然苗人风\n就是凶手，就算我武功不济，也必保此仇！");
      me->set(QUESTDIR1+"over",1);
   	  me->add("max_neili",me->query_skill("force")/2);
   	  me->add("combat_exp",me->query_skill("force"));
      i=random(40)+80;
      me->add("mana",i);
    	tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解开雪山飞狐两页刀法篇，获得"+(int)me->query_skill("force")/2+"点最大内力、"+(int)me->query_skill("force")+"点经验奖励。\n\n"NOR);
	    log_file("quest/FEIHU", sprintf("%s(%s) 揭开雪山飞狐Quest两页刀法篇,时间 %s。获得%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), ctime(time()),me->query_skill("force")/2,me->query_skill("force") ,i) );
     	me->delete_temp(QUESTDIR1+"liangye");
      return;
}
void kill_ob(object me)
{
	 command("sneer " + me->query("id"));
	::kill_ob(me);
}
int start_condition(object ob)
{
	 if(!ob) return 0;
   ob->set_skill("force", 300);
	 ob->set_skill("dodge", 300);
	 ob->set_skill("parry", 300);
	 ob->set_skill("blade", 300);
	 ob->set_skill("cuff",300);
	 ob->set_skill("taxue-wuhen",300);
	 ob->set_skill("zhentian-quan",300);
	 ob->set_skill("lengquan-shengong",300);
	 ob->set_skill("hujia-daofa",300);
   ob->map_skill("force","lengquan-shengong");
	 ob->set("combat_exp", 2000000);
	 ob->set("max_qi", 30000);
	 ob->set("max_jing", 3000);
	 ob->set("max_neili", 5000);
	 ob->set("eff_jingli",3000);
	 ob->set("qi",30000);
	 ob->set("jing",3000);
	 ob->set("jingli",3000);
	 ob->set("neili", 5000);
   return 1;
}
int power_condition(object me,object ob,int p)
{
	  int i;
    if (!present("blade",ob))
	    carry_object(BINGQI_D("blade"))->wield();
	  else command("wield blade");
    ob->set_temp("quest/雪山飞狐/武功/lengquan",1);
	  i=me->query("max_pot");
	  if(p<150) p=150;
	  if(i<p) i=p;
	  i=i-100;
	  ob->set_skill("force", i+random(50));
	  ob->set_skill("dodge", i+random(50));
	  ob->set_skill("parry", i+random(50));
	  ob->set_skill("blade", i+random(50));
	  ob->set_skill("cuff",i+random(50));
	  ob->set_skill("taxue-wuhen",i+random(50));
	  ob->set_skill("zhentian-quan",i+random(50));
	  ob->set_skill("lengquan-shengong",i+random(50));
	  ob->set_skill("hujia-daofa",i+random(50));
	  ob->map_skill("force","lengquan-shengong");
 	  i=me->query("combat_exp");
	  ob->set("combat_exp",i);
	  i=me->query("neili");
	  if(i<15000) i=15000;
	  ob->set("neili", i);
	  i=me->query("max_neili");
	  if(i<6000) i=6000;
	  ob->set("jiali",200);
	  ob->set("max_neili", i);
  	i=me->query("max_qi");
	  ob->set("max_qi", i*(2+random(3)));
 	  ob->set("eff_qi", ob->query("max_qi"));
 	  ob->set("qi", ob->query("max_qi"));
    return 1;
}
int do_hit(string arg)
{
         object me,ob;
         me=this_player();
         ob=this_object();
         if((arg==("hu"))||(arg==("hu fei"))){
           	command("sneer");
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	return 1;
         }
         return 0;
}

void do_halt(object me)
{
	if(!this_object()->is_fighting() && !me->is_fighting()) return;
   command("say 我可没功夫在耗下去了，下次再较量吧。");
   remove_call_out("do_halt");
   remove_call_out("try_fight");
	 this_object()->delete("quest/try_fight");
	 this_object()->delete("quest/try_fight_id");
   start_condition(this_object());
	 command("halt");
   this_object()->remove_all_killer();
   me->remove_all_killer();
   return;
}
void unconcious()
{
	object me,ob=this_object();

	if(this_object()->query("quest/try_fight"))
	{
	  command("ah");
    command("halt");
    start_condition(ob);
	  if(ob->query("quest/try_fight_id"))
	  {
	  	me=find_player(ob->query("quest/try_fight_id"));
	  	if(!me) return 0;
	  	if(!me->query_temp(QUESTDIR+"较量/hu_fighting")) return 0;
	    if(environment(me)!=environment(this_object()))  return 0;
	  	me->delete_temp(QUESTDIR+"较量/hu_fighting");
	  	me->add("combat_exp",me->query_skill("force")/2);
	    command("thumb "+me->query("id"));
	    command("admire "+me->query("id"));
	  	tell_object(me,HIR"\n经过一番苦斗，你发现自己的武功大有激进。你获得"+me->query_skill("force")/2+"点经验。\n"NOR);
	  }
	   ob->delete("quest/try_fight");
	   ob->delete("quest/try_fight_id");
     ob->remove_all_killer();
     me->remove_all_killer();
     remove_call_out("do_halt");
     remove_call_out("try_fight");
  }
  else
  {
	command("why");
	::unconcious();
  }
}
void die()
{
	object me,ob=this_object();

	if(this_object()->query("quest/try_fight"))
	{
	  command("ah");
    command("halt");
    start_condition(ob);
	  if(ob->query("quest/try_fight_id"))
	  {
	  	me=find_player(ob->query("quest/try_fight_id"));
	  	if(!me) return 0;
	  	if(!me->query_temp(QUESTDIR+"较量/hu_fighting")) return 0;
	    if(environment(me)!=environment(this_object()))   	return 0;
	  	me->delete_temp(QUESTDIR+"较量/hu_fighting");
	  	me->add("combat_exp",me->query_skill("force")/2);
	  	tell_object(me,HIR"\n经过一番苦斗，你发现自己的武功大有激进。你获得"+me->query_skill("force")/2+"点经验。\n"NOR);
	    command("thumb "+me->query("id"));
	    command("admire "+me->query("id"));
	  }
	   ob->delete("quest/try_fight");
	   ob->delete("quest/try_fight_id");
     ob->remove_all_killer();
     remove_call_out("do_halt");
     remove_call_out("try_fight");
  }
  else
  {
	command("why");
	::die();
  }
}
/*
int ask_me1()
{
	object me = this_player();
	{
	command("say 当年我爹爹和号称“打遍天下无敌手”的苗人凤在此比武，苗人凤以毒刀\n"
"将我爹爹害死，我娘自刎殉夫。待我遇见那杀父仇人，定将他碎尸万断......不过，\n"
"他二人豪气相侔，相敬相重，苗人凤怎么会下如此黑手？");
	command("consider");
	me->set_temp("marks/ah1",1);
	return 1;
	}
}

int do_emote()
{
	object ob = this_object();
	if(this_player()->query("id")=="yan ji") {
	  command("say 阎基，原来是你这个败类害死我爹爹，去死吧！");
	  message_vision("$N一刀将$n砍翻在地。\n", ob,present("yan ji"));
	  present("yan ji")->die();
	  command("say 我去杀了那个田归农，为爹爹报仇！");
	  message_vision("$N勿勿忙忙离开了。\n",ob);
	  destruct(ob);
	  return 1;
	  }
}
*/
