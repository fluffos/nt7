// 侦察
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

#define WARINFO "/sgdomain/cmd/warinfo.c"

int p_id,p_skill;
string p_name;
string get_conds(int t);

void main(object ob)
{
	int i, x, y, x2, y2, id, *troops, b_num;
	int size;
	string disp,where,p_name,b_id,c_name, c_id,tmp;
	object env, o;
	mapping m;

	env = environment(ob);
	p_id = TROOP_D->get_char_troop(this_body()->query_primary_id());
	p_name=this_body()->query_id()[0];

        if( !(CHAR_D->get_char(p_name,"skills")) ){       
		write("你不会侦察之计。\n");
                return;
	}
	if( !p_skill=CHAR_D->get_char(p_name,"skills")["scout"] ){       
		write("你不会侦察之计。\n");
                return;
        }
	if( !p_id){
		write("只有身在军中才能使用侦察。\n");
		return;
	};
	if( ob->query_cur_mp()<60 ){
                write("你精神不足，不能使用这种计谋！\n");
		return;
	}

	ob->simple_action(SG_SKILL_D->query_use("scout"));
	size = p_skill/10;
        x = TROOP_D->get_troop_position(p_id)[0];
        y = TROOP_D->get_troop_position(p_id)[1];
	where = TROOP_D->get_troop_area(p_id);
	troops = TROOP_D->list_troops();
	troops = troops - ({ p_id });
	if( !sizeof(troops) ) return;

	disp=
"以下是你部队方圆"+chinese_number(size)+"之内的部队情况。\n";
	disp+=
"部队　　　　　代号     主将　　 大将数　兵数　 兵种    位置　状态\n";
	disp+=
"〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n";

	for( i = 0; i < sizeof(troops); i++ ){
		id = troops[i];
		x2 = TROOP_D->get_troop_position(id)[0];
		y2 = TROOP_D->get_troop_position(id)[1];
"/daemons/condition_d.c"->apply_condition(i,"appear",size,size);
		if( TROOP_D->get_troop_area(id) != where )continue;
		if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > (size * size) )continue;
		if ( mapp(m=TROOP_D->get_troops(id, "conds"))&&member_array("hide", keys(m))!=-1&&random(3)==1 ) continue;
		o = TROOP_D->find_troop(id);
		p_name = TROOP_D->get_troops(id,"name");
		b_id=o->query_id()[0];
   		c_id=TROOP_D->get_troops(id,"chars")[0];
   		c_name=CHAR_D->get_char(c_id,"name");
   		b_num=TROOP_D->get_troops(id,"total_num")+(100-p_skill)*10-random((100-p_skill)*20);
   		tmp=sprintf("%-18s%-9s%-8s %-8d%-7d%-9s%-6s%s\n",p_name,b_id,c_name,
    			sizeof(TROOP_D->get_troops(id,"chars")),
    			b_num,WARINFO->get_btype(id),WARINFO->get_pos(id),
    			get_conds(id));
    		disp+=tmp;
	};

	load_object("/daemons/cast_d.c")->reg_player(this_body()->query_primary_id(),"scout");
	ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20) ,"scout");
	more(disp);

	return;
}
string get_conds(int t)
{
	mapping conds;
	string* cond;
	string conditions;
	int i;

	conditions = "";
	conds = TROOP_D->get_troops(t, "conds");

	if (!sizeof(conds))return "正常";
	cond = keys(conds);
	for (i=0; i< sizeof(cond);i++){
		if (cond[i]=="hide")
			conditions +=" 隐藏 ";
		if (cond[i]=="poison")
			conditions +=" 中毒 ";
		if (cond[i]=="confuse")
			conditions +=" 混乱 ";
	}
	return conditions;
}	
