//内讧
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

#define _DEBUG_ID   "xiaobai"

void show_result(object ob, string who,int p_skill, int p_id, int e_id, int t_id);

/* xiaobai: 有问题，当两个玩家同时用内讧时，应有两个 p_name, e_name,
    t_name 暂时无用，解决：将有用的那两个放到函数内
string e_name, p_name, t_name;
*/

void main(object ob, string who)
{
	int p_skill, p_id, e_id, r_id, t_id = 0;
	int i,x,y,x2,y2,x3,y3, *troops;
	object env;
	string where;
	string e_name, p_name;  // xiaobai: define locally
	
	env = environment( ob );
	p_id=TROOP_D->get_char_troop(this_body()->query_primary_id());
	e_id=TROOP_D->get_char_troop(who);
	e_name=CHAR_D->get_char(who,"name");
	p_name=CHAR_D->get_char(ob->query_primary_id(),"name");
	where = TROOP_D->get_troop_area(p_id);
	if(!(p_skill=CHAR_D->get_char(ob->query_primary_id(),"skills")["neihong"]))
	{	write("你不会内讧之计。\n");
		return;}
	if( !p_id){
                write("只有身在军中才能使用内讧之计。\n");
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
	x =TROOP_D->get_troop_position(p_id)[0];
	y = TROOP_D->get_troop_position(p_id)[1];

	x2 = TROOP_D->get_troop_position(e_id)[0];
                y2 = TROOP_D->get_troop_position(e_id)[1];
	
                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 4 ){
			write("你离敌人太远无法施计。\n");
			return;}
		troops = TROOP_D->list_troops();
        troops = troops - ({ p_id }) - ({ e_id});
        if( !sizeof(troops) )
	{ write ("无其它部队可供内讧。\n");
	return;}
	for( i = 0; i < sizeof(troops); i++ ){
                r_id = troops[i];
	if(TROOP_D->get_troop_side(r_id)!=TROOP_D->get_troop_side(p_id))	
	{	x3= TROOP_D->get_troop_position(r_id)[0];
		y3=TROOP_D->get_troop_position(r_id)[1];
		if ((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)<=1)
		t_id=r_id;
		}
		}
	if (!t_id)
	{	write("无其它部队可供内讧。\n");
		return;
	}

                tell(deep_inventory(TROOP_D->find_troop(e_id)),
	"一阵喧哗中，部下来报：“有敌来袭！”\n",
                        MSG_INDENT);
		tell(deep_inventory(TROOP_D->find_troop(t_id)),
        "一阵喧哗中，部下来报：“有敌来袭！”\n",
                        MSG_INDENT);
                // In future, we have to consider effects of the
                // ablility of general, zhenxing, dixing, etc.
                // Now the damage depends only on the No of bowman
	ob->simple_action(SG_SKILL_D->query_use("neihong"));
	ob->start_busy(10, "你正忙于施计呢。\n");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(), "neihong");	
	ob->award_exp(ob->query_sk_level("sk_zhimou")/2+20, "neihong");
	call_out("show_result", 10+random(5), ob, who, p_skill, p_id, e_id, t_id);
}
void show_result(object ob, string who, int p_skill, int p_id, int e_id, int t_id)
{	
	int kill,kill1,mora,mora1;
	int e_skill;
	int damage, t_num, e_num, p_num;
	int task_id;
	float rate;
    string p_name = CHAR_D->get_char(ob->query_primary_id(),"name");  // define locally
    	
	if (!(CHAR_D->get_char(who,"skills")))
	e_skill=0;
	else {
	e_skill=CHAR_D->get_char(who,"skills")["neihong"];}
	if(!objectp(find_user(who)))
	  e_skill = CHAR_D->get_skill(who,"sk_zhimou")*1.5;  //默认NPC的chenzhuo=zhimou
	if(CHAR_D->get_skill(who,"chenzhuo"))
	  e_skill = e_skill + 1.5*CHAR_D->get_skill(who,"chenzhuo");

kill = p_skill;
kill1 = e_skill;
	kill = kill*2 - kill1 *1.2;
kill = random(kill);
	ob->stop_busy();
	if( kill>50)
	{	tell(deep_inventory(TROOP_D->find_troop(e_id)),
                "你大声吼道：“冲！冲！”\n",
                        MSG_INDENT);
		tell(deep_inventory(TROOP_D->find_troop(t_id)),
                "你大声吼道：“冲！冲！”\n",
                        MSG_INDENT);
		mora = random (-20) -10;
		mora1 = random (6) +2;
		rate = 2;
		ob->simple_action(SG_SKILL_D->query_succ("neihong"));
		} 
	else
	{     if(kill>20)
		{
	tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"你叫道：“列队，小心敌人偷袭！”\n",
                        MSG_INDENT);	
	tell(deep_inventory(TROOP_D->find_troop(t_id)),
                "你叫道：“列队，小心敌人偷袭！”\n",
                        MSG_INDENT);
		mora = random (-10) - 5;
		mora1 = random (3) + 1;
		rate = 1.1;
		ob->simple_action(SG_SKILL_D->query_succ("neihong"));
		}
	      else if( kill>5)
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"你迟疑的说道：“小心列队，不可乱了军心！”\n",
                        MSG_INDENT);
		tell(deep_inventory(TROOP_D->find_troop(t_id)),
                "你迟疑的说道：“小心列队，不可乱了军心！”\n",
                        MSG_INDENT);
		mora = random(-5) - 1;
		mora1 = 1;
		rate = 0.4;
		ob->simple_action(SG_SKILL_D->query_succ("neihong"));
		}	
	      else 
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"你胸有成竹的说道：“不慌！此乃内讧之计！”\n",
                        MSG_INDENT);
		tell(deep_inventory(TROOP_D->find_troop(t_id)),
                "你胸有成竹的说道：“不慌！此乃内讧之计！”\n",
                        MSG_INDENT);
		mora = random(8) + 3;
		mora1 = random(-8) - 3;
		rate = 0;
		ob->simple_action(SG_SKILL_D->query_fail("neihong"));
		}
	}
	p_num=TROOP_D->get_soldier_total_number(p_id);
	e_num=TROOP_D->get_soldier_total_number(e_id);
	t_num = TROOP_D->get_soldier_total_number(t_id);
	TROOP_D->add_morale(p_id,mora1);
	TROOP_D->add_morale(t_id,mora);
	TROOP_D->add_morale(e_id,mora);
	if (t_num > (e_num*5))
damage = rate * kill * 1.5;
	else 
	{if (t_num < e_num)
damage = rate * kill * 1.2;
	else 
damage = rate * kill * 2;
	}
	if(damage>0){
            task_id=TROOP_D->get_troops(e_id,"task_id");
            WARAI_D->war_inf(task_id,
              TROOP_D->find_troop(e_id)->query_id()[1]+"中了"+p_name+"的内讧之计，与"+TROOP_D->find_troop(t_id)->query_id()[1]+"互战损失"+chinese_number(damage)+"人。","b");
	 WARAI_D->kill_troop(e_id,damage);
         WARAI_D->kill_troop(t_id,damage);	        
	 WARAI_D->clear_empty_troop(({t_id}));
	 WARAI_D->clear_empty_troop(({e_id}));
         }	
	else {
damage = random(200) + 100;
	task_id=TROOP_D->get_troops(e_id,"task_id");
	WARAI_D->war_inf(task_id,
	TROOP_D->find_troop(p_id)->query_id()[1]+"使用内讧之计失败，被敌人乘机歼灭"+chinese_number(damage)+"人。","b");
	WARAI_D->kill_troop(p_id,damage);
         WARAI_D->clear_empty_troop(({p_id}));	
	}
	
#ifdef _DEBUG_ID
    TELL_BUG( _DEBUG_ID, sprintf("%s对%s使用 neihong , 效果：歼敌%d人\n", p_name, who, damage ) );
#endif  // _DEBUG_ID
    
    return;
}
