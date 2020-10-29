// /d/thd/npc/zhou.c
// Modify By River@SJ about jieyi and hubo
// Modify by Darken for taohua quest 2000
// Modify By River@Sj for jiuyin quest
// Modify by yueying@SJWL屏蔽重复的互搏失败判断488-491,否则只能解一次
// Update by JPei 2011 for yunu-xinjing/hubo && Question_Check
inherit NPC;

#include <skill.h> 
#include <ansi.h>
#include "question.h"

int ask_jieyi();
int do_answer(string arg);
int questions(object me);
int ask_jiuyin();
int ask_hubo();
int do_fangyuan();
int do_learn(string arg);
int ask_story();
int ask_skill();
int ask_story2();
int ask_xlv();
void waiting(object ob);
void create()
{
	set_name("周伯通", ({ "zhou botong", "zhou", "botong" }) );
	set("nickname", "老顽童");
	set("long", "他满头长发，直垂至地，长眉长须，鼻子嘴巴都被遮掩住了。\n"
		"他须发苍然，并未全白，只是不知有多少年不剃，就如野人一般毛茸茸地甚是吓人。\n"
		"他的举止犹如孩童一样。\n");
	set("gender", "男性" );
	set("age", 48);
	set("attitude", "peaceful");
	set("apprentice", 1);

	set("str",28);
	set("int",25);
	set("con",30);
	set("dex",29);
	set("unique", 1);
	set("pur", 30);
	set("per", 24);

	set("no_get", "周伯通对你而言太重了。\n");

	set("max_qi", 12000);
	set("max_jing", 10000);
	set("max_neili", 21000);
	set("jiali", 150);
	set("combat_exp", 5600000);
	set("eff_jingli", 9500);
	set("double_attack", 1);
	set("score", 5000);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "sword.qixing" :),
		(: perform_action, "sword.sanqing" :),
		(: perform_action, "cuff.kong" :),
		(: perform_action, "cuff.ming" :),
	}));

	set_skill("force", 380);
	set_skill("xiantian-gong", 380);
	set_skill("dodge", 390);
	set_skill("tiyunzong", 390);
	set_skill("cuff", 380);
	set_skill("kongming-quan", 380);
	set_skill("parry", 380);
	set_skill("sword", 380);
	set_skill("quanzhen-jianfa", 380);
	set_skill("taoism", 200);
	set_skill("literate", 260);

	map_skill("force", "xiantian-gong");
	map_skill("dodge", "tiyunzong");
	map_skill("cuff", "kongming-quan");
	map_skill("sword", "quanzhen-jianfa");
	map_skill("parry", "quanzhen-jianfa");
	prepare_skill("cuff", "kongming-quan");

	set("rank_info/respect", "老顽童");
	set("shen_type", 1);
	create_family("全真教", 2, "弟子");
	set("class", "taoist");

	set("inquiry", ([
		"name": "叫我周伯通就好了。",
		"rumors": "我被那个臭东邪关在这里十几年，每天就是一个哑仆来送饭。",
		"here": "这里是桃花岛。寒雨那个小坏蛋在这里加了无数的ｑｕｅｓｔ，看你能不能找全了。",
		"东邪": "是黄药师这个无耻的家伙，骗了我的九....去看。",
		"黄药师": "这个无耻的家伙，骗了我的九....去看。",
		"中神通": "我的师兄是天下武功最高的，第一次华山论剑时公推为第一高手。",
		"王重阳": "我的师兄是天下武功最高的，第一次华山论剑时公推为第一高手。",
		"周伯通": "找我有什么事吗？",
		"瑛姑": "四张机，鸳鸯织就欲双飞....",
		"刘瑛": "四张机，鸳鸯织就欲双飞....",
		"段皇爷": "老顽童做事对不起他，没脸再见他了。",
		"段智兴": "老顽童做事对不起他，没脸再见他了。",
		"南帝": "老顽童做事对不起他，没脸再见他了。",
		"老顽童": "我就是啊，找我有什么事吗？",
		"空明拳": "空明拳共七十二路，口诀是：空朦洞松、风通容梦、冲穷中弄、童庸弓虫。",
		"kongming-quan": "空明拳共七十二路，口诀是：空朦洞松、风通容梦、冲穷中弄、童庸弓虫。",
		"黄蓉": "是几个月前来陪我聊天的那个小姑娘吗？",
		"郭靖": "那是我的结义兄弟，人虽然傻，心肠倒好。",
		"寒雨": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
		"jpei": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
		"桃花岛": "这里就是桃花岛。寒雨那个小坏蛋在这里加了无数的ｑｕｅｓｔ，看你能不能找全了。",
		"方": "方要正方！",
		"fang": "方要正方！",
		"圆": "圆要浑圆！",
		"yuan": "圆要浑圆！",
		"九阴真经": (: ask_jiuyin :),
		"双手互搏": (: ask_hubo :),
		"左右互搏": (: ask_hubo :),
		"结义": (: ask_jieyi :),
		"结拜": (: ask_jieyi :),
		"故事": (: ask_story :),
              "小龙女": (: ask_xlv :),
		"后来怎样": (: ask_story2 :),
		"武功": (: questions :),
		"功夫": (: ask_skill :),
	]));

	setup();

	if(random(2))
		carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/wudang/obj/white-robe")->wear();
}

void init()
{
	object ob = this_player();
	add_action("do_fangyuan","fangyuan");
	add_action("do_draw","draw");
	add_action("do_draw","hua");
	add_action("do_answer","answer");
	add_action("do_learn","learn");
	add_action("do_learn","xue");
	::init();
	if (ob->query("family/family_name") == "全真教") {
		command("angry " + ob->query("id"));
		command("say 怎么你到今天才来找我？！明天我就去和处机说让他打你屁股。");
	}
}

void kill_ob(object me)
{
        command("chat* crazy " + me->query("id"));
        ::kill_ob(me);
}

void unconcious()
{
        command("chat* 叹道：老顽童今日是要归天了，到阴世玩玩两只鬼打架，那些大头鬼、无常鬼一定瞧得莫名其妙，鬼色大变。");
        ::unconcious();
}


int ask_story()
{
        object me = this_player();
        string msg;
        msg = CYN"周伯通听到$N要他讲故事，登时兴高采烈。\n"NOR;
        msg+= CYN"周伯通开始讲起九阴真经和黄裳的故事。\n"NOR;
        msg+= CYN"周伯通看$N不问后来怎样，便赌气不说了。\n"NOR;
        message_vision(msg, me);
        me->set_temp("thd/story",1);
        return 1;
}

int ask_story2()
{
        object me = this_player();
        string msg;
        if (me->query_temp("thd/story") == 1){
                msg = CYN"周伯通一听$N问他后来怎样，又口沫横飞的说起来。\n";
                msg+= CYN"周伯通讲完又开始对$N说起他和全真教的故事。\n";
                msg+= CYN"$N听着，也学到了些全真教练气的皮毛。\n"NOR;
                msg+= HIW"周伯通说完故事，又无聊的问道：“兄弟，有什么好玩的武功么？\n"NOR;
                message_vision(msg, me);
                me->set_temp("thd/story",2);
                return 1;
        }
        message_vision(CYN"周伯通奇怪的问道：“什么后来怎样？”\n"NOR, me);
        return 1;
}

int ask_jieyi()
{
	object ob=this_player();
	int i, time;

	i = ob->query("combat_exp") - 1000000;
       i /= 100000;

	time = time() - ob->query("quest/jiebai/time");

	if (ob->query("quest/jiebai/pass")) {
		command("? " + ob->query("id"));
		command("say 咱俩不是结拜过了吗？");
		return 1;
	}
	if (ob->query("quest/jiebai/fail") >=3 && ob->query("registered") < 3){
		command("hmm");
		command("say 我不是说了，我没兴趣和你结拜啊！");
		return 1;
	}
	if ( ob->query("quest/jiebai/time") && time < 86400 ) {
		command("shake");
		command("say 我现在可没空，我忙着玩呢。");
      tell_object(ob,HIG"看起来周伯通在"+CHINESE_D->chinese_time(86400-time)+"之内不准备理你。\n"NOR);
		return 1;
	}
        if ( ob->query("quest/jiebai/fail") >= i && !ob->query("cw_exp")){
		command("shake");
		command("say 我现在可没空，我忙着玩呢。");
		return 1;
	}
        if (!wizardp(ob) && ob->query("age") > 48 && !ob->query("cw_exp")){
		command("shake");
		command("say 我老顽童只喜欢和青年人玩，和你结拜？没意思，没意思！");
		return 1;
	}
	if (ob->query("gender") != "男性" && ob->query("gender") != "女性") {
                if (ob->query("age") > 48 && !ob->query("cw_exp")) 
			command("say 我本来也想与你结拜，就是不知是兄弟相称还是姐弟相称？");
		else
			command("say 我本来也想与你结拜，就是不知是兄弟相称还是兄妹相称？");
		command("laugh");
		return 1;
	}
/*
        if ( ob->query("class") =="bonze" || ob->query("class") == "huanxi"){
		command("monk "+ ob->query("id"));
		command("say "+RANK_D->query_respect(ob)+"，老顽童我可没有兴趣和你结拜。");
		return 1;
}

	if ( ob->query("int") > 25) {
		command("shake");
		command("say 你这个人鬼灵精，保不准打着什么主意呢。");
		return 1;
	}
*/
	if ( ob->query("shen") < -100000) {
		command("shake");
		command("say 我虽然天性随便，但师尊教诲不敢忘，于正邪之道还是要分清的。");
		return 1;
	}
	if ( ob->query("combat_exp") < 1000000) {
		command("shake "+ ob->query("id"));
		command("say 这位"+RANK_D->query_respect(ob)+"你的武艺实在太糟糕了，我可没兴趣和你结拜。");
		return 1;
	}
	if (random(ob->query("kar")) < 20 || random(ob->query_int(1)) < 30){
		command("shake");
		command("say 我现在没有空，要不你先陪我玩玩？");
		ob->add("quest/jiebai/fail", 1);
		ob->set("quest/jiebai/time", time());
		log_file("quest/jiebai",
			sprintf("%-18s想与周伯通结拜，失败%s次。\n",
				ob->name(1)+"("+capitalize(getuid(ob))+")",
				chinese_number(ob->query("quest/jiebai/fail")) 
			), ob
		);
		return 1;
	}
	command("nod " + ob->query("id"));
	if (ob->query("gender") == "男性") {
		command("say 好吧，你我就结拜为兄弟吧。");
	}
	else if (ob->query("gender") == "女性") {
		if (ob->query("age") > 48)
			command("say 好吧，你我就结拜为姐弟吧。");
		else
			command("say 好吧，你我就结拜为兄妹吧。");
	}
	message_vision("周伯通与$N并肩而跪，朗声说道：“老顽童周伯通，今日与" + ob->name(1) +"义结金兰，日后有福共享，有难共当。\n"+
			"若是违此盟誓，教我武功全失，连小狗小猫也打不过。”\n", ob);
	log_file("quest/jiebai",
		sprintf("%-18s失败%s次后，成功与周伯通结拜，福：%d，悟：%d。\n",
			ob->name(1)+"("+capitalize(getuid(ob))+")",
			chinese_number(ob->query("quest/jiebai/fail")), 
			ob->query("kar"), 
			ob->query_int(1)
		), ob
	);
	ob->set("quest/jiebai/pass", 1);
	ob->set("quest/jiebai/exp", ob->query("combat_exp"));
	return 1;
}

int ask_jiuyin()
{
	object ob = this_player();
	object zhou = this_object();
	object book;
	int i,time;

	i = ob->query("combat_exp") - 2000000;
	i /= 500000;
	time = time()- ob->query("quest/jiuyin1/time");

	if(present("jiuyinzhenjing shangjuan", ob)) {
		command("faint");
		command("say 你不是有了么？");
		return 1;
	}
	if( zhou->is_busy() || zhou->is_fighting()){
		command("hmm");
		command("say 你没看见我正忙着么？");
		return 1;
	}
        if( ob->query("quest/jiuyin1/fail") >= 3 && ob->query("registered") < 3 && !ob->query("quest/jiuyin1/pass")){
		command("say 我正忙着呢。");
		return 1;
	}
        if( time < 86400 && !ob->query("quest/jiuyin1/pass") ) {
		command("say 我正忙着呢,你过一会儿再来吧。");
       tell_object(ob,HIG"看起来周伯通在"+CHINESE_D->chinese_time(86400-time)+"之内不准备理你。\n"NOR);
		return 1;
	}

	if ( ob->query("quest/jiuyin1/fail") >= i && ! ob->query("cw_exp") ) {
		command("say 我正忙着呢，你还是先回去好好学学武艺吧。");
		return 1;
	}

        if (ob->query("quest/jiuyin1/pass")){
		book = unew("/d/thd/obj/jiuyin-book1");
		if(!clonep(book)){
			command("pat");
			command("say 我现在没有空，「九阴真经上卷」你等会再来要吧。");
			return 1;
		}
		if(clonep(book) && book->violate_unique()){
			destruct(book);
			command("pat");
			command("say 我现在没有空，「九阴真经上卷」你等会再来要吧。");
			return 1;
		}
		command("consider");
		command("say 又要再抄一份？");
		message_vision(HIW"$N重新抄录了一份九阴真经的上卷。\n"NOR,ob);
		book->set("owner", ob->query("id"));
		book->move(ob);
		return 1;
	}
	if (ob->query_temp("jyquest") != 3) {
                command("? " + ob->query("id"));
                return 1;
	}
	command("say 九阴真经？那个本来是我师哥的，可是给黄老邪跟他老婆骗了去。");
	command("say 听她老婆告诉他的上卷残缺不全，下卷又被他自己徒弟偷了，这个就叫报应。");
	command("laugh zhou");
	ob->set_temp("jyquest", 4);
	command("say 来来来，到洞里面来，难得有个人找我，你别想跑了。");
	message_vision(HIY"周伯通拉着$N说道：“乖乖的听我说故事吧。”\n"NOR,ob);
	command("grin");
	ob->move("/d/thd/neidong");
	zhou->move("/d/thd/neidong");
	call_out("waiting", 120, ob);
	return 1;
}

int ask_skill()
{
	object me = this_player();
	object ob = this_object();
	object book;
	object* ppl;
	int i, total, j =0;

	if (me->query_temp("jyquest") != 5) {
		command("? " + ob->query("id"));
		return 1;
	}

	command("hehe zhou");
	command("say 这些功夫是我自己的创作，可厉害的很啊。");
	message_vision(CYN"周伯通却只是告诉$N如何施展，完全不演练给$N看。\n"NOR,me);

//关于执行效率的问题，如果玩家不满足条件，那也没必要去先取list和玩家数据吧。
//读了llm写的wiz教程，想想自己的代码，真是汗颜啊 By Jpei 

ppl = users();
total = me->query("str")+ me->query("int")+ me->query("dex")+ me->query("con"); 
	i = sizeof(ppl);
	while(i--) {
		if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query("quest/jiuyin1/pass"))
		j++;
	} 
	if( me->query("combat_exp") > 2000000
 	   && random(me->query("kar")) > 26
           && random(total) > 78
           && (
                 (!me->query("y-card-vip")&&random(20) == 3) 
               ||( me->query("y-card-vip")&&random(15) == 3)       //这里年卡月卡一视同仁了。
             )
           && j < 2 ){ 
		message_vision(HIW"\n周伯通在$N练习纯熟後，突然哈哈大笑起来。\n"NOR,me);
		command("haha");
		command("laugh");
		command("say 这些厉害武功，怎么是我自己的功夫？那就是九阴真经啊！");
		command("say 今天我总算看到的这功夫的威力，真是死也瞑目了。");
		book=unew("/d/thd/obj/jiuyin-book1");
		log_file("quest/jiuyin",
			sprintf("%-18s失败%s次后，得到九阴真经上册，悟：%d，福：%d，淳：%d。\n",
				me->name(1)+"("+capitalize(getuid(me))+")",
				chinese_number(me->query("quest/jiuyin1/fail")),
				me->query_int(1), 
				me->query("kar"), 
				me->query("pur") 
			), me
		);
		me->delete_temp("jyquest");
		me->set("quest/jiuyin1/pass",1);
		me->set("title",HIR"武林神话"NOR"·"HIC"九阴真经传人"NOR);      //板砖侍候
		if(!clonep(book)){
			command("hungry");
			command("say 好了，都看完了，肚子都饿了，我要吃饭去了。");
			return 1;
		}
		if(clonep(book) && book->violate_unique()){
			destruct(book);
			command("hungry");
			command("say 好了，都看完了，肚子都饿了，我要吃饭去了。");
			return 1;
		}                 
		command("say 反正你已经学会了，这九阴真经上卷让你抄录一份去吧。");
		message_vision(HIW"$N将九阴真经的上卷小心的抄录下来。\n"NOR,me);
		book->set("owner", me->query("id"));
		book->move(me);
		return 1;
	}
	message_vision(CYN"$N无论怎么练习就是无法成功。\n"NOR,me);
	command("sigh");
	command("say 我这高深武功，你大概别想学了吧。");
	command("disapp");
	me->add("quest/jiuyin1/fail", 1);
	me->set("quest/jiuyin1/time", time());
	log_file("quest/jiuyin",
		sprintf("%-18s想从周伯通处得到九阴真经上册，失败%s次。\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
			chinese_number(me->query("quest/jiuyin1/fail"))
		), me
	);
	me->delete_temp("jyquest");
	return 1;
}

void waiting(object ob)
{
	if( ob->query_temp("thd/story")==2 
	 && ob->query_temp("jyquest") == 4
	 && ob->query_temp("jiuyin/question") > 3){
		command("say 你陪我陪了这么久，一定很无聊吧？");
		command("hmm");
		command("ah zhou");
		command("say 这样吧，我教你点好玩的功夫！");
		command("grin");
		ob->set_temp("jyquest",5);
		ob->move("/d/thd/cave");
		this_object()->move("/d/thd/cave");
	}
	else {
		command("yawn");
		command("say 你这个人又笨又无聊，出去！出去！");
		ob->delete_temp("jyquest");
		ob->add("jiuyin/failed", 1);
		ob->move("/d/thd/cave");
		destruct(this_object());
	}
}

int ask_hubo()
{
	object ob=this_player();
	int hubo,i,time;

       i = ob->query("combat_exp") - 1000000;
	i /= 200000;
	time = time()- ob->query("quest/hubo/time");

	if(!ob->query("quest/jiebai/pass")){
		tell_object(ob,"周伯通正盯着你看，不知道打些什么主意。\n");
		command("say 你是谁啊，怎么莫名其妙地问我双手互搏的事啊？");
		return 1;
	}               
	if ( ob->query("double_attack")) {
		command("? " + ob->query("id"));
		command("say 你不是已经学会了吗？");
		return 1;
	}
	if( ob->query("quest/hubo/fail") >= 3 && ob->query("registered")< 3){
		command("disapp " + ob->query("id"));
		command("say 已经试了这么多次，看来你一辈子也练不会这门功夫了。");
		return 1;
	}
       if ( ob->query("quest/hubo/fail") >= i&&!ob->query("cw_exp") ) {
		command("shake " + ob->query("id"));
		command("say 看来你现在还不适合学这门功夫。");
		return 1;
}
       if ( ob->query("quest/hubo/time") && time < 86400) {
		command("shake " + ob->query("id"));
		command("say 看来你现在还不适合学这门功夫，你过段时间再来试试吧。");
       tell_object(ob,HIG"看起来周伯通在"+CHINESE_D->chinese_time(86400-time)+"之内不准备理你。\n"NOR);
		return 1;
	}
	hubo = ob->query_temp("zuoyou_hubo");
	if (hubo == 22) {
		command("say 接着练第一课！");
		return 1;
	}
	if (hubo == 1) {
		command("say 让你练你就快练嘛！");
		return 1;
	}
	if (hubo > 1 && hubo <= 21) {
		command("say 怎么样，练不会吧？就象黄蓉那女孩儿玲珑剔透，一颗心儿上生了十七八个窍，可是这门功夫她便始终学不会！");
		return 1;
	}
	if (ob->query_skill("force") < 100 || ob->query("max_neili") < 500 || ob->query("combat_exp") < 50000) {
		command("say 你还是先打好武学基础再说吧。");
		return 1;
	}
	command("say 这门功夫是我在洞中无聊之时想出来的玩意儿，说难是难到极处，说容易也容易之至。\n"+
		"有的人一学便会，有的人一辈子也学不了，越是聪明，越是不成。");
	command("say 你先练练这第一课：左手画方(fang)，右手画圆(yuan)。");
	ob->set_temp("zuoyou_hubo", 1);
	return 1;
}

int do_fangyuan()
{
	object ob=this_player();
	int hubo;

	if (ob->is_busy() || ob->is_fighting())
		return notify_fail("你正忙着呢！\n");

	hubo = ob->query_temp("zuoyou_hubo");
	if (!hubo) return 0;
	if (hubo < 21) {
		message_vision("$N伸出两根食指在地上划画，但画出来的方块有点象圆圈，圆圈又有点象方块。\n", ob);
		ob->add_temp("zuoyou_hubo", 1);
		return 1;
	}
	if (hubo == 21) {
		message_vision("$N伸出两根食指在地上划画，但画出来的方块有点象圆圈，圆圈又有点象方块。\n", ob);
		command("haha " + ob->query("id"));
		command("say 是么？你这一下便办不到！");
		ob->add_temp("zuoyou_hubo", 1);
		return 1;
	}
	if (hubo == 22) {
          if( (ob->query_temp("sj_credit/quest/public/hubo")&&random(ob->query("pur"))>18) 
                || random(ob->query("pur")) > 25 
                || ( ob->query("buyvip")&& random(ob->query("pur"))>=22 ) 
                || ( ob->query_temp("sj_credit/quest/public/hubo") &&ob->query("buyvip") && random(ob->query("pur"))>16) ){
				message_vision("$N微微一笑，凝神守一，心地空明，随随便便的伸出双手手指，左手画了一个方块，右手画了一个圆圈，\n"+
					"方者正方，圆者浑圆。\n", ob);
				say("周伯通大吃一惊，过了半晌才道：“这定是你从娘胎里学来的本领，那便易办了。”\n");
				message_vision("周伯通将他领悟出来的这门天下无比的奇功，一古脑儿都教给了$N。\n", ob);
                           ob->delete_temp("sj_credit/quest/public/hubo");
				ob->delete_temp("zuoyou_hubo");
				log_file("quest/jiebai",
					sprintf("%-18s失败%s次后，从周伯通处领悟到双手互搏，淳：%d。\n",
						ob->name(1)+"("+capitalize(getuid(ob))+")",
						chinese_number(ob->query("quest/hubo/fail")),
						ob->query("pur") 
					), ob
				);
				ob->set("double_attack", 1);
				ob->set("quest/hubo/pass", 1);
				return 1;
		                                                                                                         }

            else {
				ob->delete_temp("zuoyou_hubo");
				message_vision("$N又伸出两根食指在地上划画，但画出来的仍旧是方块有点象圆圈，圆圈又有点象方块。\n", ob);
				write("看来并不是这么简单。\n");
                           ob->delete_temp("sj_credit/quest/public/hubo");
				ob->add("quest/hubo/fail", 1);
				ob->set("quest/hubo/time", time());
      		              command("disapp " + ob->query("id"));

				log_file("quest/jiebai",sprintf("%-18s想从周伯通处领悟双手互搏，失败%s次。\n",
					ob->name(1)+"("+capitalize(getuid(ob))+")",chinese_number(ob->query("quest/hubo/fail")) ), ob);
				return 1;
	         }
               }
return 0;
}

int do_draw(string arg)
{
	object ob=this_player();

	if (!ob->query_temp("zuoyou_hubo")) return 0;
	if (arg == "fang" || arg == "方" || arg == "yuan" || arg == "圆") 
		return notify_fail("周伯通怒道：让你同时画方圆！\n");
	if (arg == "fang yuan" || arg == "方圆") return do_fangyuan();
	return 0;
}

int accept_object(object who, object ob)
{
	if (ob->id("skin") && ob->query("material") == "paper") {
		if ((who->query_temp("thd/onquest") == 7)&&(who->query_temp("thd/story")==2)) {
			message_vision(CYN"周伯通将人皮仔细查看，发现是九阴真经！\n"NOR, who);
			message_vision(CYN"你正想拿去交给黄药师，却被周伯通拦住。\n"NOR, who);
			command("say 这个等等再说，先来玩玩吧！");
			command("sing");
			command("say 好久没人来陪我玩啦，你跟我练练吧！");
			command("hit " + who->query("id"));
			call_out("finish",5, who);
			return notify_fail("");
		}
		else {
			command("? " + who->query("id"));
			command("say 给我这个做什么？\n");
			return notify_fail("");
		}
	}
	else if (who->query_temp("jyquest")==2 && ob->id("fan he") && ob->query("material") == "wood") {
		command("ah " + who->query("id"));
		command("say 是黄老邪的小丫头叫你帮忙送饭来么？");
		message_vision(CYN"周伯通不等$N回答，已经开始将食物塞进嘴中。\n"NOR,who);
		message_vision(CYN"周伯通吃完，干笑了一下，才对$N问道：“不知道你吃过了没有？”\n"NOR,who);
		who->set_temp("jyquest", 3);
		command("say 黄老邪想要我的九阴真经，把我关了十五年啦。");
		command("sing3");
call_out("destructing", 1, ob);
                return 1;
	}

       else if(ob->query("id") == "yufeng zhen" && who->query("family/family_name")=="古墓派") {
       command("ah ");
       command("say 一定是龙姑娘让你来找我的吧。 ");
       command("say 当年我被金轮法王的毒蛛咬中，多亏这小小的金针解毒。 ");
       who->set_temp("marks/yufengzhen",1);
             call_out("destructing", 1, ob); 
                return 1; 
            }



	return 0;
}

int prevent_learn(object ob, string skill)
{
	if (skill == "kongming-quan")
		return 0;
	return 1;
}
 
int is_apprentice_of(object ob)
{
	return 1;
}
 
int recognize_apprentice(object ob)
{
	return 1;
}

void finish(object who)
{
	string msg;
	msg = HIC"周伯通说道：“挨打没关系，多打你就习惯啦，好久没跟人打架了。”\n";
	msg+= HIY"周伯通说著，便向$N打来。\n";
	msg+= HIC"周伯通高兴的道：“快还手啊。”\n";
	msg+= HIR"$N的武功不及他，终于承受不了，晕了过去。\n"; 

	message_vision(msg, who); 
	who->set_temp("thd/onquest",8);
	who->unconcious();
}




int ask_xlv()
{
	object me=this_player();


	command("tsk ");
	command("say 龙姑娘和杨过两个小家伙可了不得，真是一对神仙眷侣。");
 
if( me->query_temp("marks/yufengzhen") && !me->query("gmhb") )
{
	message_vision(HIY"周伯通一听你问起小龙女的事情，不由得眉飞色舞。\n"+
			"周伯通给你讲起当年他和小龙女被金轮法王的毒蜘蛛困在山洞之中，小龙女\n"+
    	"学会左右互博，一手全真剑一手玉女剑打的金轮法王落荒而逃，说到精彩之处，\n"+
    	"不由得手舞足蹈，口沫四溅。\n"+
    "周伯通盯着你看了看，饶有兴趣的问道：“不知道龙姑娘有没有教你这门功夫？”\n"NOR, me);
    me->set_temp("marks/askzhou",1);
    me->delete_temp("marks/yufengzhen");
}
	return 1;

}

