// 混乱
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>
void show_result(object ob, string who, int p_skill, int p_id, int e_id);

string e_name, p_name;

void main(object ob, string who)
{
	int p_skill, p_id, e_id;
	int x,y,x2,y2;
	object env;
	string where;
	
	env = environment( ob );
	p_id=TROOP_D->get_char_troop(this_body()->query_primary_id());
	e_id=TROOP_D->get_char_troop(who);
	e_name=CHAR_D->get_char(who,"name");
	p_name=CHAR_D->get_char(ob->query_primary_id(),"name");
	where = TROOP_D->get_troop_area(p_id);
	if(!(p_skill=CHAR_D->get_char(ob->query_primary_id(),"skills")["hunluan"]))
        {       write("你不会混乱之计。\n");
                return;}
	if( !p_id){
                write("只有身在军中才能混乱敌人。\n");
                return;
        }	
	// In the furture, We have to consider theplayer's ablility
	// add the exp of this jimou, reduce mp, etc.
	if ( !e_id || TROOP_D->get_troop_area(e_id)!=where)
		{ write("对方不在此战场上。\n");
			return;
		}
	
	if (TROOP_D->get_troop_side(e_id) ==TROOP_D->get_troop_side(p_id))
                {write ("不可向己方部队施用此计。\n");
                        return;
                }
	p_skill=CHAR_D->get_char(ob->query_primary_id(),"skills")["hunluan"];
	x =TROOP_D->get_troop_position(p_id)[0];
	y = TROOP_D->get_troop_position(p_id)[1];

	x2 = TROOP_D->get_troop_position(e_id)[0];
                y2 = TROOP_D->get_troop_position(e_id)[1];

                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 9 ){
			write("你离敌人太远无法施计。\n");
			return;}
                tell(deep_inventory(TROOP_D->find_troop(e_id)),
	"士兵一阵喧哗，原来是"+p_name+"对你的部队使用混乱之计。\n",
                        MSG_INDENT);
                // In future, we have to consider effects of the
                // ablility of general, zhenxing, dixing, etc.
                // Now the damage depends only on the No of bowman
	ob->simple_action(SG_SKILL_D->query_use("hunluan"));
	ob->start_busy(10, "你正忙于混乱呢。");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(), "hunluan");
	ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20), "hunluan");
	call_out("show_result", 5+random(5), ob, who,p_skill, p_id, e_id);
}
void show_result(object ob, string who, int p_skill, int p_id, int e_id)
{	
	int kill,kill1,mora,mora1;
    int e_skill;
	int rate, damage, p_num, e_num, x, y, z;
	x=1.8;
	y=1;
	z =1.5;
	if (!(CHAR_D->get_char(who,"skills")))
        e_skill=0;
	else {
       	e_skill=CHAR_D->get_char(who,"skills")["hunluan"];
    }
//	if(!objectp(find_user(who))){
/*
	if(CHAR_D->get_char(who,"status")=STATUS_NPC){
		e_skill = CHAR_D->get_skill(who,"sk_zhimou");
		x = 1;
		y = 1;
		z = 1;
	}
*/		
	if(CHAR_D->get_skill(who,"chenzhuo")){
		e_skill = e_skill + CHAR_D->get_skill(who,"chenzhuo");
//		p_skill += random(p_skill/2);
	}
	kill = (p_skill+random(p_skill));
	kill1 = (e_skill+random(e_skill));
	tell_user("emperor",sprintf("被作用对象:%s,skill=%d,kill=%d,bekill=%d\n",who,p_skill,kill,kill1));
	kill = kill*x - kill1 *y;
//	kill = random(kill);
    ob->stop_busy();	
	if(kill>50)
	{	
		tell(deep_inventory(TROOP_D->find_troop(e_id)),"士兵像没头苍蝇一般，一片混乱。\n",
                      MSG_INDENT);
		mora = random (-10) -10;
		mora1 = random (6) +2;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
              	"计策完全成功，敌人完全混乱。\n",
                      MSG_INDENT);
		ob->simple_action(SG_SKILL_D->query_succ("hunluan"));
	} 
	else
	{     
		if(kill>15)
		{
			tell(deep_inventory(TROOP_D->find_troop(e_id)),
       			"士兵乱窜，显然混乱中。。\n",
                       MSG_INDENT);	
			mora = random (-5) - 5;
			mora1 = random (3) + 1;
			tell(deep_inventory(TROOP_D->find_troop(p_id)),
               "计策大成功，敌方混乱。\n",
                       MSG_INDENT);	
			ob->simple_action(SG_SKILL_D->query_succ("hunluan"));
		}
		else 
		{
			tell(deep_inventory(TROOP_D->find_troop(e_id)),
       			"士兵没有中计。\n",
                       MSG_INDENT);
			mora = random(8) + 3;
			mora1 = random(-8) - 3;
			ob->simple_action(SG_SKILL_D->query_fail("hunluan"));
			tell(deep_inventory(TROOP_D->find_troop(p_id)),
               "计策失败，我军蒙受损失。\n",
                       MSG_INDENT);
			damage= 100 + random (100);
			WARAI_D->kill_troop(p_id,damage);
			WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
				TROOP_D->find_troop(p_id)->query_id()[1]+"使用混乱之计失败，被敌人乘机歼
				灭"+chinese_number(damage)+"人。","b");
			WARAI_D->clear_empty_troop(({p_id}));
		
		}
	}
	TROOP_D->add_morale(p_id,mora1);
	TROOP_D->add_morale(e_id,mora);
	if (kill >15)
	{	damage = (p_skill - e_skill+ random(20))/ 12;
		kill = (kill /10) * 3;
		if(kill <1) kill = 1;	
		"/daemons/condition_d.c"->apply_condition(e_id,"confuse",kill,damage);
		WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
		TROOP_D->find_troop(p_id)->query_id()[1]+"使用混乱之计，令"+
		TROOP_D->find_troop(e_id)->query_id()[1]+"陷入混乱之中。","b");
	}
	return;
}
