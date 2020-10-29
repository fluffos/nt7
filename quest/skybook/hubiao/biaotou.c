
inherit NPC;
#include <ansi.h>
#include "skill.h";

void create()
{
	mapping name;
	int i;

	i = random(4);

	name = RNAME_D->get_random_name(i);
	set_name(name["name"], name["id"]);
	set("title", HIW"福威镖局总镖头"NOR);
	set("gender", (i==0?"女性":"男性"));
	set("age", 35 +random(30));
	set("combat_exp", 100000);
	set("attitude", "friendly");
	set("int", 25+random(5));
	set("con", 25+random(5));
	set("dex", 25+random(5));
	set("str", 25+random(5));
	set("per", 25);
	set("biaotou", 1);

	set("chat_chance", 2);
        set("chat_msg",({
		CYN+query("name")+"喝道：“闲杂人等闪开了。”\n"NOR,
		CYN+query("name")+"喝道：“快走快走，别偷懒！”\n"NOR,
	}));

	set_skill("literate", query("int") * 10);

	set("location",1);
	setup();
	carry_object("/clone/armor/bcloth")->wear();
//	carry_object("/clone/weapon/blade")->wield();
	carry_object(ARMOR_D("shoes"))->wear();
}

void init()
{
	object me;
	mapping killerskill1;
	int number,k_qi,k_neili,k_jing, k_jingli;
	string t_force,t_dodge;

	::init();

	me = this_object();

	if (!me->query_temp("skill_set")) {
		number = me->query_temp("level");
		k_qi = me->query_temp("qi");
		k_jing = me->query_temp("jing");
		k_neili = me->query_temp("neili");
		k_jingli = me->query_temp("jingli");

		killerskill1=skill2[random(sizeof(skill2))];

		t_force = k_force[random(sizeof(k_force))];
		t_dodge = k_dodge[random(sizeof(k_dodge))];       

		me->set_skill("force",number);
		me->set_skill("dodge",number);
		me->set_skill("parry",number);
		me->set_skill(t_force,number);
		me->set_skill(t_dodge,number);
		me->set_skill(killerskill1["t_skill"],number);
		me->set_skill(killerskill1["b_skill"],number);

		me->map_skill("force",t_force);
		me->map_skill("dodge",t_dodge);
		me->map_skill("parry",killerskill1["t_skill"]);
		me->map_skill(killerskill1["b_skill"],killerskill1["t_skill"]);

		me->prepare_skill(killerskill1["b_skill"],killerskill1["t_skill"]);

		me->set("max_qi",k_qi*6/5);
		me->set("eff_qi",k_qi*6/5);
		me->set("qi", k_qi*6/5);
		me->set("max_neili",k_neili*5/4);
		me->set("neili", me->query("max_neili"));
		me->set("max_jing", k_jing);
		me->set("eff_jing", k_jing);
		me->set("jing", k_jing);
		me->set("eff_jingli",k_jingli);
		me->set("jingli",k_jingli);
		me->set("jiali", 50);

		me->set_temp("skill_set", 1);
		return;
	}
}

void heart_beat()
{
	object me = this_object();
	object where;

	::heart_beat();

	if ( ! me) return;
	if ( !environment(me)) return;

	if ( me->query_temp("protecting")) {
		where = environment(me->query_temp("protecting"));
		if ( where && environment(me) != where)
			me->move(where);
	}
}
