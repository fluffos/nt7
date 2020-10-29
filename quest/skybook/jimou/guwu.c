// 鼓舞
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

void show_result(object ob, int p_id, int p_skill);

string p_name;

void main(object ob)
{
	int i, p_id, p_skill;
	object env;
	string where;
	
	env = environment( ob );
	p_id=TROOP_D->get_char_troop(this_body()->query_id()[0]);
	p_name=this_body()->query_id()[0];
p_skill=CHAR_D->get_char(p_name,"skills")["guwu"];
        if(!(CHAR_D->get_char(p_name,"skills")))
        {       write("你不会鼓舞之计。\n");
                return;
	}
	if(!p_skill=CHAR_D->get_char(p_name,"skills")["guwu"])
        {       write("你不会鼓舞之计。\n");
                return;
        }
	if(!p_id){
                write("只有身在军中才能鼓舞士气。\n");
                return;
        };	

	ob->simple_action(SG_SKILL_D->query_use("guwu"));
	ob->start_busy(10, "你正忙于鼓舞士气呢。");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(), "guwu");
	ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20), "guwu");
	call_out("show_result", 5+random(5), ob, p_id, p_skill);
}
void show_result(object ob, int p_id, int p_skill)
{	
	int mora;
        int kill;
        int damage;
	int *task;

kill = p_skill;
        kill = random(kill);
        ob->stop_busy();
	task = TASK_D->get_char_task(ob->query_primary_id());
	if ( arrayp(task)&&sizeof(task)&&task[1]==3 )
		kill-=(20+random(20));
        if( kill>50)
        {
                ob->simple_action(SG_SKILL_D->query_succ("guwu"));
mora = random ((kill+10)/2) +5;
        }
        else
        {     if(kill>15)
                {
                ob->simple_action(SG_SKILL_D->query_succ("guwu"));
                mora = random (10) + 5;
                }
              else
		{
		ob->simple_action(SG_SKILL_D->query_fail("guwu"));
		mora = random (-6) - 1;		
		}
	}
	
	TROOP_D->add_morale(p_id,mora);
	TROOP_D->recover_troop(p_id);
	return;
}
