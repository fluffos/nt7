// Npc: /kungfu/class/shaolin/xuan-ci.c
// add by tangfeng@SJ 2004


inherit NPC;
inherit F_MASTER;
#include <ansi.h>

int ask_job();
int ask_times();
int ask1();
int ask2();
int ask3();
int ask_xiaofeng();
int ask_yeerniang();
int ask_zhangxing();
int ask_xuzhu();
void zhangxing(object me,object ob);
int ask_zuinie();

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"

void create()
{
	set_name("玄慈大师", ({
		"xuanci dashi",
		"xuanci",
		"dashi",
	}));
	set("long", "他是一位白须白眉的老僧，身穿一袭金丝绣红袈裟。\n"
		"他身材略显佝偻，但却满面红光，目蕴慈笑，显得神完气足。\n"
	);

	set("nickname", "少林寺方丈");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");
	set("unique", 1);
	set("no_bark",1);

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 2000);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 180);
	set("combat_exp", 1200000);
	set("score", 0);

	set_skill("force", 160);
	set_skill("yijin-jing",160);
	set_skill("dodge", 160);
	set_skill("shaolin-shenfa", 160);
	set_skill("finger", 160);
	set_skill("strike", 160);
	set_skill("hand", 160);
	set_skill("claw", 160);
	set_skill("parry", 160);
	set_skill("nianhua-zhi", 160);
	set_skill("sanhua-zhang", 160);
	set_skill("fengyun-shou", 160);
	set_skill("longzhua-gong", 160);
	set_skill("buddhism", 160);
	set_skill("literate", 160);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "nianhua-zhi");
	map_skill("strike", "sanhua-zhang");
	map_skill("hand", "fengyun-shou");
	map_skill("claw", "longzhua-gong");
	map_skill("parry", "nianhua-zhi");

	prepare_skill("finger", "nianhua-zhi");
	prepare_skill("strike", "sanhua-zhang");

	create_family("少林派", 36, "弟子");

	set("inquiry", ([
		"job" : (: ask_job :),
		"贡献": (: ask_times :),
//		"萧远山":  (: ask1 :),
//		"杀孽":  (: ask2 :),
//		"舍身消业": (: ask3 :),
		"少林" : "我弥陀佛，老衲就是少林主持。不知道施主上我少林所谓何事。\n",
		"主持" : "我弥陀佛，老衲就是少林主持。",
		"萧峰" : "他就是丐帮帮主，一身武功自不用说，其胆识智慧也是江湖一流。只是......",
		"萧远山" : "当年一场往事，都已经过去，萧施主现在神僧那里。",
		"无名神僧" : "神僧，他老人家，当称达摩转世，佛法超群。",
		"神僧" : "神僧，他老人家，当称达摩转世，佛法超群。",
		"虚竹" : (: ask_xuzhu :),

		"罪孽" : (: ask_zuinie :),
		"耻辱" : (: ask_zuinie :),
		"败类" : (: ask_zuinie :),

		"救援萧峰" : (: ask_xiaofeng :),
		"解救萧峰" : (: ask_xiaofeng :),
		"援救萧峰" : (: ask_xiaofeng :),
		"救援" : (: ask_xiaofeng :),
		"解救" : (: ask_xiaofeng :),
		"援救" : (: ask_xiaofeng :),
		"叶二娘" : (: ask_yeerniang :),
		"私生子" : (: ask_yeerniang :),
		"惩罚" : (: ask_zhangxing :),
		"杖刑" : (: ask_zhangxing :),
		"受罚" : (: ask_zhangxing :),
	]));

	setup();

	carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
	object me;
	mapping ob_fam, my_fam;
	string name;

	me = this_object();
	my_fam  = me->query("family");

	name = ob->query("name");

	if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "少林派") {
		command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
		return;
	}

	if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派") {
		command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺内学艺。");
		return;
	}

	if ( ob_fam["generation"] <= my_fam["generation"] ) {
		command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
		return;
	}

	if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..0] == "澄") {
		command("say " + ob_fam["master_name"] + "的徒弟怎麽跑到我这儿来了，哈哈哈 !");
		command("recruit " + ob->query("id"));
	}
	else {
		command("say " + RANK_D->query_respect(ob) + "，你辈份不合，不能越级拜师。");
	}
}

int accept_object(object apper, object ob)
{
	int lvl;
	object me = this_object();

	message_vision(sprintf("$N给$n一%s%s。\n", ob->query("unit"), ob->name()), apper, me);
	if( ob->query("id") != "muou" || userp(ob)){
		command("say 这东西我要来没用。");
		return 0;
	}

	notify_fail("");
	if (!apper->query_temp("lh_teacher")
	 || !apper->query_condition("lh_job")){
		message_vision("$N一把夺过木偶，怒道：你从哪里偷来的?\n", me);
		destruct(ob);
		return 0;
	}
	command("touch "+apper->query("id"));
	message_vision("$N感动得热泪盈眶，说道：老衲终于重见我少林重宝了！\n", me);
	command("thank "+apper->query("id"));
	lvl = 200 + random(50);
	apper->add("combat_exp", lvl);
	if (apper->add("potential", lvl/5+random(lvl/10)) >= apper->query("max_pot"))
		apper->set("potential", apper->query("max_pot"));
	apper->improve_skill("yijin-jing",random((int)apper->query("int"))* 2);

	log_file("job/muou", sprintf("%8s%-10s得到木偶，交给玄慈，得到奖励：%3d，现经验：%d。\n",
		apper->query("name"), "("+apper->query("id")+")", lvl, apper->query("combat_exp") ),apper);

	destruct(ob);
	return 0;
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;

	if(ob->query_temp("job_name")!="服侍玄慈方丈") return;
	command("pat "+ob->query("id"));
	command("say " + RANK_D->query_respect(ob)+ "你就给我按摩一下吧(massage 方丈)呵呵呵。\n");
}

int ask_job()
{
	object me = this_player(), ob = this_object(),ob1;
	int lvl,exp;
	object *team, maxplayer, minplayer;
	int totalexp=0, maxexp, minexp;
	int size,i;
	int index;
	int y;

	string* file= ({ "/d/shaolin/lhtang", "/d/shaolin/brtang",
		"/d/shaolin/smdian", "/d/shaolin/zhlou7", "/d/shaolin/gulou7",
		"/d/shaolin/houdian", "/d/shaolin/zdyuan", "/d/shaolin/pingtai",
		"/d/shaolin/putiyuan", "/d/shaolin/yaowang", "/d/shaolin/xumidian",
		"/d/shaolin/liuzu","/d/shaolin/jnlwang","/d/shaolin/lxting",
		"/d/shaolin/qfdian","/d/shaolin/czan","/d/shaolin/bydian",
		"/d/shaolin/dzdian","/d/shaolin/xcping"
	});
	string* name= ({ "罗汉堂","般若堂","山门殿","钟楼","鼓楼","后殿",
                        "证道院","平台","菩提院","药王院","须弥殿",
                        "六祖殿","紧那罗王殿","立雪亭","千佛殿","初祖庵",
                        "白衣殿","地藏殿","心禅坪"});
	string *name1=({ "方正大师","空见大师","空闻大师","空智大师","空性大师", });
	string *long=({
                "他是一位身材矮小的老年僧人，容颜瘦削，神色慈和，也瞧不出有多少年纪。\n",
                "他是一个身材瘦小的老年僧人，穿一身洗得发白的月白僧衣。\n",
                "他白眉下垂，直覆到眼上，便似长眉罗汉一般。\n",
                "他身躯雄伟，貌相威武。\n",
                "他一脸的苦相，嘴角下垂。\n",
	});
	int teams;
	string addr;

	if( me->query_condition("job_busy")
	|| me->query_condition("sljob")
	|| me->query_condition("sl_job_busy")
	|| me->query("job_name") == "恒山救援"){
		command("say 我这里现在没有什么任务给你。" );
		return 1;
	}

	if(me->query_temp("quest/busy")) //added by tangfeng 与quest冲突
	{
		command("say 现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。" );
		return 1;
	}

	if( me->query_temp("sljob/asked")
	 || me->query_temp("sljob/join")){
		command("say 你刚才不是已经问过了吗？" );
		return 1;
	}

	if(!wizardp(me)&& me->query("combat_exp") >= me->query("slexp") && me->query("combat_exp") <= me->query("slexp") + 500){
		command("say 你武功精进也太慢了，老衲怎么放心让你去干啊。");
		return 1;
	}

	y = sizeof(children(__DIR__"fang-zheng"));

	if( y > 2) {
		command("say 嗯，已经有人在帮我了，你还是去忙点别的什么吧。");
		return 1;
	}

	if( me->query("shen") < 1 ){
		command("heng");
		command("say 这位" + RANK_D->query_respect(me)+"眼露凶光，我少林名门正派，可不敢劳你大架。");
		return 1;
	}

	index = ob->query("index");

	command("say 我接到本派弟子通报，魔教教主任我行亲率数万教众，\n"
             + "欲血洗恒山派。虽定静师太并未向我少林求援，但少林不能坐视恒山\n"
             + "覆灭，我已请"+ name1[index]+ "亲率罗汉堂和般若堂弟子前去救援。");

	//if (sizeof(me->query_team()) < 2 && me->  )
	if (sizeof(me->query_team()) < 2 && (me->query("family/family_name") != "少林派" || me->query("wxz"))) {
		command("say 以" + RANK_D->query_respect(me)+ "的武功修为，似乎尚无力单独完成这个任务。" );
		return 1;
	}
	else {
		team = me->query_team();
		if (!sizeof(team)) team = ({ me });
		if(sizeof(team) > 4) {
			command("say 此去恒山路途危险，单靠人多是没用的。");
			return 1;
		}
		for (i=0;i<sizeof(team);i++){
			if (!team[i]) {
				command("say 你的队伍出现了问题，请解散并重新组建。");
				return 1;
			}
			if (team[i] == me) continue;
			if (!present(team[i], environment(me))){
				command("say 咦？怎么好象人不全啊？"+team[i]->query("name")+"怎么没来？");
				return 1;
			}
			if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
				command("say 你还是将"+team[i]->query("name")+"换成其他人吧。");
				return 1;
			}
		}
		maxexp=minexp=team[0]->query("combat_exp");
        	maxplayer=team[0];
		minplayer=team[0];
		for (i=0;i<sizeof(team);i++){
			if (team[i]->query("combat_exp") < 1000000) {
				command("say 此去恒山路途危险，我看这位"+RANK_D->query_respect(me)
					+"需要一个好搭档！");
				return 1;
			}
			if( team[i]->query_condition("job_busy")
			|| team[i]->query_condition("sljob")
			|| team[i]->query_condition("sl_job_busy")
			|| team[i]->query("job_name") == "恒山救援"){
				command("say 你队伍中的"+team[i]->query("name")+"正在做其它任务呢。");
				return 1;
			}
			if( team[i]->query("combat_exp") - 500 <= team[i]->query("slexp")
			&& team[i]->query("sldeath")==team[i]->query("death_count")){
				command("say 你队伍中的"+team[i]->query("name")+"武功精进太慢，这个搭档是否应该再选一个啊。");
				return 1;
			}
			if (team[i]->query("shen") < 0) {
				command("whisper "+ me->query("id")+" 此去恒山乃我正派中事，看你队伍中的"+team[i]->query("name")+
					"眼露凶光，不会是那任老贼派来的奸细吧？");
				return 1;
			}
			totalexp += team[i]->query("combat_exp");
			if(team[i]->query("combat_exp") > maxexp ){
				maxexp=team[i]->query("combat_exp");
				maxplayer=team[i];
			}
			else if(team[i]->query("combat_exp") < minexp){
				minexp=team[i]->query("combat_exp");
				minplayer=team[i];
			}
		}
		if (totalexp < 2000000 || maxexp-minexp > 1000000) {
	        	command("say 此去恒山路途危险，我看诸位似乎无此能力？");
			return 1;
		}
		if (sizeof(team) != 0 && (team[0] != me)){
			command("say 只有队伍首领才能申请任务。");
			return 1;
		}
		for (i=0;i<sizeof(team);i++){
			team[i]->delete_temp("sljob");
			team[i]->set_temp("sljob/join", 1);
			team[i]->set("slexp", team[i]->query("combat_exp"));
			team[i]->apply_condition("sljob",40);
			team[i]->apply_condition("job_busy",40);
			team[i]->set("sldeath",team[i]->query("death_count"));
	        }
	        teams=sizeof(team);
	}

	ob->set("index", (ob->query("index")+1)%5);
	size=sizeof(file);
	i=random(size);
	addr=file[i];

	command("say 就请各位随同"+name1[index]+"前去恒山，一路小心。");
	command("say "+name1[index]+"现在"+name[i]+"。\n");
	log_file("job/husong", sprintf("%8s%-10s救援，%d人\n",
		me->query("name"),"("+me->query("id")+")", teams ),me);
	ob1=new(__DIR__"fang-zheng");
	ob1->move( file[i] );
	ob1->set("name",name1[index]);
	ob1->set("long",long[index]);
	ob1->set_temp("teams",teams);
	if(teams>3)
		ob1->set_temp("team4",team[3]);
	if(teams>2)
		ob1->set_temp("team3",team[2]);
	if(teams>1)
		ob1->set_temp("team2",team[1]);
	if(teams>0){
		if( me->query_team() )
			ob1->set_temp("team1",team[0]);
		else
			ob1->set_temp("team1",me);
	}

	if( maxplayer->query("max_pot")-20 > minplayer->query("max_pot"))
		lvl = minplayer->query("max_pot")-100-10;
	else
		lvl = maxplayer->query("max_pot")-100-30;

	exp = minplayer->query("combat_exp");
	ob1->set("combat_exp",exp);
	ob1->set("max_qi",5000+exp/1200);
	ob1->set("qi",ob1->query("max_qi"));
	ob1->set("eff_qi",ob1->query("max_qi"));
	ob1->set("jing",4000);
	ob1->set("max_neili",4000+exp/1500);
	ob1->set("neili",ob1->query("max_neili"));
	ob1->set("eff_jingli",3500);
	ob1->set_temp("lvl",lvl);
	ob1->set_skill("dodge",lvl);
	ob1->set_skill("force", lvl);
	ob1->set_skill("yijin-jing", lvl);
	ob1->set_skill("shaolin-shenfa", lvl);
	ob1->set_skill("parry", lvl);
	ob1->set_skill("finger",lvl);
	ob1->set_skill("yizhi-chan",lvl);
	ob1->set_skill("medicine",150);
	ob1->set_skill("buddhism", 200);
	ob1->set_skill("literate", 200);
	ob1->map_skill("force", "yijin-jing");
	ob1->map_skill("dodge", "shaolin-shenfa");
	ob1->map_skill("finger", "yizhi-chan");
	ob1->map_skill("parry", "yizhi-chan");
	ob1->set("jobleader",me);
	ob1->set("xuanci",ob);
	ob1->set("teams",teams);
	ob1->set("lvl",maxplayer->query("max_pot")-100);
	ob1->set_name(ob1->query("name"), ({ me->query("id")+"'s dashi" }));
	tell_room(environment(ob1), ob1->name() + "轻诵佛号，慢慢地走了过来。\n", ({ ob1 }));

	me->set_temp("sljob/asked",1);
	me->apply_condition("sljob",40);
	me->apply_condition("job_busy",40);
	return 1;
}

int ask_times()
{
	object me=this_player();
	command("say 你已经为少林做了"
		+ CHINESE_D->chinese_number( me->query("job_time/少林救援") )
		+ "次贡献。");
	command("addoil "+me->query("id"));
	return 1;
}

int ask1()
{
	object me;

	me=this_player();

	if( me->query("family/family_name")!="少林派" )
		return 0;
	if( me->query("family/generation")>36 )
		return 0;

	command( "say 老衲当年误信人言，率众于雁门关外截杀萧施主全家，\n"
                + "造下无穷杀孽，今日想来，追悔末及。" );
	command( "sigh" );
	me->set_temp("sl/pks",1);
	return 1;
}

int ask2()
{
	object me = this_player();

	if( me->query_temp("sl/pks") < 1 )
		return 0;
	command( "say 老衲得知事情真相后心灰意冷，幸得本门一位高僧点化，以无上\n"
		+"佛法舍身消业，方使心情振奋，但也不免大误禅修。" );
	me->set_temp("sl/pks",2);
	return 1;
}

int ask3()
{
	object me = this_player();

	if( me->query_temp("sl/pks") < 2 )
		return 0;
	command( "whisper " + me->query("id") +
		" 大师既有此心，可去藏经阁找一位扫地的无名老僧。" );
	command( "buddhi dashi" );
	me->set_temp("sl/pks",3);
	return 1;
}

//以下是quest部分
int ask_xuzhu()
{
	object me = this_player();
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& (me->query_temp(QUESTDIR5+"son")||me->query(QUESTDIR5+"over")))
	{
	  message_vision(HIY"$N面露悲痛之色，良久没有说话，只是叹息一声。\n"NOR,this_object());
	  if(random(2)) command("sigh");
	  else command("say");
	  return 1;
	}
	command("? "+me->query("id"));
	command("say 虚竹，好像是少林第三十九代弟子之一。不知道施主找他何事？");
	return 1;
}

int ask_yeerniang()
{
	object me = this_player();
 	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   command("say "+RANK_D->query_respect(me) +"还是小心通缉吧！");
	   return 1;
	}
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& !me->query_temp(QUESTDIR5+"yeerniang")&& !me->query(QUESTDIR5+"over"))
	{
		command("? "+me->query("id"));
	  message_vision(HIC"$N对$n哼了一声，道：不要假装不明白的样子，二十年前，你难道你真的什么都不记得了......\n"NOR,me,this_object());
	  command("consider");
	  message_vision(HIY"$N大声道：“20年前你勾引叶家庄叶二姑娘，本来好端端的姑娘，美貌贞淑。可是被你所引诱，失身于你，\n"
	                    "还为你生下一个孩子，但是你只顾到自己的声名前程，全不顾念你一个年纪轻轻的姑娘，未嫁生子，处境是\n"
	                    "何等的凄惨。二十年来你可知道，当年的叶二姑娘就是现在的四大恶人叶二娘！”\n\n"NOR,me);
	  command("oh");
	  message_vision(HIG"\n$N摇摇头道：当年之事谁对谁错很难说清，就算我错，当时我也无力照顾，至于孩子，我当真不知。\n"NOR,this_object());
	  command("dunno "+me->query("id"));
		command("say 我真的没有料到叶二娘就是当年叶家庄的叶二姑娘。罪孽罪孽。");
		me->set_temp(QUESTDIR5+"yeerniang",1);
		return 1;
	}
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& (me->query_temp(QUESTDIR5+"yeerniang")||me->query(QUESTDIR5+"over")))
	{
		command("sigh");
		command("say 我真的没有料到叶二娘就是当年叶家庄的叶二姑娘。罪孽罪孽。");
		return 1;
	}
	command("say 可是四大恶人的叶二娘？");
	command("dunno "+me->query("id"));
	return 1;
}
int ask_zuinie()
{
	object me = this_player();
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& me->query_temp(QUESTDIR5+"yeerniang")
	   && !me->query_temp(QUESTDIR5+"zuinie")&& !me->query(QUESTDIR5+"over"))
	{
	  message_vision(HIY"$N哈哈笑道：你自当掩饰自己，可是作为少林主持，难道不感到羞愧。少林号称佛门圣地，确有私生子的怪事。\n"NOR,me);
	  message_vision(HIG"$N缓缓道了声佛号，良久没有说话，只是叹息一声。\n"NOR,this_object());
		command("sigh");
		me->set_temp(QUESTDIR5+"zuinie",1);
		return 1;
	}
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& (me->query_temp(QUESTDIR5+"yeerniang")||me->query(QUESTDIR5+"over")))
	{
		command("sigh");
		command("say 我真的没有料到叶二娘就是当年叶家庄的叶二姑娘。罪孽罪孽。");
		return 1;
	}
	command("say 我弥陀佛！我佛慈悲！");
	return 1;
}
int ask_zhangxing()
{
	object obj,me = this_player();
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& me->query_temp(QUESTDIR5+"yeerniang")&& me->query_temp(QUESTDIR5+"zuinie")&& !me->query_temp(QUESTDIR5+"zhangxing")&& !me->query(QUESTDIR5+"over"))
	{
	  message_vision(HIC"$N哼了一声，道：家法何在，寺规何在。想不到百年少林竟然出现这等事情，还妄称佛门善地。\n"NOR,me);
		command("sigh "+me->query("id"));
		command("nod "+me->query("id"));

	  message_vision(HIY"\n$N朗声说道：“不错，老衲犯了佛门大戒，有伤鹳林清誉。国有国法，家有家规。自来任何门派\n"
	                    "帮会，宗族寺院，都难免有不肖弟子。清名令誉之保全，不在求永远无人犯规，在求事事按律惩处，不\n"
	                    "稍假借。依本寺戒律，玄慈犯了淫戒，且身为方丈，罪刑加倍。执法僧重重责打玄慈二百棍。少林寺清\n"
	                    "誉攸关，不得循私舞弊。”说着跪伏在地，遥遥对着佛像，自行捋起了僧袍，露出背脊。\n"NOR,this_object());
	  command("sneer "+me->query("id"));
	  obj=new("/d/shaolin/npc/zjseng.c");
	  obj->move(environment(me));
    message_vision(WHT"$N匆匆了走了过来。\n"NOR,obj);
	message_vision(HIY"$N向$n施礼，道了声佛号，就侍立在一边。\n"NOR,obj,this_object());
	  obj->command("bow "+this_object()->query("id"));
	  obj=new("/d/shaolin/npc/zjseng.c");
	  obj->move(environment(me));
    message_vision(WHT"$N匆匆了走了过来。\n"NOR,obj);
	message_vision(HIY"$N向$n施礼，道了声佛号，就侍立在一边。\n"NOR,obj,this_object());
	  obj->command("bow "+this_object()->query("id"));
	  command("nod "+obj->query("id"));
	  message_vision(HIG"\n$N厉声道：“我少林寺千年清誉，岂可坏于我手？执法僧，用刑。”\n"NOR,this_object());
    remove_call_out("zhangxing");
    call_out("zhangxing",5,me,this_object());
		return 1;
	}
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& (me->query_temp(QUESTDIR5+"zhangxing")||me->query(QUESTDIR5+"over")))
	{
	  message_vision(HIY"$N道了声佛号，面露悲痛之色。\n"NOR,this_object());
		command("say 老衲确实罪孽。我弥陀佛。");
		return 1;
	}
	command("? "+me->query("id"));
	return 1;
}
void zhangxing(object me,object ob)
{
  if(!me) return;
  if(!ob) return;
  if(environment(me)!=environment(ob))
  {
  	ob->command("sigh");
  	message_vision(HIY"$N似乎犹豫了一下，还是站了起来，背过身去，不再言语。\n"NOR,ob);
  	tell_object(me,HIY"这等时候竟然走开，复兴慕容天下的任务如何完成？\n"NOR);
   	me->delete(QUESTDIR5+"start");
   	me->delete_temp("quest/天龙八部");
	me->delete_temp("quest/busy");//任务冲突标志取消
  	return;
  }
	if(me->query(QUESTDIR3+"bad") && me->query(QUESTDIR5+"start")&& me->query_temp(QUESTDIR5+"yeerniang")&& !me->query_temp(QUESTDIR5+"zhangxing")&& !me->query(QUESTDIR5+"over"))
	{
	  message_vision(HIC"二僧知道方丈受刑，最难受的还是当众受辱，不在皮肉之苦，倘若手下容情，给旁人瞧了出来落下话柄，\n"
	                    "那么方丈这番受辱反而成为毫无结果了，是以一棍棍打将下去，拍拍有声，片刻间便将玄慈背上、股上打\n"
	                    "得满是杖痕，血溅僧侣。堪堪又打了一百余杖，$N支持不住，撑在地下的双手一软，脸孔触到尘土。\n"NOR,this_object());
    message_vision(WHT"\n$N哈哈大笑起来，“我不杀你，少林自此名誉一败涂地。这余下五十杖不打也罢。”\n"NOR,me);
		me->set_temp(QUESTDIR5+"zhangxing",1);
	if(me->query("family"))
	  command("chat "+me->query("family/master_name")+"也算是一代宗师，没有料到其弟子"+me->name()+"竟然行事如此恶毒！");
	else command("faint "+me->query("id"));
	command("inn "+me->query("id"));
    message_vision(WHT"\n$N一时间气急攻心，竟然昏了过去。\n"NOR,this_object());
	command("faint");
	tell_object(me,HIY"\n你哈哈大笑，终于完成任务，只是......返回慕容的路上，恐怕更加危险重重。\n"NOR);
	this_object()->unconcious();
   }
   return;
}

int ask_xiaofeng()
{
	object room,me = this_player();
	object *obj;
	int x;
	if(me->query(QUESTDIR3+"bad") )
  {
  	command("heng");
  	command("say 难道不是当年强迫萧峰走出中原，叫我如何相信你？");
  	return 1;
  }
  	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   command("say "+RANK_D->query_respect(me) +"还是小心通缉吧！");
	   return 1;
	}
	if(me->query(QUESTDIR3+"good") &&!me->query_temp(QUESTDIR4+"shaolinzhen")&& !me->query(QUESTDIR4+"start"))
	{
		if(!me->query_temp(QUESTDIR4+"askxuanci"))
		{
			message_vision(HIC"你急声道：江湖传言，萧峰为避免南征之战，拒绝可汗命令，现被投入铁牢之中。\n"NOR,me);
			command("ah "+me->query("id"));
		}
		//增加时间和经验间隔限制
		//时间一天，经验500K
        if(!me->query_temp(QUESTDIR4+"dagouzhen") && me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
		{
			command("say 今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！");
			return 1;
		}
        if(!me->query_temp(QUESTDIR4+"dagouzhen") && me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000)
		{
			command("say 以"+RANK_D->query_respect(me) +"目前的经验就算目前有情况，也帮不上什么忙，还是抓紧练功吧！");
			return 1;
		}
	//只能一个人做
	obj = users();
	x = sizeof(obj);
	while(x--) {
		  if ( obj[x]->query_temp(QUESTDIR4+"askxuanci") && obj[x]!=me)
		  {
			  command("nod "+me->query("id"));
			  command("say 我也听说这事情，已经有"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"前往大辽营救去了，"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"武功高强，料想也无大碍！");
			  return 1;
		  }
	  }

	if(!me->query_temp(QUESTDIR4+"askxuanci"))
	{
		command("whisper "+me->query("id")+" 如果当真，少林自当尽力，当年少林与萧家误会颇多，这也是我中原武林赎罪的一次良机。\n"NOR);
		command("whisper "+me->query("id")+" 只是，你又如何得知这一消息？"NOR);
		message_vision(HIY"$N朗声说道：“我刚从大辽归来，也罢，依照江湖规矩，还是武功上考量一下吧。”。\n"NOR,me);
		command("nod "+me->query("id"));
	}
    else command("whisper "+me->query("id")+" 可是失败了，也罢，再给你一次机会。\n"NOR);
	command("whisper "+me->query("id")+" 你且随我进这少林阵法之中。");
	if (!(room = find_object("/d/shaolin/shaolinzhen")))
		room = load_object("/d/shaolin/shaolinzhen");
	if(!room)
	{
      	tell_object(me,HIR"\n赶快找wiz吧，竟然房间不存在!!!\n");
        log_file("quest/TLBB", sprintf("%s(%s)营救萧峰篇少林阵法文件缺少！\n", me->name(1),me->query("id")) );
    }
    else
    {
      tell_room(environment(me),HIC""+me->query("name")+"随玄慈主持匆匆出去了。\n"NOR, ({ me }));
		  tell_object(me,HIR"你随玄慈主持来到一个小屋之中，却见四端分别站着一个少林弟子。\n");
		  //设定标志
		  me->set(QUESTDIR+"time",time());
		  me->set(QUESTDIR+"combat_exp",me->query("combat_exp"));
		  me->move(room);
		  this_object()->move(room);
		  tell_object(me,HIY"\n玄慈主持向你挥了挥手，退了出去。\n"NOR);
		  this_object()->move("/d/shaolin/fzjs2");

		  tell_room(environment(this_object()),HIC"玄慈主持匆匆回来了，神色很是慌张。\n"NOR, ({ this_object()}));
		  log_file("quest/TLBB", sprintf("%s(%s)营救萧峰篇进入少林阵法。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		  me->set_temp(QUESTDIR5+"askxuanci",1);
		  me->set_temp("quest/busy",1);//与任务系统冲突标志
    }
    return 1;
	}
	if(me->query(QUESTDIR3+"good")&& !me->query(QUESTDIR4+"over") &&(me->query(QUESTDIR4+"start")|| me->query_temp(QUESTDIR5+"dagouzhen")))
	{
		command("addoil "+me->query("id"));
		command("say "+RANK_D->query_respect(me) +"却是了得。老衲佩服。还请"+RANK_D->query_respect(me) +"主持大局。");
		return 1;
	}
	if(me->query(QUESTDIR3+"good") &&me->query(QUESTDIR4+"over"))
	{
		command("admire "+me->query("id"));
		return 1;
	}
	if(random(2)) command("@@ "+me->query("id"));
	else command("laugh "+me->query("id"));
	return 1;
}
