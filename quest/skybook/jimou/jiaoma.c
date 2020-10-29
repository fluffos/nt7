// 牵制,效果：令对方士气降低
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

// #define _DEBUG_ID   "xiaobai"

void show_result(object ob, string who, int p_id, int e_id);
string e_name, p_name;

void main(object ob, string who)
{
	int p_id, e_id;
	int x,y,x2,y2;
	object env;
	string where;
	
	env = environment( ob );
	p_id=TROOP_D->get_char_troop(this_body()->query_primary_id());
	e_id=TROOP_D->get_char_troop(who);
	e_name=CHAR_D->get_char(who,"name");
	p_name=CHAR_D->get_char(ob->query_primary_id(),"name");
	where = TROOP_D->get_troop_area(p_id);
	if( !p_id){
                write("只有身在军中才能牵制敌方士气。\n");
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

                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 9 ){
			write("你离敌人太远无法施计。\n");
			return;}
                tell(deep_inventory(TROOP_D->find_troop(e_id)),
	"士兵一阵喧哗，原来是"+p_name+"对你的部队使用牵制之计。\n",
                        MSG_INDENT);
                // In future, we have to consider effects of the
                // ablility of general, zhenxing, dixing, etc.
                // Now the damage depends only on the No of bowman
	ob->simple_action(SG_SKILL_D->query_use("jiaoma"));
	ob->start_busy(10, "你正忙于牵制敌方士气呢。");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(),"jiaoma");
        ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20), "jiaoma");
	call_out("show_result", 5+random(5), ob, who, p_id, e_id);
}
void show_result(object ob, string who, int p_id, int e_id)
{	
	int mora,mora1;

// edc  08/05/2001
// change jiaoma logic, disconnect the relation between reputation and cast result
	int myJiaoma, itJiaoma=0, oldMorale;
	mixed sol;
	string *ss;
	string strMyId = ob->query_primary_id();

	myJiaoma = CHAR_D->get_char( strMyId, "skills" )["jiaoma"];
	if ( CHAR_D->get_char(who, "status") == "NPC" )
		itJiaoma = random(CHAR_D->get_char(who, "sk_wuli"));
	else
		itJiaoma = CHAR_D->get_skill(who,"jiaoma");
		
	mora = ( myJiaoma - itJiaoma / 4 ) / 4 + random(10) - 5;  // range: -12 -- 30

	// 敌军士气已经很低的时候, 效果降低, 死猪不怕开水烫的意思
	if ( mora > 0)
	{
		sol=TROOP_D->get_troops(e_id, "soldier");
		if(!sizeof(sol)) return;
		ss=keys(sol);
		foreach(string s in ss)
		{
			oldMorale = TROOP_D->get_soldier(e_id, s, "morale");
		}

        if ( oldMorale < 120)
            mora /= 3;
        else if ( oldMorale < 60 )
            mora /= 5;

	}
//EDCBUG(sprintf("MORALE DROP : %d \n", mora));
//EDCBUG(sprintf("the troop: %O \n", sol));
    SGSYS( sprintf("%s对%s使用 jiaoma , 效果：从%d减少了%d\n", strMyId, who, oldMorale, mora ) );
#ifdef _DEBUG_ID
    TELL_BUG( _DEBUG_ID, sprintf("%s对%s使用 jiaoma , 效果：从%d减少了%d\n", strMyId, who, oldMorale, mora ) );
#endif  // _DEBUG_ID

	if( mora > 24 )
	{	tell(deep_inventory(TROOP_D->find_troop(e_id)),
                	"士兵一片混乱，士气狂跌。\n",
                        MSG_INDENT);
		mora1 = random (6) +2;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                	"计策完全成功，敌人士气猛降。\n",
                        MSG_INDENT);
	} 
	else if( mora > 10 )
	{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        		"士兵一片颓唐，士气大降。\n",
                        MSG_INDENT);	
		mora1 = random (3) + 1;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                	"计策大成功，敌方士气大降。\n",
                        MSG_INDENT);	
	}
	else if( mora > 0)
	{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        		"士兵面露茫然之色，士气降低。\n",
                        MSG_INDENT);
		mora1 = 1;
		ob->simple_action(SG_SKILL_D->query_succ("jiaoma"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "计策成功，敌人士气降低。\n",
                        MSG_INDENT);
	}	
	else 
	{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        		"士兵识破敌人计策，士气上升。\n",
                        MSG_INDENT);
		ob->simple_action(SG_SKILL_D->query_fail("fenfa"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                	"计策失败，敌人士气上升，己方士气下降。\n",
                        MSG_INDENT);

	}
/*
	int rep=0, rep1=0;

	rep =random(CHAR_D->get_char(ob->query_primary_id(),"reputation"));
	rep1 =random(CHAR_D->get_char(who,"reputation"));
	rep+=ob->query_sk_level("jiaoma")*500*(random(5)+5)/5;
	if(CHAR_D->get_char(who,"skills"))
	rep1+=CHAR_D->get_char(who,"skills")["jiaoma"]*500*(random(5)+5)/5;
	rep = rep*2 - rep1 *3;
	rep-= (25+random(25))*500*(random(5)+5)/5; 
	ob->stop_busy();
	if( rep>100000)
	{	tell(deep_inventory(TROOP_D->find_troop(e_id)),
                "士兵一片混乱，士气狂跌。\n",
                        MSG_INDENT);
		mora = random (-20) -10 - rep/50000;
		mora1 = random (6) +2;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "计策完全成功，敌人士气猛降。\n",
                        MSG_INDENT);
	} 
	else
	{     if(rep>10000)
		{
	tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"士兵一片颓唐，士气大降。\n",
                        MSG_INDENT);	
		mora = random (-10) - 5- rep/10000;
		mora1 = random (3) + 1;
	tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "计策大成功，敌方士气大降。\n",
                        MSG_INDENT);	
		}
	      else if( rep>1000)
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"士兵面露茫然之色，士气降低。\n",
                        MSG_INDENT);
		mora = random(-5) - 1;
		mora1 = 1;
		ob->simple_action(SG_SKILL_D->query_succ("jiaoma"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "计策成功，敌人士气降低。\n",
                        MSG_INDENT);
		}	
	      else 
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"士兵识破敌人计策，士气上升。\n",
                        MSG_INDENT);
		mora = random(8) + 3;
mora1 = random(-10)-5;
		ob->simple_action(SG_SKILL_D->query_fail("fenfa"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "计策失败，敌人士气上升，己方士气下降。\n",
                        MSG_INDENT);
		}
	}
// edc 08/05/2001  set the maxium moral descresing value = -50	
	if (mora < -50) mora = -50;
////

*/
////
	WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
	TROOP_D->find_troop(p_id)->query_id()[1]+"使用叫骂之计。","b");
	TROOP_D->add_morale(p_id,mora1);
	if(p_id!=e_id){
		TROOP_D->add_morale(e_id,-mora);
	}
	return;
}
