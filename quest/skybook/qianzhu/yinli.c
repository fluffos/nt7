// yinli.c 殷离
// Modify By River@sj 99.06
// Update By River@SJ For Qzs 2002.11.21

inherit NPC;

#include <ansi.h>
string ask_lsd();
string ask_popo();
string ask_qzs();
string ask_zhizhu();

void create()
{
	set_name("殷离", ({ "yin li", "yin", "li" }));
	set("gender", "女性");
	set("age", 19);
	set("long","她是个十七八岁的少女，荆钗布裙，是个乡村贫女，\n"+
                   "面容黝黑，脸上肌肤浮肿，凹凹凸凸，生得极是丑陋，\n"+
                   "只是一对眸子颇有神采，身材也是苗条纤秀。\n");
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 26);
	set("per", 6);
	set("unique", 1);
	set("location", 1);
	set("combat_exp", 300000);

	set("shen", -500);
	set("attitude", "peaceful");
	set("max_qi",600);
	set("max_jing",600);
	set("neili",800);
	set("max_neili",800);
	set("jiali",20);

	set_skill("unarmed", 60);
	set_skill("parry",60);
	set_skill("piaoyi-shenfa",60);
	set_skill("dodge", 60);
	set_skill("throwing",60);
	set_skill("duoming-jinhua",60);
	set_skill("qianzhu-wandushou", 60);
	set_skill("finger", 60);
	set_skill("force",60);
	set_skill("shenghuo-shengong",60);

	map_skill("force","shenghuo-shengong");
	map_skill("hand","qianzhu-wandushou");
	map_skill("dodge","piaoyi-shenfa");
	map_skill("throwing","duoming-jinhua");
	map_skill("parry","duoming-jinhua");
	prepare_skill("hand","qianzhu-wandushou");
	set("inquiry", ([
		"谢逊" : "是。。。是他的。",
		"灵蛇岛"  : (: ask_lsd :),
		"金花婆婆"  : (: ask_popo :),
		"千蛛万毒手" : (: ask_qzs :),
		"蜘蛛" : (: ask_zhizhu :),
		"修炼" : (: ask_zhizhu :),
	]));
	set("chat_chance", 3);
	set("chat_msg", ({
		(: random_move :),
		CYN"殷离突然自言自语道：“死鬼！我很老了么？老得像你妈了？”，说完又吃吃地笑了起来。\n"NOR,
		(: random_move :),
		"殷离从地下拾起一根柴枝，在地上乱抽了两下。\n",
		(: random_move :),
		CYN"殷离突然板着脸道：你取笑我生得丑，你不想活了。\n"NOR,
		(: random_move :),
		CYN"殷离弯过中指，用指节轻轻在你额头上敲了两下，笑道：乖儿子，那你叫我妈罢！\n"NOR,
	}));
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	setup();
	carry_object("/d/mingjiao/obj/green-cloth")->wear();
	carry_object(BINGQI_D("feihuangshi"))->wield();
}

string ask_qzs()
{
	object ob, me = this_player();
	mapping quest;
	int i, time;

	if ( me->query("gender") != "女性")
		return "这千蛛万毒手可不太适合大男人来修炼哦。";

        if ( me->query("combat_exp") < 1200000 )
		return "你的实战经验太少了，还是再去锻炼一番吧。";

	if ( me->query("con") < 15 || me->query("int") < 20) 
		return "你的先天条件实在太差，不适合修炼千蛛万毒手。";

        if ( present("goldbox", me))
		return "修炼千蛛万毒手所用的金盒不是在你这里么？还问我作甚？";

	if ( me->query_temp("get_jinhe"))
		return "我不是刚给你金盒了，怎么还来要啊？？";

	time = time() - me->query("qianzhu_time");
	if ( me->query("qianzhu_time") && time < 86400 && !wizardp(me))
	 	return "嗯？我不是和你说了，过段时间再来问问吧。";

	ob = unew(BOOK_D("jinhe"));
	if( !clonep(ob)) 
		return "哎哟，修炼千蛛万毒手的金盒不知道给谁拿走了。";

	quest = me->query("quest/qianzhu");

	if ( quest && quest["pass"]) {
		ob->set("xiulian", 10 + random(10));
		ob->move(me);
		me->set_temp("get_jinhe", 1);
		return "嗯，这里有个我才修炼过的金盒，既然你要就拿去吧。";
	}
	else {
		i = me->query("combat_exp", 1) / 500000;

		if ( me->query("registered") < 3 && quest && quest["fail"] >= 3 ){
			destruct(ob);
			return "你不适合修炼千蛛万毒手，还是不要再打探了吧。";
		}
		if ( quest && quest["fail"] >= i ) {
			destruct(ob);
			return "你短时间内还不适合修炼千蛛万毒手，还是过段时间再来打听吧。";
		}

		if (random(me->query_int(1)) > 30
		 && random(me->query_con(1)) > 35
            && QUEST_D->questing(me,1,0,1)
            && random(me->query_kar()) > (21-(int)me->query("per",1)/10) ) {
			command("look "+ me->query("id"));
			me->set("quest/qianzhu/pass", 1);
			me->delete("qianzhu_time");
			log_file("quest/qianzhu", 
				sprintf(HIR"%-18s失败%-2d次后，解开千蛛万毒手，悟：%d，根：%d，福：%d。"NOR,
					me->name(1)+"("+capitalize(getuid(me))+")", 
					me->query("quest/qianzhu/fail"),
					me->query_int(1), 
					me->query_con(1), 
					me->query_kar()
				), me
			);
			ob->move(me);
			return "嗯，你就拿着这个金盒去修炼(xiulian)千蛛万毒手吧。";
		}
		else {
			command("look "+ me->query("id"));
			me->add("quest/qianzhu/fail", 1);
			me->set("qianzhu_time", time());
			destruct(ob);
			log_file("quest/qianzhu", 
				sprintf("%-18s试图解开千蛛万毒手，失败%-2d次，悟：%d，根：%d，福：%d。\n",
					me->name(1)+"("+capitalize(getuid(me))+")", 
					me->query("quest/qianzhu/fail"),
					me->query_int(1), 
					me->query_con(1), 
					me->query_kar()
				), me
			);
			return "看来你还不适合修炼千蛛万毒手，过段时间再来问问吧。";
		}
	}
}

string ask_zhizhu()
{
	object me = this_player();

	if ( !me->query("quest/qianzhu/pass"))
		return "你还不适合修炼千蛛万毒手，问来没用。";
	else
		return "这金盒中的蜘蛛若是死了，可去星宿海附近抓些新的来。";
}

string ask_popo()
{
	this_player()->set_temp("ask_popo", 1);
	return "金花婆婆待我最好了，我们住在东海灵蛇岛上，只是有时来中原看看。";
}

string ask_lsd()
{
	object me=this_player();

	if(!me->query_temp("ask_popo"))
		return "嗯....这我可不清楚耶，你最好问问别人吧。";
	if(me->query("combat_exp") <100000)
		return "你这点身体的基础，怎么够出海呢？";
	if(this_object()->query_temp("waiting"))
		return "我正在玩呢，别烦我。";
	if(this_object()->query_temp("waiting1"))
		return "我正在玩呢，别烦我。";
	if(me->query_temp("yinli_failed"))
		return "哼，你不陪我玩，我才不会告诉你呢。";      
	if(me->query_temp("yinli_ask"))
		return "咦，我不是叫你先陪我玩玩吗？急什么急。";
	if(me->query_temp("yinli_ask1"))
		return "咦，我不是叫你跟着我到处去玩玩吗，还等什么呀？";
	if(me->query_temp("marks/灵蛇"))
		return "咦，我不是刚刚告诉过你了吗？";
	if(me->query("luopan/lsd"))
		return "咦，我不是已经告诉你了么？";
	me->set_temp("yinli_ask1",1);
	command("xixi");
	command("say 我一个人在这里好无聊啊，你先陪我玩玩好吗？");
	this_object()->set_temp("waiting", 1);
	remove_call_out("checking");
	call_out("checking", 20, me, this_object());
	return "你跟着(follow)我，我们到处去走走。";
}

int checking(object me, object ob)
{
	ob->delete_temp("waiting");
	if(!me || environment(me)!=environment(ob) || me->query_leader() != ob){
		me->delete_temp("yinli_ask1");
		me->set_temp("yinli_failed",1);           
		command("angry");
		command("say 不陪我就算了，谁稀罕！");
		return 1;
	}
	if(me->is_killing(ob->query("id"))){
		me->delete_temp("yinli_ask1");
		me->set_temp("yinli_failed",1);
		command("hmm "+me->query("id"));
		return 1;
	}
	me->delete_temp("yinli_ask1");
	me->set_temp("yinli_ask",1);
	command("say 好啊！好啊！那我们就到处逛逛吧。");
	ob->set("chat_chance", 35);
	ob->set_temp("waiting1", 1);
	remove_call_out("checking1");
	call_out("checking1", 12*me->query_con(), me, this_object());
	return 1;
}

int checking1(object me, object ob)
{
	ob->delete_temp("waiting1");
	if(!me || environment(me)!=environment(ob) || me->query_leader() != ob){
		me->delete_temp("yinli_ask");
		me->set_temp("yinli_failed",1);
		command("angry");
		command("say 才陪我了一会儿就溜了，谁稀罕！");
		return 1;
	}
	if(me->is_killing(ob->query("id"))){
		me->delete_temp("yinli_ask1");
		me->set_temp("yinli_failed",1);
		command("hmm "+me->query("id"));
		return 1;
	}
	me->delete_temp("yinli_ask");
	me->set_temp("marks/灵蛇",1);
	me->set("luopan/lsd", 1);
	command("say 好啦，我玩够了。你想知道灵蛇岛在什么地方是吧？");
	command("say 不过我可要先警告你，去那里很危险的哦！");
	command("whisper "+me->query("id")+" 婆婆的灵蛇岛在黄道带以东一百、以南五个距离的地方。");
	new("/d/mingjiao/obj/luopan")->move(ob);
	command("give luo pan to "+me->query("id"));
	ob->set("chat_chance", 3);
	return 1;
}
                                                                                 
