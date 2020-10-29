// dongfang.c 东方不败
// By River@SJ For kuihua-baodian Quest 2003.1.11

inherit NPC;

inherit F_MASTER;

#include <ansi.h>

string ask_me();
void create()
{
	object ob;
	set_name("东方不败", ({ "dongfang bubai", "dongfang", "bubai"}));
	set("long", "他就是武林之中一位惊天动地，威震当世的怪杰。\n"+
		"此刻他剃光了胡须，脸上竟然施了脂粉，身上那件衣衫式样男不男，女不女，\n"+
		"颜色之妖，便穿在少女身上，也显得太娇艳、太刺眼了些。\n");

	set("title",HIY"日月神教教主"NOR);         
	set("nickname", HIR"日出东方 唯我不败"NOR);
	set("gender", "无性");
	set("age", 54);
	set("attitude", "friendly");
	set("str", 35);
	set("int", 45);
	set("con", 45);
	set("dex", 45);
	set("per", 28);
	set("class", "eunuch");
	set("unique", 1);

	set("max_qi", 15000);
	set("max_jing", 10500);
	set("eff_jingli", 8000);
	set("max_neili", 23000);
	set("neili", 23000);
	set("jiali", 200);
	set("combat_exp", 5600000);
	set("shen", -50000);

	set_skill("sword", 380); 
	set_skill("parry", 380);
	set_skill("dodge", 380);
	set_skill("claw", 380);
	set_skill("force", 380);
	set_skill("pixie-jian", 380);        
	set_skill("youming-zhao", 380);
	set_skill("literate", 280);
	set_skill("kuihua-shengong", 380);

	map_skill("sword", "pixie-jian");
	map_skill("parry", "pixie-jian");
	map_skill("dodge", "pixie-jian");
	map_skill("claw", "youming-zhao");
	map_skill("force", "kuihua-shengong");
	prepare_skill("claw", "youming-zhao");

	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
//		(: exert_function, "yinyun" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.jue" :),
		(: perform_action, "sword.feiying" :),
	}));

	set_temp("apply/damage", 50);
	set_temp("apply/dodge", 120);
	set_temp("apply/attack", 80);
	set_temp("apply/armor", 170);
	set_temp("幽冥", 1);

	set("inquiry", ([
		"葵花宝典": (: ask_me :),
	]));

	setup();

	if (clonep()) {
		ob = unew(BOOK_D("kuihua"));
		if (!ob) ob = new("/clone/money/gold");
		ob->move(this_object());
		carry_object(BINGQI_D("xiuhua"))->wield();
		carry_object(ARMOR_D("xiupao2"))->wear();
	}
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BOOK_D("kuihua"))))
		ob->move(this_object());
}

string ask_me()
{
	object ob, me = this_player();
	mapping quest;
	int i, time;

	if ( is_busy() || is_fighting())
	 	return "你没看到我正忙着么？";

	if ( me->query("gender") == "女性")
		return "倘若我和你一样，生为女儿身，那就好了。";

	if ( me->query("int") < 20 )
		return "你的灵性不够，「葵花宝典」不适合你练习。";

	if ( me->query("dex") < 15 )
		return "「葵花宝典」讲究的是腾挪之法，你的身法实在太低了。";

	if ( me->query("combat_exp", 1) < 5000000)
		return "你的实战经验还不够，「葵花宝典」还不适合你修炼。";

	if ( present("kuihua baodian", me))
		return "咦？「葵花宝典」不是在你身上么？还问我作甚？";

	ob = present("kuihua baodian", this_object());

	if ( ! ob)
		return "耶？「葵花宝典」给我放到那里去了？";

	time = time() - me->query("quest/pixie/pxj_time");
	if ( me->query("quest/pixie/pxj_time") && time < 86400 && !wizardp(me))
	 	return "我现在很忙，没兴趣和你多罗嗦。";

	quest = me->query("quest/pixie");

	if ( ! quest || ! quest["pxj_passwd"])
		return "你从哪里听说到「葵花宝典」的？";

	if ( quest["pass"] ) {
		if ( ob ) {
			ob->set("owner", me);
			ob->move(me);
			return "好吧，这本「葵花宝典」你拿回去好好研究研究。";
		}
		else
			return "你要的「葵花宝典」已经给别人拿走了。";
	}

	i = me->query("combat_exp", 1) - 4500000;
	i /= 500000;

        if ( me->query("registered")< 3 && quest["fail"] >= i)
	 	return "我现在很忙，没兴趣和你多罗嗦！";
        if ( quest["fail"] >= i && !me->query("cw_exp") )
	 	return "我现在很忙，没兴趣和你多罗嗦！";
	me->set_temp("pxj_quest", 1);
	kill_ob(me);
	me->kill_ob(this_object());
	return "就凭你这"+RANK_D->query_rude(me)+"也敢来窥视我的「葵花宝典」！";
}

void die()
{
	object me = query_temp("last_damage_from");
	object ob = present("kuihua baodian", this_object());

	if ( ob ) {
		if ( 

                 objectp(me) 
                && me->query("kar") < 31 
                && random(me->query_int(1)) > 30
                &&random(me->query_dex(1)) > 35
                && random(me->query_con()) > 35
                && random(me->query("kar")) > 25
  && random(20) == 4
                      )
                {
			message_vision("\n", me);
			command("say 哈哈，你我也算是有缘之人，这本「葵花宝典」就交给你吧。");
			log_file("quest/pixie",
				sprintf(HIR"%-18s失败%-2d次后，获得「葵花宝典」，悟：%d，身：%d，福：%d。"NOR,
					me->name(1)+"("+capitalize(getuid(me))+")", 
					me->query("quest/pixie/fail"),
					me->query_int(1), 
					me->query_dex(1), 
					me->query_kar()
				), me
			);
			me->set("quest/pixie/pass", 1);
			me->delete("quest/pixie/pxj_time");
			me->delete_temp("pxj_quest");
			ob->set("owner", me);
			ob->move(me);
		}
		else {
			message_vision(CYN"\n$N怒叫道：「即使我死了，你等也休想得到「葵花宝典」，哈哈哈哈……」\n"NOR, this_object());
			message_vision("$N将那「葵花宝典」放在双掌中一搓，功力到处，一本原已十分陈旧的册页登时化作碎片。\n\n", this_object());
			if ( objectp(me) && me->query_temp("pxj_quest")) {
				me->add("quest/pixie/fail", 1);
				me->set("quest/pixie/pxj_time", time());
				me->delete_temp("pxj_quest");
				log_file("quest/pixie", 
					sprintf("%-18s试图获得「葵花宝典」，失败%-2d次，悟：%d，身：%d，福：%d。\n",
						me->name(1)+"("+capitalize(getuid(me))+")", 
						me->query("quest/pixie/fail"),
						me->query_int(1), 
						me->query_dex(1), 
						me->query_kar()
					), me
				);
			}
			ob->set("name", HIW"葵花宝典的碎片"NOR);
			ob->move(environment(this_object()));
		}
	}
	::die();
}

void unconcious()
{
	die();
}
                                                                                              
