//miaorenfeng.c
//by tangfeng@SJ
//修改雷同hu-fei.c
//增加冷泉神功部分
// Update by lsxk@hsbbs add通宝物品增加解mjjf quest成功几率 2007/7/20
// By Spiderii@ty 加入天赋

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
#define QUESTDIR5 "quest/雪山飞狐/宝藏/"

void greeting(object me);
void zhenxiang(object me);
void jieshuo1(object me);
void jieshuo2(object me);
void unconcious();
void kill_ob(object me);
int do_hit(string arg);
void do_halt(object me);
void die();
int ask_huyidao();
int ask_biwu();
int ask_zhiliao();
int ask_chuangwang();
int ask_hujiadaofa();
int ask_miaojiajianfa();
int ask_cheng();
int ask_liangyedaofa();
int ask_yanji();
int ask_miaoruolan();
int ask_tian();
int ask_hufei();
int ask_hunjia();
int ask_jiaoliang();
int miao_fight(object me, object ob);
int thinking(object me, object ob);
int killing();
int start_condition(object ob);
int power_condition(object me,object ob,int p);
int busy_pass(object ob);
int skill_check(object me);
int ask_lengquanshengong();

void create()
{
	set_name("苗人凤", ({ "miao renfeng", "miao", "renfeng" }) );
	set("gender", "男性" );
	set("title", HIY"金面佛"NOR);
	set("age", 56);
	set("long",
	    HIR"苗家庄庄主。号称“"HIY"打遍天下无敌手"HIR"”\n"NOR);
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("unique", 1);
    set(QUESTDIR4+"miaojiajianfa",1);
    set(QUESTDIR4+"lengquanshengong_teach",1);
    set("no_get", 1);
    set("no_bark", 1);
	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("sword", 300);
	set_skill("cuff",300);
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("lengquan-shengong",300);
	set_skill("miaojia-jianfa",300);
	map_skill("force","lengquan-shengong");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("sword","miaojia-jianfa");
	map_skill("parry","miaojia-jianfa");
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
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
       (: exert_function, "lengquan" :),
       (: perform_action, "sword.duoming" :),
       (: perform_action, "sword.ci" :),
     }));

  set("inquiry", ([
    "婚嫁" : (: ask_hunjia :),
    "结婚" : (: ask_hunjia :),
    "做媒" : (: ask_hunjia :),
    "冷泉神功" : (: ask_lengquanshengong :),
    "lengquan-shengong" : (: ask_lengquanshengong :),
    "胡斐" : (: ask_hufei :),
    "hu fei" : (: ask_hufei :),


    "闯王宝藏" : (: ask_chuangwang :),
    "闯王" : (: ask_chuangwang :),
    "宝藏" : (: ask_chuangwang :),

    "苗家剑法" : (: ask_miaojiajianfa :),
    "miaojia-jianfa" : (: ask_miaojiajianfa :),

    "胡一刀" : (: ask_huyidao :),
    "胡家刀法" : (: ask_hujiadaofa :),
    "刀剑融合" : (: ask_hujiadaofa :),

    "两页刀法" : (: ask_liangyedaofa :),
    "较量" : (: ask_jiaoliang :),
    "真相" : (: ask_biwu :),
    "往事" : (: ask_biwu :),
    "20年前" : (: ask_biwu :),
    "20年前的比武" : (: ask_biwu :),
    "比武" : (: ask_biwu :),
    "治疗" : (: ask_zhiliao :),
    "苗若兰" : (: ask_miaoruolan :),
    "解药" : (: ask_zhiliao :),
    "阎基" : (: ask_yanji :),
    "程灵素" : (: ask_cheng :),
    "田归农" : (: ask_tian :),
	]));
	setup();
	carry_object("/clone/weapon/sword/sword.c")->wield();
	carry_object("/clone/weapon/sword/sword.c");
	carry_object("/clone/armor/baihu-qiu.c")->wear();
}

void init()
{
  object me;
	::init();
  if (!this_object()->query_temp("biwu")&& interactive(me = this_player()) ) {
  	   me->start_busy(1);
       call_out("greeting", 2, me);
  }
  add_action("do_hit", "hit");
}

void greeting(object me)
{
  object jieyao;
  if(!me) return;
  if(environment(me)!=environment(this_object()))
  {
        if( random(2)) command("?");
        else if( random(2)) command("say");
        else if( random(2)) command("sing");
        else if( random(2)) command("love");
        else if( random(2)) command("addoil");
        else command("xixi");
  	return;
  }
	if(me->query_condition("killer"))
	{
	  command("fear "+me->query("id"));
    command("say 小心官府通缉！");
    me->move(__DIR__"lanzhou");
	  return;
	}
  if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"getjieyao"))
  {
  	tell_object(me,HIG"\n你走进大厅，却看见苗人凤正面向胡一刀的灵牌发呆，你不由一阵感触，当年几多周折，今天也算真相大白。\n"NOR);
    message_vision(HIC"$n似乎是听到脚步声，转头对$N道："+RANK_D->query_respect(me) +"回来了？\n"NOR,me,this_object());
  	jieyao= present("jie yao", me);
  	if(!jieyao)
  	{
     	tell_object(me,CYN"\n你上前准备将解药送给了苗人凤服下，且发现药物遗失了。\n"NOR);
     	tell_object(me,CYN"怎么这样呢？你自是焦急万分，看来只能再去一次五毒教了。\n"NOR);
	    tell_room(environment(me),HIC"\n"+me->query("name")+"似是上前做什么，却发现遗失了什么，一脸的慌张。\n"NOR, ({}));
    log_file("quest/FEIHU", sprintf("%s(%s) 竟然遗失解药。失败。经验：%d。\n",me->name(1),me->query("id"),me->query("combat_exp")) );
     	me->set_temp(QUESTDIR3+"jieyao2",1);
     	me->delete_temp(QUESTDIR3+"getjiao");
      return;
    }
    else
    {
  	  tell_object(me,HIY"\n你上前将内服药送给了苗人凤服下，并帮他将外敷药附在眼睛上。\n"NOR);
  	  command("thank "+me->query("id"));
	  tell_room(environment(me),HIC"\n"+me->query("name")+"走到苗人凤跟前，似是在给他敷药。\n"NOR, ({}));
  	  tell_object(me,HIY"你顺手拉过一把椅子，坐在苗大侠位身边，轻轻地咳了一声，且不知道从何说起。\n"NOR);
      destruct(jieyao);
      remove_call_out("zhenxiang");
      call_out("zhenxiang", 6, me);
      return;
    }
  }
  if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"kill") && !me->query_temp(QUESTDIR2+"huyidao") && !me->query(QUESTDIR2+"over") && !me->query_temp(QUESTDIR2+"ask_"))
  {
  	command("haha");
	me->start_busy(3);
  	tell_object(me,HIG"\n你刚进大厅，就听到一阵爽朗的笑声，“是哪位朋友前来助阵？苗某先是感激了！”你不由胸口一荡。\n"NOR);
  	tell_object(me,HIC"你踌躇了一下，嘴里回答道：在下"+me->query("name")+"，不过恰巧正过此地，苗大侠可好？\n"NOR);
  	remove_call_out("zhenxiang");
    call_out("zhenxiang", 3, me);
    return;
  }

}
void zhenxiang(object me)
{
	int i,p;
  if(!me) return;
  if(environment(me)!=environment(this_object()))
  {
  	command("chat "+me->name()+"，人呢？怎么怕我不成?");
  	return;
  }
  if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"getjieyao"))
  {
 	  tell_object(me,HIW"\n苗大风不愧为当世高手，一会工夫用内力化开，这眼睛也就好了。你正要感谢，却听到苗人凤叹道：“当年若不\n"NOR);
  	tell_object(me,HIW"不是一招失手，今日与胡氏夫妇三骑漫游天下，教贪官恶吏、土豪巨寇，无不心惊胆落，那是何等的快事？”\n"NOR);
  	tell_object(me,HIY"却听到苗大侠悲笑起来，闻者无不心酸。所谓英雄豪情不多如此，而可恨天道造化。\n"NOR);
    me->delete_temp(QUESTDIR3+"getjieyao");
    me->set(QUESTDIR3+"over",1);
   	tell_object(me,HIR"你想了一会，也是莫名感叹。也罢，这故事总算告一段节，你不由长叹一口气。\n"NOR);
	p=10+random(10);
        me->add("max_neili",p);
        me->add("combat_exp",me->query_skill("force")+500);
   	i=180+random(40);
   	me->add("mana",i);
    me->set(QUESTDIR+"time",time());
    me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
        tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解开雪山飞狐解药篇，获得"+p+"点最大内力、"+((int)me->query_skill("force")+500)+"点经验奖励、"+i+"点声望。\n\n"NOR);
    log_file("quest/FEIHU", sprintf("%s(%s) 解药篇完成。奖励：%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), p,(me->query_skill("force")+500),i ) );
   	return;
  }
  if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"kill")&& !me->query_temp(QUESTDIR2+"kill_")&& !me->query_temp(QUESTDIR2+"huyidao") && !me->query(QUESTDIR2+"over") )
  {
  	message_vision(HIY"突然$N发现一阵掌风扑面而来，$N惊惧万分，却不敢硬接硬架，当下使出师门武功想卸开对方掌力。岂知双手与$n\n"
  	                  "手掌甫接，登时眼前一黑，胸口气塞，$N腾腾腾连退三步。$n的掌力只卸去了一半，余一半还是硬接了过来。\n"NOR,me,this_object());
    command("heng");
    if(!me->query("family"))
	{
  	message_vision(HIC"\n$N叫道：“苗大侠，我帮你拿贼……”却听$n道：“原来是"+me->query("name")+"。”\n"NOR,me,this_object());
  	message_vision(HIC"$N回答道：“还好，多谢关怀。”却发现$n双目突然紧闭，像是毒性发作，$N问道：“苗大侠，现在感觉如何？”\n\n"NOR,me,this_object());
        message_vision(HIC"$N犹豫了一下，沉声说道：“我与这位"+RANK_D->query_respect(me) +"俗不来往，今天来我苗家庄，怕是有什么问题吧？”\n\n"NOR,me,this_object());
	}
	else
	{
  	message_vision(HIC"\n$N叫道：“苗大侠，我帮你拿贼……”却听$n道：“原来是"+me->query("family/family_name")+"弟子，"+me->query("family/master_name")+"师傅最近可好？”\n"NOR,me,this_object());
  	message_vision(HIC"$N回答道：“还好，多谢关怀。”却发现$n双目突然紧闭，像是毒性发作，$N问道：“苗大侠，现在感觉如何？”\n\n"NOR,me,this_object());
        message_vision(HIC"$n犹豫了一下，沉声说道：“我与"+me->query("family/master_name")+"俗不来往，这位"+RANK_D->query_respect(me) +"且不管我，来我苗家庄，怕是有什么问题吧？”\n\n"NOR,me,this_object());
	}
    me->set_temp(QUESTDIR2+"kill_",1);
	me->start_busy(3);
    call_out("zhenxiang",3, me);
    return;
  }
  if(me->query(QUESTDIR2+"start") && me->query_temp(QUESTDIR2+"kill")&& !me->query_temp(QUESTDIR2+"huyidao") && !me->query(QUESTDIR2+"over") && me->query_temp(QUESTDIR2+"kill_"))
  {
  	command("say");
  	tell_object(me,HIG"苗人凤果然心思敏捷，你沉默了一下，脑子里一边盘想着如何开口询问这20年前的故事......\n"NOR);
	  tell_room(environment(me),HIC"\n"+me->query("name")+"似是沉吟不定，好像思考着什么。\n"NOR, ({}));
    log_file("quest/FEIHU", sprintf("%s(%s) 拜见苗人凤。经验：%d。\n",me->name(1),me->query("id"),me->query("combat_exp")) );
    me->set_temp(QUESTDIR2+"ask_",1);
    me->delete_temp(QUESTDIR2+"kill_");
    remove_call_out("zhenxiang");
    return;
  }
}

void kill_ob(object me)
{
	command("sneer " + me->query("id"));
  power_condition(me,this_object(),300+random(100));
  remove_call_out("killing");
	call_out("killing", 2);
	::kill_ob(me);
}

int do_hit(string arg)
{
         object me,ob;
         me=this_player();
         ob=this_object();
         if((arg==("miao"))||(arg==("miao renfeng"))){
           	command("sneer");
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon") );
           	return 1;
         }
         return 0;
}

int ask_cheng()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("thank");
	  command("say 真的感谢程大医生，要不是她恐怕我早入黄泉。");
	  return 1;
  }
  command("say 程姑娘，应该就是当年药王弟子，现在可能身在五毒教吧。");
	return 1;
}

int ask_biwu()
{
	object me = this_player();

  if(me->query(QUESTDIR2+"over"))
  {
	  command("sigh "+me->query("id"));
	  command("say 20年前的比武，现在已经完全明了。只是可恨胡兄竟然被阴险小人所暗算。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"zhenxiang"))
  {
	  command("say 当年我确实和胡一刀比过武，胡兄也确实毒发身亡，但怎么可能是我忍心下此毒手？这20年来，我也在一直查找凶手。");
	  command("consider");
	  return 1;
  }
 if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"zhenxiang_"))
  {
	  command("say 你听我说阿，别着急。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"huyidao") )
  {
	  command("nod "+me->query("id"));
	  command("say 当年我确实和胡一刀比过武，我们从初识到相交，后来更是同床而眠，彻夜切磋武功，真是好令人怀念。");
	  command("say 只是到第五天上，胡大嫂瞧出我背后的破绽，一声咳嗽，胡一刀竟然使出八方藏刀式，不及提防将我制住。");
	  tell_object(me,YEL"\n你听到这里，感觉和阎基所说不同，不由问道：“那后来呢？难不成胡一刀不是自杀？”\n\n"NOR);
    message_vision(HIC"$N露出疑惑的神色。\n"NOR,me);
	  me->start_busy(3);
	  remove_call_out("jieshuo1");
	  me->set_temp(QUESTDIR2+"zhenxiang_",1);
    call_out("jieshuo1",6, me);
  	return 1;
  }

	command("heng");
	command("say 我号称打遍天下无敌手，不知你说的是什么比武？");
	return 1;
}
void jieshuo1(object me)
{
  if(!me) return;
  if(environment(me)!=environment(this_object()))   {
  	command("chat "+me->name()+"，人呢？我正在讲故事呢。");
  	return;
  }  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"huyidao"))
  {
    command("consider");
	  command("say 但下一招我当时用的胡家刀法，胡兄用的是苗家剑法，我临时变招，新创一式，一个措手不及将胡兄所伤。");
	  message_vision(YEL"\n$N惊异的问道：“如果伤势不是很严重，怎么立刻毙命的呢？”$n闻言道：“刀上有毒。”说着，叹了口气。\n"NOR,me,this_object());
	  command("say 而且大嫂竟然也自杀，之后场面很乱，胡兄之子也被乱中砍死，20年来我一直怀疑追查真相，只是没有任何线索。");
	  remove_call_out("jieshuo2");
    call_out("jieshuo2",6, me);
    return;
  }
}
void jieshuo2(object me)
{
  if(!me) return;
  if(environment(me)!=environment(this_object()))   {
  	command("chat "+me->name()+"，人呢？我正在讲故事呢。");
  	return;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"huyidao"))
  {
    command("sigh");
    tell_object(me,HIW"\n你听完解说一阵沉默，不由被胡与苗的豪情所感动，只怕其中真有别情！你想了一会儿，只有阎基这个线索了！\n"NOR);
    me->delete_temp(QUESTDIR2+"huyidao");
    me->delete_temp(QUESTDIR2+"zhenxiang_",1);
    me->set_temp(QUESTDIR2+"zhenxiang",1);
    return;
  }
}
int ask_miaojiajianfa()
{
	object me = this_player();
	object ob = this_object();
	int i,lv;

  if(!me->query(QUESTDIR3+"over"))
  {
	  command("shake "+me->query("id"));
	  command("sigh");
	  command("say 胡兄大事未了，在下也没有什么心思切磋武功了。");
	  return 1;
  }

  if(me->query(QUESTDIR4+"miaojiajianfa")&& me->query("potential")<= 5)
  {
	  command("? "+me->query("id"));
    return 1;
  }

  if(me->query(QUESTDIR4+"miaojiajianfa"))
  {
  	if(me->query("potential")>4)
  	{
      message_vision("$N向$n请教有关苗家剑法的奥妙。\n", me, this_object());
      me->receive_damage("jing", 30);
      tell_object(me,"你听了苗人凤的指点，对苗家剑法的奥妙似乎有些心得。\n");
      me->add("potential",-(random(3)+2));
      if( me->query("potential")<0)
        me->set("potential",0);
      me->improve_skill("miaojia-jianfa", 150+random(me->query_int()*2));
      me->improve_skill("sword", random(me->query_int())/2);
       //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        lv = me->query("max_pot")-100;
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了苗家剑法的精华所在。\n"NOR);
            me->set_skill("miaojia-jianfa",lv);
            }
    }
    else
    {
      message_vision("$N向$n请教有关苗家剑法的奥妙。\n", me, this_object());
      me->receive_damage("jing", 30);
      tell_object(me,"你听了苗人凤的指点，可是还是不能理解。\n");
    }
    return 1;
  }

  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 不是刚学完吗，还是以后切磋吧。");
	  return 1;
  }
  //非vip玩家，只能失败三次
  if(me->query(QUESTDIR4+"miaojiajianfa_fail")>=3 && me->query("registered")<3)
  {
	  command("shake "+me->query("id"));
	  command("say 现在时间紧急，这剑法还是以后切磋吧。");
	  return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔1M
	//注意这个标记和刀法使用同一个标记。
	if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<86400)
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到这里吧，明天吧。");
	  return 1;
  }
	if(me->query(QUESTDIR4+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"combat_exp")<500000)
	{
	  command("look "+me->query("id"));
	  command("say 以你当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
	  return 1;
  }
	  command("nod "+me->query("id"));
    message_vision(HIY"\n$n突然运起独门内功冷泉神功，只感觉剑势无风自起。\n"NOR, me, ob);
    ob->set_temp("busy",1);
    remove_call_out("busy_pass");
		call_out("busy_pass",600, ob);
    //难度稍微大于刀法，不过关系不大。
    power_condition(me,ob,350+random(150));
    for ( i = 0; i < 6+random(6);i++)
    {
         if (!present(me,environment(ob)) || me->query("qi") <= me->query("max_qi")/20 ||me->query("eff_qi") <= me->query("max_qi")/20 || me->query("jing") <= 50 || me->query("jingli") <= 50)
         {
            if(random(2))command("sneer");
            else if(random(2)) command("say 这位"+RANK_D->query_respect(me) +"武功未能返璞归真，只怕难以领悟苗家剑法的绝技！");
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
    //标记时间和经验
    me->set(QUESTDIR4+"time",time());
    me->set(QUESTDIR4+"combat_exp",me->query("combat_exp"));
    ob->delete_temp("quest/雪山飞狐/武功/lengquan");
    start_condition(ob);
    command("haha "+me->query("id"));
    message_vision(HIC"\n\n犹如电光雷闪，一晃数招已过，$n微笑着对$N说道：「刚才我使用的招数可看清楚了？」\n"NOR,me,ob);
    remove_call_out("thinking");
		call_out("thinking",0, me, ob);
    tell_object(me,YEL"你拼命地回忆瞬间交手的一幕，回忆着刚才的招数，你开始认真思索着.........\n"NOR);
    me->start_busy(2);
	  return 1;
}

int thinking(object me, object ob)
{
	int i,p;
	if(!me) return 0;
  if(environment(me)!=environment(ob))
  {
  	start_condition(ob);
    if(random(2)) message_vision(HIC"\n$N伸了伸懒腰，道：$n竟然临阵逃脱，没料得蠢材一个。\n"NOR,ob,me);
    else message_vision(HIC"\n$N疑惑问道：夷~~~人呢？$n，人呢？\n"NOR,ob,me);
  	return 1;
  }
  if(!living(me) )
  {
  	ob->revive();
  	ob->reincarnate();
  }
  if(me->query_temp(QUESTDIR4+"thinking")<(3+random(3)))
	{
		me->add_temp(QUESTDIR4+"thinking",1);
    if(random(2)) tell_object(me,HIG"\n你努力地回忆刚才的每一招每一式，似有无数人影交相互动，每一招每一式你都努力去看清楚...\n"NOR);
    else tell_object(me,HIY"\n突然间，你似乎抓到了什么，你努力地回忆刚才的每一招每一式，你能充分感觉招数的凌厉和急速...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，一服愁眉不展的样子。\n"NOR, ({}));
	  remove_call_out("thinking");
		call_out("thinking",3+random(3), me, ob);
	}
	else
	{
    me->delete_temp(QUESTDIR4+"thinking");

	 //难度降低，毕竟单纯的苗家剑法威力一般
   //有特殊通宝物品,提高几率.
   if(me->query_temp("sj_credit/quest/public/mjjf"))
        p=random(58);
   else
	//没别的，听玩家的意见
        p=random(40);
     me->delete_temp("sj_credit/quest/public/mjjf");

    if(!QUEST_D->questing(me, 1, 0, 1)) p = 0;

         if(p > 37&& me->query("kar")<31)
    {
       tell_object(me,HIG"\n你明悟其中，突然间明白了一切。\n"NOR);
       message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me);
       tell_object(me,HIR"你听了苗人凤的指点，对苗家剑法的奥妙似乎有些心得。\n"NOR);
	   if(me->query(QUESTDIR4+"hujiadaofa"))
		    tell_object(me,HIR"你发现苗家剑法如果能够与胡家刀法相互融合，威力当可加倍。\n"NOR);
       tell_object(me,HIR"只是你发现这苗家剑法还需要冷泉神功才能发挥全效。\n"NOR);
       me->set(QUESTDIR4+"miaojiajianfa",1);
       i=180+random(40);
   	   me->add("mana",i);
  	   tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解开雪山飞狐苗家剑法篇，并获得"+i+"点声望。\n\n"NOR);
     log_file("quest/FEIHU", sprintf(HIR"%s(%s) 失败%d次后揭开苗家剑法,获得%d点声望。random（40）取值%d。"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"miaojiajianfa_fail"),i,p) );
    }
    else
    {
       tell_object(me,HIG"\n你脑海里似乎抓住了什么，可是依然不是很明白。\n"NOR);
       message_vision(HIC"\n$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n"NOR,me);
       command("poor "+me->query("id"));
       me->add(QUESTDIR4+"miaojiajianfa_fail",1);
	   log_file("quest/FEIHU", sprintf(HIR"%s(%s) 苗家剑法失败次数：%d次,random（30）取值%d。\n"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"miaojiajianfa_fail"),p) );
       if(me->query(QUESTDIR4+"miaojiajianfa_fail")>=3 && me->query("registered")<3)
       {
      	tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"最后一次尝试揭开雪山飞狐苗家剑法，却没有成功。\n\n"NOR);
   		log_file("quest/FEIHU", sprintf("%s(%s) 最后一次尝试揭开雪山飞狐苗家剑法，却没有成功。时间 %s。\n", me->name(1),me->query("id"), ctime(time()) ) );
       }
    }
  }
  return 1;
}
int ask_hujiadaofa()
{
	object me = this_player();
	int i;
  if(this_object()->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 不是刚学完吗，还是以后切磋吧。");
	  return 1;
  }
  if(me->query(QUESTDIR4+"hujiadaofa") && me->query(QUESTDIR4+"miaojiajianfa") )
  {
  	  //非vip玩家，只能失败三次
     if(me->query(QUESTDIR4+"ronghe_fail")>=3 && me->query("registered")<3)
     {
	      command("shake "+me->query("id"));
	      command("say 怕是你难以领悟阿。");
	      return 1;
	    }
	   //武功学习之间需要间隔一天，经验需要间隔1M
	   //注意这个标记和刀法使用同一个标记。
	   if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<86400)
	   {
	     command("shake "+me->query("id"));
	     command("say 今天先切磋到这里吧，明天吧。");
	     return 1;
     }
     if(me->query(QUESTDIR4+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"combat_exp")<500000)
	   {
	     command("look "+me->query("id"));
	     command("say 以你当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
	     return 1;
     }
  	 command("nod "+me->query("id"));
  	 if(me->query(QUESTDIR4+"ronghe"))
  	 {
      	command("say 你已经刀剑融合，可惜缺少内功支持。传说：冷泉神功可能在闯王宝藏里！");
	      return 1;
      }
      me->set(QUESTDIR4+"time",time());
      me->set(QUESTDIR4+"combat_exp",me->query("combat_exp"));
 	    command("say 胡家刀法的确可以与苗家剑法融合，但是需要冷泉神功支持，这里我可以先教给你融合的口诀！");

 	    //难度也很大，其实这也是这门武功的关键
		//这里增加门槛，不希望每个玩家都能够学会
		//假设富源random之后取28的话，int随机应该大于22
		//int 假设25 bili 20的话，con和dex之和35 400等级exp 那么就是75
      if((random(me->query("kar"))+random(me->query("int")))>50
		  && (random(me->query_con())+random(me->query_dex()))>60
		  && random(me->query("combat_exp"))>2000000
            &&me->query("kar")<31
            &&QUEST_D->questing(me, 1, 0, 1))
      {
           tell_object(me,HIR"你听了苗人凤的指点，对苗家剑法和胡家刀法的奥妙似乎更加明白。\n"NOR);
           message_vision(HIC"\n$N当即左刀右剑比划一招，「哈哈哈」大笑几声，说道：“原来如此。”\n"NOR,me);
           me->set(QUESTDIR4+"ronghe",1);
           i=180+random(40);
   	       me->add("mana",i);
  	       tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"解开雪山飞狐刀剑融合的奥秘，并获得"+i+"点声望。\n\n"NOR);
		   log_file("quest/FEIHU", sprintf(HIR"%s(%s) 失败%d次后，揭开刀剑融合，获得%d点声望。kar%d/int%d/后天con%d/dex%d。\n"NOR, me->name(1),me->query("id"),me->query(QUESTDIR4+"ronghe_fail"),i ,me->query("kar"),me->query("int"),me->query_con(),me->query_dex()) );
       }
       else
       {
           tell_object(me,HIG"\n你听了苗人凤的指点，脑海里似乎抓住了什么，可是依然不是很明白。\n"NOR);
           message_vision(HIC"\n$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n"NOR,me);
           command("poor "+me->query("id"));
           me->add(QUESTDIR4+"ronghe_fail",1);
           if(me->query(QUESTDIR4+"ronghe_fail")>=3 && me->query("registered")<3)
           {
          	tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"最后一次尝试揭开雪山飞狐刀剑融合的奥秘，却没有成功。\n\n"NOR);
   		      log_file("quest/FEIHU", sprintf("%s(%s) 最后一次尝试揭开雪山飞狐刀剑融合的奥秘，却没有成功。\n", me->name(1),me->query("id")) );
           }
        }
	  return 1;
  }
  command("nod "+me->query("id"));
  command("say 当年的关东大侠胡一刀曾指点我这路刀法，确实精妙无比！");
	return 1;
}
int ask_huyidao()
{
	object me = this_player();
  if(me->query(QUESTDIR3+"start"))
  {
  	command("cry");
  	command("say 胡一刀，我的好兄弟啊！");
	  return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"huyidao"))
  {
  	command("say 胡一刀，我的好兄弟啊！");
  	return 1;
  }
  if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"kill"))
  {
  	tell_object(me,YEL"苗人凤突然看起来苍老了很多，不知沉默了多久，才缓缓叹了口气。\n"NOR);
    command("nod "+me->query("id"));
    command("say 关东大侠胡一刀正是我的至交好友啊！不知道这位"+RANK_D->query_respect(me) +"为什么提起他？");
    me->set_temp(QUESTDIR2+"huyidao",1);
    me->delete_temp(QUESTDIR2+"kill_ren");
    me->delete_temp(QUESTDIR2+"kill_");
  	return 1;
  }
  command("nod "+me->query("id"));
  command("say 关东大侠胡一刀正是我的至交好友，你找他什么事情！");
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
  if(!me->query(QUESTDIR3+"over"))
  {
	  command("shake "+me->query("id"));
	  command("sigh");
	  command("say 在下现在没有什么心思切磋武功了。");
	  return 1;
  }
  if(ob->query_temp("busy"))
  {
	  command("shake "+me->query("id"));
	  command("say 在下现在没有什么心思切磋武功了。");
	  return 1;
  }
    //普通玩家三次,
   if(me->query(QUESTDIR4+"fight_miao")>=3 && me->query("registered")<3)
  {
	  command("shrug "+me->query("id"));
	  command("say 天色不早了，这剑法还是以后切磋吧。");
	  return 1;
	}

	//较量增加时间间隔1个小时。
    if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<(3600*3))
	{
	  command("shake "+me->query("id"));
	  command("say 今天先切磋到这里吧，稍后吧。");
	  return 1;
  }
	if((me->query(QUESTDIR4+"fight_miao")>=3 && me->query(QUESTDIR4+"fight_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"fight_exp")<500000)
		||(me->query(QUESTDIR4+"fight_miao")<3 && me->query(QUESTDIR4+"fight_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"fight_exp")<100000))
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
	  command("nod "+me->query("id"));
    message_vision(HIY"\n$n突然运起独门内功冷泉神功，只感觉剑势无风自起。\n"NOR, me, this_object());

    //玩家最好武功在400等级以上，纵然如此还是比较危险。
    power_condition(me,ob,300+random(200));
    if (!(room = find_object("/d/lanzhou/lianwuchang")))
        room = load_object("/d/lanzhou/lianwuchang");
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
	me->add(QUESTDIR4+"fight_miao",1);
    ob->set_temp("busy",1);
    ob->set_temp("biwu",1);
	  ob->set_temp("quest/try_fight_id",me->query("id"));

    message_vision(HIY"$N向$n一招手道：“"+RANK_D->query_respect(me) +"且随我来”，$N和$n急急忙忙地离开坟地。\n"NOR, ob,me);
    ob->move(room);
    me->move(room);
    message_vision(YEL"$N急急忙忙地来到练武场。\n"NOR, ob);
    message_vision(YEL"$N急急忙忙地来到练武场。\n"NOR, me);
	  command("sneer");
    remove_call_out("busy_pass");
		call_out("busy_pass",600, ob);
    log_file("quest/FEIHU", sprintf("%s(%s) 再次与苗人凤较量。经验：%d。\n",me->name(1),me->query("id"),me->query("combat_exp")) );
    me->start_busy(1);
    ob->start_busy(1);
	  return 1;
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

  if (!present("changjian",ob))
  {
	  message_vision(HIR"\n$N身行向后一跃，不知道从哪里竟然又拿出一把钢剑。\n"NOR,ob);
  	carry_object(BINGQI_D("sword"))->wield();
  }
	else command("wield changjian");
  i=ob->query_temp("pfm");

  //zongjue 无用
  if(ob->query_skill_mapped("sword") != "miaojia-jianfa")
  {
	  ob->map_skill("sword","miaojia-jianfa");
	  ob->map_skill("parry","miaojia-jianfa");
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
            message_vision(HIW"\n$N"HIW"轻舒猿臂，手中的长剑吞吞吐吐，变化莫测，笼罩了$n"HIW"周身要害！\n" NOR, this_object(),me);
            if(random(3) && !me->query_busy())
            {
            	message_vision(HIC"$n见来招实在是变幻莫测，不由得心生惧意，招式登时出了破绽！\n" NOR, this_object(),me);
              me->add_busy(1+random(4));
            }
            break;
     	case 1:
     		  message_vision(HIR"\n$N手中的长剑幻出漫天剑影，雷霆霹雳般的击向$n！\n" NOR, this_object(),me);
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
int ask_liangyedaofa()
{
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
 	command("doubt");
	command("say 谁？我认识吗？");
	command("consider");
	return 1;
}
int ask_zhiliao()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"over"))
  {
	  command("say 需要治疗可以寻找程姑娘，确实高手。我也多谢她了。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"start"))
  {
	  command("sigh "+me->query("id"));
	  command("say 如此说来，治疗我这毒，怕是只有程灵素了。");
	  return 1;
  }
  if(me->query(QUESTDIR2+"over"))
  {
	  tell_object(me,HIW"你也将真相告诉苗人凤，显然现在不是悲伤的时候，这毒性越发得厉害。你说服苗人凤，亲自上前仔细观察中毒症状。\n\n"NOR);
	  tell_object(me,CYN"你说道：“苗大侠眼中所染的毒药，乃是断肠草的粉末，只怕是从毒手药王那里得来的。”说话期间，苗人凤已经痛楚不忍。\n"NOR);
	  tell_object(me,CYN"苗人凤听道：“恩，如此说来，要治这毒只有药王谷的人了”你点了点头，当前之急还是赶快寻找程灵素，这毒看似好凶猛。\n\n"NOR);
	  tell_object(me,CYN"苗人凤听言，停顿了一下：“现在药王谷就在苗疆之内，那就拜托"+RANK_D->query_respect(me) +"走一趟了。只是听说药王谷的人......”\n"NOR);
	  command("sigh");
	  tell_object(me,HIC"\n你当即说道：“咱们好歹也得将他请到，他要什么便给他什么。我这就去一趟苗疆药王谷。”\n"NOR);
	  command("addoil "+me->query("id"));
	  me->set(QUESTDIR3+"start",1);
	  return 1;
  }
  command("say 药王的唯一亲传弟子，前段时间药王病逝，恐怕药术一派只有这程灵素程姑娘的天地了。");
	return 1;
}
int ask_miaoruolan()
{
	object me = this_player();

  if(me->query(QUESTDIR3+"marry"))
  {
	  command("say 小女苗若兰这工夫只怕和胡斐那孩子在一起吧。");
	  return 1;
  }
	command("? "+me->query("id"));
	command("say 那是小女，不知你找她有何事？");
	return 1;
}
int ask_hufei()
{
	object me = this_player();

	if(me->query(QUESTDIR3+"marry"))
  {
	  command("say 现在只怕和小女苗若兰在一起吧。天可怜见胡家一脉啊！");
	  return 1;
  }

  if(me->query(QUESTDIR3+"start"))
  {
	  command("say 天可怜见胡家一脉啊！胡兄九泉之下也可瞑目了。");
	  return 1;
  }
	command("say 胡兄之子的名字正是这胡斐，可惜当年一场大乱，被乱刀砍死了。");
	command("sigh");
	command("say 好后悔未能照顾胡兄唯一之子啊！");
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
  if(me->query(QUESTDIR3+"start"))
  {
	  command("heng");
	  command("say 确实没有想到事情如此复杂。天龙门现在一门尽亡，也算是天网恢恢阿。");
	  return 1;
  }
	command("say 上任天龙门掌门，很久不知下落了。现在天龙门大不如以前了。");
	return 1;
}
int ask_hunjia()
{
	object obj,me = this_player();
  if(me->query(QUESTDIR3+"marry"))
  {
	  command("haha");
	  command("say 苗胡两家恩怨终得圆满啊。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
  	tell_object(me,CYN"你说道：苗大侠，你可知道你家苗大姑娘和雪山飞狐胡斐情投意合这码子事情？\n"NOR);
	  command("say 不知是真是假，如此甚好，哈哈，苗胡两家恩怨终得圆满啊。");
	  command("haha");
	  command("say 这位"+RANK_D->query_respect(me) +"为胡苗两家出尽大力，不慎感激啊。无以为报，这是我一点心意，还请收下！");
	  me->set(QUESTDIR3+"marry",1);
	  obj=new("/clone/medicine/renshen-guo");
	  command("give "+obj->query("id")+" to "+me->query("id"));

	  if(!present(obj,me)) obj->move(me);
	  return 1;
  }
	command("say 这事和我说来无用，小女自有自己主张。");
	return 1;
}
int ask_chuangwang()
{
        object me,obj;
        me = this_player();
  if(me->query(QUESTDIR3+"over")&& !present("baozang tu",me))
  {
	if(!me->query(QUESTDIR4+"win_miao") && (me->query(QUESTDIR4+"fight_miao")<3 || random(4)))
    {
	      command("look "+me->query("id"));
	      command("say 你连我都赢不了，如何独力寻找宝藏。我这也算是为了你好。");
	      command("pat "+me->query("id"));
	      command("say 你还是抓紧时间练功去吧。");
	      return 1;
    }
	if(!me->query(QUESTDIR4+"win_hu") && (me->query(QUESTDIR4+"fight_hu")<3 || random(4)))
    {
	      command("look "+me->query("id"));
	      command("say 你连胡斐都赢不了，如何独力寻找宝藏。我这也算是为了你好。");
	      command("pat "+me->query("id"));
	      command("say 你还是抓紧时间练功去吧。");
	      return 1;
    }
	if(!random(10))
	{
	    if(random(2))
		{
			command("consider");
			command("say 宝藏图在哪里呢。");
			if(random(2)) command("pat "+me->query("id"));
			else command("papaya");
			command("addoil");
			return 1;
		}
		else if(random(2))
		{
			command("consider");
			command("say 刚才还在这里啊。我再找找看。");
			command("papaya");
			return 1;
		}
		else if(random(2))
		{
			command("consider");
			command("say 宝藏图.....宝什么来着，啊，我忘记了。");
			command("pat "+me->query("id"));
			command("say 这样吧，你还是抓紧时间练功去吧，过一会再来问吧，我这就找找看。");
			command("addoil "+me->query("id"));
			return 1;
		}
		else
		{
			command("?");
			command("makeup");
			command("say 啊呀，你久等了，你要什么来着？");
			command("say 这样吧，你还是抓紧时间练功去吧，过一会再来问吧，我这就找找看。");
			command("addoil "+me->query("id"));
			return 1;
		}
	}
	obj=unew("/d/lanzhou/obj/map");

	if(!clonep(obj)){
	      command("pat");
	      command("say 宝藏图不在我这里，真是老了糊涂了。");
	      command("pat "+me->query("id"));
	      command("say 这样吧，你还是抓紧时间练功去吧，过一会再来问吧，我这就找找看。");
	      command("addoil "+me->query("id"));
		  return 1;
	}

	if(clonep(obj) && obj->violate_unique()){
	  	  if(objectp(environment(obj))) tell_object(environment(obj),HIC""+obj->query("name")+"被一阵风刮走了。\n"NOR, ({}));
		  destruct(obj);
	      command("pat");
	      command("say 宝藏图不在我这里，真是老了糊涂了。");
	      command("pat "+me->query("id"));
	      command("say 这样吧，你还是抓紧时间练功去吧，过一会再来问吧，我这就找找看。");
	      command("addoil "+me->query("id"));
		  return 1;
	}
  	tell_object(me,HIR"苗人凤偷偷告诉你："HIG"当年闯王破了北京之后，明朝的皇亲国戚、大臣大将尽数投降。这些人无不家资豪富，闯王部下的将领\n"NOR);
  	tell_object(me,HIG"数日之间，财宝山积，那里数得清了。后来闯王退出北京，派了亲信将领，逼他们献出金银珠宝赎命。押著财宝去藏在一个极\n"NOR);
  	tell_object(me,HIG"稳妥的所在，以便将来卷土重来之时作为军饷。他将藏宝的所在绘成一图，而看图寻宝的关键，却置在军刀之中。九宫山兵败\n"NOR);
  	tell_object(me,HIG"逃亡，闯王将宝藏之图与军刀都交给了飞天狐狸。后来飞天狐狸被杀，一图一刀落入三位义弟手中，但不久又被飞天狐狸的儿\n"NOR);
  	tell_object(me,HIG"子夺去。百年来辗转争夺，终于军刀由天龙门田氏掌管，藏宝之图却由我苗家家传。只是苗田两家不知其中有这样一个大秘密，\n"NOR);
  	tell_object(me,HIG"是以没去发掘宝藏。这秘密由胡家世代相传，可是姓胡的没军刀地图，自也无法找到宝藏。是胡大哥将这事告知我的，请我去\n"NOR);
  	tell_object(me,HIG"掘出宝藏，救济天下穷人。其实这个秘密到今天早已经公开，今天告诉了你，你大可去寻找一下这个宝藏。这便是藏宝图，至\n"NOR);
  	tell_object(me,HIG"于藏宝的秘密你还是去自己挖掘吧。\n"NOR);
    tell_object(me,HIR"\n苗人凤偷偷告诉你："HIG"探险的时候，一定要注意安全，带好药物，另外类似绳子、火折等常备工具不要遗漏。\n"NOR);
    command("smile");
    tell_object(me,HIR"\n苗人凤交给你一张宝藏图。\n"NOR);
    command("addoil");
    obj->set("owner",me->query("id"));
    obj->move(me);
    log_file("quest/FEIHU", sprintf("%s(%s) 获得宝藏图。经验：%d。\n",me->name(1),me->query("id"),me->query("combat_exp")) );
    me->set(QUESTDIR+"宝藏/start",1);
	return 1;
  }
	command("say 李闯王当年确实威震朝野，可惜时不逢时，也听说留有一大宝藏，不知道是真是假。");
	return 1;
}
int start_condition(object ob)
{
	 if(!ob) return 0;
   ob->set_skill("force", 300);
	 ob->set_skill("dodge", 300);
	 ob->set_skill("parry", 300);
	 ob->set_skill("sword", 300);
	 ob->set_skill("cuff",300);
	 ob->set_skill("taxue-wuhen",300);
	 ob->set_skill("zhentian-quan",300);
	 ob->set_skill("lengquan-shengong",300);
	 ob->set_skill("miaojia-jianfa",300);
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
    if (!present("changjian",ob))
	    carry_object(BINGQI_D("sword"))->wield();
	  else command("wield changjian");
    ob->set_temp("quest/雪山飞狐/武功/lengquan",1);
	  i=me->query("max_pot");
	  if(p<150) p=150;
	  if(i<p) i=p;
	  i=i-100;
	  ob->set_skill("force", i+random(50));
	  ob->set_skill("dodge", i+random(50));
	  ob->set_skill("parry", i+random(50));
	  ob->set_skill("sword", i+random(50));
	  ob->set_skill("cuff",i+random(50));
	  ob->set_skill("taxue-wuhen",i+random(50));
	  ob->set_skill("zhentian-quan",i+random(50));
	  ob->set_skill("lengquan-shengong",i+random(50));
	  ob->set_skill("miaojia-jianfa",i+random(50));
	  i=me->query("combat_exp");
	  ob->set("combat_exp",i);
	  i=me->query("neili");
	  if(i<15000) i=15000;
	  ob->set("neili", i);
	  i=me->query("max_neili");
	  if(i<8000) i=8000;
	  ob->set("max_neili", i);
	  ob->set("jiali",200);
  	i=me->query("max_qi");
          ob->set("max_qi", i*(6+random(3))/4);
 	  ob->set("eff_qi", ob->query("max_qi"));
 	  ob->set("qi", ob->query("max_qi"));
    return 1;
}
int busy_pass(object ob)
{
	if(!ob) return 0;
	if(ob->query_temp("busy")) ob->delete_temp("busy");
	if(ob->query("busy")) ob->delete("busy");
  if(random(2)) message_vision(HIC"\n$N打了个哈气。\n"NOR,ob);
  else if (random(2)) message_vision(HIC"\n$N皱了皱眉头。\n"NOR,ob);
  else message_vision(HIC"\n$N伸了伸懒腰。\n"NOR,ob);
  return 1;
}

int accept_object(object who, object ob,object me)
{

	 if(ob->query("id")=="yu pei"&&ob->query("quest")&&ob->query("owner")==who->query("id"))
   {
     if(who->query(QUESTDIR4+"lengquanshengong") && !who->query(QUESTDIR4+"lengquanshengong_teach"))
     {
     	command("ah "+(string)who->query("id"));
     	command("whisper "+(string)who->query("id")+" 这是我爹爹的东西？你从哪里得来的？");
        tell_object(who,CYN"\n你在苗人凤的耳边悄声说道：我刚才去过闯王宝藏，在那里捡到的。\n"NOR);
     	who->set_temp(QUESTDIR4+"lengquanshengong_teach",1);
     	command("hehe");
     	command("say 30年前，田安豹与我爹爹结伴同去关外，当时我们不知为了何事，但见他二人兴高采烈，欢欢喜喜而去，可是从此不见归来。");
     	command("say 武林中朋友后来传言，说道他们两位为胡一刀所害，所以我与田师弟才大举向胡一刀寻仇，那知道这一切全是误会，全错了！");
     	who->start_busy(1);
     }
     else  command("thank "+(string)who->query("id"));
     call_out("destroying", 1, ob);
     return 1;
   }
    else
     command("? "+(string)who->query("id"));
   return 0;
}
void destroying(object obj)
{
        if(!userp(obj)) destruct(obj);
        return;
}
int ask_lengquanshengong()
{      int lv;
	object me = this_player();
       lv = me->query("max_pot")-100;
  if(me->query(QUESTDIR4+"lengquanshengong_teach"))
  {
  	if(me->query("potential")>4)
  	{
      message_vision("$N向$n请教有关冷泉神功的奥妙。\n", me, this_object());
      me->receive_damage("jing", 30);
      if(skill_check(me))
      {
          tell_object(me,HIC"你听了苗人凤的指点，可是领悟起来速度极慢。\n"NOR);
          tell_object(me,HIC"也许是因为其他内功的干扰，无法全心领悟冷泉神功。\n"NOR);
        me->add("potential",-(random(3)+3));
        if( me->query("potential")<0)
            me->set("potential",0);
        me->improve_skill("lengquan-shengong", 10+random(me->query_int()/2));
      }
      else
      {
        tell_object(me,"你听了苗人凤的指点，对冷泉神功的奥妙似乎有些心得。\n");
        me->add("potential",-(random(3)+2));
        if( me->query("potential")<0)
            me->set("potential",0);
        me->improve_skill("lengquan-shengong", 150+random(me->query_int()*2));
        me->improve_skill("force", random(me->query_int())/2);
      }
        //天赋“领悟大师”影响效果：  by spiderii@ty ..lsxk想法太过变态了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你经过转世重修后，领悟到了武技万变不离其宗的道理，瞬间领悟到了冷泉神功的精华所在。\n"NOR);
            me->set_skill("lengquan-shengong",lv);
            }
    }
    else
    {
      message_vision("$N向$n请教有关冷泉神功的奥妙。\n", me, this_object());
      tell_object(me,"你听了苗人凤的指点，可是还是不能理解。\n");
    }
    return 1;
  }
  if(me->query_temp(QUESTDIR4+"lengquanshengong_teach"))
  {
	  command("nod "+me->query("id"));
	  command("say 这位"+RANK_D->query_respect(me) +"对我有多次大恩。也罢，这门神功也传给你吧。");

    message_vision(HIR"$N向$n请教有关冷泉神功的奥妙。\n"NOR, me, this_object());
    me->receive_damage("jing", 30);
    if(skill_check(me))
    {
        tell_object(me,HIC"你听了苗人凤的指点，可是总感觉领悟起来极其困难。\n"NOR);
      tell_object(me,HIC"也许是因为其他内功的干扰，无法全心领悟冷泉神功。\n"NOR);
      me->improve_skill("lengquan-shengong", random(me->query_int()*2/3));
      me->delete_temp(QUESTDIR4+"lengquanshengong_teach");
      me->set(QUESTDIR4+"lengquanshengong_teach",1);
    }
    else
    {
    	tell_object(me,"你听了苗人凤的指点，对冷泉神功的奥妙似乎有些心得。\n");
      me->improve_skill("lengquan-shengong", 10+random(me->query_int()));
      me->improve_skill("force", random(me->query_int())/2);
      me->delete_temp(QUESTDIR4+"lengquanshengong_teach");
      me->set(QUESTDIR4+"lengquanshengong_teach",1);
    }
    return 1;
  }
  if(me->query(QUESTDIR4+"hujiadaofa")||me->query(QUESTDIR4+"hujiadaofa"))
  {
	  command("nod "+me->query("id"));
	  command("say 冷泉神功是胡家刀和苗家剑的基础内功，也只有冷泉神功才能最大限度发挥刀剑的威力。");
	  return 1;
  }
  if(me->query(QUESTDIR3+"over"))
  {
	  command("nod "+me->query("id"));
	  command("say 冷泉神功是闯王时期四大护卫的招牌功夫，这门武功也是我苗家武功的基础。");
	  return 1;
  }
	command("hehe");
	command("say 我号称打遍天下无敌手，靠的就是这身武功。");
	return 1;
}
int skill_check(object me)
{
	int i,p;
	mapping skill_status;
  string *sname;
  p=0;
  if(mapp(skill_status=me->query_skills()))
	{
		skill_status=me->query_skills();
    sname = keys(skill_status);
	  for(i=0; i < sizeof(skill_status); i++)
   	  if(SKILL_D(sname[i])->valid_enable("force")&&sname[i]!="lengquan-shengong") p=1;
  }
	return p;
}
