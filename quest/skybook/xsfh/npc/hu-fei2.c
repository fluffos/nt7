//hufei.c
//by tangfeng@SJ
//较量和胡家刀法的设定有些不好，重新修改，类似擂台比武，这样避免死亡
//胡家刀法skills既然完成，武功部分重新设定
// Update By lsxk@hsbbs add通宝物品提高解quest几率 2007/7/20
// By Spideiri@ty 加入天赋系统
inherit F_MASTER;
inherit NPC;
//inherit FIGHTER;
#include <ansi.h>
//inherit F_SSERVER;

#define QUESTDIR "quest/雪山飞狐/"
#define QUESTDIR1 "quest/雪山飞狐/两页刀法篇/"
#define QUESTDIR2 "quest/雪山飞狐/复仇篇/"
#define QUESTDIR3 "quest/雪山飞狐/解药篇/"
#define QUESTDIR4 "quest/雪山飞狐/武功/"

//int do_halt1(string arg);
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
int killing();
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
	    "辽东大侠胡一刀的儿子。\n"
	    "这人满腮虬髯，根根如铁，一头浓发，却不结辫，横生倒竖般有如乱草。"NOR);
	set("str", 25+random(30));
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("unique", 1); //千万别出问题阿，这个设定
    set(QUESTDIR4+"hujiadaofa",1);
    set(QUESTDIR4+"lengquanshengong_teach",1);
	set_skill("force", 300);
    set("no_get", 1);
    set("no_bark", 1);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("blade", 300);
	set_skill("cuff",300);
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
  set_skill("lengquan-shengong",300);
	set_skill("hujia-daofa",300);
	map_skill("force","lengquan-shengong");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("blade","hujia-daofa");
	map_skill("parry","hujia-daofa");
	set("double_attack",1);
    prepare_skill("cuff", "zhentian-quan");
	set("combat_exp", 2000000);
	set("max_qi", 30000);
	set("max_jing", 30000);
	set("max_neili", 5000);
	set("eff_jingli",30000);
	set("qi",30000);
	set("jing",30000);
	set("jingli",30000);
	set("neili", 5000);
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
       (: exert_function, "lengquan" :),
       (: perform_action, "blade.feidao" :),
       (: perform_action, "blade.luandao" :)
     }));
    set("inquiry", ([
    "胡一刀" : (: ask_huyidao :),
    "hu yidao" : (: ask_huyidao :),
    "胡家刀法" : (: ask_hujiadaofa :),
    "hujia-daofa" : (: ask_hujiadaofa :),
    "两页刀法" : (: ask_liangyedaofa :),
    "较量" : (: ask_jiaoliang :),
    "切磋" : (: ask_jiaoliang :),
    "比武" : (: ask_biwu :),
    "20年前" : (: ask_biwu :),
    "比试" : (: ask_biwu :),
    "决斗" : (: ask_biwu :),
    "治疗" : (: ask_zhiliao :),
    "解药" : (: ask_zhiliao :),
    "苗若兰" : (: ask_miaoruolan :),
    "苗人凤" : (: ask_miaorenfeng :),
    "阎基" : (: ask_yanji :),
    "程灵素" : (: ask_cheng :),
    "田归农" : (: ask_tian :),
    "天龙门" : (: ask_tian :),
    "家仇" : (: ask_jiachou :),
     "报仇" : (: ask_jiachou :),
    "仇恨" : (: ask_jiachou :),
    "复仇" : (: ask_jiachou :),
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
  if (!this_object()->query_temp("biwu")&& interactive(ob = this_player()) ) {
       remove_call_out("greeting");
       call_out("greeting", 2, ob);
  }
  add_action("do_answer","answer");
  add_action("do_hit", "hit");
}

void greeting(object me)
{
  int shen,i;
  if(!me) return;
  if(environment(me)!=environment(this_object())) return;
  shen = me->query("shen");
  if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"over")&&!me->query(QUESTDIR2+"over"))
  {
	me->start_busy(1);
	tell_object(me,CYN"\n你急忙在胡斐的耳边悄声地将真相告诉胡斐，胡斐闻言更是泣不成声....\n\n"NOR);
    tell_room(environment(me),HIC"\n只见"+me->query("name")+"急步赶来，在胡斐的耳边悄声地说着什么。\n\n"NOR, ({ me }));
  	command("chat* cry");
	tell_room(environment(me),HIC"\n胡斐突然大哭起来，悲叫道：“田归农！”，似乎有不解之仇。"NOR, ({}));
    tell_object(me,HIW"\n“田归农！”只是这段杀父之仇，因为天龙门的消飞云散，这段恩怨也只能不了了之。\n"NOR);
  	tell_object(me,HIG"你不知道是喜是悲，想想这个结果对胡斐来说也许也是个了结。\n\n"NOR);
  	command("whisper "+me->query("id")+" 苗大侠，不知道毒发如何？");
  	tell_object(me,HIC"你点头道：我马上去苗家庄，你心情不定，还是先歇息为妙。\n"NOR);
	tell_room(environment(me),HIC""+me->query("name")+"向胡斐点了点头，神色很是着急。\n"NOR, ({}));
    //设定标记
    me->set(QUESTDIR2+"over",1);
    me->delete_temp(QUESTDIR2+"over");
    me->set(QUESTDIR+"time",time());
    me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
    //奖励
    me->add("combat_exp",me->query_skill("force")*3/2);
   	i=180+random(40);
   	me->add("mana",i);
    tell_object(me,YEL"\n你于"+NATURE_D->game_time()+"解开雪山飞狐复仇篇，获得"+(int)me->query_skill("force")*3/2+"点经验奖励、"+i+"点声望。\n"NOR);
    log_file("quest/FEIHU", sprintf("%s(%s) 复仇篇完成。奖励：%d点经验，%d点声望。\n", me->name(1),me->query("id"), me->query_skill("force")*3/2,i ) );
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
  	message_vision(YEL"$N脸上露出怀念之情。\n"NOR,this_object());
	  command("say 真的感谢程姑娘，要不是她恐怕我抱憾终生。");
	  command("think");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& me->query_temp(QUESTDIR3+"getjieyao"))
  {
  	message_vision(YEL"$N脸上露出怀念之情。\n"NOR,this_object());
	  command("suicide1");
	  command("say 真的感谢程姑娘，我们还是赶快去救治苗大侠吧。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start")&& (me->query_temp(QUESTDIR3+"jieyao2")||me->query_temp(QUESTDIR3+"qixinghaitang")))
  {
  	message_vision(YEL"$N脸上露出怀念之情。\n"NOR,this_object());
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
    message_vision(YEL"$N脸上露出怀念之情。\n"NOR,this_object());
	  command("blush");
	  command("say 程姑娘当年我与她有过一面之交，只是现在身在何处，不很清楚......");
	  command("sigh");
	  return 1;
  }
  message_vision(YEL"$N脸上露出怀念之情。\n"NOR,this_object());
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
  message_vision(YEL"$N脸上露出不解之情。\n"NOR,this_object());
	command("say 当年我爹爹和号称“打遍天下无敌手”的苗人凤在此比武，苗人凤以毒刀\n将我爹爹害死，我娘自刎殉夫。待我遇见那杀父仇人，定将他碎尸万断......不过，\n"
          "他二人豪气相侔，相敬相重，苗人凤怎么会下如此黑手？");
	command("consider");
	return 1;
}

int ask_hujiadaofa()
{
	object me = this_player();
	object ob = this_object();
	int i,lv;
	if(me->query_condition("killer"))
	 {
	   command("fear "+me->query("id"));
     command("say 小心官府通缉！");
	   return 1;
   }
    if(!me->query(QUESTDIR4+"hujiadaofa") && me->query("combat_exp")<= 2000000)
   {
     command("@@ "+me->query("id"));
     command("say 以你当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
     return 1;
   }
	if(me->query(QUESTDIR2+"start") && !me->query(QUESTDIR3+"over"))
  {
	  command("shake "+me->query("id"));
	  command("say 现在时间紧急，这刀法还是以后切磋吧。");
	  return 1;
  }

  if(me->query(QUESTDIR4+"hujiadaofa"))
  {
   if(me->query("potential")<= 5)
   {
	  command("kick "+me->query("id"));
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
    me->improve_skill("hujia-daofa", 150+random(me->query_int()*2));
    me->improve_skill("blade", random(me->query_int())/2);
    //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        lv = me->query("max_pot")-100;
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了胡家刀法的精华所在。\n"NOR);
            me->set_skill("hujia-daofa",lv);
            }

    return 1;
   }
  }
  //600sec招待一次玩家
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 有些累了，这刀法还是以后切磋吧。");
	  return 1;
  }
  //非vip玩家，只能失败三次
  if(me->query(QUESTDIR4+"hujiadaofa_fail")>=3 && me->query("registered")<3)
  {
	  command("shake "+me->query("id"));
	  command("say 现在时间紧急，这刀法还是以后切磋吧。");
	  return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔1M
	//注意这个标记和苗家剑法使用同一个标记。
	if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到这里吧，明天吧。");
	  return 1;
  }
   if(me->query(QUESTDIR4+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"combat_exp")<500000 &&!me->query("cw_exp"))
	{
	  command("look "+me->query("id"));
	  command("say 以你当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	command("nod "+me->query("id"));
    message_vision(HIB"\n$n突然运起独门内功冷泉神功，只感觉刀势无风自起。\n"NOR, me, ob);
    //胡斐忙碌
    ob->set_temp("busy",1);
    remove_call_out("busy_pass");
	call_out("busy_pass",600, ob);
    power_condition(me,ob,300+random(100));
	  for ( i = 0; i < 6+random(6);i++)
	  {
         if (!present(me,environment(ob)) || me->query("qi") <= me->query("max_qi")/20 ||me->query("eff_qi") <= me->query("max_qi")/20 || me->query("jing") <= 50 || me->query("jingli") <= 50)
         {
            if(random(2))command("sneer");
            else if(random(2)) command("say 这位"+RANK_D->query_respect(me) +"武功未能返璞归真，只怕难以领悟胡家刀法的绝技！");
         	  me->reincarnate();
            return 1;
         }
         else
         {
            if(random(2)) command("sneer "+me->query("id"));
            else command("say 小心了，还有一招。");
            ob->delete_temp("quest/雪山飞狐/武功/lengquan");
            COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
            ob->set_temp("quest/雪山飞狐/武功/lengquan",1);
          }
    }
    ob->delete_temp("quest/雪山飞狐/武功/lengquan");
    start_condition(ob);
    command("smile "+me->query("id"));
    message_vision(HIC"\n\n犹如电光雷闪，一晃数招已过，$n微笑着对$N说道：「刚才我使用的招数可看清楚了？」\n"NOR,me,ob);
    //标记时间和经验
    me->set(QUESTDIR4+"time",time());
    me->set(QUESTDIR4+"combat_exp",me->query("combat_exp"));
    tell_object(me,YEL"你拼命地回忆瞬间交手的一幕，回忆着刚才的招数，你开始认真思索着.........\n"NOR);
    remove_call_out("thinking");
		call_out("thinking",0, me, ob);
    me->start_busy(1);
	  return 1;
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("shout");
	  if(random(2)) command("say 可惜我武功未能圆通，不能为报父仇，这胡家刀法总是不能返璞归真。");
	  else command("say 苗人凤听说武功号称打遍天下，自是厉害，可惜我胡家刀法秘籍竟有残缺，因此在下武功终未大成。");
	  return 1;
  }
  if(me->query_temp(QUESTDIR1+"jiachou"))
  {
 	  command("heng");
	  command("say 我胡家刀法确是一等一的武功，只是爹爹留给我秘籍竟然缺了两页，缺了扎根基的入门功夫，缺了拳法刀法的总诀。");
	  command("say 这些年来，无论怎么用功，总是难以融会贯通，听说苗人凤号称打遍天下无敌手，可惜我胡家刀法秘籍竟有残缺，不是对手。");
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

int busy_pass(object ob)
{
	if(!ob) return 0;
	if(ob->query_temp("busy")) ob->delete_temp("busy");
	if(ob->query("busy")) ob->delete("busy");
   remove_call_out("busy_pass");
  message_vision(HIC"\n$N伸了伸懒腰。\n"NOR,ob);
  return 1;
}

int thinking(object me, object ob)
{
	int i,p;
	if(!me) return 0;
  if(environment(me)!=environment(this_object()))
  {
  	start_condition(ob);
    if(random(2)) message_vision(HIC"\n$N伸了伸懒腰，道：$n竟然临阵逃脱，没料得蠢材一个。\n"NOR,ob,me);
    else message_vision(HIC"\n$N疑惑问道：夷~~~人呢？$n，人呢？\n"NOR,ob,me);
  	return 1;
  }

  if(me->query_temp(QUESTDIR4+"thinking")<(3+random(3)))
	{
		me->add_temp(QUESTDIR4+"thinking",1);
    if(random(2)) tell_object(me,HIG"\n你努力地回忆刚才的每一招每一式，似有无数人影交相互动，每一招每一式你都努力去看清楚...\n"NOR);
    else tell_object(me,HIY"\n突然间，你似乎抓到了什么，你努力地回忆刚才的每一招每一式，你能充分感觉招数的凌厉和急速...\n"NOR);
          tell_room(environment(me),HIC""+me->query("name")+HIC"似乎在思索着什么，一服愁眉不展的样子。\n"NOR, ({}));
	  remove_call_out("thinking");
		call_out("thinking",4+random(3), me, ob);
	}
	else
	{
	  //难度降低，毕竟单纯的胡家刀法威力一般
    //如果有特殊通宝物品，略微提高成功几率。  by lsxk@hsbbs 2007/7/20
      if(me->query_temp("sj_credit/quest/public/hjdf"))
          p=random(me->query("kar")+10);
      else
		p=random(me->query("kar"));
      me->delete_temp("sj_credit/quest/public/hjdf");
          if(p> 27 && me->query("kar")<31 && QUEST_D->questing(me,1,0,1))
      {
       tell_object(me,HIG"\n你明悟其中，突然间明白了一切。\n"NOR);
       message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me);
       command("ah");
       command("congra "+me->query("id"));
       command("chat* congra "+me->query("id"));
       tell_object(me,HIR"你听了胡斐的指点，对胡家刀法的奥妙似乎有些心得。\n"NOR);
       tell_object(me,HIR"只是你发现这胡家刀法还需要冷泉神功才能发挥全效。\n"NOR);
       me->set(QUESTDIR4+"hujiadaofa",1);
       me->delete_temp(QUESTDIR4+"thinking");
   	   i=180+random(40);
   	   me->add("mana",i);
  	   tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解开雪山飞狐胡家刀法篇，并获得"+i+"点声望。\n\n"NOR);
       log_file("quest/FEIHU", sprintf(HIR"%s(%s) 失败%d次后揭开胡家刀法，获得%d点声望。富源：%d;随机取值：%d。\n"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"hujiadaofa_fail"), i,me->query("kar"),p ) );
    }
    else
    {
       tell_object(me,HIG"\n你脑海里似乎抓住了什么，可是依然不是很明白。\n"NOR);
       command("poor "+me->query("id"));
       message_vision(HIC"\n$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n"NOR,me);
	   me->add(QUESTDIR4+"hujiadaofa_fail",1);
	   log_file("quest/FEIHU", sprintf(HIR"%s(%s) 胡家刀法失败次数：%d次,富源：%d；随机取值%d。\n"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"hujiadaofa_fail"),me->query("kar"),p) );
       if(me->query(QUESTDIR4+"hujiadaofa_fail")>=3 && me->query("registered")<3)
       {
      	tell_object(me,HBYEL"\n很遗憾你于"+NATURE_D->game_time()+"最后一次尝试揭开雪山飞狐胡家刀法，却没有成功。\n\n"NOR);
        log_file("quest/FEIHU", sprintf("%s(%s) 最后一次尝试揭开雪山飞狐胡家刀法，却没有成功。经验 %d。\n", me->name(1),me->query("id"), me->query("combat_exp") ) );
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
  	command("say 爹爹的死我这就去找苗人凤算账去！");
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
	  command("say 所谓父仇不共戴天，既然知道杀害我爹的凶手，就算我这身武功不济，也决不苟生。");
	  if(!me->query_temp(QUESTDIR2+"answer")){
		  //询问家仇是涉及quest的第一二步，增加时间间隔半天，经验需要间隔500K
		  if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<43200)
		  {
			  command("cry "+me->query("id"));
			  command("say 不过，今天已经很麻烦了"+me->query("name")+"了，复仇的事情也不急在一时。");
			  return 1;
		  }
                  if(me->query(QUESTDIR+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000 && !me->query("cw_exp"))
		  {
			  command("look "+me->query("id"));
			  command("say 不过，以你当前的经验恐怕还是难以有所帮助，还是抓紧去练功去吧。");
			  return 1;
		  }
		  if(me->query(QUESTDIR4+"win_hu") || me->query(QUESTDIR4+"fight_hu")>=3)
		  {
			  command("look "+me->query("id"));
			  command("sigh");
			  if(!me->query(QUESTDIR4+"win_hu"))
				  command("whisper "+me->query("id")+" 这位"+RANK_D->query_respect(me) +"武功也算不错，不知道是否愿意帮忙？");
			  else command("whisper "+me->query("id")+" 这位"+RANK_D->query_respect(me) +"，武功超绝，不知道是否愿意帮忙？");
			  me->set(QUESTDIR+"time",time());
			  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
			  command("addoil "+me->query("id"));
			  tell_object(me,HIG"回答命令answer yes 或者answer no\n"NOR);
			  me->set_temp(QUESTDIR2+"answer_",1);
			  log_file("quest/FEIHU", sprintf("%s(%s) 决定进入苗家庄。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
			  return 1;
		  }
		  else
		  {
			  command("look "+me->query("id"));
			  command("say 你连我都不是对手，如何帮我复仇？");
			  return 1;
		  }
	  }
	  else
	  {
		  command("look "+me->query("id"));
		  command("thank "+me->query("id"));
		  command("say 只要这位"+RANK_D->query_respect(me) +"能够帮忙，在下不胜感激。其实我也不能确认这事情原委。");
	  }
	  return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {

	  command("say 我一直怀疑他就是杀害我爹的凶手，只是苗家素有侠名，所以不敢确认，如今真相大白。");
	  command("say 所谓父仇不共戴天，既然知道杀害我爹的凶手，就算我这身武功不济，也决不敢偷生了。");
	  command("sigh");
	    //询问家仇是涉及quest的第一二步，增加时间间隔半天，经验需要间隔500K
       if(me->query(QUESTDIR+"time") && time()-me->query(QUESTDIR+"time")<43200)
	   {
		   command("cry "+me->query("id"));
		   command("say 不过，今天已经很麻烦了"+me->query("name")+"了，复仇的事情也不急在一时。");
		   return 1;
	   }
           if(me->query(QUESTDIR+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000 && !me->query("cw_exp"))
	   {
		   command("look "+me->query("id"));
		   command("say 不过，以你当前的经验恐怕还是难以有所帮助，还是抓紧去练功去吧。");
		   return 1;
	   }
        //必须胜过hu,或者比试三场之后
	   if(me->query(QUESTDIR4+"win_hu") || me->query(QUESTDIR4+"fight_hu")>=3)
       {
   		   command("look "+me->query("id"));
		   command("sigh");
		   if(!me->query(QUESTDIR4+"win_hu"))
			   command("whisper "+me->query("id")+" 这位"+RANK_D->query_respect(me) +"武功也算不错，不知道是否愿意帮忙？");
		   else command("whisper "+me->query("id")+" 这位"+RANK_D->query_respect(me) +"，武功超绝，不知道是否愿意帮忙？");
		   me->set(QUESTDIR+"time",time());
		   me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));

		   tell_object(me,HIG"回答命令answer yes 或者answer no\n"NOR);
		   command("addoil "+me->query("id"));
		   me->set_temp(QUESTDIR2+"answer_",1);
		   me->set(QUESTDIR2+"start",1);//?? 怎么有玩家没有成功??
		   log_file("quest/FEIHU", sprintf("%s(%s) 决定进入苗家庄。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		   return 1;
	   }
	   else
	   {
		   command("look "+me->query("id"));
		   command("say 你连我都不是对手，如何帮我复仇？");
		   return 1;
	   }
  }
  if(me->query(QUESTDIR1+"start"))
  {
	  command("shout");
	  command("say 我一直怀疑苗人凤就是杀害我爹的凶手，只是他素有侠名，所以不敢确认。");
	  return 1;
  }
  if(me->query_temp(QUESTDIR1+"jiachou"))
  {
    message_vision(YEL"$N脸上露出不解之情。\n"NOR,this_object());
	  command("consider");
	  command("say 我真的不明白，想不通这其中的变化，只可惜我爹妈死得不明不白。");
	  return 1;
  }

  message_vision(YEL"$N脸上露出不解之情。\n"NOR,this_object());
	command("say 当年我爹爹和号称“打遍天下无敌手”的苗人凤在此比武，苗人凤以毒刀\n"
"  将我爹爹害死，我娘自刎殉夫。待我遇见那杀父仇人，定将他碎尸万断......不过，\n"
"  他二人豪气相侔，相敬相重，苗人凤怎么会下如此黑手？");
	command("consider");
	me->set_temp(QUESTDIR1+"jiachou",1);
  me->set(QUESTDIR+"time",time());
  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
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
	  me->set_temp(QUESTDIR2+"answer",1);
	}
	else
	{
    tell_object(me,CYN"\n你惊异地说道：我却有些怀疑，苗大侠怎么可能是凶手呢！不是算为你，我也要去一次苗家庄吧！\n"NOR);
	  me->set_temp(QUESTDIR2+"answer",1);
	}
	return 1;
}

int ask_jiaoliang()
{
	object me = this_player();
	object ob = this_object();
	object room;
	mapping mp;
	int i;
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
     command("say 小心官府通缉！");
	   return 1;
	}
  if( mapp(mp = me->query_conditions_by_type("poison")) && sizeof(mp)>0 )
	{
	   command("poor "+me->query("id"));
     command("say 你还是先治好你的病再来切磋吧！");
	   return 1;
	}
  if( mapp(mp = me->query_conditions_by_type("killer")) && sizeof(mp)>0 )
	{
	   command("sigh "+me->query("id"));
     command("say 你还是先解决了你的个人恩怨再来切磋吧！");
	   return 1;
	}
  if(!me->query(QUESTDIR3+"over") && me->query(QUESTDIR2+"start"))
  {
	  command("shake "+me->query("id"));
	  command("say 现在时间紧急，还是先治疗苗大侠要紧。");
	  return 1;
  }
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 刚切磋完，以后切磋吧。");
	  return 1;
  }
  //普通玩家三次,
   if(me->query(QUESTDIR4+"fight_hu")>=3 && me->query("registered")<3)
  {
	  command("shrug "+me->query("id"));
	  command("say 天色不早了，这刀法还是以后切磋吧。");
	  return 1;
	}

	//较量增加时间间隔3个小时。
  if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<(3600*3))
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到这里吧，稍后吧。");
	  return 1;
  }
        if((me->query(QUESTDIR4+"fight_hu")>=3 && me->query(QUESTDIR4+"fight_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"fight_exp")<500000 && !me->query("cw_exp"))
                ||(me->query(QUESTDIR4+"fight_hu")<3 &&me->query(QUESTDIR4+"fight_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"fight_exp")<100000)&& !me->query("cw_exp"))
	{
		command("shake "+me->query("id"));
		command("say 你武功没什么大的变化，还是抓紧练武去吧。");
		return 1;
	}
  //经验太差的直接让他昏倒，嘿嘿
  if(random(me->query("combat_exp"))<random(ob->query("combat_exp")/2) && !wizardp(me))
  {
	  for ( i = 0; i < 1+random(3);i++)
	  {
	     COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
    }
    return 1;
  }
  if(me->query(QUESTDIR1+"over"))
  {
	  command("nod "+me->query("id"));
    message_vision(HIY"\n$n突然运起独门内功冷泉神功，只感觉刀势无风自起。\n"NOR, me, this_object());
    //玩家最好武功在400等级以上，纵然如此还是比较危险。
    power_condition(me,ob,300+random(100));
    //胡斐和玩家将进入另外一个房间
    if (!(room = find_object("/d/huanghe/lianwuchang")))
       room = load_object("/d/huanghe/lianwuchang");
    if( !room )
 	  {
	     command("shake "+me->query("id"));
	     command("say 暂时没有空余的场地较量，稍后吧，或者通知巫师一下。");
	     return 1;
    }
    if(room->query_temp("biwu"))
 	  {
	     command("shake "+me->query("id"));
	     command("say 暂时没有空余的场地较量，稍后吧，或者通知巫师一下。");
	     return 1;
    }
    //标志
    me->set(QUESTDIR4+"time",time());
	me->set(QUESTDIR4+"fight_exp",me->query("combat_exp"));
    me->set_temp(QUESTDIR4+"fight_id",ob->query("id"));
    me->add(QUESTDIR4+"fight_hu",1);
    ob->set_temp("busy",1);
    ob->set_temp("biwu",1);
	  ob->set_temp("quest/try_fight_id",me->query("id"));

    message_vision(HIY"$N向$n一招手道：“且随我来”，$N和$n急急忙忙地离开坟地。\n"NOR, ob,me);
    ob->move(room);
    me->move(room);
    message_vision(YEL"$N急急忙忙地来到练武场。\n"NOR, ob);
    message_vision(YEL"$N急急忙忙地来到练武场。\n"NOR, me);
	  command("sneer");
    remove_call_out("busy_pass");
		call_out("busy_pass",600, ob);
    me->start_busy(1);
    ob->start_busy(1);
  log_file("quest/FEIHU", sprintf("%s(%s) 决定再次和胡斐较量。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
	  return 1;
  }
	command("say 想和我比试？看好了！");
  power_condition(me,ob,250+random(200));
	for ( i = 0; i < 2+random(3);i++)
	{
	     COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);
  }
	command("sneer");
	start_condition(ob);
	return 1;
}

int ask_liangyedaofa()
{
	object me = this_player();
  if(me->query(QUESTDIR1+"over"))
  {
  	command("thank "+me->query("id"));
	  command("say 感谢"+RANK_D->query_respect(me) +"帮我找到这两页刀法，我才能将胡家刀法融会贯通。");
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
    message_vision(HIC"$N缓缓地摇了摇头，叹气道：恩恩怨怨何时了。\n"NOR, me);
	  return 1;
  }
	command("say 听说是上任天龙门掌门，很久不知下落了。现在天龙门大不如以前了。");
	return 1;
}

int accept_object(object who, object ob,object me)
{
	if(who->query_condition("killer"))
	{
	   command("shake "+who->query("id"));
     command("say 你目前被官府通缉，我如何敢受"+ob->name()+"！");
	   return 0;
	 }
	 if(ob->query("id")=="liangye daofa")
   {
   	 command("ah "+(string)who->query("id"));
     if(who->query_temp(QUESTDIR1+"liangye") && who->query(QUESTDIR1+"start"))
     {
     	command("jump "+(string)who->query("id"));
      tell_object(who,HIC"\n你把两页刀法将给胡斐。胡斐仔细地看了两遍，不由惊叫起来，“正是这两页刀法，不是大侠何处得来？”\n"NOR);
      tell_object(who,HIC"你简单说了一下你去苗疆；却见胡斐傻傻地盯着这两页刀法，不由自主地演练起来，全然忘记你的存在。\n"NOR);
	    tell_room(environment(who),HIC"\n胡斐似乎从"+who->query("name")+"拿到一本武功秘籍，竟然当场演练起来。\n"NOR, ({ who }));
     	who->start_busy(1);
      remove_call_out("telltruth");
      call_out("telltruth",6, who);
     }
     else  command("thank "+(string)who->query("id"));
     call_out("destroying", 1, ob);
     return 1;
   }
    else
   {
     command("? "+(string)who->query("id"));
     return 0;
   }
}
void destroying(object obj)
{
        if(!userp(obj)) destruct(obj);
        return;
}
void telltruth(object me)
{
	    int i;
	    if(!me) return;
	    if(environment(me)!=environment(this_object()))
	    {
   	    message_vision(HIB"\n$n突然抬起头来，疑惑问道：“$N已经走了？我还没有好好感谢呢。”\n"NOR, me, this_object());
	    	return;
	    }
      if(!me->query_temp(QUESTDIR1+"liangye")) return;
     	command("haha");
     	command("say 不错就是它，正是我胡家刀法无法圆通的缺陷所在！");
     	tell_object(me,YEL"\n你看胡斐练得差不多，同时把从阎基那里听来的关于20年前比武的一些信息告诉胡斐，从比武到最后，最\n"NOR);
     	tell_object(me,YEL"后因为胡一刀妄想破解“提撩剑白鹤舒翅”结果不敌而自杀。说了好一会，才说完。\n\n"NOR);
	    tell_room(environment(me),HIC"\n"+me->query("name")+"似乎悄悄告诉胡斐一些事情。\n"NOR, ({}));
     	command("bite");
     	command("say");
     	command("say 无论如何，看来爹爹死在苗人凤手下千真万确。我的胡家刀法终于能够返璞归真，既然苗人凤\n就是凶手，就算我武功不济，也必保此仇！");
      me->set(QUESTDIR1+"over",1);
   	  me->add("max_neili",me->query_skill("force")/3);
          me->add("combat_exp",me->query_skill("force")*2);
      i=random(40)+80;
      me->set(QUESTDIR+"time",time());
      me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
      me->add("mana",i);
          tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解开雪山飞狐两页刀法篇，获得"+(int)me->query_skill("force")/3+"点最大内力、"+((int)me->query_skill("force")*2)+"点经验奖励以及"+i+"点声望。\n\n"NOR);
      log_file("quest/FEIHU", sprintf("%s(%s) 两页刀法篇完成。获得%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), me->query_skill("force")/3,me->query_skill("force")*2 ,i) );
     	me->delete_temp(QUESTDIR1+"liangye");
      return;
}
void kill_ob(object me)
{
	command("sneer " + me->query("id"));
  power_condition(me,this_object(),300+random(100));
  remove_call_out("killing");
	call_out("killing", 2);
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
	 ob->set("eff_qi", 30000);
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
          ob->set("max_qi", i*(6+random(3))/4);
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
int killing()
{
	int i;
	object *enemy,ob,me;

	ob=this_object();
	enemy = ob->query_enemy();
	if( !enemy || !arrayp(enemy) )
	{
		 remove_call_out("killing");
	   start_condition(ob);
  	 return 0;
  }
	i = sizeof(enemy);
	if(i>4) i=4;
  if(i>0) me=enemy[random(i)];
  else
  {
		 remove_call_out("killing");
	   start_condition(ob);
  	 return 0;
  }
  if(!me || !ob->is_fighting(me) )
	{
		 remove_call_out("killing");
	   start_condition(ob);
  	 return 0;
  }

  if (!present("blade",ob))
  {
	  message_vision(HIR"\n$N身行向后一跃，不知道从哪里竟然又拿出一把钢刀。\n"NOR,ob);
  	carry_object(BINGQI_D("blade"))->wield();
  }
	else command("wield blade");
  i=ob->query_temp("pfm");

 //zongjue 无用
 if(ob->query_skill_mapped("blade") != "hujia-daofa")
  {
	ob->map_skill("blade","hujia-daofa");
	ob->map_skill("parry","hujia-daofa");
	  message_vision(HIR"\n$N冷冷一笑：“$n的那点招数，对我完全无效，什么独孤九剑，岂能料到我神功奥妙无双。”\n"NOR,ob,me);
  }
  //增加绝技
  if(i<(2+random(me->query("int")/5))) i++;
  else
  {
    ob->delete_temp("quest/雪山飞狐/武功/lengquan");
    i=0;
  	if(ob->query_busy())
  	{
  		if(ob->query_busy()>2) ob->start_busy(me->query_busy()/2);
  		else ob->start_busy(random(2));
      if(random(2)) message_vision(HIR"\n$N逆转冷泉神功，瞬间化解原本束缚$N行动的困境，手脚顿时灵活了许多！\n"NOR, ob);
      else message_vision(HIC"\n$N气穿百穴，逆转冷泉神功，瞬间原本束缚$N行动的困境已化为乌有，招数更见凌厉！\n"NOR, ob);
    }
     switch(random(6))
     {
     	case 0:
            message_vision(HIW"\n$N轻舒猿臂，手中的钢刀吞吞吐吐，变化莫测，笼罩了$n周身要害！\n" NOR, this_object(),me);
            if(random(3) && !me->query_busy())
            {
            	message_vision(HIC"$n见来招实在是变幻莫测，不由得心生惧意，招式登时出了破绽！\n" NOR, this_object(),me);
              me->add_busy(2+random(4));
            }
            break;
     	case 1:
     		    message_vision(HIR"\n$N手中的钢刀幻出漫天刀云，雷霆霹雳般的击向一刀劈向$n！\n" NOR, this_object(),me);
	          ob->add_temp("apply/attack", ob->query_skill("blade"));
	          ob->add_temp("apply/damage", ob->query_skill("blade"));
          	  COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
	          ob->add_temp("apply/attack", -ob->query_skill("blade"));
	          ob->add_temp("apply/damage", -ob->query_skill("blade"));
	          ob->start_busy(1);
            break;
     }
    ob->set_temp("quest/雪山飞狐/武功/lengquan",1);
  }
  ob->set_temp("pfm",i);
	call_out("killing",1);
  return 1;
}
/*
void die()
{
	object ob=this_object();

	if(ob->query_temp("biwu"))
	{
    start_condition(ob);
    if((string)file_name(environment(ob))!="/d/huanghe/lianwuchang")
        message_vision(HIR"\n$N挠了挠头，似乎很是困惑。\n"NOR,ob);
    ob->set_temp("lost",1);
   	ob->remove_all_killer();
  }
  else
  {
	::die();
  }
}

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
