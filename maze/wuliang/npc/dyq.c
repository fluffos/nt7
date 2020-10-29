// cool980310
// 段延庆
// cool980724
// Modify By River 98/12
// Modify by tangfeng@SJ
// 主要修改了标志的纪录方式；其他无修改

inherit NPC;
#include <ansi.h>
string ask_duan1();
string ask_duan2();
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"

int do_kill(object me, object ob);

void create()
{
        set_name("青袍客", ({ "qingpao ke", "ke"}) );
        set("gender", "男性" );
        set("age", 52);
        set("str", 30);
        set("con", 30);
        set("dex", 30);
        set("int", 25);
        set("per", 10);
   	set("attitude", "friendly");

	set("max_qi", 30000);
	set("max_jing", 30000);
	set("eff_jingli", 30000);
        set("max_neili", 6000);
        set("neili", 12000);
	set("jiali", 150);
        
        set("long","这人是个老者，长须垂胸，面目漆黑。\n",);
	set("env/一阳指","三叠");
        set("combat_exp", 1200000+random(500000));
        set("shen", -8000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat",({ 
		(: perform_action, "finger.sandie" :), 
		(: perform_action, "finger.sanmai" :),
		(: perform_action, "finger.yizhisanmai" :),
	}));

        set_skill("parry", 210);
        set_skill("dodge", 110);
        set_skill("force", 210);
        set_skill("finger", 300);
        set_skill("buddhism", 150);
        set_skill("literate", 300);
        set_skill("staff", 300);
        set_skill("duanjia-jian", 220);
        set_skill("qiantian-yiyang", 300);
        set_skill("sun-finger", 300);
        set_skill("tianlong-xiang", 100);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "sun-finger");
	map_skill("finger", "sun-finger");
	map_skill("force", "qiantian-yiyang");
	prepare_skill("finger","sun-finger");

	set("inquiry", ([
		"段誉" : (: ask_duan2 :),
		"name" : (: ask_duan1 :),
		"段延庆" : (: ask_duan1 :),
	]));

	setup();
	carry_object("/clone/cloth/cloth")->wear();
}
 void init()
{       
        object me,ob;
        ob = this_player(); 
        me = this_object();
        ::init();
        if( interactive(ob)
           && query_temp(QUESTDIR1+"kill", ob)){
          //query("kill_id",query("id",ob), me);
         call_out("kill_ob",1, ob); 
         }
}

string ask_duan1()
{
	object me,ob;
	ob=this_player();
	me=this_object();

	me->set_name("段延庆", ({ "duan yanqing", "duan","yanqing"}) );
set("title", HIC"四大恶人"NOR, 	me);
set("nickname", HIG"恶贯满盈"NOR, 	me);
	if( !query_temp(QUESTDIR1+"kill", ob))set_temp(QUESTDIR1+"ask1", 1, ob);
	return "老夫便是四大恶人中的老大：段延庆！";
}

string ask_duan2()
{
        object me,ob;
        ob=this_player();
        me=this_object();

	if( !query(QUESTDIR1+"over", ob) && query(QUESTDIR1+"pass_shanlu", ob) && query_temp(QUESTDIR1+"ask1", ob)){
		command("hehe"+query("id", ob));
set("kill_id",query("id",  ob), 		me);
		call_out("do_kill", 1, me, ob);
		return "想救段誉？送死来了！";
	}
	else return "你问这个干什么？";
}

int do_kill(object me, object ob)
{
	me->kill_ob(ob);
	ob->fight_ob(me);
	call_out("checking", 0, me, ob);
 	return 1;
}

void checking(object me, object ob)
{
	if (!ob) return;
	if (!me) return;
	if( !query_temp(QUESTDIR1+"kill", ob)){
		if( query("qi", me)*10/query("max_qi", me)<5
		 || query("eff_qi", me)*10/query("max_qi", me)<5){
set_temp(QUESTDIR1+"kill", 1, 			ob);
			message_vision(HIR"$n看见$N向后一跳，逃向一片大树林。\n"NOR, me, ob);
			message_vision(HIG"$n大声喝道：哪里跑！$n紧紧追了过去。\n"NOR, me, ob);
			ob->move("/maze/wuliang/shanlin-1");
			destruct(me);
		}
		else 
			call_out("checking", 1, me, ob);
	}
}

void die()
{
	  object me;
	  object ob=this_object();
      if( query("kill_id", ob )
                   && userp(me=present(query("kill_id", ob),environment(ob)) )
		 && query(QUESTDIR1+"pass_shanlu", me )
		 && !query_temp(QUESTDIR1+"kill", me )
		 && !query(QUESTDIR1+"over", me)){
set("quest/天龙八部/time", time(), 		me);
set("quest/天龙八部/combat_exp",query("combat_exp",  me), 		me);
delete_temp("quest/天龙八部", 		me);
delete_temp("quest/busy", 		me);
		log_file("quest/TLBB",sprintf("%s(%s)砍死段延庆，失败。经验：%d。\n",me->name(1),query("id", me),query("combat_exp", me)));
		command("sneer");
		message_vision(HIR"\n$N惨笑道：你杀了我，这辈子别想找到段誉了。\n"NOR, this_object());
		tell_object(me,HIG"\n看来，营救的事情只能由其他人完成，你还是暂时回避一下。\n"NOR);
	}
	::die();
}

void unconcious()
{
	die();
}
