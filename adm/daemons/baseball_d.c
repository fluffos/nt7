/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : baseball_d.c
 * Author : Clode@RevivalWorld
 * Date   : 2010-08-14
 * Note   : 棒球系统
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <message.h>
#include <npc.h>
#include <time.h>
#include <skill.h>
#include <baseball.h>
#include <equipment.h>
#include <buff.h>

#define DATA		"/data/daemon/baseball.o"
#define BACKUP_DATA	"/data/daemon/baseball.o.bak"

string *season;
mapping setup;
mapping record;
array games;
private nosave int tick;
private nosave int max_game_times;
int post_season_level;
int post_season_start;
string *post_season_team_8;
string *post_season_team_4;
string *post_season_team_2;
string *post_season_eliminate_teams;
int season_year;

private varargs string *game_finish(int gameindex, string stopid);

private nosave mapping positionname = 
([
	"P" : HIC"投"NOR CYN"手"NOR,
	"C" : HIG"捕"NOR GRN"手"NOR,
	"1B" : HIG"一"NOR GRN"垒手"NOR,
	"2B" : HIG"二"NOR GRN"垒手"NOR,
	"3B" : HIG"三"NOR GRN"垒手"NOR,
	"SS" : HIG"游"NOR GRN"击手"NOR,
	"RF" : HIY"右"NOR YEL"外野手"NOR,
	"CF" : HIY"中"NOR YEL"外野手"NOR,
	"LF" : HIY"左"NOR YEL"外野手"NOR,
	"DH" : HIR"指"NOR RED"定打击"NOR,
]);
private nosave string *pitch_ball_types = ({ "fourseam", "twoseam", "curveball", "slider", "forkball", "sinker" });
private nosave mapping pitch_ball_types_name = 
([
	"fourseam":"四缝线快速球",
	"twoseam":"二缝线快速球",
	"curveball":"曲球",
	"slider":"滑球",
	"forkball":"指叉球",
	"sinker":"伸卡球",
]);

// 调整能力数值，可控制变化率并限制在一定范围内
int calculate(int value, float decay, int value_max, int to_min, int to_max)
{
	float ratio = (to_max - to_min) / pow(to_float(value_max), decay);
	
	value = to_int( pow(to_float(value), decay) * ratio );
	
	value += to_min;
	
	return value;
}

int calculate_max_game_times(int year)
{
	if( !mapp(record[year]) ) return 0;
		
	max_game_times = 0;
	
	foreach(string team, mapping data in record[year][RECORD_TEAM])
		if( data["win"] + data["lose"] > max_game_times )
			max_game_times = data["win"] + data["lose"];
			
	return max_game_times;
}

int sort_team(string team1, string team2)
{
	int year = season_year;
	int win1, win2, lose1, lose2;
	int limit = (max_game_times-10)/2;
	float winrate1, winrate2;
	
	if( !mapp(record[year]) ) return 0;
		
	if( !mapp(record[year][RECORD_TEAM][team1]) )
		return 1;
		
	if( !mapp(record[year][RECORD_TEAM][team2]) )
		return -1;
		
	win1 = record[year][RECORD_TEAM][team1]["win"];
	win2 = record[year][RECORD_TEAM][team2]["win"];
	lose1 = record[year][RECORD_TEAM][team1]["lose"];
	lose2 = record[year][RECORD_TEAM][team2]["lose"];
	
	if( win1+lose1 == 0 )
		return 1;
	
	if( win2+lose2 == 0 )
		return -1;
		
	winrate1 = to_float(win1)/(win1+lose1);
	winrate2 = to_float(win2)/(win2+lose2);
	
	if( limit < 10 ) limit = 10;
		
	if( win1+lose1 < limit )
	{
		if( win2+lose2 <= limit )
			return winrate1 > winrate2 ? -1 : 1;
				
		return 1;
	}
	
	if( win2+lose2 < limit )
		return -1;

	if( winrate1 == winrate2 )
		return win1 > win2 ? -1 : 1;
	else
		return winrate1 > winrate2 ? -1 : 1;
}

string query_positionname(string code)
{
	return positionname[code];	
}

int save()
{
	save_object(DATA);
}

int backup()
{
	return cp(DATA, BACKUP_DATA);
}

varargs void broadcast(string msg, mapping game)
{
	if( post_season_start && post_season_level > 0 )
	{
		CHANNEL_D->channel_broadcast("sport", msg);
	}
	else
	{
		object user;
		
		foreach(string listener in setup[game[TEAM1]]["listener"] | setup[game[TEAM2]]["listener"] )
			if( objectp(user = find_player(listener)) )
				tell(user, HIG"【棒赛】"NOR+msg+"\n");
	}
}

// 球员或球队纪录
mixed add_record(int recordtype, string id, string key, mixed value)
{
	int year = season_year;
	
	if( undefinedp(record[year]) )
	{
		record[year] = allocate_mapping(0);
		record[year][RECORD_TEAM] = allocate_mapping(0);
		record[year][RECORD_PLAYER] = allocate_mapping(0);
		record[year][RECORD_SPECIAL] = allocate_mapping(0);
	}
	
	if( undefinedp(record[year][recordtype][id]) )
		record[year][recordtype][id] = allocate_mapping(0);
		
	if( intp(value) || floatp(value) )
		record[year][recordtype][id][key] += value;
	else
		record[year][recordtype][id][key] = value;
	
	return record[year][recordtype][id][key];
}

varargs mixed get_record(int recordtype, string id, string key, int year)
{
	if( undefinedp(year) )
		year = season_year;
	
	if( undefinedp(record[year]) ||  undefinedp(record[year][recordtype][id]) ) return 0;
		
	return record[year][recordtype][id][key];
}

// 增加球员纪录
void add_player_record(string id, int number, string key, int value)
{
	string player = setup[id]["roster"][number]["file"];

	add_record(RECORD_PLAYER, player, key, value);
}

// 增加球队纪录
void add_team_record(string id, string key, int value)
{
	add_record(RECORD_TEAM, id, key, value);
}

// 确认球队设定合法
varargs int valid_setup(string id, int all)
{
	object labor;
	object env;
	mapping roster_data;
	object boss = find_player(id);
	int fldaccuracy, fldrange;
	
	if( !mapp(setup[id]) ) return 0;	
	
	if( objectp(boss) )
	{
		setup[id]["username"] = boss->query_idname();
	}
	else if( !stringp(setup[id]["username"]) )
	{
		boss = load_user(id);
			
		setup[id]["username"] = boss->query_idname();	
			
		if( !userp(boss) )
			destruct(boss);	
	}
	
	if( !stringp(setup[id]["name"]) ) return 0;

	if( all )
	{
		setup[id]["outfield"] = 0;
		setup[id]["infield"] = 0;
	}
	
	for(int i=0;i<10;++i)
	{
		roster_data = setup[id]["roster"][i];
		
		if( !mapp(roster_data) )
			return 0;
			
		if( !objectp(labor = roster_data["object"]) )
		{
			if( !file_exists(roster_data["file"]) || !objectp(labor = load_object(roster_data["file"])) )
			{
				setup[id]["roster"][i] = 0;
				return 0;
			}

			roster_data["object"] = labor;
		}

		if( i==0 && labor->query_skill_level("twohands") > 0 )
			return 0;

		env = environment(labor);
		
		if( !objectp(env) || !env->is_module_room() || env->query_building_type() != "baseball" || query("owner", env) != query("boss", labor) || query("job/type", labor) != SPORTER )
		{
			setup[id]["roster"][i] = 0;
			return 0;
		}
		
		if( all )
		{
			roster_data[BUFF_BATTER_POWER] = labor->query_equipment_buff(BUFF_BATTER_POWER);
			roster_data[BUFF_PITCHER_POWER] = labor->query_equipment_buff(BUFF_PITCHER_POWER);
			roster_data[BUFF_FIELDER_POWER] = labor->query_equipment_buff(BUFF_FIELDER_POWER);

			fldaccuracy = labor->query_skill_level("fldaccuracy") + roster_data[BUFF_FIELDER_POWER];
			fldrange = labor->query_skill_level("fldrange") + roster_data[BUFF_FIELDER_POWER];
				
			switch(roster_data["position"])
			{
				case "P": setup[id]["infield"] += fldaccuracy * 4 / 5 + fldrange * 1 / 5 + labor->query_agi()/2; break;
				case "C": setup[id]["infield"] += fldaccuracy * 4 / 5 + fldrange * 1 / 5 + labor->query_agi()/2; break;
				case "1B": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "2B": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "3B": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "SS": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "RF": setup[id]["outfield"] += fldaccuracy * 1 / 4 + fldrange * 3 / 4 + labor->query_agi()/2; break;
				case "CF": setup[id]["outfield"] += fldaccuracy * 1 / 4 + fldrange * 3 / 4 + labor->query_agi()/2; break;
				case "LF": setup[id]["outfield"] += fldaccuracy * 1 / 4 + fldrange * 3 / 4 + labor->query_agi()/2; break;
				case "DH": break;
			}
			
			if( i == 9 )
			{
				setup[id]["outfield"] = calculate(setup[id]["outfield"], 0.8, 999*3, 500, 1000);
				setup[id]["infield"] = calculate(setup[id]["infield"], 0.8, 999*6, 500, 1000);
			}	
		}
	}
	
	return 1;
}

// 计算球队每场比赛应有收入
int query_income(string id)
{
	int year = season_year;
	int win, lose;
	
	if( !valid_setup(id) || !mapp(record[year]) || !mapp(record[year][RECORD_TEAM][id]) ) 
		return 0;	
	
	win = record[year][RECORD_TEAM][id]["win"];
	lose = record[year][RECORD_TEAM][id]["lose"];

	if( win + lose <= 0 ) return 0;

	return BASEINCOME * win / (win + lose);
}

string query_player_status(object player)
{
	string id = query("boss", player);
	mapping data;
	
	if( !undefinedp(setup[id]) && arrayp(setup[id]["roster"]) )
	{
		for(int i=0;i<10;++i)
		{
			data = setup[id]["roster"][i];
			
			if( !mapp(data) ) continue;

			if( data["file"] == base_name(player) )
				return positionname[data["position"]]+" "+(i > 0 ? GRN"第 "HIG+i+NOR GRN" 棒 "NOR:"");
		}	
	}
	
	return "";
}

// 球队设定
void set_setup(string id, mapping newsetup)
{
	setup[id] += newsetup;
	
	save();
}

// 删除球队设定
void delete_setup(string id)
{
	map_delete(setup, id);
	
	save();
}

// 加入季赛
void join_season(string id)
{
	int index;
	
	// 已经加入季赛
	if( member_array(id, season) != -1 ) return;
		
	season = sort_array(season, (: random(2) ? 1 : -1 :));

	foreach(string oldid in season)
	{
		index = random(sizeof(setup[oldid]["opponents"]));
	
		if( member_array(id, setup[oldid]["opponents"]) == -1 )
			setup[oldid]["opponents"] = setup[oldid]["opponents"][0..index] + ({ id }) + setup[oldid]["opponents"][index+1..];
	}
	
	if( !sizeof(setup[id]["opponents"]) )
		setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :)));

	setup[id]["listener"] |= ({ id });

	season |= ({ id });		
}

// 取消比赛
varargs void cancel_game(string id, int force)
{
	int gamessize = sizeof(games);
	
	for(int i=0;i<gamessize;++i)
	{
		if( !mapp(games[i]) ) continue;
		
		if( games[i][TEAM1] == id || games[i][TEAM2] == id )
		{
			if( force )
			{
				if( games[i][TEAM1] == id )
					game_finish(i, id);
				else if( games[i][TEAM2] == id )
					game_finish(i, id);
			}
			else
			{
				setup[games[i][TEAM1]]["status"] = STATUS_IDLE;
				setup[games[i][TEAM2]]["status"] = STATUS_IDLE;
				
				games[i] = 0;
			}
		}
	}
	
	games -= ({ 0 });
}

// 退出季赛
void leave_season(string id)
{
	if( member_array(id, season) == -1 ) return;

	foreach(string oldid in season)
		setup[oldid]["opponents"] -= ({ id });

	cancel_game(id);

	season -= ({ id });
}

// 是否加入季赛
int in_season(string id)
{
	return member_array(id, season) != -1;
}

// 是否正在比赛中
int query_status(string id)
{
	if( !in_season(id) ) return 0;
		
	return setup[id]["status"];
}

// 比赛结束
private varargs string *game_finish(int gameindex, string stopid)
{
	int year = season_year;
	string *msg = allocate(0);
	mapping game = games[gameindex];
	string team1name = setup[game[TEAM1]]["name"];
	string team2name = setup[game[TEAM2]]["name"];
	string income_msg = HIG"收入"NOR GRN"分配"NOR;
	string finalscore;
	string winteam, loseteam;
	
	if( !undefinedp(stopid) && stringp(stopid) )
	{
		if( game[TEAM1] == stopid )
			game[TEAM1SCORE] = -1;
		else if( game[TEAM2] == stopid )
			game[TEAM2SCORE] = -1;	
	}

	if( game[TEAM1SCORE] > game[TEAM2SCORE] )
	{
		winteam = game[TEAM1];
		loseteam = game[TEAM2];
	}
	else
	{
		winteam = game[TEAM2];
		loseteam = game[TEAM1];
	}
	finalscore = HIG"比赛"NOR GRN"结果"NOR" 双方"+(game[INNING]>18?"一共缠斗了 "+(game[INNING]/2+game[INNING]%2)+" 局，":"")+"比分为"+setup[game[TEAM2]]["username"]+"“"+team2name+" "+game[TEAM2SCORE]+" : "+game[TEAM1SCORE]+" "+team1name+"”"+setup[game[TEAM1]]["username"];
	
	switch(game[TEAM1SCORE] - game[TEAM2SCORE])
	{
		case -999..-16:		msg += ({ finalscore+"，可怜的“"+team1name+"”遭到了恐怖的血腥屠杀" });	break;
		case -15..-11:		msg += ({ finalscore+"，“"+team2name+"”彻底的羞辱了对手" });			break;
		case -10..-6:		msg += ({ finalscore+"，“"+team2name+"”不留颜面地痛宰了对手" });		break;
		case -5..-3:		msg += ({ finalscore+"，“"+team2name+"”在这场比赛中轻松获胜" });		break;
		case -2..-1:		msg += ({ finalscore+"，“"+team2name+"”在惊险中获胜" });			break;
		case 1..2:		msg += ({ finalscore+"，“"+team1name+"”在惊险中获胜" });			break;
		case 3..5:		msg += ({ finalscore+"，“"+team1name+"”在这场比赛中轻松获胜" });		break;
		case 6..10:		msg += ({ finalscore+"，“"+team1name+"”不留颜面地痛宰了对手" });		break;
		case 11..15:		msg += ({ finalscore+"，“"+team1name+"”彻底的羞辱了对手" });			break;
		case 16..999:		msg += ({ finalscore+"，可怜的“"+team2name+"”遭到了恐怖的血腥屠杀" });	break;
		//default: error("error score");
	}
	
	if( !post_season_level )
	{	
		add_team_record(winteam, "win", 1);
		add_team_record(loseteam, "lose", 1);

		if( setup[winteam]["keeploses"] >= 5 )
		{
			msg += ({ "“"+setup[winteam]["name"]+"”中止了最近的 "HIG+setup[winteam]["keeploses"]+NOR" 连败。" });
		}
		if( setup[loseteam]["keepwins"] >= 5 )
		{
			msg += ({ "“"+setup[loseteam]["name"]+"”中止了最近的 "HIR+setup[loseteam]["keepwins"]+NOR" 连胜。" });
		}
			
		setup[winteam]["keepwins"]++;
		setup[winteam]["keeploses"] = 0;
		
		setup[loseteam]["keepwins"] = 0;
		setup[loseteam]["keeploses"]++;
		
		if( setup[winteam]["keepwins"] > record[year][RECORD_SPECIAL]["keepwins"] )
		{
			record[year][RECORD_SPECIAL]["keepwins"] = setup[winteam]["keepwins"];
			record[year][RECORD_SPECIAL]["keepwinsteam"] = winteam;
			
			msg += ({ HIY"纪录"NOR YEL"更新 "NOR"士气高昂的“"+setup[winteam]["name"]+"”突破本季最长连胜纪录，"HIR"连胜"NOR RED"纪录"NOR"来到第 "HIR+setup[winteam]["keepwins"]+NOR" 场" });
		}
		else if( setup[winteam]["keepwins"] >= 5 )
		{
			msg += ({ "“"+setup[winteam]["name"]+"”打出一波 "HIR+setup[winteam]["keepwins"]+NOR" 连胜，战绩大幅跃进" });
		}
		
		if( setup[loseteam]["keeploses"] > record[year][RECORD_SPECIAL]["keeploses"] )
		{
			record[year][RECORD_SPECIAL]["keeploses"] = setup[loseteam]["keeploses"];
			record[year][RECORD_SPECIAL]["keeplosesteam"] = loseteam;
			
			msg += ({ HIY"纪录"NOR YEL"更新 "NOR"士气低落的“"+setup[loseteam]["name"]+"”苦吞本季最长连败纪录，"HIG"连败"NOR GRN"纪录"NOR"来到第 "HIG+setup[loseteam]["keeploses"]+NOR" 场" });
		}
		else if( setup[loseteam]["keeploses"] >= 5 )
		{
			msg += ({ "“"+setup[loseteam]["name"]+"”连续吞下 "HIG+setup[loseteam]["keeploses"]+NOR" 连败，战绩大幅退后" });
		}
	}
	
	// 单场最多三振纪录
	if( game[TEAM1K] > game[TEAM2K] && game[TEAM1K] > record[year][RECORD_SPECIAL]["maxstrikeouts"] )
	{
		record[year][RECORD_SPECIAL]["maxstrikeouts"] = game[TEAM1K];
		record[year][RECORD_SPECIAL]["maxstrikeoutsplayer"] = setup[game[TEAM1]]["roster"][0]["file"];
		
		msg += ({ HIY"纪录"NOR YEL"更新 "NOR"“"+team1name+"”的"+setup[game[TEAM1]]["roster"][0]["object"]->query_idname()+"突破本季投手单场最多三振纪录，纪录来到 "HIY+game[TEAM1K]+NOR YEL"K"NOR" ！！" });
	}
	else if( game[TEAM2K] > game[TEAM1K] && game[TEAM2K] > record[year][RECORD_SPECIAL]["maxstrikeouts"] )
	{
		record[year][RECORD_SPECIAL]["maxstrikeouts"] = game[TEAM2K];
		record[year][RECORD_SPECIAL]["maxstrikeoutsplayer"] = setup[game[TEAM2]]["roster"][0]["file"];
		
		msg += ({ HIY"纪录"NOR YEL"更新 "NOR"“"+team2name+"”的"+setup[game[TEAM2]]["roster"][0]["object"]->query_idname()+"突破本季投手单场最多三振纪录，纪录来到 "HIY+game[TEAM2K]+NOR YEL"K"NOR" ！！" });
	}
	
	// 单场最多安打纪录
	if( game[TEAM1HIT] > game[TEAM2HIT] && game[TEAM1HIT] > record[year][RECORD_SPECIAL]["maxhits"] )
	{
		record[year][RECORD_SPECIAL]["maxhits"] = game[TEAM1HIT];
		record[year][RECORD_SPECIAL]["maxhitsteam"] = game[TEAM1];
		
		msg += ({ HIY"纪录"NOR YEL"更新 "NOR"“"+team1name+"”突破本季单场最多安打纪录，纪录来到 "HIY+game[TEAM1HIT]+NOR YEL" 只安打"NOR" ！！" });
	}
	else if( game[TEAM2HIT] > game[TEAM1HIT] && game[TEAM2HIT] > record[year][RECORD_SPECIAL]["maxhits"] )
	{
		record[year][RECORD_SPECIAL]["maxhits"] = game[TEAM2HIT];
		record[year][RECORD_SPECIAL]["maxhitsteam"] = game[TEAM2];
		
		msg += ({ HIY"纪录"NOR YEL"更新 "NOR"“"+team2name+"”突破本季单场最多安打纪录，纪录来到 "HIY+game[TEAM2HIT]+NOR YEL" 只安打"NOR" ！！" });
	}
		
	// 单场最多得分纪录
	if( game[TEAM1SCORE] > game[TEAM2SCORE] && game[TEAM1SCORE] > record[year][RECORD_SPECIAL]["maxscores"] )
	{
		record[year][RECORD_SPECIAL]["maxscores"] = game[TEAM1SCORE];
		record[year][RECORD_SPECIAL]["maxscoresteam"] = game[TEAM1];
		
		msg += ({ HIY"纪录"NOR YEL"更新 "NOR"“"+team1name+"”突破本季单场最多得分纪录，纪录来到 "HIY+game[TEAM1SCORE]+NOR YEL" 分"NOR" ！！" });
	}
	else if( game[TEAM2SCORE] > game[TEAM1SCORE] && game[TEAM2SCORE] > record[year][RECORD_SPECIAL]["maxscores"] )
	{
		record[year][RECORD_SPECIAL]["maxscores"] = game[TEAM2SCORE];
		record[year][RECORD_SPECIAL]["maxscoresteam"] = game[TEAM2];
		
		msg += ({ HIY"纪录"NOR YEL"更新 "NOR"“"+team2name+"”突破本季单场最多得分纪录，纪录来到 "HIY+game[TEAM2SCORE]+NOR YEL" 分"NOR" ！！" });
	}
	
	// 单场最多局数纪录
	if( game[INNING] > record[year][RECORD_SPECIAL]["maxinnings"] )
	{
		record[year][RECORD_SPECIAL]["maxinnings"] = game[INNING];
		record[year][RECORD_SPECIAL]["maxinningsteam1"] = game[TEAM1];
		record[year][RECORD_SPECIAL]["maxinningsteam2"] = game[TEAM2];
		
		msg += ({ HIY"纪录"NOR YEL"更新 "NOR"“"+team1name+"”与“"+team2name+"”共同创造本季单场延长赛最多局数纪录，纪录来到 "HIY+(game[INNING]/2 + game[INNING]%2)+NOR YEL" 局"NOR" ！！" });
	}
	
	// 单场分数差最多纪录
	if( abs(game[TEAM1SCORE] - game[TEAM2SCORE]) > record[year][RECORD_SPECIAL]["maxscorediff"] )
	{
		record[year][RECORD_SPECIAL]["maxscorediff"] = abs(game[TEAM1SCORE] - game[TEAM2SCORE]);
		record[year][RECORD_SPECIAL]["maxscorediffwin"] = game[TEAM1SCORE] > game[TEAM2SCORE] ? game[TEAM1] : game[TEAM2];
		record[year][RECORD_SPECIAL]["maxscoredifflose"] = game[TEAM1SCORE] < game[TEAM2SCORE] ? game[TEAM1] : game[TEAM2];
		
		msg += ({ HIY"纪录"NOR YEL"更新 "NOR"“"+team1name+"”与“"+team2name+"”共同创造本季单场分数差距最大纪录，纪录来到 "HIY+abs(game[TEAM1SCORE] - game[TEAM2SCORE])+NOR YEL" 分"NOR" ！！" });
	}
	
	setup[game[TEAM1]]["status"] = STATUS_IDLE;
	setup[game[TEAM2]]["status"] = STATUS_IDLE;

	if( !post_season_level )
		for(int i=0;i<sizeof(msg);++i)
			call_out((: CHANNEL_D->channel_broadcast("sport", $(msg)[$(i)]) :), 0);
			
	if( undefinedp(stopid) )
	{
		int income;
		int total_income = query_income(game[TEAM1]) + query_income(game[TEAM2]);
		
		if( file_exists(setup[game[TEAM2]]["master"]) )
		{
			object master = load_object(setup[game[TEAM2]]["master"]);
			
			income = total_income * 10 / 100;
			income += total_income * 80 / 100 * game[TEAM2SCORE] / (game[TEAM1SCORE]+game[TEAM2SCORE]);
			
			if( post_season_level && post_season_start )
				income *= 20;
				
			if( query("owner", master) == game[TEAM2] && objectp(find_player(game[TEAM2])) )
			{
				addn("money", income, master);
				income_msg += "“"+setup[game[TEAM2]]["name"]+"”获得票房收入 "HIY+money(MONEY_D->query_default_money_unit(), income)+NOR;
							
				master->save();
			}
		}
		
		if( file_exists(setup[game[TEAM1]]["master"]) )
		{
			object master = load_object(setup[game[TEAM1]]["master"]);
			
			income = total_income * 10/ 100;
			income += total_income * 80 / 100 * game[TEAM1SCORE] / (game[TEAM1SCORE]+game[TEAM2SCORE]);
			
			if( post_season_level && post_season_start )
				income *= 20;
	
			if( query("owner", master) == game[TEAM1] && objectp(find_player(game[TEAM1])) )
			{
				addn("money", income, master);
				income_msg += "“"+setup[game[TEAM1]]["name"]+"”获得票房收入 "HIY+money(MONEY_D->query_default_money_unit(), income)+" "NOR;
				
				master->save();
			}
		}
		
		if( income_msg != HIG"收入"NOR GRN"分配"NOR )
			msg += ({ income_msg });
	}

	if( post_season_start )
	{		
		switch(post_season_level)
		{
			case 1..4: 
			{
				if( game[TEAM1SCORE] > game[TEAM2SCORE] )
				{
					post_season_team_4 |= ({ game[TEAM1] });
					msg += ({ HIR"季后"NOR RED"赛"NOR" "+setup[game[TEAM1]]["username"]+"领军的“"+setup[game[TEAM1]]["name"]+"”获得四强晋级！！" });
					post_season_eliminate_teams |= ({ game[TEAM2] });
				}
				else
				{
					post_season_team_4 |= ({ game[TEAM2] });
					msg += ({ HIR"季后"NOR RED"赛"NOR" "+setup[game[TEAM2]]["username"]+"领军的“"+setup[game[TEAM2]]["name"]+"”获得四强晋级！！" });
					post_season_eliminate_teams |= ({ game[TEAM1] });
				}
				save();
				break;
			}
			case 5..6:
			{
				if( game[TEAM1SCORE] > game[TEAM2SCORE] )
				{
					post_season_team_2 |= ({ game[TEAM1] });
					msg += ({ HIR"季后"NOR RED"赛"NOR" "+setup[game[TEAM1]]["username"]+"领军的“"+setup[game[TEAM1]]["name"]+"”获得晋级总冠军赛！！" });
					post_season_eliminate_teams |= ({ game[TEAM2] });
				}
				else
				{
					post_season_team_2 |= ({ game[TEAM2] });
					msg += ({ HIR"季后"NOR RED"赛"NOR" "+setup[game[TEAM2]]["username"]+"领军的“"+setup[game[TEAM2]]["name"]+"”获得晋级总冠军赛！！" });
					post_season_eliminate_teams |= ({ game[TEAM1] });
				}
				save();
				break;
			}
			case 7:
			{
				object user;
				
				if( game[TEAM1SCORE] > game[TEAM2SCORE] )
				{
					msg += ({ HIR"季后"NOR RED"赛"NOR" 恭喜"+setup[game[TEAM1]]["username"]+"领军的“"+setup[game[TEAM1]]["name"]+"”获得"NOR CYN"第 "HIC+year+NOR CYN" 球季"HIY"棒球"NOR YEL"世界冠军"NOR"！！" });
					record[year][RECORD_SPECIAL]["champion"] = game[TEAM1];
					record[year][RECORD_SPECIAL]["2rd"] = game[TEAM2];
					post_season_eliminate_teams |= ({ game[TEAM2] });
					user = load_user(game[TEAM1]);
				}
				else
				{
					msg += ({ HIR"季后"NOR RED"赛"NOR" 恭喜"+setup[game[TEAM2]]["username"]+"领军的“"+setup[game[TEAM2]]["name"]+"”获得"NOR CYN"第 "HIC+year+NOR CYN" 球季"HIY"棒球"NOR YEL"世界冠军"NOR"！！" });
					record[year][RECORD_SPECIAL]["champion"] = game[TEAM2];
					record[year][RECORD_SPECIAL]["2rd"] = game[TEAM1];
					post_season_eliminate_teams |= ({ game[TEAM1] });
					
					user = load_user(game[TEAM2]);
				}
				
				if( objectp(user) )
				{
					object ring = new("/obj/baseball/champion_ring_"+year);
					
					user->add_title(sprintf(HIC+"%-4d"+HIY"总"NOR YEL"冠"NOR YEL"军"NOR, year));
					user->save();				
					
					tell(user, pnoun(2, user)+"获得一只“"+ring->query_idname()+"”。\n");
					CHANNEL_D->channel_broadcast("sport", user->query_idname()+"获得一只“"+ring->query_idname()+"”。");
					
					ring->set_keep();
					ring->move(user);
					
					if( !userp(user) )
						destruct(user);
				}
					
				save();
					
				break;
			}
		}
	}
	
	if( !random(10) )
	{
		int status;
		object *equipments;
		
		foreach(mapping roster_data in setup[game[TEAM1]]["roster"] + setup[game[TEAM2]]["roster"])
		{
			if( !objectp(roster_data["object"]) ) continue;
				
			equipments = roster_data["object"]->query_equipping_object(EQ_MITT[PART_ID]) || allocate(0);
			equipments |= roster_data["object"]->query_equipping_object(EQ_BAT[PART_ID]) || allocate(0);
			
			if( !sizeof(equipments) ) continue;
				
			equipments = sort_array(equipments, (: random(2) ? 1 : -1 :));
				
			if( !random(25) )
			{
				msg += ({ roster_data["object"]->query_idname()+"所使用的"+equipments[0]->query_idname()+"在这场比赛中坏掉了！！\n" });
				
				roster_data["object"]->unequip(equipments[0], ref status);
				
				destruct(equipments[0], 1);
			}
		}
	}
			
	games[gameindex] = 0;
	//games -= ({ 0 });

	return msg;
}

// 计算分数
private string *new_score(int gameindex, string attacker, string defender, int score, int scoretype)
{
	string *msg = allocate(0);
	mapping game = games[gameindex];
	int attacknumber;
	
	// 计算得分
	if( attacker == game[TEAM1] )
	{
		game[TEAM1SCORE] += score;
		attacknumber = game[TEAM1NUMBER];
	}
	else
	{
		game[TEAM2SCORE] += score;
		attacknumber = game[TEAM2NUMBER];
	}
		
	add_player_record(defender, 0, "run", score);
	add_player_record(attacker, attacknumber, "rbi", score);
	
	msg += ({ "“"+setup[game[TEAM2]]["name"]+" "+game[TEAM2SCORE]+" : "+game[TEAM1SCORE]+" "+setup[game[TEAM1]]["name"] +"”" });
	
	// 下半局，再见得分
	if( game[INNING] >= 18 && (game[INNING] % 2) == 0 && game[TEAM1SCORE] > game[TEAM2SCORE] )
	{
		switch(scoretype)
		{
			case SCORETYPE_HOMERUN:		msg += ({ "这是一只再见全垒打！！" }); 	break;
			case SCORETYPE_FOURBALL:	msg += ({ "这是一个再见四坏！！" }); 	break;
			case SCORETYPE_SACRIFICE:	msg += ({ "这是一只再见牺牲打！！" });	break;
			case SCORETYPE_HIT:		msg += ({ "这是一只再见安打！！" }); 	break;
			default: error("error scoretype");
		}

		msg += game_finish(gameindex);
	}
	
	return msg;
}

// 计算新的出局数
private string *new_out(int gameindex, string attacker, string defender, int outcount, int outtype)
{
	string *msg = allocate(0);
	mapping game = games[gameindex];
	int attackernumber = attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER];
		
	game[STRIKE] = 0;
	game[BALL] = 0;

	// 打席次数纪录
	add_player_record(attacker, attackernumber, "ab", 1);
	
	// 投手对决人次纪录
	add_player_record(defender, 0, "bf", 1);
	
	// 投手对决出局数
	add_player_record(defender, 0, "out", outcount);
	
	if( outtype == BASETYPE_STRIKEOUT )
		add_player_record(defender, 0, "strikeout", 1);	
			
	if( (game[OUT]+=outcount) >= 3 )
	{			
		game[OUT] = 0;

		if( game[INNING] >= 17 && (((game[INNING] % 2) && game[TEAM1SCORE] > game[TEAM2SCORE]) || (!(game[INNING] % 2) && game[TEAM1SCORE] != game[TEAM2SCORE])))
			return game_finish(gameindex);
		
		game[INNING]++;
		
		msg += ({ "“"+setup[game[TEAM2]]["name"]+" "+game[TEAM2SCORE]+" : "+game[TEAM1SCORE]+" "+setup[game[TEAM1]]["name"] +"”攻守交替，比赛进入到"+(game[INNING]>=19?"延长赛":"")+"第 "+( game[INNING]%2 ? ((game[INNING]+1)/2)+" 局上半" : ((game[INNING]+1)/2)+" 局下半" ) });
			
		game[RUNNER1ST] = 0;
		game[RUNNER2ND] = 0;
		game[RUNNER3RD] = 0;
	}
	else
	{	
		// 刺杀, 有机会进垒
		if( outtype == BASETYPE_BUNT || outtype == BASETYPE_TOUCHKILL )
		{
			// 满垒则封杀三垒跑者
			if( game[RUNNER3RD] > 0 && game[RUNNER2ND] > 0 && game[RUNNER1ST] > 0 )
			{
				game[RUNNER3RD] = game[RUNNER2ND];
				game[RUNNER2ND] = game[RUNNER1ST];
				game[RUNNER1ST] = attackernumber;
			}
			else
			{
				// 三垒无人 二垒有人, 进垒
				if( game[RUNNER3RD] == 0 && game[RUNNER2ND] > 0 )
				{
					game[RUNNER3RD] = game[RUNNER2ND];
					game[RUNNER2ND] = 0;
				}
				
				// 二垒无人 一垒有人, 进垒
				if( game[RUNNER2ND] == 0 && game[RUNNER1ST] > 0 )
				{
					game[RUNNER2ND] = game[RUNNER1ST];
					game[RUNNER1ST] = 0;
				}
			}	
		}
		// 接杀, 有机会进垒
		else if( outtype == BASETYPE_CATCHKILL )
		{
			if( game[RUNNER3RD] > 0 )
			{
				msg += ({ "“"+setup[attacker]["name"]+"”三垒跑者冲回本垒得分！" });
				msg += new_score(gameindex, attacker, defender, 1, SCORETYPE_SACRIFICE);
				
				if( !games[gameindex] )
					return msg;

				game[RUNNER3RD] = 0;
			}
		}
		// 双杀, 有机会进垒
		else if( outtype == BASETYPE_DOUBLEPLAY )
		{
			// 三垒无人 二垒有人, 进垒
			if( game[RUNNER2ND] > 0 )
			{
				game[RUNNER3RD] = game[RUNNER2ND];
				game[RUNNER2ND] = 0;
			}
			
			game[RUNNER1ST] = 0;
		}
		// 三杀 , 理论上不会执行到此(直接换局)
		//else if( outtype == BASETYPE_TRIPLEPLAY ) { }
		
		if( game[RUNNER3RD] > 0 || game[RUNNER2ND] > 0 || game[RUNNER1ST] > 0 )
			msg += ({ "“"+setup[attacker]["name"]+"”目前垒上的跑者情形为 [ "+(game[RUNNER3RD] > 0?HIW"○"NOR:WHT"╳"NOR)+" "+(game[RUNNER2ND] > 0?HIW"○"NOR:WHT"╳"NOR)+" "+(game[RUNNER1ST] > 0?HIW"○"NOR:WHT"╳"NOR)+" ] "HIW+game[OUT]+NOR WHT"out"NOR });
	}

	// 轮下一棒
	if( attacker == game[TEAM1] )
		game[TEAM1NUMBER] = 1 + (game[TEAM1NUMBER] % 9);
	else
		game[TEAM2NUMBER] = 1 + (game[TEAM2NUMBER] % 9);
		
	setup[attacker]["hint"] = 0;
	setup[defender]["hint"] = 0;
	
	games[gameindex] = game;
	
	return msg;
}

// 计算新的进垒
private string *new_base(int gameindex, string attacker, string defender, int basecount, int basetype)
{
	string *msg = allocate(0);
	mapping game = games[gameindex];

	int score = 0;
	int attacknumber = attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER];
	
	if( basecount <= 0 ) error("basecount_error");

	game[STRIKE] = 0;
	game[BALL] = 0;

	// 投手对决人次
	add_player_record(defender, 0, "bf", 1);

	if( basetype == BASETYPE_HIT ) // 安打进垒
	{
		int scoretype;
		
		// 打者打击次数纪录
		add_player_record(attacker, attacknumber, "ab", 1);

		if( attacker == game[TEAM1] )
			game[TEAM1HIT]++;
		else
			game[TEAM2HIT]++;
			
		switch(basecount)
		{
			case 1:
			{
				add_player_record(attacker, attacknumber, "hit1", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”三垒跑者奔回本垒得分！" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 )
				{
					if( random(setup[attacker]["roster"][game[RUNNER2ND]]["object"]->query_int()) > random(400) )
					{
						score++; 
						msg += ({ "“"+setup[attacker]["name"]+"”二垒跑者奔回本垒得分！" });	
					
						game[RUNNER2ND] = 0; 
					}
					else
					{
						game[RUNNER3RD] = game[RUNNER2ND];
						game[RUNNER2ND] = 0; 
					}
				}
						
				// 一垒有人，进垒
				if( game[RUNNER1ST] > 0 )
				{
					if( game[RUNNER3RD] > 0 )
						game[RUNNER2ND] = game[RUNNER1ST];
					else
						game[RUNNER3RD] = game[RUNNER1ST];
						
					game[RUNNER1ST] = 0;
				}
				
				// 打者上到一垒
				game[RUNNER1ST] = (attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER]);
				
				scoretype = SCORETYPE_HIT;
				
				break;
			}
			case 2:
			{
				add_player_record(attacker, attacknumber, "hit2", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”三垒跑者奔回本垒得分！" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”二垒跑者奔回本垒得分！" }); game[RUNNER2ND] = 0; }
				if( game[RUNNER1ST] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”一垒跑者奔回本垒得分！" }); game[RUNNER1ST] = 0; }
				
				// 打者上到二垒
				game[RUNNER2ND] = (attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER]);
	
				scoretype = SCORETYPE_HIT;
				
				break;	
			}
			case 3:
			{
				add_player_record(attacker, attacknumber, "hit3", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”三垒跑者奔回本垒得分！" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”二垒跑者奔回本垒得分！" }); game[RUNNER2ND] = 0; }
				if( game[RUNNER1ST] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”一垒跑者奔回本垒得分！" }); game[RUNNER1ST] = 0; }
							
				// 打者上到三垒
				game[RUNNER3RD] = (attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER]);
				
				scoretype = SCORETYPE_HIT;
				
				break;	
			}
			case 4:
			{
				add_player_record(attacker, attacknumber, "hit4", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”三垒跑者奔回本垒得分！" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”二垒跑者奔回本垒得分！" }); game[RUNNER2ND] = 0; }
				if( game[RUNNER1ST] > 0 ) {	score++; msg += ({ "“"+setup[attacker]["name"]+"”一垒跑者奔回本垒得分！" }); game[RUNNER1ST] = 0; }
					
				msg += ({ "“"+setup[attacker]["name"]+"”打者奔回本垒得分！" });
				score++;
	
				scoretype = SCORETYPE_HOMERUN;
				
				break;
			}
		}
		
		msg += new_score(gameindex, attacker, defender, score, scoretype);
			
		if( !games[gameindex] )
			return msg;
	}
	else if( basetype == BASETYPE_BALL ) // 保送进垒
	{
		add_player_record(defender, 0, "fourball", 1);
		add_player_record(attacker, attacknumber, "walk", 1);

		// 若一垒有人
		if( game[RUNNER1ST] > 0 )
		{
			// 若二垒也有人
			if( game[RUNNER2ND] > 0 )
			{
				// 若三垒也有人
				if( game[RUNNER3RD] > 0 )
				{
					msg += ({ "“"+setup[attacker]["name"]+"”三垒跑者毫不费力地走回本垒得分！" });
					msg += new_score(gameindex, attacker, defender, 1, SCORETYPE_FOURBALL);
					
					if( !games[gameindex] )
						return msg;
				}

				game[RUNNER3RD] = game[RUNNER2ND];	
			}

			game[RUNNER2ND] = game[RUNNER1ST];
		}

		game[RUNNER1ST] = attacknumber;	
	}

	// 轮下一棒
	if( attacker == game[TEAM1] )
		game[TEAM1NUMBER] = 1 + (game[TEAM1NUMBER] % 9);
	else
		game[TEAM2NUMBER] = 1 + (game[TEAM2NUMBER] % 9);

	setup[attacker]["hint"] = 0;
	setup[defender]["hint"] = 0;
	
	if( game[RUNNER3RD] > 0 || game[RUNNER2ND] > 0 || game[RUNNER1ST] > 0 )
		msg += ({ "“"+setup[attacker]["name"]+"”目前垒上的跑者情形为 [ "+(game[RUNNER3RD] > 0?HIW"○"NOR:WHT"╳"NOR)+" "+(game[RUNNER2ND] > 0?HIW"○"NOR:WHT"╳"NOR)+" "+(game[RUNNER1ST] > 0?HIW"○"NOR:WHT"╳"NOR)+" ] "HIW+game[OUT]+NOR WHT"out"NOR });
		
	games[gameindex] = game;

	return msg;
}

private void check_cache(object player)
{
	if( query_temp("baseballcache/handside/time", player) < time() - 300 )
	{
		int type;
		int level;
		
		if( (level = player->query_skill_level("twohands")) > 0 )
			type = HANDSIDE_TWOHANDS;
		else if( (level = player->query_skill_level("lefthand")) > 0 )
			type = HANDSIDE_LEFTHAND;
		else if( (level = player->query_skill_level("righthand")) > 0 )
			type = HANDSIDE_RIGHTHAND;
		else
			type = HANDSIDE_NONE;
			
		set_temp("baseballcache/handside", ([ "time":time(), "type":type, "level":level ]), player);
	}
}

int get_handside_type(object player)
{
	check_cache(player);
	return query_temp("baseballcache/handside/type", player);
}

int get_handside_level(object player)
{
	check_cache(player);
	return query_temp("baseballcache/handside/level", player);
}

// 打者与投手左右方的差异 (-60~70) 之间
int get_handside_diff(object pitcher, object batter)
{
	int base_level_diff = (get_handside_level(batter) - get_handside_level(pitcher))/20;
	int batter_handside_type = get_handside_type(batter);
	int pitcher_handside_type = get_handside_type(pitcher);
	
	if( pitcher_handside_type == HANDSIDE_NONE )
		return 20 + base_level_diff;
	else if( batter_handside_type == HANDSIDE_TWOHANDS )
		return 8 + base_level_diff;
	else if( batter_handside_type != pitcher_handside_type )
		return 20 + base_level_diff;
	else
		return -10 + base_level_diff;
}

// 取得打击率
varargs float get_hit_rate(string teamid, int num, int year)
{
	int hit, ab;
	
	if( undefinedp(year) )
		year = season_year;

	if( undefinedp(setup[teamid]) || !mapp(setup[teamid]["roster"][num]) )
		return 0.;

	hit = get_record(RECORD_PLAYER, setup[teamid]["roster"][num]["file"], "hit", year);
	ab = get_record(RECORD_PLAYER, setup[teamid]["roster"][num]["file"], "ab", year);

	if( !hit || !ab ) return 0.;
		
	return 10. * hit / ab;
}

// 进行球赛
void play_game()
{
	string *msg;
	mapping attacksetup, defendsetup;
	string attackteamname, defendteamname;
	int attacknumber, defendnumber;
	string attacker, defender;
	string team1, team2;
	mapping game;
	
	games -= ({ 0 });

	for(int gameindex=0;gameindex<sizeof(games);++gameindex)
	{
		msg = allocate(0);

		game = games[gameindex];
			
		if( ++game[TICK] < PREPARETIME ) continue;

		if( post_season_start && post_season_level )
		{
			if( (game[TICK]+gameindex) % POSTSEASON_TICKTIME ) continue;
		}
		else if( (game[TICK]+gameindex) % TICKTIME ) continue;

		team1 = game[TEAM1];
		team2 = game[TEAM2];
	
		if( !setup[team1] || !setup[team2] ) continue;

		if( !valid_setup(team1) )
		{
			broadcast(HIG"【棒赛】"NOR"“"+setup[team1]["name"]+"”的球队资料不完整，中止比赛。\n", game);
			cancel_game(team1, 1);
			continue;
		}
			
		if( !valid_setup(team2) )
		{
			broadcast(HIG"【棒赛】"NOR"“"+setup[team2]["name"]+"”的球队资料不完整，中止比赛。\n", game);
			cancel_game(team2, 1);
			continue;
		}
		
		if( game[TICK] <= PREPARETIME + TICKTIME && game[TICK] >= PREPARETIME )
		{
			setup[team1]["status"] = STATUS_PLAYING;
			setup[team2]["status"] = STATUS_PLAYING;
		}
		
		if( (game[INNING] % 2) > 0 )
		{	
			attacksetup = setup[team2];
			defendsetup = setup[team1];
			
			attacknumber = game[TEAM2NUMBER];
			defendnumber = game[TEAM1NUMBER];
			
			attacker = team2;
			defender = team1;
		}
		else
		{
			attacksetup = setup[team1];
			defendsetup = setup[team2];
			
			attacknumber = game[TEAM1NUMBER];
			defendnumber = game[TEAM2NUMBER];
			
			attacker = team1;
			defender = team2;
		}

		attackteamname = "“"+attacksetup["name"]+"”";
		defendteamname = "“"+defendsetup["name"]+"”";
		
		if( game[INNING] == 0 )
		{
			string defendhandside, attackhandside;
			
			switch(get_handside_type(defendsetup["roster"][0]["object"]))
			{
				case HANDSIDE_NONE: defendhandside = ""; break;
				case HANDSIDE_LEFTHAND: defendhandside = HIC"左"NOR CYN"投"NOR; break;
				case HANDSIDE_RIGHTHAND: defendhandside = HIG"右"NOR GRN"投"NOR; break;
				default: defendhandside = HIR"错误"NOR; break;
			}
			switch(get_handside_type(attacksetup["roster"][0]["object"]))
			{
				case HANDSIDE_NONE: attackhandside = ""; break;
				case HANDSIDE_LEFTHAND: attackhandside = HIC"左"NOR CYN"投"NOR; break;
				case HANDSIDE_RIGHTHAND: attackhandside = HIG"右"NOR GRN"投"NOR; break;
				default: attackhandside = HIR"错误"NOR; break;
			}
			
			msg += ({ attacksetup["username"]+"的"+attackteamname+"与"+defendsetup["username"]+"的"+defendteamname+"比赛正式开始。" });
			msg += ({ "双方派出的先发投手分别为"+attackteamname+attackhandside+attacksetup["roster"][0]["object"]->query_idname()+"与"+defendteamname+defendhandside+defendsetup["roster"][0]["object"]->query_idname()+"。" });
			
			game[INNING]++;
		}
		else
		{
			object pitcher = defendsetup["roster"][0]["object"];
			object batter = attacksetup["roster"][attacknumber]["object"];
			
			string defend_msg="", attack_msg="", info_msg="", *special_msg = allocate(0);
			string pitcherballtype;
			
			int pitcherbase = get_handside_level(pitcher) + pitcher->query_str() * 2;		// 投手基本能力(预估范围 10~1500 之间)
			int batterbase = get_handside_level(batter) + batter->query_str() * 2;			// 打者基本能力(预估范围 10~1500 之间)
			
			string *availableballtypes;
			int pitchballpower;
			int pitchballspeed;
			int pitchswingeffect = 0;
			int pitchhiteffect = 0;
			int pitchgoodhiteffect = 0;
			
			availableballtypes = filter_array(pitch_ball_types, (: $(pitcher)->query_skill_level($1) > 0 :));
			
			
				
			if( sizeof(availableballtypes) )
			{
				string balltype = availableballtypes[random(sizeof(availableballtypes))];
				
				pitchballpower = pitcher->query_skill_level(balltype);
				pitcherballtype = pitch_ball_types_name[balltype];
				
				switch(balltype)
				{
					case "fourseam":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 120, 157) + random(6); 
						pitchswingeffect = -20;
						pitchhiteffect = 10;
						pitchgoodhiteffect = 10;
						break;
					case "twoseam":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 115, 151) + random(6);
						pitchswingeffect = -10;
						pitchhiteffect = 0;
						pitchgoodhiteffect = 10;
						break;
					case "curveball":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 90, 127) + random(6);
						pitchswingeffect = 10;
						pitchhiteffect = -15;
						pitchgoodhiteffect = 5;
						break;
					case "slider":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 110, 148) + random(6);
						pitchswingeffect = -5;
						pitchhiteffect = 10;
						pitchgoodhiteffect = -5;
						break;
					case "forkball":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 100, 137) + random(6);
						pitchswingeffect = 0;
						pitchhiteffect = -10;
						pitchgoodhiteffect = 10;
						break;
					case "sinker":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 110, 148) + random(6);
						pitchswingeffect = 5;
						pitchhiteffect = 20;
						pitchgoodhiteffect = -25;
						break;
				}
				
				// 球种愈多，威力愈强
				if( sizeof(availableballtypes) == 1 )
					pitchballpower -= 200;
				else
					pitchballpower += sizeof(availableballtypes) * 30;
			}
			else
			{
				pitchballpower = 0;
				pitcherballtype = "软弱直球";
				
				pitchballspeed = 100+random(15);
			}
			
			pitchballpower += defendsetup["roster"][0][BUFF_PITCHER_POWER];
			
			if( pitchballpower <= 0 )
				pitchballpower = 0;
				
			pitchballpower = calculate(pitchballpower, 0.8, 999, 0, 100);
			
			if( objectp(find_player(defender)) )
			switch(get_handside_type(pitcher))
			{
				case HANDSIDE_LEFTHAND: pitcher->add_skill_exp("lefthand", random(100)); break;
				case HANDSIDE_RIGHTHAND: pitcher->add_skill_exp("righthand", random(100)); break;
			}
			
			if( objectp(find_player(attacker)) )
			switch(get_handside_type(batter))
			{
				case HANDSIDE_LEFTHAND: batter->add_skill_exp("lefthand", random(900)); break;
				case HANDSIDE_RIGHTHAND: batter->add_skill_exp("righthand", random(900)); break;
				case HANDSIDE_TWOHANDS: batter->add_skill_exp("twohands", random(900)); break;
			}
			
			if( defendsetup["hint"] == HINTTYPE_PITCHER )
			{
				pitchballpower += 70;
				pitchballspeed += range_random(2, 5);
				
				defend_msg = defendteamname+pitcher->query_idname()+HIY"全神"NOR YEL"贯注"NOR+(pitchballspeed>=155?"飙":"投")+"出"+(pitchballspeed>=160?"惊人的":"")+" "+pitchballspeed+"km "+ pitcherballtype;
			}
			else
			{
				defend_msg = defendteamname+pitcher->query_idname()+(pitchballspeed>=155?"飙":"投")+"出"+(pitchballspeed>=160?"惊人的":"")+" "+pitchballspeed+"km "+ pitcherballtype;
			}

			
			attack_msg = attackteamname+attacknumber+" 棒"+batter->query_idname();
			
			// 敬远四坏
			if( defendsetup["hint"] == HINTTYPE_WALK )
			{
				if( ++game[BALL] == 4 )
				{
					defend_msg = defendteamname+pitcher->query_idname()+"往一旁轻轻抛球给捕手，"HIG"坏球"NOR"！引来观众一阵嘘声";
					attack_msg += "获得敬远四坏保送上垒。";
	
					// 进一垒
					special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_BALL);
				}
				else
				{
					defend_msg = defendteamname+pitcher->query_idname()+"往一旁轻轻抛球给捕手，"HIG"坏球"NOR"！引来观众一阵嘘声";
					attack_msg += "耐心地等待四坏保送";
	
					info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
				}				
			}
			// 进行触击短打
			else if( attacksetup["hint"] == HINTTYPE_BUNT )
			{
				// 内野安打!
				if( random(batter->query_int()) > random(600) )
				{
					attack_msg += "摆出奇袭短棒将球击出！这是一支内野安打！！";
					
					special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_HIT);
				}
				else if( !random(5) )
				{
					attack_msg += "摆出短棒将球击出！但却碰出一颗软弱飞球被接杀！";
					
					info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
					
					special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_CATCHKILL);
				}
				else
				{
					// 满垒
					if( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 )
					{
						if( game[OUT] < 2 )								
							attack_msg += "摆出短棒将球击出！三垒跑者被封杀在本垒！";
						else
							attack_msg += "摆出短棒将球击出！但被内野手拦住并刺杀在一垒！";
					}
					else
						attack_msg += "摆出短棒将球击出！但被内野手拦住并刺杀在一垒！";
													
					info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
					
					special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_BUNT);
				}
			}
			// 投出好球
			else if( calculate(pitcherbase, 0.8, 1500, 400, 700) > random(1000) )
			{
				// 打者精准选球且出棒的机率 550 + (0~100) + (-60~70) - (0~100) + (-20~5)
				int swingchance = 550 + calculate(batter->query_skill_level("hitaccuracy"), 0.8, 999, 0, 100) + get_handside_diff(pitcher, batter) - pitchballpower + pitchswingeffect;
								
				if( attacksetup["hint"] == HINTTYPE_BATTER )
				{
					attack_msg += HIY"全神"NOR YEL"贯注"NOR;
					swingchance += 40;
				}

				defend_msg += HIR"好球"NOR"！";

				if( game[TEAM1SCORE] > game[TEAM2SCORE] && game[TEAM2] == attacker )
					swingchance += 3 * (game[TEAM1SCORE] - game[TEAM2SCORE]);

				if( game[TEAM2SCORE] > game[TEAM1SCORE] && game[TEAM1] == attacker )
					swingchance += 3 * (game[TEAM2SCORE] - game[TEAM1SCORE]);
						
				// 好球且出棒
				if( swingchance > random(1000) )
				{
					// 击出球的机率 700 + (0~100) - (0~100)
					int hitchance = 700 + calculate(batter->query_skill_level("hitrange"), 0.7, 999, 0, 100) - pitchballpower;
						
					if( attacksetup["hint"] == HINTTYPE_BATTER )
						hitchance += 40;
					
					if( game[INNING] > 18 )
						hitchance += 3 * (game[INNING]/2-9);
								
					hitchance += attacksetup["roster"][attacknumber][BUFF_BATTER_POWER];
		
					switch(attacknumber)
					{
						case 1: hitchance += 50; break;
						case 2: hitchance += 20; break;
						case 3: hitchance += 40; break;
						case 4: hitchance += 80; break;
						case 5: hitchance += 40; break;
						case 6: hitchance += 10;break;
						case 7: hitchance -= 10; break;
						case 8: hitchance -= 10; break;
						case 9: hitchance -= 10; break;
					}
							
					// 打击出去
					if( hitchance + pitchhiteffect > random(1000) )
					{
						//tell(find_player("clode"), attacker+(hitchance + pitchgoodhiteffect)+"/"+defender+(defendsetup["outfield"]+defendsetup["infield"])+"\n");
						
						// 安打
						if( hitchance + pitchgoodhiteffect + 100 > random(800 + defendsetup["outfield"] + defendsetup["infield"] ) )
						{												
							// 击出球的速度(500~3300)
							int hitpower = batter->query_skill_level("hitpower");
							int ballspeed = 500 + hitpower + batterbase;
							
							ballspeed = calculate(ballspeed, 0.7, 3000, 0, 1000);

							// 全垒打
							if( ballspeed > random(8000) )
							{
								int distance;
								
								// 进垒
								special_msg += new_base(gameindex, attacker, defender, 4, BASETYPE_HIT);
								
								if( hitpower > random(5000) )
								{
									if( hitpower > random(5000) )
									{
										if( hitpower > random(5000) )
											distance = range_random(180, 190);
										else
											distance = range_random(170, 180);
									}
									else
										distance = range_random(160, 170);
										
									attack_msg += "轰出了一只超大号"+( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 ? "满贯" : "" )+"全垒打("+distance+"m)！！";
								}
								else
								{
									distance = range_random(140, 160);
									attack_msg += "击出"+( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 ? "满贯" : "" )+"全垒打("+distance+"m)！！";
								}
								
								if( distance > record[season_year][RECORD_SPECIAL]["maxhomerundistance"] )
								{
									record[season_year][RECORD_SPECIAL]["maxhomerundistance"] = distance;
									record[season_year][RECORD_SPECIAL]["maxhomerundistanceplayer"] = attacksetup["roster"][attacknumber]["file"];
									
									CHANNEL_D->channel_broadcast("sport", HIY"纪录"NOR YEL"更新 "NOR+attackteamname+"的"+batter->query_idname()+"击出本季最大号全垒打，距离来到 "HIY+distance+NOR YEL"m"NOR" ！！" );
								}
								
								attack_msg += "("HIY+get_record(RECORD_PLAYER, attacksetup["roster"][attacknumber]["file"], "hit4", season_year)+NOR")";
							}
							// 三垒打
							else if( ballspeed > random(10000) )
							{
								// 进垒
								special_msg += new_base(gameindex, attacker, defender, 3, BASETYPE_HIT);
								
								if( random(defendsetup["outfield"]) < 100 )
									attack_msg += "击出高远飞球，外野手奋力扑球仍然慢了一步，形成三垒安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
								else
									attack_msg += "击出三垒安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
							}
							// 二垒打
							else if( ballspeed > random(3000) )
							{
								// 进垒
								special_msg += new_base(gameindex, attacker, defender, 2, BASETYPE_HIT);
								
								if( random(defendsetup["outfield"]) < 100 )
									attack_msg += "击出不营养飞球但外野手跚跚来迟，形成二垒安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
								else
									attack_msg += "击出二垒安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
							}
							// 一垒打
							else
							{
								// 进垒
								special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_HIT);
								
								if( random(defendsetup["infield"]) < 100 )
									attack_msg += "击出的滚地球硬是从内野防线中穿越出去，形成一垒安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
								else
									attack_msg += "击出一垒安打！("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
							}								
						}
						// 界外球
						else if( hitchance > random(5000) )
						{
							if( game[STRIKE] < 2 )
							{
								attack_msg += "击成界外球";

								game[STRIKE]++;

								info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
							}
							else
							{
								attack_msg += "击成界外球";

								info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
							}
						}
						// 打击出去遭接杀或刺杀
						else
						{						
							// 飞球
							if( random(2) )
							{
								attack_msg += "将球远远打击出去！但被接杀";
								
								info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
									
								special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_CATCHKILL);
							}
							// 滚地
							else
							{
								if( !random(15) && game[RUNNER2ND] > 0 && game[RUNNER1ST] > 0 && game[OUT] == 0 )
								{
									attack_msg += "将球打击出去！这是一支罕见的三杀打！！";
									
									info_msg = " "HIW+(game[OUT]+3)+NOR WHT"out"NOR;
									
									special_msg += new_out(gameindex, attacker, defender, 3, BASETYPE_TRIPLEPLAY);
								}
								else if( random(2) && game[RUNNER3RD] == 0 && game[RUNNER1ST] > 0 && game[OUT] < 2 )
								{
									attack_msg += "将球打击出去！这是一支双杀打！！";
									
									info_msg = " "HIW+(game[OUT]+2)+NOR WHT"out"NOR;
									
									special_msg += new_out(gameindex, attacker, defender, 2, BASETYPE_DOUBLEPLAY);
								}
								else
								{								
									// 满垒
									if( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 )
									{
										if( game[OUT] < 2 )								
											attack_msg += "将球打击出去！三垒跑者被封杀在本垒！";
										else
											attack_msg += "将球打击出去！但被内野手拦住并刺杀在一垒！";
									}
									else
										attack_msg += "将球打击出去！但被内野手拦住并刺杀在一垒！";
									
									info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
									
									special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_TOUCHKILL);
								}
							}
						}

					}
					// 挥棒落空
					else
					{
						if( ++game[STRIKE] == 3 )
						{							
							defender == game[TEAM1] ? game[TEAM1K]++ : game[TEAM2K]++;

							attack_msg += "挥棒落空遭到三振出局";

							info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out "HIY + (defender == game[TEAM1] ? game[TEAM1K] : game[TEAM2K]) +NOR YEL"K!"NOR;

							special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_STRIKEOUT);
						}
						else
						{
							attack_msg += "挥棒落空";	

							info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
						}
					}	
				}
				// 好球未出棒
				else
				{
					if( ++game[STRIKE] == 3 )
					{					
						defender == game[TEAM1] ? game[TEAM1K]++ : game[TEAM2K]++;

						attack_msg += "站着发呆遭到三振出局";

						info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out "HIY + (defender == game[TEAM1] ? game[TEAM1K] : game[TEAM2K]) +NOR YEL"K!"NOR;

						special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_STRIKEOUT);
					}
					else
					{
						attack_msg += "站着发呆";

						info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
					}
				}
			}
			// 投出坏球
			else
			{
				// 打者看准坏球且不出棒的机率 750 + (0~100) + (-60~70)
				int swingchance = 750 + calculate(batter->query_skill_level("hitaccuracy"), 0.8, 999, 0, 100) + get_handside_diff(pitcher, batter) + pitchswingeffect;

				if( setup[attacker]["hint"] == HINTTYPE_BATTER )
				{
					attack_msg += HIY"全神"NOR YEL"贯注"NOR;
					swingchance += 50;
				}

				if( game[TEAM1SCORE] > game[TEAM2SCORE] && game[TEAM2] == attacker )
					swingchance += 3 * (game[TEAM1SCORE] - game[TEAM2SCORE]);

				if( game[TEAM2SCORE] > game[TEAM1SCORE] && game[TEAM1] == attacker )
					swingchance += 3 * (game[TEAM2SCORE] - game[TEAM1SCORE]);

				defend_msg += HIG"坏球"NOR"，";

				// 坏球且没出棒
				if( swingchance > random(1000) )
				{
					if( random(200 + pitcherbase) < 5 )
					{
							attack_msg += "被暴投球击中！获得触身保送上垒";

							// 进一垒
							special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_BALL);
					}
					else
					{
						if( ++game[BALL] == 4 )
						{
							attack_msg += "忍住没有挥棒，获得保送上垒";

							// 进一垒
							special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_BALL);
						}
						else
						{
							attack_msg += "忍住没有挥棒";

							info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
						}
					}
				}
				// 坏球但有出棒
				else
				{
					if( 200 + pitchballpower > random(800) )
					{
						if( ++game[STRIKE] == 3 )
						{						
							defender == game[TEAM1] ? game[TEAM1K]++ : game[TEAM2K]++;

							attack_msg += "挥棒落空遭到三振出局";

							info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out "HIY + (defender == game[TEAM1] ? game[TEAM1K] : game[TEAM2K]) +NOR YEL"K!"NOR;

							special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_STRIKEOUT);	
						}
						else
						{
							attack_msg += "大力一挥，挥棒落空";

							info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
						}
					}
					else
					{
						// 飞球
						if( random(2) )
						{						
							attack_msg += "将球远远打击出去！但被接杀";

							info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;

							special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_CATCHKILL);
						}
						// 滚地
						else
						{
							if( !random(15) && game[RUNNER2ND] > 0 && game[RUNNER1ST] > 0 && game[OUT] == 0 )
							{
								attack_msg += "将球打击出去！这是一支罕见的三杀打！！";

								info_msg = " "HIW+(game[OUT]+3)+NOR WHT"out"NOR;

								special_msg += new_out(gameindex, attacker, defender, 3, BASETYPE_TRIPLEPLAY);
							}
							else if( random(2) && game[RUNNER3RD] == 0 && game[RUNNER1ST] > 0 && game[OUT] <= 1 )
							{
								attack_msg += "将球打击出去！这是一支双杀打！！";

								info_msg = " "HIW+(game[OUT]+2)+NOR WHT"out"NOR;

								special_msg += new_out(gameindex, attacker, defender, 2, BASETYPE_DOUBLEPLAY);
							}
							else
							{
								// 满垒
								if( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 )
								{
									if( game[OUT] < 2 )								
										attack_msg += "将球打击出去！三垒跑者被封杀在本垒！";
									else
										attack_msg += "将球打击出去！但被内野手拦住并刺杀在一垒！";
								}
								else
									attack_msg += "将球打击出去！但被内野手拦住并刺杀在一垒！";

								info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;

								special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_TOUCHKILL);
							}
						}
					}
				}
			}

			if( !game ) continue;

			msg += ({ defend_msg+attack_msg+info_msg });
			
			if( sizeof(special_msg) > 0 )
				msg += special_msg;
		}

		if( sizeof(attacksetup["messages"]) )
		{
			msg = attacksetup["messages"] + msg;
			attacksetup["messages"] = 0;
		}

		if( sizeof(defendsetup["messages"]) )
		{
			msg = defendsetup["messages"] + msg;
			defendsetup["messages"] = 0;
		}
				
		if( sizeof(msg) )
		{
			foreach(string m in msg)
			{
				broadcast(m, game);
			}
		}
	}
}

// 新球赛准备开始, 前者为主场, 后者为客场
void new_game(string id1, string id2)
{
	mapping game = allocate_mapping(0);
	object user;
	
	game[TEAM1] = id1;
	game[TEAM2] = id2;
	game[TEAM1NUMBER] = 1;
	game[TEAM2NUMBER] = 1;
	
	if( post_season_start && post_season_level )
	{
		if( objectp(find_player(id1)) )
			tell(find_player(id1), "\a");
		
		if( objectp(find_player(id2)) )
			tell(find_player(id2), "\a");
			
		game[TICK] = PREPARETIME*4/5 - random(POSTSEASON_TICKTIME);
		
	}
	else
		game[TICK] = random(TICKTIME);

	games += ({ game });

	setup[id1]["status"] = STATUS_PREPARING;
	setup[id2]["status"] = STATUS_PREPARING;

	if( post_season_start && post_season_level )
	{
		setup[id1]["hinttimes"] = HINTTIMES * 2;
		setup[id2]["hinttimes"] = HINTTIMES * 2;
	}
	else
	{
		setup[id1]["hinttimes"] = HINTTIMES;
		setup[id2]["hinttimes"] = HINTTIMES;
	}

	setup[id1]["opponents"] -= ({ id2 });
	setup[id2]["opponents"] -= ({ id1 });
	
	if( objectp(user = find_player(id1)) )
		tell(user, pnoun(2, user)+"的棒球队伍即将与"+setup[id2]["username"]+"的“"+setup[id2]["name"]+"”进行比赛。\n");
	
	if( objectp(user = find_player(id2)) )
		tell(user, pnoun(2, user)+"的棒球队伍即将与"+setup[id1]["username"]+"的“"+setup[id1]["name"]+"”进行比赛。\n");
}

void start_game(string id)
{
	foreach(mapping ref game in games)
	{
		if( game[TEAM1] == id || game[TEAM2] == id )
		{
			if( game[TICK] < PREPARETIME )
				game[TICK] = PREPARETIME - 1 - random(TICKTIME);
		}
	}
}

string query_opponent(string id)
{
	foreach(mapping game in games)
	{
		if( !mapp(game) ) continue;

		if( game[TEAM1] == id )
			return game[TEAM2];
		if( game[TEAM2] == id )
			return game[TEAM1];
	}
	
	return 0;
}

varargs mixed query_game(string id)
{
	if( undefinedp(id) ) 
		return games;

	foreach(mapping game in games)
	{
		if( !mapp(game) ) continue;

		if( game[TEAM1] == id || game[TEAM2] == id )
			return game;
	}
	
	return 0;
}

string *query_season()
{
	return season;
}

varargs mapping query_setup(string id)
{
	if( undefinedp(id) )
		return setup;
	else
	{
		// 初始化设定
		if( undefinedp(setup[id]) )
		{
			setup[id] = allocate_mapping(0);
			setup[id]["listener"] = ({ id });
			setup[id]["roster"] = allocate(10);
		}

		return setup[id];
	}
}

int exists(string id)
{
	return !undefinedp(setup[id]);
}

// 重新设定所有球队的对手
void reset_all_opponents()
{
	foreach(string id, mapping data in setup)
		setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :))) - ({ id });	
}

int is_playing(object labor)
{
	string id = query("boss", labor);
	string file = base_name(labor);

	if( undefinedp(setup[id]) ) return 0;

	if( setup[id]["status"] != STATUS_PLAYING ) return 0;

	for(int i=0;i<10;++i)
		if( setup[id]["roster"][i]["file"] == file )
			return 1;

	return 0;
}

mapping query_record()
{
	return record;
}

// 心跳函式
void heart_beat()
{
	int *realtime = TIME_D->query_realtime_array();

	if( !(++tick % 1855) ) save();

	if( !post_season_start && realtime[WDAY] == 0 && realtime[HOUR] == 14 )
	{
		CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 停止季赛配对，目前正在进行的比赛全部结束后第 "HIC+season_year+NOR" 球季季后赛即将开始。");
		post_season_start = 1;	
	}
	
	if( !(tick%10) )
	{
		if( post_season_start )
		{		
			// 尚有比赛进行中
			if( sizeof(games) ) return;
			
			switch(post_season_level)
			{
				// 开始季后赛
				case 0:
				{
					post_season_team_8 = sort_array(filter_array(season, (: valid_setup($1, 1) :)), (: sort_team($1, $2) :))[0..7];
					post_season_team_4 = allocate(0);
					post_season_team_2 = allocate(0);
					post_season_eliminate_teams = allocate(0);

					// 季后赛队伍不足 8 队
					if( sizeof(post_season_team_8) != 8 )
					{
						if( realtime[WDAY] == 0 && realtime[HOUR] == 20 )
						{
							CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 季后赛队伍不足八支球队，宣告此次季后赛取消。");
							post_season_level = 8;
						}
						return;
					}
					
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 所有正规季赛已经结束，以下选出本球季胜率最高的前八强队伍进行季后赛。");
					
					for(int i=0;i<sizeof(post_season_team_8);++i)
					{
						if( objectp(find_player(post_season_team_8[i])) )
							tell(find_player(post_season_team_8[i]), "\a");

						CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" "NOR YEL"第"HIY+(i+1)+NOR YEL"名"NOR"：“"+setup[post_season_team_8[i]]["name"]+"”，由"+setup[post_season_team_8[i]]["username"]+"领军。");
					}
		
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 以上八队劲旅将参加本球季的最终决赛，争取棒球界最高荣耀“"HIY"世"NOR YEL"界"HIY"冠"NOR YEL"军"NOR"”。");
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 季后赛所有赛事皆一战定胜负，总共 7 场比赛将于运动频道全世界同步实况转播。");
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 季后赛的比赛过程中将可拥有 2 倍的暗号使用次数，同时将拥有 20 倍的票房收入。");
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 首先进行 "HIC"A 组八强赛"NOR"的是排名第 1 的“"+setup[post_season_team_8[0]]["name"]+"”对上排名第 8 的“"+setup[post_season_team_8[7]]["name"]+"”，比赛将在 2 分钟后开始。");
				
					post_season_level++;
					new_game(post_season_team_8[0], post_season_team_8[7]);
					
					break;
				}
				case 1:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 接着进行 "HIC"B 组八强赛"NOR"的是排名第 2 的“"+setup[post_season_team_8[1]]["name"]+"”对上排名第 7 的“"+setup[post_season_team_8[6]]["name"]+"”，比赛将在 2 分钟后开始。");
					
					post_season_level++;
					new_game(post_season_team_8[1], post_season_team_8[6]);
					
					break;
				}
				case 2:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 接着进行 "HIC"C 组八强赛"NOR"的是排名第 3 的“"+setup[post_season_team_8[2]]["name"]+"”对上排名第 6 的“"+setup[post_season_team_8[5]]["name"]+"”，比赛将在 2 分钟后开始。");
					
					post_season_level++;
					new_game(post_season_team_8[2], post_season_team_8[5]);
					
					break;
				}
				case 3:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 接着进行 "HIC"D 组八强赛"NOR"的是排名第 4 的“"+setup[post_season_team_8[3]]["name"]+"”对上排名第 5 的“"+setup[post_season_team_8[4]]["name"]+"”，比赛将在 2 分钟后开始。");
					
					post_season_level++;
					new_game(post_season_team_8[3], post_season_team_8[4]);
					
					break;
				}
				case 4:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 接着进行"HIY"四强准决赛"NOR"的是 A 组晋级队伍“"+setup[post_season_team_4[0]]["name"]+"”对上 D 组晋级队伍“"+setup[post_season_team_4[3]]["name"]+"”，比赛将在 2 分钟后开始。");
					
					post_season_level++;
					new_game(post_season_team_4[0], post_season_team_4[3]);
					
					break;
				}
				case 5:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 接着进行"HIY"四强准决赛"NOR"的是 B 组晋级队伍“"+setup[post_season_team_4[1]]["name"]+"”对上 C 组晋级队伍“"+setup[post_season_team_4[2]]["name"]+"”，比赛将在 2 分钟后开始。");
					
					post_season_level++;
					new_game(post_season_team_4[1], post_season_team_4[2]);
					
					break;
				}
				case 6:
				{
				CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 接着进行第 "HIC+season_year+NOR" 球季"HIY"总"NOR YEL"冠军赛"NOR"的是“"+setup[post_season_team_2[0]]["name"]+"”对上“"+setup[post_season_team_2[1]]["name"]+"”，比赛将在 2 分钟后开始。");
					
					post_season_level++;
					new_game(post_season_team_2[0], post_season_team_2[1]);
					
					break;
				}
				case 7:
				{
					post_season_level++;
					CHANNEL_D->channel_broadcast("sport", HIR"季后"NOR RED"赛"NOR" 本球季所有季赛与季后赛已经全部结束，我们下一个球季再见！！");
					break;
				}
				case 8:
				{
					post_season_level = 0;
					post_season_start = 0;
					season_year++;
					
					CHANNEL_D->channel_broadcast("sport", HIG"全新"NOR GRN"球季"NOR" 新的第 "HIC+season_year+NOR" 球季开始，所有参赛球队开始进行比赛配对。");
					
					post_season_team_8 = allocate(0);
					post_season_team_4 = allocate(0);
					post_season_team_2 = allocate(0);
					post_season_eliminate_teams = allocate(0);
					
					record[season_year] = allocate_mapping(0);
					record[season_year][RECORD_TEAM] = allocate_mapping(0);
					record[season_year][RECORD_PLAYER] = allocate_mapping(0);
					record[season_year][RECORD_SPECIAL] = allocate_mapping(0);
		
					reset_all_opponents();
					
					foreach(string id in season)
					{
						setup[id]["keepwins"] = 0;
						setup[id]["keeploses"] = 0;
					}	
			
					save();
					break;	
				}
			}
		}
		else
		{
			// 处理比赛配对
			foreach(string id in season)
			{
				if( undefinedp(setup[id]) ) continue;
		
				// 寻找对手，新的比赛准备开始
				if(setup[id]["status"] == STATUS_IDLE )
				{
					string opponent_id = 0;
		
					// 球队设定有误，取消配对
					if( !valid_setup(id, 1) )
					{
						leave_season(id);
						continue;
					}
		
					// 若已无对手，重新列表
					if( !sizeof(setup[id]["opponents"]) )
						setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :))) - ({ id });
		
					// 搜寻目前没有比赛的对手
					foreach(string teamid in setup[id]["opponents"])
					{
						if( setup[teamid]["status"] == STATUS_IDLE )
						{
							if( !valid_setup(teamid, 1) )
							{
								leave_season(teamid);
								continue;
							}
		
							opponent_id = teamid;
							break;
						}
					}
		
					// 找不到对手，等待下次 heartbeat 再重新搜寻
					if( !stringp(opponent_id) )
					{
						// 连续 180 次(40min)找不到对手，重新列表
						if( ++setup[id]["no_opponent"] > 240 )
						{
							setup[id]["no_opponent"] = 0;
							setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :))) - ({ id });
						}
						continue;
					}
		
					setup[id]["no_opponent"] = 0;
					setup[opponent_id]["no_opponent"] = 0;
					
					// 随机决定主客场
					if( !random(2) )
					{
						//CHANNEL_D->channel_broadcast("sport", HIC+"季赛"NOR CYN"配对 "NOR+setup[id]["username"]+"的“"+setup[id]["name"]+"”与"+setup[opponent_id]["username"]+"的“"+setup[opponent_id]["name"]+"”将于 "+(PREPARETIME/60)+" 分钟后进行球赛。");
						new_game(id, opponent_id);
					}
					else
					{
						//CHANNEL_D->channel_broadcast("sport", HIC+"季赛"NOR CYN"配对 "NOR+setup[opponent_id]["username"]+"的“"+setup[opponent_id]["name"]+"”与"+setup[id]["username"]+"的“"+setup[id]["name"]+"”将于 "+(PREPARETIME/60)+" 分钟后进行球赛。");
						new_game(opponent_id, id);
					}
				}
			}
		}
	}
	play_game();
}

// 切换即时战况
void set_listener(string listener_id, string target_team)
{	
	if( !stringp(target_team) )
	{
		foreach(string team, mapping data in setup)
			setup[team]["listener"] -= ({ listener_id });
	}
	else
	{
		setup[target_team]["listener"] |= ({ listener_id });
	}
}

int remove()
{
	return save();
}

void fix_setup()
{
	/*
	foreach(string id, mapping data in setup)
	{

	}
*/
	save();
}

void fix_record()
{

}

int query_season_year()
{
	return season_year;	
}

int is_in_post_season()
{
	return post_season_start && post_season_level;	
}

string *query_post_season_team(int number)
{
	switch(number)
	{
		case 8:
			return post_season_team_8;
			break;
		case 4:
			return post_season_team_4;
			break;
		case 2:
			return post_season_team_2;
			break;
	}
}

string *query_post_season_eliminate_teams()
{
	return post_season_eliminate_teams;
}

void add_message(string id, string message)
{
	if( undefinedp(setup[id]) ) return;	
	
	if( !arrayp(setup[id]["messages"]) )
		setup[id]["messages"] = ({ message });
	else
		setup[id]["messages"] += ({ message });
}

void create()
{
	backup();
	
	if( !restore_object(DATA) )
	{
		setup = allocate_mapping(0);
		season = allocate(0);
		games = allocate(0);
		record = allocate_mapping(0);
		
		save();
	}

	set_heart_beat(1);
}

string query_name()
{
	return "棒球系统(BASEBALL_D)";
}
