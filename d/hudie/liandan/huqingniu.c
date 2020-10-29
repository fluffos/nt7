#include <ansi.h>;
inherit F_DEALER;
inherit NPC;

int ask_puti();
int ask_yuqing();
int ask_jinchuang();
int ask_yangjing();
int ask_jifeng();
int ask_jiuhua();
int ask_xieqi();
int ask_zhengqi();
int ask_longxi();
int ask_xiaoke();



void create()
{
    	set_name("胡青牛", ({ "hu qingniu", "hu", "qingniu" }));
    	set("title", YEL"蝶谷医仙"NOR);
    	set("gender", "男性");
    	set("long", "他就是医术高超的「蝶谷医仙」胡青牛。\n");
    	set("age", 65);
    	set("int", 30);
    	set("qi", 1000);
    	set("max_qi", 1000);
    	set("jing", 1000);
    	set("max_jing", 1000);
    	set("shen_type", 0);
    	set("combat_exp", 500000);
    	set("attitude", "heroism");
    	set_skill("unarmed", 80);
    	set_skill("dodge", 80);
    	set_skill("parry", 60);
    	set_temp("apply/attack", 70);
    	set_temp("apply/defense", 70);
    	set_temp("apply/damage", 50);
       set("inquiry", 
	([
    		"菩提子":(:ask_puti:),
    		"玉清散":(:ask_yuqing:),
    		"金创药":(:ask_jinchuang:),
    		"养精丹":(:ask_yangjing:),
		"九花玉露丸":(:ask_jiuhua:),
		"疾风骤雨丹":(:ask_jifeng:),
		"正人君子丹":(:ask_zhengqi:),
		"心狠手辣丹":(:ask_xieqi:),
		"龙犀百草丹":(:ask_longxi:),
		"消渴止饿丹":(:ask_xiaoke:),

       ]));
     	set("vendor_goods", 	({
     		__DIR__"axe",
     		__DIR__"blade",
     		__DIR__"yaochu",
     		__DIR__"dinglu",
                   __DIR__"bottle",
     		__DIR__"yao/huazhong",
     		__DIR__"yao/guozhong",

     	}));

    	setup();
    	carry_object("/clone/cloth/changpao")->wear();
} 
void init()
{
       add_action("do_list", "list");
       add_action("do_buy", "buy");
}

int accept_object(object who, object ob)
{
    
       if( !query("peifang", who) )
       	return notify_fail("胡青牛皱眉说道：你不是明教弟子，给我钱，我就会给你治病吗？\n");

    	if( query("money_id", ob) && ob->value()<100000 )
    	{
	       return notify_fail("胡青牛皱眉说道：这么一点点钱，还不够给炼药童子的零用呢！\n");
    	}

    	else if( query("money_id", ob) && ob->value() >= 100000 )
    	{
        	message_vision ("胡青牛说道："+RANK_D->query_respect(who)+"，上次的配方炼不出来？没关系，我这里的药方还多着呢。\n");
        delete("peifang", 	who);
        delete("mubiao", 	who);
        	return 1;
    	}
    	return 0;
}


int ask_puti()
{
    	object gen, mu, cao, hua, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 200)
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，你的炼丹能力不足，不能炼制菩提子。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "putizi", 	who);

   	message_vision("$N露出深思的神色，对$n说道：菩提子的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", hua)+"、"+query("name", guo)+"这五味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	destruct(guo);
	return 1;
}

int ask_yuqing()
{
    	object gen, mu, cao, hua, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 200)
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，你的炼丹能力不足，不能炼制玉清散。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "yuqingsan", 	who);


   	message_vision("$N露出深思的神色，对$n说道：玉清散的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", hua)+"、"+query("name", guo)+"这五味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	destruct(guo);
	return 1;
}

int ask_yangjing()
{
    	object gen, mu;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}

	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);

set("peifang", peifang, 	who);
set("mubiao", "yangjing", 	who);


   	message_vision("$N露出深思的神色，对$n说道：养精丹的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"这两味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(mu);
	return 1;
}
int ask_jinchuang()
{
    	object gen, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	cao=new(__DIR__"/yao/caolei");

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}

	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", cao);

addn("peifang", peifang, 	who);
set("mubiao", "jinchuang", 	who);


   	message_vision("$N露出深思的神色，对$n说道：金创药的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", cao)+"这两味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(cao);
	return 1;
}

int ask_jiuhua()
{
    	object gen, mu, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");

	if((int)who->query_skill("liandan-shu",1) < 50)
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，你的炼丹能力不足，不能炼制九花玉露丸。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);

set("peifang", peifang, 	who);
set("mubiao", "jiuhuawan", 	who);


   	message_vision("$N露出深思的神色，对$n说道：九花玉露丸的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"这三味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	return 1;
}

int ask_jifeng()
{
    	object gen, mu, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");

	if((int)who->query_skill("liandan-shu",1) < 50)
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，你的炼丹能力不足，不能炼制疾风骤雨丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);

set("peifang", peifang, 	who);
set("mubiao", "jifengdan", 	who);


   	message_vision("$N露出深思的神色，对$n说道：疾风骤雨丹的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"这三味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	return 1;
}

int ask_zhengqi()
{
    	object gen, mu, cao, hua;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");

	if((int)who->query_skill("liandan-shu",1) < 100)
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，你的炼丹能力不足，不能炼制正人君子丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);

set("peifang", peifang, 	who);
set("mubiao", "zhengrendan", 	who);


   	message_vision("$N露出深思的神色，对$n说道：正人君子丹的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", hua)+"这四味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	return 1;
}
int ask_xieqi()
{
    	object gen, mu, cao, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 100)
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，你的炼丹能力不足，不能炼制心狠手辣丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "xinhendan", 	who);


   	message_vision("$N露出深思的神色，对$n说道：心狠手辣丹的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", guo)+"这四味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(guo);
	return 1;
}

int ask_longxi()
{
    	object gen, mu, cao, hua, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 200)
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，你的炼丹能力不足，不能炼制龙犀百草丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "longxidan", 	who);


   	message_vision("$N露出深思的神色，对$n说道：龙犀百草丹的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"、"+query("name", hua)+"、"+query("name", guo)+"这五味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	destruct(guo);
	return 1;
}

int ask_xiaoke()
{
    	object gen, mu, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");

	if((int)who->query_skill("liandan-shu",1) < 50)
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，你的炼丹能力不足，不能炼制消渴止饿丹。\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N说道："+RANK_D->query_respect(who)+"，我上次给你的配方炼好了吗？\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);

set("peifang", peifang, 	who);
set("mubiao", "xiaokedan", 	who);


   	message_vision("$N露出深思的神色，对$n说道：消渴止饿丹的配方吗？我这里正好有一个，但是需要"+query("name", gen)+"、"
	+query("name", mu)+"、"+query("name", cao)+"这三味药材才能炼成。\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	return 1;
}