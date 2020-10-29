// 单挑
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>
#define EV_DANTIAO "/sgdomain/event/ev_dantiao.c"
void input_way(string arg);
void show_result(object ob, string who);
int p_id, p_skill;
int e_id;
string e_name, p_name,who_id,pl_id;
object target;
void main(object ob, string who)
{
	int x,y,x2,y2;
	object env;
	string where;
	
	env = environment( ob );
	p_id=TROOP_D->get_char_troop(this_body()->query_primary_id());
	e_id=TROOP_D->get_char_troop(who);
	e_name=CHAR_D->get_char(who,"name");
	p_name=CHAR_D->get_char(ob->query_primary_id(),"name");
	pl_id = ob->query_primary_id();
	where = TROOP_D->get_troop_area(p_id);
	target= find_body(who);
	who_id = who;
	if( !p_id){
                write("只有身在军中才能单挑。\n");
                return;
        }	
	// In the furture, We have to consider theplayer's ablility
	// add the exp of this jimou, reduce mp, etc.
	
	if ( !e_id || TROOP_D->get_troop_area(e_id)!=where)
		{ write("对方不在此战场上。\n");
			return;
		}
	
	if (!objectp(target))
		{ write("对方暂时不能单挑。\n");
			return;
		}
		
	if (TROOP_D->get_troop_side(e_id) ==TROOP_D->get_troop_side(p_id))
                {write ("不可向己方部队施用单挑。\n");
                        return;
                }
	x =TROOP_D->get_troop_position(p_id)[0];
	y = TROOP_D->get_troop_position(p_id)[1];

	x2 = TROOP_D->get_troop_position(e_id)[0];
                y2 = TROOP_D->get_troop_position(e_id)[1];

                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 36 ){
			write("你离敌人太远，无法单挑。\n");
			return;}
                tell(deep_inventory(TROOP_D->find_troop(e_id)),
	p_name+"遥指敌阵，怒声喝道：可有贼将敢与我一战？！\n",
                        MSG_INDENT);
                // In future, we have to consider effects of the
                // ablility of general, zhenxing, dixing, etc.
                // Now the damage depends only on the No of bowman
	ob->simple_action("$N遥指敌阵，怒声喝道：可有贼将敢于我一战？！\n");
	ob->start_busy(5, "你正忙于单挑呢。");
	set_this_player(find_user(who));
	find_user(who)->modal_push((:input_way:),"请输入你的选择(yes/no)：");
	return;
}

void input_way(string arg)
{
	if (arg == "yes")
		EV_DANTIAO->main(pl_id,who_id);
	else{
	if (arg == "no")
	  {
	tell(deep_inventory(TROOP_D->find_troop(p_id)),
	"敌将拒绝与你单挑。\n",MSG_INDENT);
	tell(deep_inventory(TROOP_D->find_troop(e_id)),
        "你拒绝与敌将单挑。\n",MSG_INDENT);		
	}
	else return;
	}
	 	
	find_user(who_id)->modal_pop();
	return;
}