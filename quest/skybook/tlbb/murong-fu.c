// /d/mr/npc/murong-fu.c  慕容复
// by leontt /12/05/2000
// by tiantian@sj 6/3/2000 fix mr job bug
// Modify By River@SJ 修正 job，另外门派drug全部cut 12/08/Y2k
// cut gold by augx@sj 9/27/2001
// Modify By tangfeng@SJ 8/15/2004
// 增加复兴天下篇，tlbb内容
// By Spiderii@ty加入bishen quest

inherit NPC;
#include <job_mul.h>
#include <ansi.h>
#include <combat.h>
#include "skill.h"
#include "murong-fu.h";

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"

int ask_fuming(string arg);
mixed ask_bo();
string ask_fenglu();
mixed ask_sword2();
string ask_skill();
string ask_wang();
string ask_learn();
string ask_ge();
string ask_sword();
string ask_book();
string ask_book2();
string ask_times();
int ask_fangqi();
string ask_fuxing();
string ask_yuxi();
int ask_bishen();

string* npc_where = ({"/d/mr/mtl/qianyuan","/d/mr/mtl/xiaojing7","/d/mr/mtl/liulin3","/d/mr/mtl/hc2","/d/mr/mtl/keting","/d/mr/mtl/cl","/d/mr/mtl/hhyuan",});                    
                     
void create()
{
	object weapon;
	set_name("慕容复",({"murong fu","murong","fu"}));
	set("title","姑苏慕容公子");
	set("nick","以彼之道 还施彼身");
	set("long",
		"他就是天下号称以彼之道，还施彼身的姑苏慕容复。\n"
		"他脸上带着不可一世的笑容。\n");
	set("age", 27);
	set("attitude", "friendly");
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("no_get", "慕容复背不起来。\n");

	set("max_qi",4500);
	set("max_jing", 3000);
	set("eff_jingli", 4000);
	set("neili",5500);
	set("max_neili", 3500);
	set("jiali", 1);
	set("combat_exp", 2500000);
	set("dan", 10);
	set("shen", -1000);
	set("no_bark",1);
	set("chat_chance_combat", 25);
	set("chat_msg_combat", ({
		(: exert_function, "shenyuan" :),
		(: perform_action, "strike.riyue" :),
		(: perform_action, "finger.ci" :),
		(: perform_action, "sword.lianhuan" :),
	}));
	set_skill("strike",170);
	set_skill("finger",170);
	set_skill("dodge",180);
	set_skill("force", 170);
	set_skill("canhe-zhi", 160);
	set_skill("murong-jianfa",170);
	set_skill("shenyuan-gong", 180);
	set_skill("yanling-shenfa", 160);
	set_skill("xingyi-zhang",170);
	set_skill("douzhuan-xingyi", 180);
	set_skill("parry", 180);
	set_skill("sword", 270);
	set_skill("literate", 170);
	set_skill("murong-daofa", 160);
	set_skill("blade",160);
	set_skill("xingyi-jianzhen",170);

	map_skill("blade", "murong-daofa");
	map_skill("finger", "canhe-zhi");
	map_skill("force", "shenyuan-gong");
	map_skill("dodge", "yanling-shenfa");
	map_skill("strike", "xingyi-zhang");
	map_skill("parry", "murong-jianfa");
	map_skill("sword", "murong-jianfa");

	prepare_skill("finger","canhe-zhi");
	prepare_skill("strike","xingyi-zhang");

	create_family("姑苏慕容", 2, "弟子");

	set("inquiry", ([
		"name" : "我就是以彼之道，还施彼身的姑苏慕容复。\n",
		"here" : "这里是大名鼎鼎的燕子坞，难道你没有听说过？\n",
		"rumors" : "家父突染恶疾，我连他老人家最后一面都没见到，此事顶有蹊跷！\n",
		"姑妈" : "我的姑妈住在曼佗罗山庄，那里有闻名天下的娘缳玉洞。\n",
		"虚竹" : "你说的可是少林弟子虚竹？我不认识......\n",
		"叶二娘" : "我不认识......你找错人问了。\n",
		"还施水阁" : (: ask_ge :),
		"慕容博" : (: ask_bo :),
		"领悟" : (: ask_book :),
	//	"俸禄" : (: ask_fenglu :),
		"王语嫣" : (: ask_wang :),
		"碧玉剑" : (: ask_sword2 :),
		"宝剑" : (: ask_sword :),
		"次数" : (: ask_times :),
		"斗转星移"  : (: ask_skill :),
		"图解" : (: ask_book2 :),
		"武学" : (: ask_learn :),
		"复命" : (: ask_fuming :),
		"放弃" : (: ask_fangqi :),
		"复兴天下" : (: ask_fuxing :),//tlbb quest
		"大燕国" : (: ask_fuxing :),
		"复国" : (: ask_fuxing :),	
		"大燕国玉玺" : (: ask_yuxi :),
		"秘密" : (: ask_yuxi :),		
		"玉玺" : (: ask_yuxi :),	
              "以彼之道还施彼身" : (: ask_bishen :),
	
	]));
	set("dan_count", 2);
	set("book_count",1);
	set("book2_count" ,1);
	set("dan1_count", 2);
	setup();
	if (clonep()) {
		weapon = unew(BINGQI_D("sword/biyu-jian"));
		if (!weapon)
			weapon = new(BINGQI_D("changjian"));
		weapon->move(this_object());
		weapon->wield();
		carry_object(__DIR__"obj/cloth3")->wear();
		add_money("gold", 2);
	}
}

void init()
{
	object ob;
	::init();
	ob = this_player();
	if (interactive(ob = this_player()) 
		&&ob->query(QUESTDIR5+"start")
		&&!ob->query(QUESTDIR5+"over")
		&&ob->query_temp(QUESTDIR5+"dagouzhen")
		&&ob->query_temp(QUESTDIR5+"zhenfa")
		&&ob->query_temp(QUESTDIR5+"shaolinzhen")) {
			ob->start_busy(2);
			remove_call_out("greeting");
			call_out("greeting", 2, ob);
		}
        add_action("do_lingwu","taojiao");
	add_action("do_jiaoliang", "jiaoliang");
}
void greeting(object me)
{
	int i,p;
	if(!me) return;
	if (!me->query(QUESTDIR5+"start") 
		|| me->query(QUESTDIR5+"over")
		|| !me->query_temp(QUESTDIR5+"dagouzhen")
		|| !me->query_temp(QUESTDIR5+"zhenfa")
		|| !me->query_temp(QUESTDIR5+"shaolinzhen"))
		return;
	if(environment(me)!=environment(this_object())) 
	{
		message_vision(HIC"\n$n疑惑地问道：$N，人呢？\n"NOR,me,this_object()); 
		me->delete_temp("quest/天龙八部");
		me->delete_temp("quest/busy");//任务冲突标志取消
		return;
	}
	command("whisper "+me->query("id")+" 没想到"+ RANK_D->query_respect(me) +"竟然有如此实力，独闯少林，连破少林伏魔阵和丐帮打狗阵！");
	command("whisper "+me->query("id")+" 更没有想到"+ RANK_D->query_respect(me) +"竟然能够击败无名神僧和萧峰的联手！\n");
	command("chat* admire "+me->query("id"));
	command("pat "+me->query("id"));
	command("whisper "+me->query("id")+" 有"+ RANK_D->query_respect(me) +"的帮助，想来复兴我大燕国指日可待！");
	command("haha "+me->query("id"));
	command("whisper "+me->query("id")+" "+ RANK_D->query_respect(me) +"，等朕兴复大燕，身登大宝，人人皆有封赏。");

	command("addoil "+me->query("id"));
	command("crazy");

	me->set(QUESTDIR5+"over",1);
	me->delete_temp("quest/天龙八部");
	me->delete_temp("quest/busy");//任务冲突标志取消
	//奖励
        p=10+random(100);
	me->add("max_neili",p);
        me->add("combat_exp",me->query_skill("force")*2+500);
        i=100+random(100);
	me->add("mana",i);
        tell_object(me,HIY"\n你于"+NATURE_D->game_time()+"帮助慕容复打败少林丐帮，实现复兴天下的计划，获得"+p+"点最大内力、"+((int)me->query_skill("force")*2+500)+"点经验奖励、"+i+"点声望。\n"NOR);   
        log_file("quest/TLBB", sprintf("%s(%s) 复兴天下篇完成。奖励：%d点最大内力，%d点经验，%d点声望。\n", me->name(1),me->query("id"), p,(me->query_skill("force")*2+500),i ) );
}
void attempt_apprentice(object ob)
{
	if (ob->query_skill("parry", 1) < 120) {
		command("say 我姑苏慕容以彼之道、还施彼身对招架要求甚高。");
		command("say " + RANK_D->query_respect(ob) + "的功力不够，还是请回吧。");
		return;
	}

	if (ob->query_skill("shenyuan-gong", 1) < 100) {
		command("say 我姑苏慕容以彼之道、还施彼身对内功心法要求甚高。");
		command("say " + RANK_D->query_respect(ob) + "的功力不够，还是请回吧。");
		return;
	}

	command("say 嗯，看你还是个学武的料，我就收下你吧！");
	command("say 苍天在上，让我姑苏慕容又得一良材，为复兴我大燕多了一份力量。");
	command("chat* 朗声说道：公子我又收一良材，大燕兴复指日可待啦！");
	command("chat* haha");
	command("recruit " + ob->query("id"));
	ob->set("title","姑苏慕容第三代弟子");
}
string ask_fuxing()
{
	object ob=this_player();
	object *obj;
	int x;

	mapping fam = ob->query("family");
	if ( !fam )
		return "这位"+ RANK_D->query_respect(ob) +"无门无派，此话从何说起？";
	if( !ob->query(QUESTDIR3+"bad"))
		return "我与"+ RANK_D->query_respect(ob) +"向来没什么往来，此话从何说起？"; 		

	if( ob->query(QUESTDIR5+"over"))
	{
		command("haha");
		command("whisper "+ob->query("id")+" 有"+ RANK_D->query_respect(ob) +"的帮助，想来复兴我大燕国指日可待！");
		if (random(2))return "今天天气就是好，就是好。";
		return "今天天气真不错。";
	}
	if( ob->query(QUESTDIR5+"start"))
	{
		command("nod " + ob->query("id"));
		command("whisper "+ob->query("id")+" 唯上之策，先从少林下手了。玄慈的事情正是个机会。");
		if (random(2))return "今天天气就是好，就是好。";
		return "今天天气真不错。";
	}
	if( ob->query_temp(QUESTDIR5+"yuxi") && !ob->query(QUESTDIR5+"start"))
	{
		command("addoil " + ob->query("id"));
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"，不是告诉尽快将玉玺找回？");
		if (random(2))return "今天天气就是好，就是好。";
		return "今天天气真不错。";
	}
	if( ob->query_temp(QUESTDIR5+"give_shouji") && !ob->query(QUESTDIR5+"start"))
	{
		command("addoil " + ob->query("id"));
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"，确实不错。");
		if (random(2))return "今天天气就是好，就是好。";
		return "今天天气真不错。";
	}		
    
	command("addoil "+ob->query("id"));
	command("say "+ RANK_D->query_respect(ob) +"帮我把萧峰赶出中原，已经帮我大忙了！");
	//增加时间和经验间隔限制
	//时间一天，经验500K
	if(ob->query(QUESTDIR+"time")&&time()-ob->query(QUESTDIR+"time")<86400)
		return "不过，"+ RANK_D->query_respect(ob) +"今天很忙了，先行休息去吧！";
	if(ob->query(QUESTDIR+"combat_exp")&&ob->query("combat_exp")-ob->query(QUESTDIR+"combat_exp")<500000)
		return "以"+ RANK_D->query_respect(ob) +"目前的经验就算目前有情况，也帮不上什么忙，还是抓紧练功吧！";
	//只能一个人做
	obj = users();
	x = sizeof(obj);
	while(x--) {
		if ( obj[x]->query_temp(QUESTDIR5+"askfu") && obj[x]!=ob) 
		{
			command("sigh "+ob->query("id"));
			return "只是关于这件事情，已经有"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"帮我了.........";
		}
	}
	//设定标志
	ob->set(QUESTDIR+"time",time());
	ob->set(QUESTDIR+"combat_exp",ob->query("combat_exp"));  

	command("whisper " + ob->query("id")+" 恩，只是所谓复兴天下，谈何容易，而且......");
	command("look " + ob->query("id"));
	command("whisper " + ob->query("id")+" 当今，天下武林所谓正派有“两派一帮”之说，就是少林派、武当派与丐帮。");
	command("whisper " + ob->query("id")+" 其中少林、武当人称武林泰山北斗，卧龙藏虎之辈层出不穷，无名神僧和张三丰人称不死老怪物。");
	command("whisper " + ob->query("id")+" 而丐帮乃天下第一大帮，从前任帮主萧峰，到大侠郭靖、还是神丐洪七，都是名震一方的高手。");
	command("consider");
	command("whisper " + ob->query("id")+" 近年来，张无忌掌教西域明教，大有凌驾中原武林之势，且因武当关系紧密，影响力日益加剧。");
	command("whisper " + ob->query("id")+" 西南大理，枯荣复出，六脉重现，段誉更被称为青年第一高手，挟皇室之威，隐约成为江南武林之尊。");
	command("whisper " + ob->query("id")+" 因此，要复兴天下，必须扫除这“两派一帮一教一世家”。对付丐帮少林，我已经有了一个完全之策。");
	command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"竟然立志复兴天下，就先带张三丰、张无忌或枯荣三个中任意一个人头回来见我，以明心志！");
	log_file("quest/TLBB", sprintf("%s(%s)为复兴天下需要砍人了，特此纪录。经验：%d。\n", ob->name(1),ob->query("id"), ob->query("combat_exp")) );
	command("addoil " + ob->query("id"));
	ob->set_temp(QUESTDIR5+"askfu",1);
	ob->set_temp("quest/busy",1);//与任务系统冲突标志
	if (random(2))		return "今天天气就是好，就是好。";
	return "今天天气真不错。";
}
string ask_yuxi()
{
	string where;
	object room,mrdizi,ob=this_player();
	object *obj;
	int x;

	mapping fam = ob->query("family");
	if ( !fam )
		return "这位"+ RANK_D->query_respect(ob) +"无门无派，此话从何说起？";
	if( !ob->query(QUESTDIR3+"bad"))
		return "我与"+ RANK_D->query_respect(ob) +"向来没什么往来，此话从何说起？"; 		

	if( ob->query(QUESTDIR5+"over"))
	{
		command("haha");
		command("whisper "+ob->query("id")+" 有"+ RANK_D->query_respect(ob) +"的帮助，想来复兴我大燕国指日可待！");
		if (random(2))return "今天天气就是好，就是好。";
		return "今天天气真不错。";
	}
	if( ob->query(QUESTDIR5+"start"))
	{
		command("nod " + ob->query("id"));
		command("whisper "+ob->query("id")+" 唯上之策，先从少林下手了。玄慈的事情正是个机会。");
		if (random(2))return "今天天气就是好，就是好。";
		return "今天天气真不错。";
	}

	if( ob->query_temp(QUESTDIR5+"yuxi") && !ob->query(QUESTDIR5+"start"))
	{
		command("? " + ob->query("id"));
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"，不是告诉尽快将玉玺找回？");
		if (random(2))return "今天天气就是好，就是好。";
		return "今天天气真不错。";
	}
	if(!ob->query_temp(QUESTDIR5+"give_shouji") && !ob->query(QUESTDIR5+"start"))
	{
		command("? " + ob->query("id"));
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"，你哪里知道玉玺这回事情？");
		if (random(2))return "今天天气就是好，就是好。";
		return "今天天气真不错。";
	}

	command("nod "+ob->query("id"));
	command("whisper " + ob->query("id")+" 既然如此，我就坦诚以开，我其实就是大燕国慕容氏皇裔，兴复燕国的大业是从古继来的大业。");
	command("whisper " + ob->query("id")+" 虽然艰难万分，但依旧鞠躬尽瘁，竭力以赴。为此已经付出几代人的努力。\n");
	command("shrug "+ob->query("id"));
    command("whisper " + ob->query("id")+" 前一段时间，有慕容三代弟子背叛我慕容，更可恶的是竟然偷走大燕国玉玺。");
	//只能一个人做
	obj = users();
	x = sizeof(obj);
	while(x--) {
		if ( obj[x]->query_temp(QUESTDIR5+"yuxi") && obj[x]!=ob) 
		{
			command("sigh "+ob->query("id"));
			return "还好，已经有"+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"帮我了.........";
		}
	}
	ob->set(QUESTDIR+"time",time());
	ob->set(QUESTDIR+"combat_exp",ob->query("combat_exp"));  

	where=npc_where[random(sizeof(npc_where))];  
	if(!room=find_object(where))
		room=load_object(where);
	if(!room) room=load_object("/d/mr/mtl/midao");
	mrdizi=new(__DIR__"mrdizi");
	mrdizi->set("party","mr"); 
	mrdizi->set("fight_id",ob->query("id")); 
	if(random(2)) mrdizi->move(room);
	mrdizi=new(__DIR__"mrdizi");
	mrdizi->set("party","mr"); 
	mrdizi->set("fight_id",ob->query("id")); 
	mrdizi->move(room);  
	mrdizi=new(__DIR__"mrdizi");
	mrdizi->set("party","mr"); 
	mrdizi->set("fight_id",ob->query("id")); 
	mrdizi->set("yuxi_have",1);//带玉玺的弟子
	mrdizi->move(room);
	ob->set_temp("quest/busy",1);//与任务系统冲突标志
	tell_room(environment(mrdizi), HIB"\n"+mrdizi->name()+"匆匆地来到"+room->query("short")+"，神色大是慌张。\n"NOR);
	command("whisper " + ob->query("id")+" 我已经在燕子屋布下天罗地网，刚才探子回报，叛徒很在曼陀罗山庄"+room->query("short")+"出现过！");
	log_file("quest/TLBB", sprintf("%s(%s)为复兴天下需要寻找玉玺，特此纪录。经验：%d。\n", ob->name(1),ob->query("id"), ob->query("combat_exp")) );
	command("addoil "+ob->query("id"));
	if(wizardp(ob)) tell_object(ob,"\n"+where+"\n");
	ob->set_temp(QUESTDIR5+"yuxi",1);
	if (random(2))		return "今天天气就是好，就是好。";
	return "今天天气真不错。";
}
string ask_fenglu()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	int gold = 0, fenglu;

	if ( !fam || fam["family_name"] != "姑苏慕容")
		return "这位"+ RANK_D->query_respect(ob) +"不是我慕容弟子，此话从何说起？";
        switch ( fam["generation"] ) {
		case 2:
			gold += 500;
		case 3:
			gold += 800;
			break;
		default:
			return "这位"+ RANK_D->query_respect(ob) +"在我姑苏慕容的身份太低，现在还没有资格领取俸禄。";
	}
	fenglu = ob->query("age") * 12 + ob->query("month");
	if (ob->query("fenglu") >= fenglu)
		return "这位"+RANK_D->query_respect(ob) +"本月已经领过俸禄了，还是等下个月再来吧。";
	gold *= ob->query_skill("shenyuan-gong",1);
           if (ob->query_skill("shenyuan-gong", 1) < 216)  return "你这个月没有俸禄。";
	ob->set("fenglu", fenglu);
	command ("addoil " + ob->query("id"));
	ob->add("balance", gold);
	return "你本月的俸禄"+MONEY_D->money_str(gold)+"已经存入钱庄了，但愿这位"+ RANK_D->query_respect(ob) +"不要使我失望，好好干吧！";
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BINGQI_D("sword/biyu-jian")))) {
		ob->move(this_object());
		command("wield biyu jian");
	}
}

mixed ask_sword2()
{
	object me=this_player(), weapon;

	if ( me->query("family/family_name") != "姑苏慕容")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";

	if ( me->query("family/generation") > 3 )
		return "碧玉剑是本派宝物，不知道这位" + RANK_D->query_respect(me) + "打听这个干嘛？";

	weapon = present("biyu jian", this_object());
	if (!objectp(weapon))
		return "碧玉剑已经被人拿走了, 现在不在我手里。";
	command("unwield biyu jian");
	command("give biyu jian to " + me->query("id"));
	return 1;
}

string ask_wang()
{
	mapping fam;

	if (!fam = this_player()->query("family") || fam["family_name"] !="姑苏慕容")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	return "语嫣是我表妹，一直被姑妈管的很严，连我都很长时间没有见到她了。";
}

string ask_skill()
{
	mapping fam;

	if (!(fam = this_player()->query("family"))|| fam["family_name"] != "姑苏慕容")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	return "斗转星移是我慕容家的绝学，最是注重招架和身法。";
}

string ask_ge()
{
	mapping fam;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	return "还施水阁是我慕容收藏天下秘籍之所在，在我的书……";
}

string ask_sword()
{
	mapping fam;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	return "碧玉剑是家父身后的遗物，我让阿朱姑娘收起来好好保管！";
}

string ask_book()
{
	object me = this_player();
	object ob;

	if (me->query("family/family_name") != "姑苏慕容")
		return RANK_D->query_respect(me) +
		"与本派素无来往，不知此话从何谈起？";

	if (me->query_skill("parry",1) < 121)
		return RANK_D->query_respect(me) + "功力不够，何以谈及领悟？";
	if (present("douzhuan xingyi", me))
		return RANK_D->query_respect(me) +
		"现在身上不是有斗转星移的武籍了吗？怎么又来要了？ 真是贪得无厌！";

	ob = unew("/d/mr/obj/shu1");
	if(!clonep(ob))
		return "斗转星移武籍已经被别人要走了。";

	ob->move(me);

	message_vision("$N得到一本斗转星移的武功秘籍。\n", me);
	return "好吧，看你为慕容家忠心耿耿，这本书就赐于你吧。";
}

string ask_book2()
{
	object me = this_player();
	object ob;

	if (me->query("family/family_name") != "姑苏慕容")
		return RANK_D->query_respect(me) +
		"与本派素无来往，不知此话从何谈起？";

	if (me->query_skill("parry",1) < 121)
		return RANK_D->query_respect(this_player()) + "功力不够，何以谈及领悟？";

	if (me->query_skill("douzhuan-xingyi",1)<50)
		return RANK_D->query_respect(me) +
		"功力不够，何以谈及领取图解？";
	if (present("douzhuan xingyi", me))
		return RANK_D->query_respect(this_player()) +
		"你现在身上不是有斗转星移的武籍了嘛，怎么又来要了？ 真是贪得无厌！";

	ob = unew("/d/mr/obj/shu2");
	if (!clonep(ob))
		return "对不起，斗转星移的武籍已经被别人要走了。";

	ob->move(this_player());
	message_vision("$N得到一本斗转星移的武功秘籍。\n", me);
	return "好吧，看你为慕容家忠心耿耿，这本书就赐于你吧。";
}

mixed ask_bo()
{
	object me = this_player();
	object ob = this_object();

	if (me->query_temp("marks/失败")) {
		message_vision(
			"$N眼中发出两道寒光直射$n，一字一字地说道：已经较量过了，你怎么还不回去安心练功呢！\n",
			ob, me
		);
		return 1;
	}
	if (me->query("family/family_name") != "姑苏慕容")
		return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？";

	if (me->query("family/generation") != 3)
		return RANK_D->query_respect(me) + "为何开这等玩笑？";

	if (me->query_temp("marks/bai_bo"))
		return "你已经可以去见家父，不用再向我学了！";

	message_vision(
		"$N眼中发出两道寒光直射$n，一字一字地说道：家父现在身处少林，那里藏龙卧虎，\n"
		"你若武功未成，最好不要去自取其辱；如果你有信心，就和我较量一下。(jiaoliang)\n",
		ob, me
	);

	me->set_temp("marks/jiao", 1);
	return 1;
}

int do_jiaoliang()
{
	object me, obj, jiaxin;
	int current_qi;
	int i;

	me = this_object();
	obj = this_player();

	if (obj->query_temp("marks/jiao")) {
		message_vision("$N对$n说：好吧，那就请师父指点几招。\n", obj, me);
		set("max_qi", 4500);
		set("jiali", 50);
		set("neili", 6500);
		set("max_neili", 4500);
		current_qi = set("qi", 4500);

		i=10;
		obj->delete_temp("marks/jiao");
		while ((obj->query("qi")*100 / (int)obj->query("max_qi")) > 30) {
			if (!present(obj, environment()))
				return 1;
			i--;
			COMBAT_D->do_attack(obj, me, obj->query_temp("weapon"), 1);
			if (!i || (me->query("qi")*100/current_qi) < 30) {
				message_vision(
					"$N对$n说道：不想我慕容世家又出良材，我这就写封家信，你马上动身前去少林，\n"
					"把它交给家父。希望你能不负众望，振兴慕容世家，光复大燕国。\n",
					me, obj
				);
				jiaxin = new("/d/mr/obj/jiaxin");
				jiaxin->move(obj);
				obj->set_temp("marks/bai_bo", 1);
				message_vision("$N交给$n一封家信\n", me, obj);
				return 1;
			}
			COMBAT_D->do_attack(me, obj, me->query_temp("weapon"), 1);
		}
		message_vision(
			"$N对着$n冷冷说道：你武功未成，就好高骛远，你还是安心练功去吧！\n",
			me, obj
		);
		obj->set_temp("marks/失败", 1);
	}
	return 1;
}

string ask_learn()
{
	int j=random(sizeof(my_skills));
	mapping skill = my_skills[j];
	int i;
	object me = this_player();

	i = 7+random(5);
	if (me->query("family/family_name") != "姑苏慕容" && !wizardp(me)) // 必须是慕容派弟子
		return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？";

	if (me->query("combat_exp") > 2000000  && !wizardp(me))
		return RANK_D->query_respect(me)
		+ "你已经尽数掌握了精深奥妙的武学诀要，我可不敢劳您的大架了。";

	if (me->query_skill("parry", 1) < 100 ) // 招架必须大于等于100级
		return RANK_D->query_respect(me) +
		"于本门武学尚不能运用自如，如何谈及天下之武学？";
	if (me->query_skill("douzhuan-xingyi", 1) < 100 )  // 斗转星移必须大于等于100级
		return RANK_D->query_respect(me) +
		"于本门武学尚不能运用自如，如何谈及天下之武学？";
	if (me->query_condition("mr_job") )
		return RANK_D->query_respect(me) +"还没完成我交给你的任务呢。";
	if (is_fighting())
		return "嚷什么嚷，没看见我这正忙着呢吗？";
	if (me->query("job_name") =="慕容偷学" && !wizardp(me))
		return RANK_D->query_respect(me) +
		"先等等吧，我现在没有什么感兴趣的武功想学。";
	if (me->query_condition("wait_mr_job", 1) > 0
	 || me->query_condition("job_busy"))
		return RANK_D->query_respect(me) +"先等等吧，我现在没有什么感兴趣的武功想学。";

	if(!skill["skill_id"])
		return sprintf("SKILL.H文件在第%d个技能出错，请通知巫师修改。\n",j);
	me->set_temp("skill_target", skill["skill_name"]);  // 此标记表明此次偷学目标技能的中文名字
	me->set_temp("skill_id", skill["skill_id"]); // 此标记表明此次偷学目标技能的英文名字
	me->set_temp("skill_type", skill["skill_type"]); // 此标记表明此次偷学目标技能的英文类型
	me->set_temp("skill_lvl", i); // 此标记表明此次偷学目标技能所需要的级别
	me->apply_condition("mr_job", 30+random(15)); // 设置此次任务必须在所需时间内完成;
	me->apply_condition("job_busy",10);
	command( "whisper "+me->query("id") + " 我姑苏慕容傲视天下所有武功，但也不乏为之羡慕的。");
	command("whisper "+ me->query("id")
	+ " 好吧，"+"「"+skill["skill_name"]+"」"+"「"+skill["skill_id"]+"」我垂涎已久，你们把它学回来，我大大的有赏。");

	if ( !present("murong paper", me))
		new("/d/mr/obj/paper")->move(me);

	if (random(2))
		return "今天天气就是好，就是好。";
	return "今天天气真不错。";
}

int ask_fuming(string arg)
{
	object me, ob;
	int bouns,My_exp,Target_exp,pot;
	float rate;

	me = this_player();
	ob = this_object();

	if( !arg)
	{
		command("say 你要展示什么？");
		return 1;
	}

	if( !me->query_condition("mr_job"))
	{
		command("say 你现在没有任务吧？");
		return 1;
	}

	if( me->is_busy())
	{
		command("say 你正忙着呢，有什么事情呆会再说。");
		return 1;
	}

	if( me->is_fighting())
	{
		command("say 你正打架呢，有什么事情呆会再说。");
		return 1;
	}

	if(!me->query_temp("job_done"))
	{
		command("say 你学到什么东西了？还有脸敢回来？");
		return 1;
	}

	if( this_object()->is_fighting())
	{
		command("say 嚷什么嚷，没看见我这正忙着呢吗？");
		return 1;
	}
	me->set("job_name", "慕容偷学");
/*
	Target_exp = me->query_temp("master_exp");
	My_exp= me->query("combat_exp");

	bouns = me->query_temp("skill_lvl")*5/2;
	bouns +=  me->query_skill("douzhuan-xingyi",1) * 5 / 3;

	rate = to_float(Target_exp)/to_float(My_exp);
	if (rate > 2) rate = 2;
	if (rate < 0.6) rate = 0.6;
	bouns *= rate;
             
              if (bouns > 300) bouns = 250 + random(50);		
	bouns = me->add_exp_combat(bouns,this_object(),"慕容");
	pot = bouns/5+random(bouns/10);        
	if (me->add("potential", pot) > me->query("max_pot"))
		me->set("potential", me->query("max_pot"));
	write(GRN"你获得了"+CHINESE_D->chinese_number(bouns)+"点经验和"+CHINESE_D->chinese_number(pot)+"点潜能的奖励。\n"NOR);
	write(GRN"你已经为慕容世家做了"+me->query("job_time/慕容")+"次任务!\n"NOR);

	log_file("job/touxue",sprintf("%8s%-10s偷学 %s, 经验：%3d，潜能：%2d，次%3d，目前经验：%d。\n",
		me->name(1), "("+geteuid(me)+")", me->query_temp("skill_target"),
		bouns,pot,me->query("job_time/慕容"),me->query("combat_exp")), me);
*/
          
	message_vision(CYN"慕容复仔细研究着$N记在纸卷上的武功精要，情不自禁地说道：好一个"+me->query_temp("skill_target")+"。\n"NOR, me);
              TASKREWARD_D->get_reward(me,"慕容",0,0,0,16+ random(5),0,0,0,this_object());
	message_vision(CYN"慕容复拍了拍$N的头，对$P说道：辛苦你了，下去休息吧。\n"NOR, me);


	me->improve_skill("douzhuan-xingyi", me->query_int()*2);

	me->delete_temp("skill_target");
	me->delete_temp("skill_id");
	me->delete_temp("skill_type");
	me->delete_temp("skill_lvl");
	me->delete_temp("job_done");

	me->clear_condition("mr_job");
	me->apply_condition("wait_mr_job", random(10)+5);

	if(present("paper", me)){
		destruct(present("paper",me));
	}
	return 1;
}

int ask_fangqi()
{
	object me=this_player(),obj;

	if( !me->query_condition("mr_job")){
		command("say 你现在没有任务吧？");
		return 1;
	}

	command( "say 也好，那么你先下去休息一会吧。" );
	command( "disapp");
	command( "sigh "+me->query("id"));
	obj=me->query_temp("dizi");
	if( objectp(obj) )
		destruct(obj);
	me->delete_temp("skill_target");
	me->delete_temp("skill_id");
	me->delete_temp("skill_type");
	me->delete_temp("skill_lvl");
	me->delete_temp("job_done");

	me->clear_condition("mr_job");
	me->apply_condition("wait_mr_job", random(2)+2);
	me->add("combat_exp",-(20+random(30)));
	return 1;
}

string ask_times()
{
	object ob;
	ob = this_player();
	if(!ob->query("job_time/慕容"))
		return "很遗憾，"+ob->name()+"，你好象没有为慕容做过贡献！";
	return ""+ob->name()+"，你已经完成了"+CHINESE_D->chinese_number((int)ob->query("job_time/慕容"))+"次慕容偷学任务！";
}

int accept_object(object who, object ob)
{
   if(userp(ob)) return 0;        
   if(ob->query("id") == "yu xi")
   {
      if(who->query_temp(QUESTDIR5+"yuxi")
		  &&!who->query(QUESTDIR5+"start")) 
	  {
      	if( ob->query("owner")==who->query("id"))
        {
           command("smile "+who->query("id"));
  	       command("whisper "+who->query("id")+" 不错，看你如此用心，这里有个天大的秘密可以告诉你。");
  	       command("whisper "+who->query("id")+" 二十年前，江南叶家庄叶二姑娘离奇失踪，几年后江湖上出现所谓四大恶人，其中一个就叫叶二娘。");
		   command("smile "+who->query("id"));
  	       command("whisper "+who->query("id")+" 没有人想到，叶二娘就是当年叶二姑娘。而这一切罪魁祸首就是当今的少林主持玄慈！");
		   command("smoke");
  	       command("whisper "+who->query("id")+" 二十年前，还是少年的玄慈曾经夜宿叶家庄，勾引叶二姑娘，几年后叶二姑娘更为他生下一子。");
  	       command("whisper "+who->query("id")+" 这是我们天大的机会。这个孩子就是少林三十六代弟子虚竹。他屁股上的胎记可以证明一切！！");
		   command("claw");
  	       command("whisper "+who->query("id")+" 如此一来，少林名誉扫地，之后趁丐帮萧峰离走内乱之际灭其丐帮，之后武林便是你我的天下！");
           command("crazy");
           command("addoil "+who->query("id"));
           who->set(QUESTDIR5+"start",1);
		   log_file("quest/TLBB", sprintf("%s(%s)为复兴天下找到玉玺。经验：%d。\n", who->name(1),who->query("id"), who->query("combat_exp")) );
        }
        else
        {
           command("? "+who->query("id"));
  	       command("whisper "+who->query("id")+" 这不是你要找的玉玺，这块你从哪里得来的？");
  	       command("heng "+who->query("id"));
		   command("whisper "+who->query("id")+" 竟然随便找来一块就来胡弄我.........");
		   log_file("quest/TLBB", sprintf("%s(%s)找的玉玺不是本人的，失败。经验：%d。\n", who->name(1),who->query("id"), who->query("combat_exp")) );
           who->set(QUESTDIR+"time",time());
           who->set(QUESTDIR+"combat_exp",who->query("combat_exp"));
           who->delete_temp("quest/天龙八部/复兴天下篇");
        }
	  }
	  else command("thank "+who->query("id"));
	  call_out("destroying", 1, ob);
	  return 1;
   }
   if(ob->query("id") == "shouji" 
	   && ob->query("kill_by")
	   && ob->query("kill_by")==who
	   && (ob->query("victim_id")=="zhang sanfeng"
	       ||ob->query("victim_id")=="zhang wuji"
		   ||ob->query("victim_id")=="kurong zhanglao"))
   {

      if(who->query_temp(QUESTDIR5+"askfu")
		  &&!who->query_temp(QUESTDIR5+"give_shouji")) 
	  {
		  command("smile "+who->query("id"));	  
		  if(ob->query("victim_id")=="zhang sanfeng")
			  command("whisper "+who->query("id")+" 不错，武当那个老杂毛没想到也有今天，这里有个天大的秘密可以告诉你。");
		  if(ob->query("victim_id")=="zhang wuji")
			  command("whisper "+who->query("id")+" 不错，明教那个小家伙没想到也有今天，这里有个天大的秘密可以告诉你。");
		  if(ob->query("victim_id")=="kurong zhanglao")
			  command("whisper "+who->query("id")+" 不错，大理那个死秃子没想到也有今天，这里有个天大的秘密可以告诉你。");
		  command("addoil "+who->query("id"));
		  who->set_temp(QUESTDIR5+"give_shouji",1);
		  log_file("quest/TLBB", sprintf("%s(%s)为复兴天下杀死一个掌门人。经验：%d。\n", who->name(1),who->query("id"), who->query("combat_exp")) );
	  }
	  else
	  {
		  command("nod "+who->query("id"));
		  command("admire "+who->query("id"));
	  }
	  call_out("destroying", 1, ob);
	  return 1;
   }
   return 0;
}
int ask_bishen()
{
	object ob=this_player();
       mapping fam;
	int i, time;
        i = ob->query("combat_exp") - 500000;
        i /= 500000;

	time = time() - ob->query("quest/bishen/time");


      if (!(fam = this_player()->query("family")) || fam["family_name"] !="姑苏慕容"){
		command("? " + ob->query("id"));
             command("say 你与本派素无来往，不知为何有此一问？");
             return 0;
        }
	if (ob->query("quest/bishen/pass")) {
		command("? " + ob->query("id"));
		command("say 你不是已经明白其中的奥妙了吗？");
		return 1;
	}
	if (ob->query("quest/bishen/fail") >=3 && ob->query("registered") < 3){
		command("hmm");
		command("say 你受天资所限,看来此生无望了！");
		return 1;
	}
	if ( ob->query("quest/bishen/time") && time < 86400 ) {
		command("shake");
		command("say 你解迷时间未到,请稍后再来。");
		return 1;
	}
	if ( ob->query("quest/hubo/fail") >= i ){
		command("shake");
		command("say 你解迷时机未到,请稍后再来。");
		return 1;
	}
        if ( ob->query("combat_exp") < 1000000) {
		command("shake "+ ob->query("id"));
		command("say 这位"+RANK_D->query_respect(ob)+"你的武功过于浮躁,现在还不是告诉你的时候。");
		return 1;
	}
	if (random(ob->query("kar")) < 26 && ob->query("int") < 25){
	       command("look " + ob->query("id"));
		command("poor");
		command("say 看来你还是未到明白其中奥妙所在的时候!");
		ob->add("quest/bishen/fail", 1);
		ob->set("quest/bishen/time", time());
		log_file("quest/bishen",
			sprintf("%-18s想从慕容复处领悟斗转星移的精髓所在失败，失败%s次。\n",
				ob->name(1)+"("+capitalize(getuid(ob))+")",
				chinese_number(ob->query("quest/bishen/fail")) 
			), ob
		);
		return 1;
	}
	command("look " + ob->query("id"));
	command("nod " + ob->query("id"));
	command("say 好吧,我就将其中的奥妙告诉你吧。");
       command("chat* 纵声长笑道：我姑苏慕容又有一人领悟斗转星移精髓所在,何愁复国大业不成！");
       command("chat* yeah");
	log_file("quest/bishen",
		sprintf("%-18s失败%s次后，成功从慕容复处领悟斗转星移精髓所在，福：%d，悟：%d。\n",
			ob->name(1)+"("+capitalize(getuid(ob))+")",
			chinese_number(ob->query("quest/bishen/fail")), 
			ob->query("kar"), 
			ob->query_int(1)
		), ob
	);
	ob->set("quest/bishen/pass", 1);
	ob->set("quest/bishen/exp", ob->query("combat_exp"));
	return 1;
}



void destroying(object ob)
{     
	destruct(ob);
	return;
}     
