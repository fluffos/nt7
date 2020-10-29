// 谎报
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

void show_result(object ob, string who, int p_skill, int p_id, int e_id);

string e_name, p_name;

void main(object ob, string who)
{
	int p_skill, p_id, e_id;
string* charlist;
	int x,y,x2,y2, task;
	object env;
	string where,side;
	
	env = environment( ob );
	p_id=TROOP_D->get_char_troop(this_body()->query_primary_id());
	e_id=TROOP_D->get_char_troop(who);
	e_name=CHAR_D->get_char(who,"name");
	p_name=CHAR_D->get_char(ob->query_primary_id(),"name");
	where = TROOP_D->get_troop_area(p_id);
	if(!(p_skill=CHAR_D->get_char(ob->query_primary_id(),"skills")["huangbao"]))
        {       write("你不会谎报之计。\n");
                return;}
	if( !p_id){
                write("只有身在军中才能谎报。\n");
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
	side = TROOP_D->get_troops(p_id,"side");
	if (side == "a")
	{	write("只有防守方可以施用此计。\n");
		return;
	}
	task = TROOP_D->get_troops(e_id, "task_id");
	if( (who==TASK_D->get_task(task, "att_leader")) ){
                write("不可对主将施用此计。\n");
                return;
		}
charlist = TROOP_D->get_troops(e_id,"chars");

if(member_array(TASK_D->get_task(task, "att_leader"),charlist)>=0)
        {write("不可对主将部队使用.\n");
                return;
        }
	x =TROOP_D->get_troop_position(p_id)[0];
	y = TROOP_D->get_troop_position(p_id)[1];

	x2 = TROOP_D->get_troop_position(e_id)[0];
                y2 = TROOP_D->get_troop_position(e_id)[1];

                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 9 ){
			write("你离敌人太远无法施计。\n");
			return;}
                tell(deep_inventory(TROOP_D->find_troop(e_id)),
	"士兵一阵喧哗，原来是"+p_name+"对你的部队使用谎报之计。\n",
                        MSG_INDENT);
                // In future, we have to consider effects of the
                // ablility of general, zhenxing, dixing, etc.
                // Now the damage depends only on the No of bowman
	ob->simple_action(SG_SKILL_D->query_use("huangbao"));
	ob->start_busy(10, "你正忙于谎报呢。");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(), "huangbao");
        ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20), "huangbao");
	
	call_out("show_result", 5+random(5), ob, who, p_skill, p_id, e_id);
}
void show_result(object ob, string who, int p_skill, int p_id, int e_id)
{	
	int kill,kill1,mora,mora1;
        int e_skill;
int *task;
        int damage, p_num, e_num;
 	float rate;

        if (!(CHAR_D->get_char(who,"skills")))
        e_skill=0;
        else {
        e_skill=CHAR_D->get_char(who,"skills")["huangbao"];}
if(!objectp(find_user(who)))
e_skill = CHAR_D->get_skill(who,"sk_zhimou");
	if(CHAR_D->get_skill(who,"chenzhuo"))
e_skill = e_skill + 1.5*CHAR_D->get_skill(who,"chenzhuo");

kill = p_skill;
task = TASK_D->get_char_task(ob->query_primary_id());
if ( arrayp(task)&&sizeof(task)&&task[1]==3 )
{
kill-=20;
if(kill>50)kill=50;
}
kill1 = e_skill;
        kill = kill*2 - kill1 *1.2;
kill = random(kill);
        ob->stop_busy();	
	if(kill>100)
	{	tell(deep_inventory(TROOP_D->find_troop(e_id)),
                "你大喝道：救兵如救火，吾等速退！\n",
                        MSG_INDENT);
		mora1 = random (6) +2;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "计策完全成功，敌人撤退。\n",
                        MSG_INDENT);
		ob->simple_action(SG_SKILL_D->query_succ("huangbao"));	
		WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
TROOP_D->find_troop(p_id)->query_id()[1]+"使用谎报之计，令"+
TROOP_D->find_troop(e_id)->query_id()[1]+"全军撤退。","b");
	TROOP_D->remove_troop(e_id);
		return;
} 
	else
	{     if(kill>20)
		{
	tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"士兵开始逃走，想是受了谎报的影响。\n",
                        MSG_INDENT);	
		mora = random (-3) - 5;
		mora1 = random (3) + 1;
		rate = 1.1;
	tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "计策大成功，敌方士兵开始逃走。\n",
                        MSG_INDENT);	
	ob->simple_action(SG_SKILL_D->query_succ("huangbao"));
		}
	      else if( kill>5)
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"士兵面有疑问，受了谎报的影响。\n",
                        MSG_INDENT);
		mora = random(-2) - 1;
		mora1 = 1;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "计策成功，敌人受了谎报的影响。\n",
                        MSG_INDENT);
	ob->simple_action(SG_SKILL_D->query_succ("huangbao"));
		}	
	      else 
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"士兵成功破解敌人谎报。\n",
                        MSG_INDENT);
		mora = random(20) + 10;
		mora1 = random(-8) - 3;
		ob->simple_action(SG_SKILL_D->query_fail("huangbao"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "计策失败，我军蒙受损失。\n",
                        MSG_INDENT);
	  	damage= 100 + random (150);
        	WARAI_D->kill_troop(p_id,damage);
		WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
TROOP_D->find_troop(p_id)->query_id()[1]+"使用谎报之计失败，被敌人乘机歼
灭"+chinese_number(damage)+"人。","b");
		WARAI_D->clear_empty_troop(({p_id}));
		
		}
	}
	TROOP_D->add_morale(p_id,mora1);
	TROOP_D->add_morale(e_id,mora);
	if (kill >20)
	{	damage =kill*rate*2;
		WARAI_D->kill_troop(e_id,damage);
                WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
TROOP_D->find_troop(p_id)->query_id()[1]+"使用谎报之计，令"+
TROOP_D->find_troop(e_id)->query_id()[1]+"逃走"+
chinese_number(damage)+"人。","b");
                WARAI_D->clear_empty_troop(({e_id}));
	}
	return;
}
