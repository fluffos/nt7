// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int kill_him();
void create()
{
        set_name("羽天白", ({ "master yu", "master"}) );
        set("nickname", HIR "万胜刀魔" NOR);
        set("gender", "男性" );
        set("age", 64);
	set("per", 3);
 set("reward_npc", 1);
    set("difficulty", 20);
        set("agi",25);
        set("int",30);
	set("attitude","friendly");
        set("max_force", 1500);
        set("force", 1500);
        set("force_factor", 30);
        set("long",
"
羽天白是西方神教中的教主，羽天白的来历谁也不清楚，
也没人敢问。凡是问过或知道羽天白来历的人都不明不白的
消失了。
\n"
	);
        create_family("西方神教", 1, "教主");
        	set("skill_public",1);
        	    set("rank_nogen",1);
    set("ranks",({"教徒","守卫","探子",RED"杀手"NOR,HIB"使者"NOR,
                      HIG"青翼蝠王"NOR,HIW"白眉鹰王"NOR,HIY"金毛狮王"NOR,MAG"紫衫龙王"NOR,
                      HIC"护法"NOR,HIC"尊者"NOR,WHT"狂刀"NOR,RED"刀魔"NOR,HIR"霸刀"NOR,HIW BLK"魅影刀煞"NOR}));
    	set("rank_levels",({ 5,10, 15,
					20,25,30,35,40,
					45,50, 55,60,65,
					70}));
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: perform_action, "blade.tiandirenmo" :),
                (: perform_action, "dodge.lianhuanbabu" :),
                (: perform_action, "blade.tiandirenmo" :),
                (: exert_function, "mihun" :)
        }) );
        set("combat_exp", 1000000);
        set("score", 200000);

        set_skill("move", 100);
        set_skill("parry",100);
        set_skill("dodge", 100);
        set_skill("force", 100);
        set_skill("literate", 180);
	set_skill("unarmed",160);
	set_skill("demon-steps",100);
	set_skill("demon-strike",100);
	set_skill("demon-force",100);
set_skill("blade",200);
	set_skill("demon-blade",150);
        map_skill("dodge", "demon-steps");
	map_skill("force", "demon-force");
	map_skill("unarmed", "demon-strike");
	map_skill("blade","demon-blade");
	map_skill("parry","demon-blade");
        set("inquiry", ([
                "白天羽" : (: kill_him :),
                "万马堂" : (: kill_him :),
        ]));
        setup();
        carry_object(__DIR__"obj/wufu")->wear();
	carry_object(__DIR__"obj/lou")->wield();

}

void attempt_apprentice(object me)
{
	if(me->query_temp("for_bandit"))
	{
	command("say 好！好！老夫今天可找到块有用之材。\n");
        command("recruit " + me->query("id") );
		return;
	}
	else
	{
	command("sigh");
        command("say 最近本教层出意外，先是罗刹牌被盗，再者副教主被刺，
还有老夫宝刀的寒萸刀鞘也丢了。\n");
	command("say 你若有能力察清此事，老夫便收你为徒。\n");

	}
}

void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "bandit");
}
int kill_him()
{
	object me;
	me = this_player();
	command("say 看来你已经知道我的来历了！！ \n");
	this_object()->kill_ob(me);
	me->kill_ob(this_object());
	return 1;
}
int accept_object(object me, object obj)
{
	if(obj->query("for_bandit"))
	{
	command("? "+me->query("id"));
        command("say 你．．你杀了本教的人，偷了本教的东西，还敢来愚弄老夫！\n");
	this_object()->kill_ob(me);
	me->kill_ob(this_object());
	return 1;
	}
	if(obj->query("for_bandit2"))
	{
	me->set_temp("for_bandit",1);
	command("smile");
	command("say 好，很好，还不乘着老夫高兴，拜老夫为师？\n");
	return 1;	
	}
	return 0;
}


void die()
{
        object ob;
        if( !ob = query_temp("last_damage_from") )
                ob = this_player(1);
        if(ob) 
        ob->set("marks/killyu",1);
        ::die();
}
