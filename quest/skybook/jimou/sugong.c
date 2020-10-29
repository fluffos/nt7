// 速攻
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

void show_result(object ob, int p_skill, int p_id);

void main(object ob)
{
	int p_id,p_skill;
	object env;
	string p_name;
	
	env = environment( ob );
	p_id=TROOP_D->get_char_troop(this_body()->query_id()[0]);
	p_name=this_body()->query_id()[0];

	if( !(CHAR_D->get_char(p_name,"skills")) )
		write("你不会速攻之计。\n");
        else if( !p_skill=CHAR_D->get_char(p_name,"skills")["sugong"] )
		write("你不会速攻之计。\n");
	else if( !p_id)
                write("只有身在军中才能使用速攻之计。\n");
	else {
		load_object("/daemons/cast_d.c")->reg_player(p_name, "sugong");
	ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20),"sugong");
		ob->simple_action(SG_SKILL_D->query_use("sugong"));
		ob->start_busy(10, "你正忙于使用速攻之计。");

		call_out("show_result", 5+random(5), ob, p_skill, p_id);
	}
}
void show_result(object ob, int p_skill, int p_id)
{	
	int mora;
	int kill;
	int damage;
	int soldier;

	kill = p_skill*2/3;
	kill = random(kill/2)+kill/2;
	soldier = TROOP_D->get_soldier_total_number(p_id);
	ob->stop_busy();

	if( kill>50 ){
		ob->simple_action(SG_SKILL_D->query_succ("sugong"));
		mora = random(5)+10;
	} else 
		{if( kill>15 ){
		ob->simple_action(SG_SKILL_D->query_succ("sugong"));
		mora = random(3)+5;
	} else {
		ob->simple_action(SG_SKILL_D->query_fail("sugong"));
		mora = -random(5) - 1;
	}}
	if( mora < 0 ){
		damage = (random(p_skill) + 12)/6;
	   	mora = -(mora * 10);
		load_object("/daemons/condition_d.c")->apply_condition(p_id,"confuse",mora,damage);
		WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
	TROOP_D->find_troop(p_id)->query_id()[1]+"使用速攻之计失败，陷入混乱之中。","b");
	} else {
	if ( soldier < 1000 ) soldier = 1000;
        mora = mora*1000/soldier;
	if(mora ==0) mora =1;	
	damage = (random(p_skill) + 12)/ 12;
		mora = mora * 10;
load_object("/daemons/condition_d.c")->apply_condition(p_id,"speedup",mora,damage);
		TROOP_D->set_troops(p_id, "sugong", 1);
	}

	return;
}
