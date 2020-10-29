//by tangfeng@SJ 8/2004


inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR1 "quest/雪山飞狐/两页刀法篇/"
#define QUESTDIR2 "quest/雪山飞狐/复仇篇/"
#define QUESTDIR3 "quest/雪山飞狐/解药篇/"

void kill_player(object me);
void unconcious();
void die();
void kill_ob(object me);
int do_hit(string arg);
int ask_hufei();
int ask_qixinghaitang();
int ask_liangyedaofa();
int ask_hujiadaofa();
int ask_biwu();
int ask_miaorenfeng();
int ask_huyidao();
int ask_tian();
int ask_xiadu();
int ask_cheng();
int power_condition(object me,object ob,int p);
int start_condition(object ob);

void create()
{
	set_name("阎基", ({ "yan ji", "yan", "ji" }) );
	set("gender", "男性" );
	set("title", RED"江湖郎中"NOR);
	set("age", 51);
	set("long",
	    "赤脚医生，善于用毒，脸上透露着一丝狡诈。\n");
	set("str", 20);
	set("dex", 20);
	set("con", 20);
	set("int", 20);
	set("per", 15);
	set("shen_type", -1);
	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("cuff",300);
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("blade",150);
	set_skill("hujia-daofa",150);
	set_skill("huagong-dafa",150);
	map_skill("force","huagong-dafa");
	map_skill("blade","hujia-daofa");
	map_skill("parry","hujia-daofa");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
  prepare_skill("cuff", "zhentian-quan");
	set("combat_exp", 300000);
	set("max_qi", 30000);
	set("max_jing", 10000);
	set("eff_jingli",10000);
	set("max_neili", 21000);
	set("qi",30000);
	set("jing",10000);
	set("jingli",10000);
	set("neili", 42000);
  set("no_get",1);
  set("no_bark",1);
	set("inquiry", ([
		"胡一刀" : (: ask_huyidao :),
		"苗人凤" : (: ask_miaorenfeng :),
		"田归农" : (: ask_tian :),
		"天龙门" : (: ask_tian :),
		"比武" : (: ask_biwu :),
		"比试" : (: ask_biwu :),
		"20年前" : (: ask_biwu :),
		"决斗" : (: ask_biwu :),
		"胡斐" : (: ask_hufei :),
		"七星海棠" : (: ask_qixinghaitang :),
		"两页刀法" : (: ask_liangyedaofa :),
		"胡家刀法" : (: ask_hujiadaofa :),
		"真相"   : (: ask_xiadu :),
		"下毒"   : (: ask_xiadu :),
    "程灵素" : (: ask_cheng :),
	]));
	setup();
	set("chat_chance", 2);
	set("chat_msg", ({
		"阎基将一条带有巨毒的蛇放入竹篓里，“嘿嘿”的奸笑几声。\n",
		"阎基望了你一眼，低声说道：你面黄肌瘦，肾水亏空，是否．．．过度？\n",
	}) );
	carry_object("/clone/armor/cloth.c")->wear();
}

void init()
{
	::init();
	add_action("do_hit","hit");
}


int ask_biwu()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 不关我的事，不关我的事啊！都是“田归农”指使小人干的......");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh");
	  command("say 20年前的比武，其实我也不是很明白，但是胡大侠死在苗人凤手上，确是事实。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("consider");
	  command("say 我是乱中偷盗胡家秘籍，只是当时一片混乱，我全家被毁，我也是为了生计，别无他法。");
  	command("say 但是胡大侠当年豪气冲天，可惜小人苗人凤竟然使用毒剑，这段公案迟早有人要去还的。");
	  return 1;
  }
	command("heng");
	command("say 胡大侠当年豪气冲天，可惜小人苗人凤竟然使用毒剑，这段公案迟早有人要去还的。");
	return 1;
}

int ask_tian()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("fear "+me->query("id"));
	  command("say 都是“田归农”指使小人干的......这天杀的卑鄙小人！");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh");
	  command("say 田相公，原是天龙门掌门，当年苗胡比武期间，我曾见过一面，最近一直没有消息，天龙门也似乎灭迹江湖。");
	  return 1;
  }
	command("en");
	command("say 当年苗胡比武期间，我好像见过一面，那时年轻得很。最近好像早无音讯。不是很熟悉。");
	return 1;
}

int ask_miaorenfeng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"start"))
  {
	  command("fear "+me->query("id"));
	  command("say 我，我，苗大侠最近可好？...都是“田归农”指使小人干的......这天杀的卑鄙小人！");
	  return 1;
  }
  command("sigh");
	command("say 苗大侠，很久没有听过他的踪迹了，20年前有过一面而已。");
	return 1;

}
int ask_cheng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("fear "+me->query("id"));
	  command("say 程姑娘还在五毒教吧！");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"qixinghaitang"))
  {
	  command("fear "+me->query("id"));
	  command("say 程姑娘，别杀我，我什么都交出去了，刚说的也说了，饶了我吧！");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao2"))
  {
	  command("fear "+me->query("id"));
	  command("say 程姑娘，别杀我，我什么都交出去了，刚说的也说了，饶了我吧！");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
	  command("fear "+me->query("id"));
	  command("say 那丫头？和我什么关系！");
	  return 1;
  }
  command("nod");
	command("say 听说药王最得意的关门弟子，现在不知道在哪里。");
	return 1;
}
int ask_huyidao()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"start"))
  {
	  command("fear "+me->query("id"));
	  command("say 是我错了，害死了胡大侠，不过罪魁祸首是天田归农！");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh");
	  command("say 20年前的比武，其实我也不是很明白，但是胡大侠死在苗人凤手上，确是事实。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("consider");
	  command("say 我是乱中偷盗胡家秘籍，只是当时一片混乱，我全家被毁，我也是为了生计，别无他法。");
  	command("say 但是胡大侠当年豪气冲天，可惜小人苗人凤竟然使用毒剑，这段公案迟早有人要去还的。");
	  return 1;
  }
	command("heng");
	command("say 胡大侠当年豪气冲天，可惜小人苗人凤竟然使用毒剑，这段公案迟早有人要去还的。");
	return 1;
}
int ask_xiadu()
{
	object me = this_player();

  if(me->query(QUESTDIR2+"over"))
  {
	  command("fear "+me->query("id"));
          command("say 是我错了，害死了胡大侠，不过罪魁祸首是田归农指使我下毒的！");
	  return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"zhenxiang"))
  {
	  command("fear "+me->query("id"));
          command("say 是我错了，害死了胡大侠，不过罪魁祸首是田归农指使我下毒的！");
	  command("say 早一日晚上，胡大爷和金面佛同榻长谈，我在窗外偷听，后来给金面佛隔窗打了一拳，只打得眼青鼻肿，满脸鲜血！");
	  command("say 我就有些生气，第二天，正巧田归农过来给了我一包毒药，说是事成之后给我100两黄金，我也是该死，贪图这钱！");
	  command("say 那天晚上胡大爷与金面佛同房而睡，两人光明磊落，把兵刃都放在大厅之中。我取出那毒药悄悄去涂在两人刀剑之上。");
          command("say 是我错了，害死了胡大侠，不过罪魁祸首是田归农指使我下毒的！");
	  me->set_temp(QUESTDIR2+"over",1);
	  me->delete_temp(QUESTDIR2+"zhenxiang");
    me->start_busy(3);
    remove_call_out("move_fendi");
    call_out("move_fendi", 3, me);
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("consider");
	  command("say 20年前的比武，其实我也不是很明白，但是胡大侠死在苗人凤的毒剑上，确是事实。");
  	command("say 但是胡大侠当年豪气冲天，可惜小人苗人凤竟然使用毒剑，这段公案迟早有人要去还的。");
	  return 1;
  }
	command("heng");
  command("say 20年前的比武，其实我也不是很明白，但是胡大侠死在苗人凤的毒剑上，确是事实。");
 	command("say 但是胡大侠当年豪气冲天，可惜小人苗人凤竟然使用毒剑，这段公案迟早有人要去还的。");
	return 1;
}
void move_fendi(object me)
{
  if(!me) return;
  if(!me->query_temp(QUESTDIR2+"over")) return;
  if(!me->query_temp(QUESTDIR2+"move_fendi"))
  {
	  tell_object(me,HIC"你听完这段，可是惊心动魄，万万没有料到堂堂的辽东大侠竟然被一个郎中下毒害死，而指使人似乎早已不在人世。\n"NOR);
    tell_object(me,HIC"你暗想：这当务之急，恐怕是先告诉胡斐这事情的经过，只是胡家这所谓大仇也最终不了了之，的确出乎意料之外。\n"NOR);
     tell_room(environment(me),HIC"\n阎基似乎告诉了"+me->query("name")+"一些事情，"+me->query("name")+"显得有些焦急。\n"NOR, ({ me }));
     me->set_temp(QUESTDIR2+"move_fendi",1);
	 /*
     tell_room(environment(me),HIC""+me->query("name")+"疾步离开后山。\n"NOR, ({}));
    me->move("/d/miaojiang/slu1");
    tell_object(me,HIR"你还是加快速度，往胡斐的地方奔去。\n"NOR);
          tell_room(environment(me),HIC"突然一个身影掠过，原来是"+me->query("name")+"疾步离开。\n"NOR, ({ me }));
    me->move("/d/miaojiang/myp");
    tell_object(me,HIR"你还是加快速度，往胡斐的地方奔去。\n"NOR);
          tell_room(environment(me),HIC"突然一个身影掠过，原来是"+me->query("name")+"疾步离开。\n"NOR, ({ me }));
    me->move("/d/xiangyang/damen");
    tell_object(me,HIR"你稍微歇息一下。\n"NOR);
          tell_room(environment(me),HIC"突然一个身影掠过，原来是"+me->query("name")+"疾步离开。\n"NOR, ({ me }));
  	*/
    remove_call_out("move_fendi");
    call_out("move_fendi",5, me);
  }
  else
  {
    remove_call_out("move_fendi");
    tell_object(me,HIR"你稍微歇了一口气。\n"NOR);
	/*
    me->move("/d/huanghe/shulin2");
    tell_object(me,HIR"你还是加快速度，往胡斐的地方奔去。\n"NOR);
          tell_room(environment(me),HIC"突然一个身影掠过，原来是"+me->query("name")+"疾步离开。\n"NOR, ({ me }));
    me->move("/d/huanghe/shulin6");
    tell_object(me,HIR"你还是加快速度，往胡斐的地方奔去。\n"NOR);
	  tell_room(environment(me),HIC"突然一个身影掠过，原来是$N疾步离开。\n"NOR, ({ me }));
    me->move("/d/huanghe/fendi");
    tell_object(me,HIR"\n终于到了，你长叹一口气。\n"NOR);
          tell_room(environment(me),HIC"突然一个身影掠过，原来是"+me->query("name")+"疾步离开。\n"NOR, ({ me }));
		  */
    me->delete_temp(QUESTDIR2+"move_fendi");
  }
  return;
}

int ask_hujiadaofa()
{
	object me = this_player();
  if(me->query(QUESTDIR1+"over"))
  {
	  command("consider");
	  command("say 我是乱中偷盗胡家秘籍，只是当时一片混乱，我全家被毁，我也是为了生计，别无他法。");
	  return 1;
  }
	command("?");
  command("say 胡家刀法？在下从不使用刀法。");
	return 1;
}
int ask_hufei()
{
	object me = this_player();
  if(me->query(QUESTDIR1+"over"))
  {
	  command("fear "+me->query("id"));
	  command("say 虽然干了一场荒唐事，天可怜见胡大侠还剩下胡斐这个孩子。我真是后悔啊......");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& !me->query_temp(QUESTDIR1+"hufei") && !me->query_temp(QUESTDIR1+"liangye"))
  {
	  command("consider");
	  command("say 当年冤死的胡大侠的孩子好像叫胡斐，我已经有些忘记了。");
	  command("?");
	  command("say 这位大侠不知道我和提起这个干什么？");
	  me->set_temp(QUESTDIR1+"hufei",1);
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"hufei"))
  {
	  command("?");
	  command("say 我想起来了，确实叫胡斐，这位大侠不知道我和提起这个干什么？");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"liangye"))
  {
	  command("cry");
	  command("say 我是乱中偷盗胡家秘籍，只是当时一片混乱，我全家被毁，我也是为了生计，别无他法。");
	  return 1;
  }
	command("consider");
	command("say 当年冤死的胡大侠的孩子好像叫胡斐，我已经有些忘记了。");
	return 1;
}
int ask_liangyedaofa()
{
	object me = this_player();
	if(me->query_condition("killer"))
	{
	  command("fear "+me->query("id"));
    command("say 小心官府通缉！");
	  return 1;
	}
  if(me->query(QUESTDIR1+"over"))
  {
	  command("fear "+me->query("id"));
	  command("say 我是乱中偷盗胡家秘籍，只是当时一片混乱，我全家被毁，我也是为了生计，别无他法。");
	  command("say 虽然干了一场荒唐事，天可怜见胡大侠还剩下胡斐这个孩子。我真是后悔啊......");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& !me->query_temp(QUESTDIR1+"hufei") && !me->query_temp(QUESTDIR1+"liangye"))
  {
	  command("?");
	  command("say 我很少用刀的。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"hufei"))
  {
	  command("fear "+me->query("id"));
	  command("say 你，你是怎么知道的？嘿嘿，看来我只能让真相永远消失了。");
	  me->set_temp(QUESTDIR1+"liangye",1);
	  me->delete_temp(QUESTDIR1+"hufei");
	  this_object()->kill_ob(me);
	  me->kill_ob(this_object());
	  this_object()->start_busy(1);
	  me->start_busy(1);
    power_condition(me,this_object(),200+random(100));
    remove_call_out("kill_player");
    call_out("kill_player", 1, me);
  	tell_object(me,RED"\n你不由谈了口气，何必一定兵刃相见......\n"NOR);
	  this_object()->set("quest/try_fight",1);
	  this_object()->set("quest/try_fight_id",me->query("id"));
	  return 1;
  }
 	command("?");
	command("say 我很少用刀的。");
	return 1;
}
int ask_qixinghaitang()
{
	object obj,me = this_player();
  if(me->query(QUESTDIR3+"over"))
  {
	  command("? "+me->query("id"));
	  command("say 不在我这里了。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& (me->query_temp(QUESTDIR3+"qixinghaitang")||me->query_temp(QUESTDIR3+"jieyao2")))
  {
	  command("sigh "+me->query("id"));
	  command("say 不在我这里了。");
	  return 1;
  }

  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao1"))
  {
	  command("fear");
	  command("say 是程丫头让你来得？哼，能不能拿到要看你的实力了。");
  	tell_object(me,RED"\n你不由皱着眉头，这厮当真可恶......\n"NOR);
    power_condition(me,this_object(),300+random(50));
	  this_object()->kill_ob(me);
	  me->kill_ob(this_object());
	  this_object()->start_busy(1);
	  me->start_busy(1);
    remove_call_out("kill_player");
    call_out("kill_player", 1, me);
    obj=new(__DIR__"heiyiren");
    obj->set_name("石万嗔", ({ "shi wanchen", "shi" }));
    obj->set("title",HIR"毒手药王"NOR);
    obj->set("kill_id",me->query("id"));
    obj->set("type_speical","xx");
    obj->move(environment(me));
  	message_vision(HIC"\n突然从后山窜出一个人来，叫道：别怕，老阎，我来帮你！这小子，纯粹找死！\n"NOR,me);
	  this_object()->set("quest/try_fight",1);
	  this_object()->set("quest/try_fight_id",me->query("id"));
	  return 1;
  }

	command("?");
	command("say 我也在寻找七星海棠。");
	return 1;
}
void kill_player(object me)
{
	object ob=this_object();
  if(!me) return;
  if(environment(me)!=environment(this_object())) return;
  if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"liangyedaofa"))
  {
     if (!present("blade",ob))
	             carry_object(BINGQI_D("blade"))->wield();
	      else command("wield blade");
    return;
  }
  if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"getjieyao1"))
  {
    if (!present("blade",ob))
	             carry_object(BINGQI_D("blade"))->wield();
	      else command("wield blade");
    return;
  }
}

void kill_ob(object me)
{
	 command("sneer " + me->query("id"));
   COMBAT_D->do_attack(this_object(), me, this_object()->query_temp("weapon") );
   COMBAT_D->do_attack(this_object(), me, this_object()->query_temp("weapon") );
   COMBAT_D->do_attack(this_object(), me, this_object()->query_temp("weapon") );
	::kill_ob(me);
}

int do_hit(string arg)
{
         object me,ob;
         me=this_player();
         ob=this_object();
         if((arg==("yan"))||(arg==("yan ji"))){
           	command("sneer");
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	return 1;
         }
         return 0;
}

void unconcious()
{
  die();
}

void die()
{
	object me,obj,ob=this_object();
	if(ob->query("quest/try_fight"))
	{
	  command("ah");
	  if(ob->query("quest/try_fight_id"))
	  {
      remove_call_out("kill_player");
      ob->remove_all_killer();
      start_condition(ob);
	  	me=find_player(ob->query("quest/try_fight_id"));
	    ob->delete("quest/try_fight");
	    ob->delete("quest/try_fight_id");
	  	if(!me) return;
      me->remove_all_killer();
      if(environment(me)!=environment(this_object())) return;
      if(me->query(QUESTDIR1+"start")&& me->query_temp(QUESTDIR1+"liangye"))
      {

	         command("say 我错了，我错了......");
	         command("sorry");
        	 command("say 我是乱中偷盗胡家秘籍，只是当时一片混乱，我全家被毁，我也是为了生计，别无他法。\n");
        	 tell_object(me,HIY"\n"+ob->query("name")+"交给你两页纸，上面记载着胡家刀法。\n"NOR);
                 tell_room(environment(me),HIC"阎基好像交给"+me->query("name")+"什么东西，似乎是两页纸张。\n"NOR, ({ me }));
 	         obj=new(__DIR__"obj/paper");
           obj->set("owner",me->query("id"));
 	         obj->move(me);
           tell_object(me,HIC"\n你又询问了一些当时的情况，阎基当即简单说起了当时比武的经过......\n"NOR);
           tell_object(me,HIC"\n\n却说当年比武的第六天，胡一刀之妻竟然发现苗人凤的剑法破绽，按那剑法，苗人凤右手一剑斜刺，左手上扬，就与白鹤将\n"
        	                       "双翅扑开来一般，但胡一刀可以抢了先著，金面佛双手刚展开之时，被他左右连环两刀。出乎意料的是岂知金面佛的武功，\n"
        	                       "当真是出神入化，就在这危急之间，他双臂一曲，剑尖斗然刺向自己胸口。胡一刀大吃一惊，只道他比武输了，还剑自杀，\n"
        	                       "忙叫道：『"HIR"苗兄，不可"HIC"！』\n"NOR);
                 tell_room(environment(me),HIC"只见，阎基附在"+me->query("name")+"身边，低声说着什么，神色有些恍惚，似乎在回忆着往事，说话有时一顿一顿的。\n"NOR, ({ me }));
        	 command("sigh");
        	 tell_object(me,HIC"\n殊不知金面佛的剑尖在第一日比武之时就已用手指拗断了的，剑尖本身是钝头，他再胸口一运气，那剑刺在身上，竟然反弹出\n"
        	                     "来。但见长剑一弹，剑柄蹦将出来，正好点在胡一刀胸口的『神藏穴』上，胡一刀登时软倒。\n\n"NOR);
        	 tell_object(me,HIC"金面佛伸手扶住，叫道：『"HIR"得罪"HIC"！』\n"NOR);
        	 tell_object(me,HIC"胡一刀笑道：『"HIR"苗兄剑法，鬼神莫测，佩服佩服。"HIC"』\n"NOR);
        	 tell_object(me,HIC"金面佛道：『"HIR"若非胡兄好意关心，此招何能得手？"HIC"』\n\n"NOR);
        	 tell_object(me,HIC"两人坐在桌边一口气乾了三碗烧酒。胡一刀哈哈一笑，提起刀来往自己颈中一抹，咽喉中喷出鲜血，伏桌而死。夫人跟着也自杀了。\n\n"NOR);
        	 tell_object(me,HIG"这段往事听来当真一波三折，你确实没有料到其中如此曲折，至于两人相继自杀更是想不明白。你默然了一会，放开阎基。\n"NOR);
        	 tell_object(me,HIG"你深深地叹了口气。\n"NOR);
                 tell_room(environment(me),HIC""+me->query("name")+"深深地叹了口气。\n"NOR, ({ me }));
        }
        if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"jieyao1"))
        {
	         command("say 我错了，我错了......");
	         command("sorry");
        	 command("say 我还给程丫头就是，犯不着为这个大打出手。");
        	 tell_object(me,HIW"\n"+ob->query("name")+"交给你一株七星海棠。\n"NOR);
                 tell_room(environment(me),HIC"阎基交给"+ob->query("name")+"一株七星海棠。\n"NOR, ({ me }));
 	         obj=new(__DIR__"obj/qixinghaitang");
           obj->set("owner",me->query("id"));
 	         obj->move(me);
 	         tell_object(me,HIR"\n你上前喝道：“"+ob->query("name")+"，那也不能饶你。”当即内力一松，"+ob->query("name")+"竟然晕了过去，你顺势跟上一掌。\n"NOR);
 	         me->delete_temp(QUESTDIR3+"jieyao1");
 	         me->set_temp(QUESTDIR3+"qixinghaitang",1);
 	         tell_room(environment(me),HIC"突然阎基气血似乎不顺，双脚一软，径直瘫在地上。\n"NOR, ({ me }));
 	         command("inn "+me->query("id"));
 	         if(obj=present("shi wanchen",environment(me)))
 	         {
 	         	message_vision(HIC"\n$N对$n叫道：“你等着，我马上去找救兵来！”转身几个起落就不见了。\n"NOR,obj,ob);
 	         	command("why "+obj->query("id"));
 	         	destruct(obj);
 	         }
 	         ob->unconcious();
        }
      }
	  }
  else
  {
	command("why");
	::die();
  }
}
int start_condition(object ob)
{
	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("unarmed", 150);
	set_skill("blade",150);
	set_skill("hujia-daofa",150);
	set_skill("huagong-dafa",150);
	map_skill("force","huagong-dafa");
	map_skill("blade","hujia-daofa");
	set("combat_exp", 300000);
	set("max_qi", 3000);
	set("max_jing", 1000);
	set("eff_jingli",1000);
	set("max_neili", 2100);
	set("qi",30000);
	set("jing",1000);
	set("jingli",1000);
	set("neili", 4200);
  return 1;
}
int power_condition(object me,object ob,int p)
{
	  int i;
    if(environment(me)!=environment(ob)) return 0;
    if (!present("blade",ob))
	    carry_object(BINGQI_D("blade"))->wield();
	  else command("wield blade");
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
	  ob->set_skill("xuantian-wuji",i+random(50));
	  ob->set_skill("hujia-daofa",i+random(50));
	  i=me->query("combat_exp");
	  ob->set("combat_exp",i);
	  i=me->query("neili");
	  if(i<12000) i=12000;
	  ob->set("neili", i);
	  i=me->query("max_neili");
	  if(i<6000) i=6000;
	  ob->set("max_neili", i);
  	i=me->query("max_qi");
	  ob->set("max_qi", i*(1+random(2)));
 	  ob->set("eff_qi", ob->query("max_qi"));
 	  ob->set("qi", ob->query("max_qi"));
    return 1;
}
