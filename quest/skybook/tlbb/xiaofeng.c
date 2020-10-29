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
int ask_skills();
int ask_save();
void greeting(object me);
void xiaofeng_guiyin(object me);

void create()
{
	set_name("萧峰", ({"xiao feng", "xiao", "feng"}));
	set("gender", "男性");
	set("nickname",HIB"奇侠"NOR);
	set("title",HIY"前丐帮帮主"NOR);
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
	set("neili", 30000);
	set("max_neili", 20000);
	set("jiali", 200);
  set("max_jingli", 15000);
  set("jingli", 15000);
	set("eff_jingli", 15000);
  set("combat_exp", 6000000);	 
	set_skill("force", 400);   
	set_skill("bangjue", 200);
	set_skill("literate", 200);        
	set_skill("medicine", 200);        
	set_skill("huntian-qigong", 420);
	set_skill("yijin-jing", 200);     
	set_skill("strike", 400);           
	set_skill("jingang-quan", 400);     
	set_skill("xianglong-zhang", 400);     
	set_skill("dodge", 400);      	     
	set_skill("xiaoyaoyou", 400);   
	set_skill("parry", 400);          
	set_skill("stick", 400);          
	set_skill("dagou-bang", 400);          
	set_skill("cuff", 400);          
	map_skill("cuff", "jingang-quan");
	map_skill("force", "huntian-qigong");
	map_skill("strike", "xianglong-zhang");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "xianglong-zhang");
	map_skill("stick", "dagou-bang");
	set("doule_attack",1);
	prepare_skill("strike","xianglong-zhang");
  set("chat_chance_combat", 99);
  set("chat_msg_combat", ({
          (: exert_function, "huntian" :),
          (: exert_function, "shentong" :),
          (: perform_action, "strike.paiyun" :),
          (: perform_action, "strike.xiao" :),
  }));
  set("inquiry", ([
		"段誉" : random(2)?"那是我二弟。":"我二弟一身内力震古烁今，六脉神剑更是天下无双。",
		"虚竹" : random(2)?"那是我三弟。":"我三弟现为缥缈宫宫主，只怕现在更是西夏国的驸马爷了。",
		"真相" : (: ask_truth :),
		"当年" : (: ask_truth :),
		"为什么" : (: ask_truth :),
		"原因" : (: ask_truth :),
		//太祖拳增加绝技
		"太祖拳" : (: ask_skills :),
		"拳理" : (: ask_skills :),

		"save" : (: ask_save :),
		"help" : (: ask_save :),
		"解救" : (: ask_save :),
		"搭救" : (: ask_save :),
		"救援" : (: ask_save :),
		"救命" : (: ask_save :),

		"萧远山" : (: ask_father :),
		"拜师" : "嗯....，我注定一声漂泊，还是算了吧。",
		"丐帮" : "丐帮是我家，我家在丐帮。",
		"少林" : "我一身武功出自少林，也算是半个少林弟子。",
		"天龙寺" : "天龙寺是大理段家武学的最高之地。",
		"洪七公" : "恩，听说下一辈中也是他为人最为侠义，武功最高。",
		"阿朱" : "......怕是这一生我唯一的牵挂了。",
		"阿紫" : "恩，不提也罢，丁老怪的弟子，那个不是心狠手辣。",
		"阿碧" : "阿朱的妹妹，听说和慕容公子在一起。",
		"天龙寺" : "天龙寺是大理段家武学的最高之地。",
		"降龙十八掌" : "这是我行走江湖的吃饭的东西，哈哈。",
		"排云双掌" : "这是我最得意的一招，也是最凶猛的一招。",
		"打狗棒" : "丐帮帮主之外不传之武功，确实精妙无比。",
		"归隐" : (: ask_yintui :),
		"隐退" : (: ask_yintui :),
		"洗手" : (: ask_yintui :),
		"隐退江湖" : (: ask_yintui :),
		"归隐江湖" : (: ask_yintui :),
		"喝酒" : "哈哈，一日不可无酒。等空闲时分，我们一同喝酒去！",
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
	object me;
	//object room;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
		if(!me->query_condition("killer")&&me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"lookcliff")&& !me->query_temp(QUESTDIR3+"over") && !me->query(QUESTDIR3+"over"))
		{
			this_object()->set("qi", this_object()->query("max_qi"));
			this_object()->set("eff_qi", this_object()->query("max_qi"));
			this_object()->set("neili", this_object()->query("max_neili")*2);
			message_vision(HIY"\n只听一声啸声，一个身影已经窜上峭壁，$n定眼一看，正是$N。\n"NOR,this_object(),me); 
			command("nod "+me->query("id")); 
			message_vision(HIR"$N微一凝神，运起「混天」神功，全身骨节发出一阵爆豆般的声响。\n\n"NOR,this_object());   
			tell_object(me,CYN"你惊讶地「啊！」了一声。\n"NOR);    
			message_vision(HIW"$N长长地舒了一口气，伤势看来基本全部恢复了。"NOR,this_object());                    
			tell_object(me,HIC"\n你没有料道，萧峰竟然恢复如此之迅速，果然是功夫了得。\n"NOR);  
			log_file("quest/TLBB", sprintf("%s(%s)萧峰来到颂摩崖，特此纪录。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) ); 
			me->set_temp(QUESTDIR3+"over",1);
			command("pat "+me->query("id")); 
			command("thank "+me->query("id"));
			remove_call_out("greeting");
			call_out("greeting",4,me);
			call_out("dest", 600,this_object());
		}
		if(!me->query_condition("killer")&& me->query(QUESTDIR4+"start") && me->query_temp(QUESTDIR4+"breakmen")&&!me->query_temp(QUESTDIR4+"helpstart") &&!me->query_temp(QUESTDIR4+"follow")&& !me->query(QUESTDIR4+"over"))
		{
			command("ah "+me->query("id"));
			message_vision(HIY"$n进来时，$N靠在铁笼的栏杆上，神色倒是正常。\n看暗室一旁酒坛堆积，感觉$N这里的日子竟也是好酒好饭，礼数不缺。\n"NOR,this_object(),me);   		
			command("say 没想到，又是"+RANK_D->query_respect(me) +"舍命相救。"); 
			command("touch "+me->query("id"));
			command("thank "+me->query("id"));
			me->start_busy(2);
			me->set_temp(QUESTDIR4+"helpstart",1);
			call_out("dest", 600,this_object());
		}
	} 
}

void greeting(object me)
{
	object ob=this_object();
	int i;
	if(!me)
	{
		message_vision(HIW"$N急急忙忙地离开这里。\n"NOR,ob);
		destruct(ob);
		return;
	}
	if(environment(this_object())!=environment(me)) 
	{
		command("chat "+me->name()+"怎么如此邋遢，竟然无端走开？");
		command("chat* heng "+me->query("id"));
		tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
		me->delete_temp("quest/天龙八部");
		me->delete_temp("quest/busy");//任务冲突标志取消
		me->delete(QUESTDIR3+"start");
		me->add("mana",-200);
		if(me->query("mana")<0) me->set("mana",0);
		return;
	}
	if(me->query(QUESTDIR3+"start") && me->query_temp(QUESTDIR3+"lookcliff")&& me->query_temp(QUESTDIR3+"over") && !me->query(QUESTDIR3+"over"))
	{
		message_vision(HIW"$N对$n表示衷心的感谢。\n"NOR,this_object(),me);
		tell_object(me,HIG"\n\n你走过去看了看萧峰，还是将你看到的告诉了萧峰：“智光大师所道的山壁上如今正中一大片尽是斧凿的印痕，\n"
			"显而易见，是有人故意将留下的字迹削去了。”\n"NOR);
		tell_room(environment(me),HIG"\n"+me->name()+"走到萧峰跟前，低声说了些什么。\n"NOR, ({ me }));

		command("oh");

		me->set(QUESTDIR3+"over",1);
		me->delete_temp("quest/天龙八部");
		me->delete_temp("quest/busy");//任务冲突标志取消
		me->start_busy(3);
		i=20+random(10);
		me->add("max_neili",i);
		me->add("combat_exp",me->query_skill("force")/2);
		me->add("mana",me->query_skill("force")/5);
        me->set(QUESTDIR+"time",time());
        me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
        tell_object(me,HIY"\n你于"+NATURE_D->game_time()+"终于帮助萧峰确定身世之谜，获得"+i+"点最大内力、"+me->query_skill("force")/2+"点经验和"+(int)me->query_skill("force")/5+"点声望。\n\n"NOR);
        log_file("quest/TLBB", sprintf("%s(%s) 萧峰身世确定。玩家结局选择中。奖励：%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), i,(me->query_skill("force")/2),me->query_skill("force")/5) );


		command("consider");
		message_vision(HIW"\n\n$N突然悲笑起来，四顾茫然，喃喃道：“看来我真是契丹人，我真的不是汉人。”\n"NOR,this_object());
		command("say");
		message_vision(HIC"$N神色渐渐有些不正常，似乎已经有些发狂。\n"NOR,this_object());
		command("crazy");
		tell_object(me,HIW"\n突然之间，你脑子闪过两个念头。一个因为这萧峰已确是契丹人，他若公开反对大宋，只怕朝廷不知多少人因此\n"
			"丧命，而且此时你趁他意乱伤神之际，正是扬你威名的大好时机；可是一个侠义之心告诉你，如此确似小人行为\n"
			"一般不堪，这契丹人中也有好人坏人，也可以行侠仗义，何必执著于身份。\n\n"NOR);
		remove_call_out("check_answer");
		call_out("check_answer",3,me,1);
	}
}
void check_answer(object me,int i)
{
	object ob=this_object();
	if(!ob) return;
	if(!me) 
	{
		message_vision(HIW"$N急急忙忙地离开这里。\n"NOR,ob);
		destruct(ob);
		return;
	}
	if(environment(ob)!=environment(me)) 
	{
		command("say "+me->name()+"什么时候走了？我也该走了。");
		message_vision(HIC"\n$N飞身跳下山崖，一瞬间已经踪影全无。\n"NOR,ob);
		destruct(ob);
		return;
	}
	if(me->is_fighting(ob)||ob->is_fighting(me)) 
	{
		remove_call_out("check_answer");
		ob->set("kill_id",me->query("id"));
		message_vision(HIW"$N对$n冷笑一声，竟然趁我之危！如此小看于我。\n"NOR,ob,me);
		me->set(QUESTDIR3+"bad",1);//这里只要下kill就认为选择恶人
		                           //但是奖励需要杀完才给
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		ob->kill_ob(me);
		command("perform strike.xiao");
		command("yun huntian");
		command("yun shentong");
		return;
	}
	if(me->query(QUESTDIR3+"over"))
	{
		if(random(2)) command("haha");
		else command("smile");
		command("cry");
		if(random(2)) command("say");
		message_vision(HIC"$N越发得有些癫狂。\n"NOR,ob);
		if(random(2)) command("crazy");

		if(i>=10)
		{
			message_vision(HIC"$n正迟疑间，只见$N猛一阵癫狂，飞身跳下山崖，等$n看时，已经踪影全无。\n"NOR,ob,me);
			log_file("quest/TLBB", sprintf("%s(%s)竟然让萧峰离开，以后可没机会的。\n", me->name(1),me->query("id")) );                  
			destruct(ob);
		}
		else
		{    	
			i++;
			if(i<2)  tell_object(me,HIR"一时间，你是劝其归隐（ask xiao about 归隐），还是为武林除害（kill xiao）？你一时委实难以决定。\n"NOR);
			else 
			{
				if(random(2)) tell_object(me,HIR"是劝其归隐（ask xiao about 归隐），还是为武林除害（kill xiao），瞬间的决定掌握在你手中。\n"NOR);
				else if(random(2))  tell_object(me,HIR"（ask xiao about 归隐）（kill xiao）两个命令都很简单。\n"NOR);
				else tell_object(me,HIR"你还有一个选择，不去理睬。何必理会这烦人的江湖琐事呢。\n"NOR);
			}
			tell_object(me,HIC"你还有"+(88-i*8)+"秒决定。\n"NOR);
			remove_call_out("check_answer");
			call_out("check_answer",8,me,i);
		}
	}
}
int ask_save()
{
    object me;
    me=this_player();
    if(me->query(QUESTDIR4+"over"))
    {
    	command("thank "+me->query("id"));
		return 1;
	}
	if(!me->query_condition("killer")&& me->query(QUESTDIR4+"start") 
		&& me->query_temp(QUESTDIR4+"breakmen")
		&& me->query_temp(QUESTDIR4+"helpstart") 
		&&!me->query_temp(QUESTDIR4+"follow")
		&& !me->query(QUESTDIR4+"over"))
	{
		tell_object(me,HIC"\n你上前说道，“我们还是赶快离开此地，只怕这次为了营救你，江湖中人已全部出动，无论丐帮、少林、大理、\n"
			"还是远在西域的缥缈七十二宫。”\n"NOR);
		command("nod");
    	command("pat "+me->query("id"));
		command("say 好，我们这就赶快一起闯出去。");
		log_file("quest/TLBB", sprintf("%s(%s)准备冲出大辽，特此纪录。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) ); 
		me->set_temp(QUESTDIR4+"follow",1);
		this_object()->set("daliao",me->query("id"));
		this_object()->set("qi", this_object()->query("max_qi"));
		this_object()->set("eff_qi", this_object()->query("max_qi"));
		this_object()->set("neili", this_object()->query("max_neili")*2);
		command("follow "+me->query("id"));
		message_vision(HIR"$N微一凝神，运起「混天」神功，全身骨节发出一阵爆豆般的声响。\n\n"NOR,this_object());   
		remove_call_out("check_me_where");
		call_out("check_me_where",1,me);
		return 1;
	}
	command("@@ "+me->query("id"));
	command("haha "+me->query("id"));
	command("pat "+me->query("id"));
	command("addoil "+me->query("id"));
	return 1;
}
void check_me_where(object me)
{
	object ob;
    int i;
	ob=this_object();
	remove_call_out("check_me_where");
	if(!ob->query("daliao")) return;
	if(!me || me->is_ghost()) 
	{
		ob->unconcious();
		return;
	}
	if(environment(ob)!=environment(me)) 
	{
		if(wizardp(me)) tell_object(me,HIR"\n寻找玩家!\n"NOR);
		message_vision(HIW"$N急急忙忙地离开这里。\n"NOR,ob);
		ob->set("qi", ob->query("max_qi"));
		ob->set("eff_qi", ob->query("max_qi"));
		ob->set("neili", ob->query("max_neili")*2);
		ob->move(environment(me));
		message_vision(HIW"$N匆匆地走了过来。\n"NOR,ob);
		message_vision("$N深深吸了几口气，脸色看起来好多了。\n", ob);
		message_vision("$N深深吸了几口气，精神看起来好多了。\n", ob);
	}

	command("kill liao bing");
	command("kill liao bing 2");
	if((string)file_name(environment(me))!="/d/xingxiu/daliao/shulin")
		call_out("check_me_where",1,me);
	else
	{
		me->start_busy(1);
        tell_object(me,HIG"\n你们边打边退，一路奔波，连续走过好几个地方，才来到一个一片树林边。\n"NOR);
		command("touch "+me->query("id"));
        message_vision(HIW"$N长长地舒了一口气。\n"NOR,ob);
		message_vision(HIW"$N长长地舒了一口气。\n"NOR,me);
		command("pat "+me->query("id"));
		command("shrug "+me->query("id"));
		command("whisper "+me->query("id")+" 穿过这片树林，一直南行，应该就可以回来中原了。");
		message_vision(HIW"$N突然高声而唱：“亡我祁连山，使我六畜不蕃息。亡我焉支山，使我妇女无颜色。”\n"NOR,ob);
		command("say 当年汉武帝大伐匈奴，抢夺了大片地方，匈奴人惨伤困苦。其实无论契丹、匈奴还是大宋，凡是战争，受苦的肯定是百姓。");
		message_vision(HIW"$N喟然吟道：“烽火燃不息，征战无已时。野战格斗死，败马号鸣向天悲。鸟鸢啄人肠，冲飞上挂枯枝树。士卒涂草莽，将军空尔为。”\n"NOR,ob);
		command("whisper "+me->query("id")+" 兵器乃凶器，圣人不得已而用之。也罢，我与中原武林之间的恩恩怨怨也一笔勾销。");
		command("wave "+me->query("id"));
		command("bye "+me->query("id"));

		i=20+random(10);
		if(!me->query(QUESTDIR4+"over")) 
		{
			me->add("max_neili",i);
			me->add("combat_exp",(me->query_skill("force")+500));
			me->add("mana",me->query_skill("force")/3);
			tell_object(me,HIY"\n你于"+NATURE_D->game_time()+"终于将萧峰从大辽解救出来，获得"+i+"点最大内力、"+(me->query_skill("force")+500)+"点经验和"+(int)me->query_skill("force")/3+"点声望。\n\n"NOR);
			log_file("quest/TLBB", sprintf("%s(%s) 大辽解救篇完成。奖励：%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), i,(me->query_skill("force")+500),me->query_skill("force")/3) );
		}
		me->set(QUESTDIR4+"over",1);
        me->set(QUESTDIR+"time",time());
        me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
        me->delete_temp("quest/天龙八部/大辽救援篇");
		me->delete_temp("quest/busy");//任务冲突标志取消
		destruct(ob);
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
	command("say 萧远山，不认识......");
	return 1;
}
int ask_skills()
{
    object me;
    me=this_player();
    if(me->query("quest/天龙八部/武功/quanli"))
    {
		command("pat "+me->query("id"));
		command("say 不是都告诉你了吗......");
		
		message_vision(HIY"\n$N向你呼的一拳打出，$n急忙应招。两人所使的拳招，都是一般的平平无奇，但$N每一招都是\n"
			             +"慢了一步，任由$n先发。$n一出招，$N跟着递招，也不知是由于他年轻力壮，还是行动加倍的\n"
						 +"迅捷，每一招都是后发先至。这“太祖长拳”本身拳招只有六十四招，但每一招都是相互克制，\n"
						 +"$N看准了对方的拳招，然后出一招愉好克制的拳法，$n焉得不败？\n\n"NOR,this_object(),me);
		command("haha "+me->query("id"));
		return 1;
	}
    if(!me->query(QUESTDIR3+"over"))
    {
    	command("heng");
    	command("say 我正忙着报仇，此仇不能不报。");
		return 1;
	}
    //可以考虑增加一个太祖拳的pfm
	//纯粹为了玩耍，威力一般甚至偏低

	command("say 不错，武功至理，关键在一个融会贯通，无论后发制人，还是先发制人，都要看情况而定。");
	command("pat "+me->query("id"));
	command("say 何谓平淡，太祖拳可是江湖上是武林中最为流行的武功，但是其中三味，又有谁真正体会到？");
	command("haha "+me->query("id"));

	message_vision(HIY"\n$N蓦地心念一动，呼的一拳打出，一招“冲阵斩将”，也正是“太祖长拳”中的招数。这一招\n"
		             +"姿工既潇洒大方已极，劲力更是刚中有柔，柔中有刚，武林高手毕生所盼望达到的拳术完美之\n"
					 +"境， 竟在这一招中青露无遗。\n"NOR,this_object());
	command("noshame "+me->query("id"));
	message_vision(HIY"\n$N点了点头，默想了一会，似乎对武功之道体会更深一步。\n\n"NOR,me);
	me->set("quest/天龙八部/武功/quanli",1);
	me->add("combat_exp",200);
	log_file("quest/TLBB", sprintf("%s(%s) 向萧峰询问拳理，获得200点经验。\n", me->name(1),me->query("id")) );
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
    	command("say 这么快你能找到我？BUG啊，靠，老实交待谁在帮你？");
		return 1;
	}
    if(me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"help")&&!me->query_temp(QUESTDIR3+"askxiao"))
    {
    	message_vision(HIY"$N听过$n的询问，顿时似乎苍老了很多。\n"NOR,this_object(),me);
    	command("say 我也不知道具体原委，这些日子以来，生不得安宁，朋友东分西裂，养父、师傅都无端被害。");
    	command("sigh");
    	command("say 我受伤未能远行，还请这位"+RANK_D->query_respect(me) +"去一次颂摩崖，那里据说有一块刻字记载当年事迹。");
    	command("shout");
    	command("thank "+me->query("id"));
    	me->set_temp(QUESTDIR3+"askxiao",1);
		return 1;
	}
    command("thank "+me->query("id"));
    command("say 一切有劳"+RANK_D->query_respect(me) +"了。");
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
    if(!me->query_temp(QUESTDIR3+"good") && !me->query(QUESTDIR3+"good") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"bad"))
    {
        remove_call_out("check_answer");
    	tell_object(me,HIW"你见萧峰呆呆发蒙，知道他正为这契丹人的身份伤神，却听萧峰越来越暴躁，大声号叫：“我不是汉人，我不是汉人！\n"
    	                  "我是契丹胡虏，我是契丹胡虏！”提起手来，一掌掌往山壁上劈去，壁上石屑四溅。乔峰心中郁怒难伸，仍是一掌掌的\n"
    	                  "劈去，似要将这一个多月来所受的种种委屈，都要向这块石壁发泄，到得后来，手掌出血，一个个血手印拍上石壁，他\n"
    	                  "兀自不停。\n\n"NOR);
		command("shout");
    	message_vision(HIY"$N渐渐发起狂来，神色却是越来越是悲痛。\n\n"NOR,this_object());
    	tell_object(me,HIW"你知道似萧峰这等武功若不及时劝说，这等悲愤只怕内功大有损伤，当即哈哈大笑一声。果然，萧峰怒视于你。你且自\n"
    	                  "顾说道：“大丈夫提得起、放得下，汉人中有好人坏人，契丹人中，自然也有好人坏人。你生为契丹人又当如何，只要\n"
    	                  "行侠仗义，这天下还不是要去要来”。\n\n"NOR);          	 
    	command("ah "+me->query("id"));
		me->set_temp(QUESTDIR3+"good",1);
		command("papaya");
    	command("consider");
		command("papaya "+this_object()->query("id"));
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
   object ob=this_object();
   if(!me) 
   {
	   message_vision(HIW"$N急急忙忙地离开这里。\n"NOR,ob);
	   destruct(ob);
	   return;
   }
  if(environment(ob)!=environment(me)) 
  {
    command("chat "+me->name()+"怎么如此邋遢，竟然无端走开？");
    command("chat* heng "+me->query("id"));
    tell_object(me,HIG"\n你这种情况竟然临阵逃脱，实在违背侠义之情。你的江湖威望大幅下降。\n"NOR); 
	me->delete_temp("quest/天龙八部");
	me->delete_temp("quest/busy");//任务冲突标志取消
    me->delete(QUESTDIR3+"start");
    me->delete(QUESTDIR3+"over");
    me->add("mana",-200);
    if(me->query("mana")<0) me->set("mana",0);
	destruct(ob);
    return;
  }
  if(me->query_temp(QUESTDIR3+"good") && !me->query(QUESTDIR3+"good") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"bad"))
  {
    command("nod "+me->query("id"));
    tell_object(me,HIG"\n却见萧峰脸色大见缓和，以萧峰原本的大智慧，也定能明白这其中的道理。你也放下心来。\n"NOR);
    command("sigh");
    command("pat "+me->query("id"));
    command("say 也罢，我这就回我大辽，做我自己，还自行侠仗义，怎能这般自甘消沉。");
    command("haha");
    command("thank "+me->query("id"));
    command("wave "+me->query("id"));
    command("bye "+me->query("id"));
    me->set(QUESTDIR3+"good",1);
	me->delete_temp("quest/天龙八部");
	me->delete_temp("quest/busy");//任务冲突标志取消
	me->set(QUESTDIR+"time",time());
	me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
	me->add("mana",me->query_skill("force")/4);
    tell_object(me,HIY"\n\n你于"+NATURE_D->game_time()+"选择劝说萧峰归隐江湖，也算功德无量，获得"+(int)me->query_skill("force")/4+"点声望的奖励。\n\n");
	log_file("quest/TLBB", sprintf("%s(%s) 选择劝说萧峰归隐江湖。获得%d点声望。\n", me->name(1),me->query("id"), me->query_skill("force")/4) );
	destruct(ob);
  }
}
void kill_ob(object me)
{
 if(me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR3+"good") && !me->query(QUESTDIR3+"bad"))
  {
    message_vision(HIR"$N呼啸一声，虽然我并非最佳状态，也不是"+me->name()+"之辈就能偷袭的！\n"NOR,this_object());
    command("chat* sneer "+me->query("id"));
   }
  ::kill_ob(me);
}
void die()
{
  object me,ob=this_object();
  int i;
  if(ob->query("kill_id")
         && (me=present(ob->query("kill_id"),environment(ob)))
	  && me->query(QUESTDIR3+"over")
	  && !me->query(QUESTDIR3+"good")
	  && me->query(QUESTDIR3+"bad"))
	{
		me->delete_temp("quest/天龙八部");
		me->delete_temp("quest/busy");//任务冲突标志取消
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		command("chat* heng");
		command("chat 好好，"+me->name()+"竟然趁我不注意偷袭我，等我武功恢复之日，当是中原武林血洗之时！");
		command("sneer "+me->query("id"));
		command("dead "+me->query("id"));
		command("bye "+me->query("id"));
		i = 10+random(20);
		me->add("max_neili",i);
		tell_object(me,HIY"\n\n你于"+NATURE_D->game_time()+"选择为武林除害，击败萧峰，获得"+i+"点内力的奖励。\n\n");
		log_file("quest/TLBB", sprintf("%s(%s) 选择击败萧峰。获得%d点内力。\n", me->name(1),me->query("id"), i) );
		destruct(ob);
		return;
	}
  if(ob->query("daliao")
    && (me=find_player(ob->query("daliao")))
    && me->query(QUESTDIR4+"start")
    && !me->query(QUESTDIR4+"over"))
	{
		command("chat* inn "+me->query("id"));
		command("say 想不到敌人如此强劲，"+me->name()+"不要管我，你还是先自离开吧，不要枉自送了性命，有机会再会！");
		command("dead");
		command("wave "+me->query("id"));
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		me->delete_temp("quest/天龙八部");
		me->delete_temp("quest/busy");//任务冲突标志取消
		tell_object(me,HIY"\n\n你于"+NATURE_D->game_time()+"营救萧峰失败。\n\n");
		log_file("quest/TLBB", sprintf("%s(%s) 营救萧峰失败，萧峰死亡。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")));
		destruct(ob);
		return;
  }
  if(ob->query("no_death"))
  {
	  ob->set("qi", ob->query("max_qi")*2/3);
	  ob->set("eff_qi", ob->query("max_qi")*2/3);
	  ob->set("jing", ob->query("max_jing"));
	  ob->set("eff_jing", ob->query("max_jing"));
	  ob->add("neili", ob->query("max_neili")*2);
	  ob->set("jingli", ob->query("max_jingli"));
	  if(ob->is_busy()) ob->start_busy(-1);	  
	  message_vision("$N深深吸了几口气，脸色看起来好多了。\n", ob);
	  message_vision("$N深深吸了几口气，精神看起来好多了。\n", ob);
	  message_vision(HIR "\n$N微一凝神，运起混天气功，全身骨节发出一阵爆豆般的声响。\n" NOR, ob);
	  command("heng");
	  return;
  }
  ::die();
}
void unconcious()
{
  die();
}
void dest(object ob)
{
  if(!ob) return;
  tell_room(environment(ob), HIR+"\n"+ob->name()+"匆匆忙忙地离开了。\n"NOR);
  destruct(ob);
}
