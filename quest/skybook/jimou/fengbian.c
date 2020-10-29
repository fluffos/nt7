// 风变
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

#define WEATHER_CHANNEL "weather"
#define CHANNEL_FORMAT "%%^WEATHER_CHANNEL%%^【%s】%s%%^RESET%%^\n"

void show_wind(string where, int wind);

void main(object ob, string wind)
{
	int i;
	string where;
	object env;
	string *winds = ({"无风", "北风", "东北风", "东风", "东南风", "南风", "西南风", "西风", "西北风",});
	env = environment( ob );
        while( env && !inherits(BASE_ROOM, env) )env = environment( env );
	if( !where = env->get_area() ){
		write("只有在战场上才能改变风向。\n");
		return;
	};
	if( !wind || !stringp(wind) || member_array(wind, winds) == -1 ){
                write("现在本地区的风向是：" + DAY_D->get_wind_short(AREA_D->get_area(where, "wind")) + "。\n");
		write("无风，北风，东北风，东风，东南风，南风，西南风，西风，或西北风。\n");
                return;
        };
	if( member_array(wind, winds) == AREA_D->get_area(where, "wind") ){
		write("现在的风向就是：" + DAY_D->get_wind_short(AREA_D->get_area(where, "wind")) + "。\n");
		return;
	};

	// In the furture, We have to consider the player's ablility
	// add the exp of this jimou, reduce mp, etc.

	ob->simple_action("$N盘膝而坐，口中念念有词。\n");
	ob->simple_action("转眼间，乌云密布，狂风四起。\n");
	ob->start_busy(10, "你正忙于作法呢。");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(), "fengbian");
        ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20), "fengbian");
	call_out("show_result", 5+random(5), ob, where, member_array(wind, winds));
}
void show_result(object ob, string where, int wind)
{
	ob->stop_busy();
	if( random(2) == 1 ){
		ob->simple_action("一道闪电从天而降，接着一声巨响，风向改变了。\n");
		AREA_D->set_area(where, "wind", wind);
		show_wind(where, wind);
	} else {
		ob->simple_action("一道闪电从天而降，正好打在$N身上。\n");
		ob->set_cur_hp(0);
	}
	return;
}
void show_wind(string where, int wind)
{
	string w_info;
	object env, body, *players;
	
	players = users();
	foreach( object user in players ){
		if( !body = user->query_body() )continue;
		if( !env = environment(body) )continue;
		while (env && !inherits(BASE_ROOM, env))env = environment(env);
		if( !(env->get_area()) || env->get_area() != where )continue;
		if( wind ) w_info = "开始吹"+DAY_D->get_wind_short(wind)+"了。";
		else w_info = "风停了。";
		tell(({user}), sprintf(CHANNEL_FORMAT, "天气", w_info), MSG_INDENT);
	};
	return;
}
