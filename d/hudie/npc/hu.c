#include <ansi.h>
inherit NPC;
inherit F_VENDOR;
int ask_me();
int ask_quest();

void create()
{
	set_name("胡青牛", ({"hu qingniu", "hu"}));
	set("long", 
		"他就是江湖上闻名的蝶谷医仙胡青牛。\n"
		"不过，如果不是明教弟子，他是不会救治的，因此\n"
		"又有“见死不救”的外号。\n");
	set("title",HIW"蝶谷医仙"NOR);
	set("nickname",HIB"见死不救"NOR);
	set("rank_info/rude", "见死不救");
	set("attitude","peaceful");
	set("str", 20);
	set("dex", 20);
	set("con", 20);
	set("int", 20);
	set("per", 20);
	set("gender", "男性");
	set("age", 37);
	set("shen_type", 0);
	
	set("unique", 1); 
	set("no_get","他太重了。\n");
	set("vendor_goods", ({
	    }));
	set("combat_exp", 500000);

	set("max_qi", 2000);
	set("max_jing", 2000);
	set("eff_jingli",2000);
	set("max_jingli",2000);
	set("eff_jing",2000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali",50);
	
	set_skill("dodge",100);
	set_skill("force", 100);
	set_skill("literate",200);
	set_skill("hand",100);
	set_skill("strike",100);
	set_skill("hanbing-mianzhang",100);
	set_skill("sougu-yingzhua",100);
	set_skill("piaoyi-shenfa", 100);
	set_skill("shenghuo-shengong", 100);
	set_skill("parry", 100);

	map_skill("force", "shenghuo-shengong");
	map_skill("dodge", "piaoyi-shenfa");
	map_skill("sword", "liehuo-jian");
	map_skill("parry", "liehuo-jian");
	map_skill("blade", "lieyan-dao");
	map_skill("hand", "sougu-yingzhua");
	map_skill("strike", "hanbing-mianzhang");

	prepare_skill("strike", "hanbing-mianzhang");
	prepare_skill("hand","sougu-yingzhua");

	set("inquiry", ([
		"针灸": "针灸的学问可是很深奥啊。",
		"治疗" : (:ask_me:),
		"疗伤" : (:ask_me:),
		"解毒" : (:ask_me:),
		"经脉学" : (:ask_quest:),
	]));

	set("book9",1);
	set("book10",1);
	
	setup();
	
	carry_object("/clone/cloth/cloth")->wear();
}


void init()
{       
	object ob;
	::init();
	if( interactive(ob = this_player()) && visible(ob) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

void greeting(object ob)
{
       if(!ob || environment(ob) != environment()) return;
       command("say 这位"+RANK_D->query_respect(ob)+"来蝴蝶谷有什么事么？");
}


int ask_me()
{
	object ob;
	ob=this_player();

	if( query("family/family_name", ob) != "明教"){
	    command("sneer");
	    command("say 你不是明教弟子，休想要我治伤。");
	    return 1; }
	if( query("eff_qi", ob) >= query("max_qi", ob )
	 && query("eff_jing", ob) >= query("max_jing", ob )
	) {
		command("?"+query("id", ob));
		command("say 你根本没受伤，跑我这里添乱！");
		command("knock"+query("id", ob));
		return 1;
	}
	if (sizeof(ob->query_conditions_by_type("poison"))) {
		command("say 你中的毒我无能为力，还是另请高明吧。");
		return 1;
	}
	message_vision(HIW"胡青牛连点$N身上的穴道，再施金针。$N感觉舒服多了。\n", ob);
	ob->start_busy(3);
	remove_call_out("recover");
	call_out("recover",5,ob);
	return 1;
}

void recover(object ob)
{
	if (!ob) return;
set("eff_qi",query("max_qi",  ob), 	ob);
set("eff_jing",query("max_jing",  ob), 	ob);
	message_vision("过了一会儿，$N觉得伤势完全回复了！\n",ob);
	command("hehe"+query("id", ob));
}

int ask_quest()
{
	object me = this_player();
	object book;
	if (me->query_int() < 40) {
		command("say 你看来一副蠢样，还妄想学我的经脉学？");
		return 1;}
	if (me->query_skill("jingmai-xue",1)<170) {
		command("laugh"+query("id", me));
		command("say 你先好好打好基础吧。");
		return 1;}
	if (present("jingmai book",me)) {
		command("say 一次读太多书不好啊。");
		return 1;}
	if (me->query_skill("jingmai-xue",1)<180) {
		command("say 好吧，你就拿去好好研究吧。");
		message_vision(HIG"胡青牛给$N一卷华陀内昭图。\n"NOR, me);
		new("/d/mingjiao/obj/jingmai-book8")->move(me);
		return 1;} else
	if (me->query_skill("jingmai-xue",1)<190) {
	if( query_temp("hu/quest1", me) == 3 && query("book9")>0){
		command("ah");
		command("say 原来无忌已经帮我报仇了，多谢你帮我跑了一趟。");
		command("say 这本带脉论你拿去好好研究一下吧。");
		  book = new("/d/mingjiao/obj/jingmai-book9")->move(me);
		  addn("book9",-1);
		return 1;}
		command("say 唉，我那可怜的妹子，被华山那家伙。。。");
		command("say 可惜我武功实在不如。");
		command("sigh");
set_temp("hu/quest1", 1, 		me);
		return 1;} else
	if (me->query_skill("jingmai-xue",1)<200) {
	   if (present("tieyan ling",me) && query("book10") > 0) {
		command("oh");
		command("say 既然他实在无法分身前来，也就罢了。");
		command("say 他要我传你医术？");
		command("ok hu");
		command("say 这本子午针灸经是我一生心血所寄，你好好研究吧。");
		  destruct(present("tieyan ling",me));
		  book = new("/d/mingjiao/obj/jingmai-book10")->move(me);
		  addn("book10",-1);
		return 1;}
		command("say 无忌那孩子杀了鲜于通，报了我的大仇。");
		command("say 听说他已经身为明教教主了。我实在是想见他一面啊。");
		command("hmm");
set_temp("hu/quest2", 1, 		me);
		return 1;}
}