// 奋发
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

int p_id,p_skill;
string p_name;

void main(object ob)
{
	int i, x, y, x2, y2, id, kill, kills,*troops,xtmp,ytmp,cn;
	int count;
	string where, s_type;
	mapping solider,enemy;
	object env;

	env = environment(ob);
p_id = TROOP_D->get_char_troop(ob->query_primary_id());
p_name=ob->query_id()[0];
if(objectp(find_user(ob->query_id()[0]))){
        if(!(CHAR_D->get_char(p_name,"skills")))
        {       write("你不会奋发之计。\n");
                return;
	}
	if(!p_skill=CHAR_D->get_char(p_name,"skills")["fenfa"])
        {       write("你不会奋发之计。\n");
                return;
        }
	if( !p_id){
		write("只有身在军中才能使用奋发。\n");
		return;
	};
}
else
       p_skill = 60+random(40);  //2001.4.19 npc的等级设定为60+random(40)
       
	solider = TROOP_D->get_troops(p_id, "soldier");
	s_type= keys(solider)[random(sizeof(keys(solider)))];	
	if( solider[s_type]["energy"] < 20 ){
		write("士兵行动力不足，难以使用奋发。\n");
		return;
	};


	troops = TROOP_D->list_troops();
	troops = troops - ({ p_id });
	if( !sizeof(troops) )return;
	where = TROOP_D->get_troop_area(p_id);
	if(sizeof(troops) < 2)
	{	write("你没有被包围吧。\n");
		return;
	}
	cn =0;
	xtmp = -1;
	ytmp= -1;
	x = TROOP_D->get_troop_position(p_id)[0];
        y = TROOP_D->get_troop_position(p_id)[1];
	count =0;
	for( i = 0; i < sizeof(troops); i++ ){
                id = troops[i];
                x2 = TROOP_D->get_troop_position(id)[0];
                y2 = TROOP_D->get_troop_position(id)[1];

                if( TROOP_D->get_troop_area(id) != where )continue;
                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 1 ||
TROOP_D->get_troop_side(id)==TROOP_D->get_troop_side(p_id))continue;
//		tell_user("group",id+"\n");
		if(xtmp== -1 || ytmp == -1)	
		{ xtmp = x2;
		 ytmp = y2;
		cn =1;
		}
		else {if (xtmp != x2 || ytmp!= y2)
		cn++;
		}
		}
//	tell_user("group","cn is "+chinese_number(cn));	
	if(cn<2)	
	 {       write("你没有被包围吧。\n");
                return;
        }		
	
	solider[s_type]["energy"] = 0;
        TROOP_D->set_troops(p_id, "solider", solider);
        ob->simple_action(SG_SKILL_D->query_use("fenfa"));
		
	x = TROOP_D->get_troop_position(p_id)[0];
	y = TROOP_D->get_troop_position(p_id)[1];
	load_object("/daemons/cast_d.c")->reg_player(p_name, "fenfa");
        ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20) ,"fenfa");
	
	for( i = 0; i < sizeof(troops); i++ ){
		if(count < 2){
		id = troops[i];
		x2 = TROOP_D->get_troop_position(id)[0];
		y2 = TROOP_D->get_troop_position(id)[1];

		if( TROOP_D->get_troop_area(id) != where )continue;
		if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 1 || TROOP_D->get_troop_side(id)==TROOP_D->get_troop_side(p_id))continue;
		tell(deep_inventory(TROOP_D->find_troop(id)),
			"被包围的敌人向你军冲了过来！\n",
			MSG_INDENT);		
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                        "奋勇的士兵冲入一支敌军中！\n",
                        MSG_INDENT);
kill = p_skill*p_skill*100/(21*50);
		if(kill<200)
		kill = random(50) + 150;
kills = 70*2000/(p_skill*p_skill);
		if(kills==0)kills=1;
		enemy = TROOP_D->get_troops(id, "soldier");
		s_type= keys(enemy)[random(sizeof(keys(enemy)))];
		WARAI_D->kill_troop(id,kill);
		WARAI_D->kill_troop(p_id,kills);
		WARAI_D->clear_empty_troop(({id}));
		count++;
		}
	};
	WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
TROOP_D->find_troop(p_id)->query_id()[1]+"使用奋发之计，杀敌"+
chinese_number(kill)+"人。","b");
	return;
}
