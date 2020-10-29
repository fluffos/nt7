// Flagd.c 抢旗战主控制程序

#include <ansi.h>
inherit F_DBASE; 

#define MIN_TIME          60
#define ROUND_TIME        7200
#define RESET_TIME        40
#define START_TIME        5
#define END_TIME          1500
//#define END_TIME          300
#define START_TIME_COUNT  3
#define END_TIME_COUNT    5
#define REWARD_POT        3500
#define REWARD_EXP        10000
#define REWARD_EXPRI      1000
#define BLUE_START        "/d/flagwar/blue_entry" 
#define RED_START         "/d/flagwar/red_entry"
#define BLUE_RESET        "/d/flagwar/blue_reset" 
#define RED_RESET         "/d/flagwar/red_reset"
#define FLAG_OB           "/d/flagwar/obj/flag"
#define CENTER_FLAG       "/d/flagwar/center_flag"
#define WEST_FLAG         "/d/flagwar/west_flag"
#define EAST_FLAG         "/d/flagwar/east_flag"


int clean_up() { return 1; }
nosave int startnow,can_accept, reward_money, rsc, bsc, rfin, bfin, start_time;
nosave object *all_player_ob;
nosave string *all_player;
nosave mapping red, blue;
nosave int check_event_id, round_event_id;
void leave_player(string id);
void init_player(object me);
void auto_check();
void give_bouns();
int add_score(object me, int reward);
int set_score(string id, string party, int reward);
void remove_flag_war();
void restore_player(object me);
void drop_flag(object me, object ob);
void end_flag_war();
void put_flag_in_room(string t);
int sort_user(object ob1, object ob2);

mapping party_str = (["blue":HIB"蓝队"NOR, "red":HIR"红队"NOR]);
int query_flagwar_time() {
	if(can_accept) return -1;
	if(!round_event_id || !SCHEDULE_D->query_event(round_event_id)) return -2;
	return (SCHEDULE_D->query_event(round_event_id)[3] - SCHEDULE_D->query_event(round_event_id)[2]);
}
int query_flagwar() {
	return startnow;
}
mixed query_flagwar_data(string t) {
	switch(t) {
		case "all_player":
			return all_player;
		break;
		case "all_player_ob":
			return all_player_ob;
		break;		
		case "red":
			return red;
		break;
		case "blue":
			return blue;
		break;
		case "bsc":
			return bsc;
		break;
		case "rsc":
			return rsc;
		break;
		case "can_accept":
			return can_accept;
		break;
		
    default:
    return 0;		
	}
}
void clear_all_data() {
	all_player = ({ });
	all_player_ob = ({ });
	red = ([ ]);
	blue = ([ ]);
	startnow = 0;
	can_accept = 0;
	reward_money = 0;
	bsc = 0;
	rsc = 0;
	bfin = 0;
	rfin = 0;
}
void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "抢旗战精灵");
        CHANNEL_D->do_channel(this_object(), "sys", "抢旗战已经启动。");
        clear_all_data();
        round_event_id = SCHEDULE_D->set_event(ROUND_TIME, 0, this_object(), "start_flag_war");
}
void remove()
{
	remove_flag_war();
}
void message_flag(string str) {
	 if(str)
	 message("channel:rumor", HIG "【抢旗情报】活动主持人："+str+"\n" NOR, users());
}
void message_flag_tell(string str) {
	 if(str)
	 message("vision", HIG "【抢旗战场】战场裁判官："+str+"\n" NOR, all_player_ob);
}
void add_flag_round() {
	string round;
	round = explode(read_file("/www/flag_round"), "\n")[0];
	if(!round) round = "1";
	round = count_add(round, 1);
	write_file("/www/flag_round", round, 1);
}
string query_flag_round() {
	string round;
	round = explode(read_file("/www/flag_round"), "\n")[0];
	if(!round) round = "1";
	return round;
}
void start_flag_war() {
	if(objectp(WAR_D->query_marshal())) {
		message_flag("第 "+query_flag_round()+" 场抢旗战将延至 10 分钟后重新开始。");
		round_event_id = SCHEDULE_D->set_event(600, 0, this_object(), "start_flag_war");
		return;
	}
  clear_all_data();
	message_flag("第 "+query_flag_round()+" 场抢旗战将在 "+START_TIME+" 分钟后开始，请使用 flag join 报名。");
	can_accept = 1;
	start_time = time();
	if(round_event_id) SCHEDULE_D->delete_event(round_event_id);
	SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "start_flag_war_count", START_TIME);
}
void start_flag_war_count(int num) {
	    object me, be, re;
	    string *temp_all_player = ({});
      if(num <= 1) {
      		// check player have click html?

      	if(sizeof(all_player) < 5) {
      		message_flag("由于人数过少本场抢旗战取消。");
      		foreach(string id in all_player) {
      			if(!me = find_player(id)) continue;
      			me->add("balance", 500000);
      			tell_object(me, HIY"由于人数过少本场抢旗战取消，退还报名费用。\n"NOR);
      		}
          clear_all_data();
          add_flag_round();
          round_event_id = SCHEDULE_D->set_event(ROUND_TIME, 0, this_object(), "start_flag_war");
      	} else {
      		startnow = 1;
      		can_accept = 0;
          // 关闭起点出口
          if(be = load_object(BLUE_START)) be->delete("exits");
          if(re = load_object(RED_START)) re->delete("exits");

      		// 这里开始分配队伍      		
      		foreach(string id in all_player) {
 	        if(!me = find_player(id)) {
 	         leave_player(id);
 	         continue;	
 	        }
      		temp_all_player += ({ me });
      		}
      		temp_all_player = sort_array(temp_all_player, (: sort_user :));
      		foreach(object mes in temp_all_player) {
 	         if(!mes) {
 	         leave_player(mes->query("id"));
 	         continue;	
 	        }
 	         all_player_ob += ({ mes });
 	         if(sizeof(red) >= sizeof(blue)) {
 	         	blue[mes->query("id")] = 0;
 	          mes->set_temp("flag_war/party", "blue");
 	          mes->set_temp("title", HIB"抢旗蓝队"NOR);
 	         } else {
 	         	red[mes->query("id")] = 0;
 	         	mes->set_temp("flag_war/party", "red");
 	         	mes->set_temp("title", HIR"抢旗红队"NOR);
 	         }
 	         init_player(mes);
      		}
          message_flag("抢旗战开始，本场红队有 "+sizeof(red)+" 人，蓝队有 "+sizeof(blue)+" 人，胜利奖金："+MONEY_D->money_str(reward_money)+"。");
          SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "start_flag_war_count_in", START_TIME_COUNT);
          SCHEDULE_D->set_event(END_TIME, 0, this_object(), "end_flag_war");
          check_event_id = SCHEDULE_D->set_event(1, 1, this_object(), "auto_check");
          temp_all_player = ({});
      	}
      } else {
      	num--;
      	message_flag("第 "+query_flag_round()+" 场抢旗战将在 "+num+" 分钟后开始，请使用 flag join 报名。");
      	SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "start_flag_war_count", num);
      }
}
void start_flag_war_count_in(int num) {
	object be, re;
	if(num <= 1) {
    if(be = load_object(BLUE_START)) be->open_exit();
    if(re = load_object(RED_START)) re->open_exit();
   	message_flag_tell("抢旗战已经开放出口了，请快点出发吧。");
   	put_flag_in_room("center");
    SCHEDULE_D->set_event(5+random(10), 0, this_object(), "put_flag_in_room", "west");
    SCHEDULE_D->set_event(5+random(10), 0, this_object(), "put_flag_in_room", "east");
    
	} else {
   num--;
   message_flag_tell("抢旗战将在 "+num+" 分钟后开放出口，请做好准备。");
   SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "start_flag_war_count_in", num);		
	}
}
int add_player(object me, int money) {
	    if(!me || !money || startnow || !can_accept) return 0;
	    if(member_array(me->query("id"), all_player) != -1) return 0;
	    all_player += ({ me->query("id") });
	    reward_money += money;
	    message_flag(me->query_idname()+"报名参加抢旗战。");
	    return 1;
}
void auto_check() {
	   string room;
	   if(!startnow || !sizeof(all_player_ob)) {
	   	if(check_event_id) SCHEDULE_D->delete_event(check_event_id);
	   	return;
	   }
     if(!sizeof(red) || !sizeof(blue)) {
     	end_flag_war();
	   	if(check_event_id) SCHEDULE_D->delete_event(check_event_id);     	
    }
	   foreach(object pl in all_player_ob) {
        if(!pl) continue;
        
        // 检验位置
        if(room = base_name(environment(pl))) {
        if (!sscanf(room, "/d/flagwar/%*s")) {
         leave_player(pl->query("id"));  	   	  	
        }
      }
	  }
}
void leave_player(string id) {
	    object me, room;
	    if(!id) return;
	    if(find_player(id)) if(member_array(find_player(id), all_player_ob) != -1) all_player_ob -= ({ find_player(id) });
	    if(member_array(id, all_player) != -1) all_player -= ({ id });
      if(member_array(id, keys(red)) != -1) map_delete(red, id);
      if(member_array(id, keys(blue)) != -1) map_delete(blue, id);
      if(me = find_player(id)) {
      if(startnow) {
      	message_flag(me->query_idname()+"在中途逃离抢旗战了。");
      	restore_player(me);
      	if(!me->is_net_dead()) {
      	tell_object(me, "你一口气逃出了战场，来到扬州中央广场。\n");   	
      	me->move("/d/city/guangchang");
      	message("vision", "只见" + me->name() + "慌里慌张的跑了过来。\n", environment(me), ({ me }));
        }
      } else {
      	me->add("balance", 490000);
      	reward_money -= 500000;
      	message_flag(me->query_idname()+"取消报名抢旗战，退还报名费"+MONEY_D->money_str(490000)+"。");
      }
    }
}
void init_player(object me)
{
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        me->set_override("die", (: call_other, __FILE__, "check_die" :));
        me->set_override("unconcious", (: call_other, __FILE__, "check_die" :));
        me->move("/d/flagwar/"+me->query_temp("flag_war/party")+"_entry");
        tell_object(me, HIY "活动主持人将你带到了" + environment(me)->short() + HIY "。\n");
        message("vision", HIY"只见活动主持人将" + me->name() + "带到了" + environment(me)->short() + HIY "。\n", environment(me), ({ me }));
}
int check_quit(object me)
{
        leave_player(me->query("id"));  
        return 1;
}
void send_rune(object me)
{
	string *runes = ({"/clone/enchase/skull1","/clone/enchase/skull2","/clone/enchase/rune01","/clone/enchase/rune02","/clone/enchase/rune03","/clone/enchase/rune04","/clone/enchase/rune05","/clone/gift/tianshi-charm"});
	string *gems = ({"/clone/enchase/CYNjewel", "/clone/enchase/BLKjewel", "/clone/enchase/GRNjewel", "/clone/enchase/MAGjewel", "/clone/enchase/REDjewel", "/clone/enchase/WHTjewel", "/clone/enchase/YELjewel",});
	object rune;
	if(!me) return;
	if(random(3) >= 2) return;
	rune = new(runes[random(sizeof(runes))]);
  rune->move(me);
  tell_object(me, HIG"你获得了一个"+rune->name()+"。\n"NOR);
	rune = new(gems[random(sizeof(gems))]);
  rune->move(me);
  tell_object(me, HIG"你获得了一个"+rune->name()+"。\n"NOR);  
  if(random(300) >= 295) {
	rune = new(runes[random(sizeof(runes))]);
  rune->move(me);
  tell_object(me, HIG"你获得了一个"+rune->name()+"。\n"NOR);
  }
  if(random(300) >= 295) {
	rune = new(gems[random(sizeof(gems))]);
  rune->move(me);
  tell_object(me, HIG"你获得了一个"+rune->name()+"。\n"NOR);
  }  
}
void random_item(object me)
{
	object item;
	string *items = ({"/d/flagwar/obj/item1","/d/flagwar/obj/item2","/d/flagwar/obj/item3","/d/flagwar/obj/item4","/d/flagwar/obj/item4","/d/flagwar/obj/item5","/d/flagwar/obj/item6"});
	item = new(items[random(sizeof(items))]);
	message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"获得抢旗战专用特殊物品"+item->name()+"。");
	item->move(me);
}
int check_die(object me)
{
	      mapping my;
	      object ob, flag;
	      my = me->query_entire_dbase();
	      if(objectp(flag = present("fwar flag", me)))
        if(flag->move(environment(me))) drop_flag(me, flag);
	      if(objectp(flag = present("fwar count seal", me))) {
        message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"在临死前引发"+flag->name());
        foreach(object ppl in all_inventory(environment(me))) {
         if(ppl == me) continue;
         ppl->start_busy(20);
        }
        destruct(flag);
        }
        
        if(me->query_temp("flag_war/stab_event_id")) SCHEDULE_D->delete_event(me->query_temp("flag_war/stab_event_id"));
        me->delete_temp("flag_war/stab_now");
	      if(!objectp(ob = me->query_last_damage_from())) {
	      message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"莫名其妙被杀，"+party_str[me->query_temp("flag_war/party")]+HIG+"扣 3 分。");

        my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["qi"] = my["max_qi"];
        my["jing"] = my["max_jing"];
	      if(me->query_temp("flag_war/party") == "red") {
	      	rsc -= 3;
	        red[me->query("id")] -= 3;
	        me->move(RED_RESET);
	      } else {
	      	bsc -= 3;
	        blue[me->query("id")] -= 3;
	        me->move(BLUE_RESET);
	      }
	      if(!living(me)) me->revive();
	      me->start_busy(20);
	      random_item(me);
	      if(random(6) >= 3) random_item(me);
	      if(random(6) >= 3) random_item(me);
	      return 1;
	      } else {
        message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"被"+ob->query_idname()+HIG+"无情的击杀，"+party_str[me->query_temp("flag_war/party")]+HIG+"扣 3 分。");
	      my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["qi"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        ob->remove_killer(me);
        if(me->query_temp("flag_war/party") == "red") {
	      	rsc -= 3;
	      	red[me->query("id")] -= 3;
	        if(ob->query_temp("flag_war/party") == "blue") {
	        bsc += 3;
	        blue[ob->query("id")] += 3;
	        }
	        me->move(RED_RESET);
	      } else {
	      	bsc -= 3;
	      	blue[me->query("id")] -= 3;
	      	if(ob->query_temp("flag_war/party") == "red") {
	      	rsc += 3;
	        red[ob->query("id")] += 3;
	        }
	        me->move(BLUE_RESET);
	      }
	      if(!living(me)) me->revive();
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->start_busy(20);
        random_item(me);
        if(random(6) >= 3) random_item(me);
        if(random(6) >= 3) random_item(me);
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        me->set_override("die", (: call_other, __FILE__, "check_die" :));
        me->set_override("unconcious", (: call_other, __FILE__, "check_die" :));        
	      }
        return 1;
}
void get_flag(object me, object ob)
{
	mapping party_str = (["blue":HIB"蓝队"NOR, "red":HIR"红队"NOR]);
	if(!me || !ob) return;
	message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"夺得了"+ob->name()+HIG+"。");
	me->set_temp("flag_war/move_busy", 1);
	me->set_temp("title", me->query_temp("title")+" "HIM"扛旗者"NOR);
}
void drop_flag(object me, object ob)
{
	
	if(!me || !ob) return;
	message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"遗失了"+ob->name()+HIG+"。");
	me->delete_temp("flag_war/move_busy");
	if(me->query_temp("flag_war/party") == "blue") me->set_temp("title", HIB"抢旗蓝队"NOR);
	else me->set_temp("title", HIR"抢旗红队"NOR);
}

void end_flag_war()
{
	if(!sizeof(red)) message_flag_tell("由于"+party_str["red"]+HIG+"已经没有人了，本场抢旗战将在 "+END_TIME_COUNT+" 分钟后提早结束。");
	else if(!sizeof(blue)) message_flag_tell("由于"+party_str["blue"]+HIG+"已经没有人了，本场抢旗战将在 "+END_TIME_COUNT+" 分钟后提早结束。");
  message_flag_tell("本场抢旗战将在 "+END_TIME_COUNT+" 分钟后结束。");
  SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "end_flag_war_count", END_TIME_COUNT);		
}

void end_flag_war_count(int num) {
	object be, re;
	if(num <= 1) {
	 startnow = 0;
	 message_flag("本场抢旗战结束，正在统计结果。");
	 give_bouns();
   //SCHEDULE_D->set_event(5, 0, this_object(), "give_bouns"); // 给奖励
	} else {
   num--;
   message_flag_tell("本场抢旗战将在 "+num+" 分钟后结束。");
   SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "end_flag_war_count", num);		
	}
}

void give_bouns() {
	int exp, pot, expri, allsc, sc, m, allppl;
	int base_exp, base_pot, base_expri, flag_time;
	object ob;
	if(!all_player) return;

	// 奖励
	allppl = sizeof(all_player);
	if(allppl > 50) allppl = 50;
	base_exp = REWARD_EXP*allppl;
	base_pot = REWARD_POT*allppl;
	base_expri = REWARD_EXPRI*allppl;
	flag_time = ACTION_D->query_action("flagwar_reward"); 
  if(flag_time) {
  	base_exp *= flag_time;	
  	base_pot *= flag_time;	
  	base_expri *= flag_time;
  }		
//	if(base_exp >= 400000) base_exp = 400000;
//	if(base_pot >= 250000) base_pot = 250000;
//	if(base_expri >= 100000) base_expri = 100000;
	// 总分
	allsc = bsc+rsc;
	if(allsc <= 0) allsc = 1;
	if(reward_money <= 0) reward_money = 0;
	else reward_money *= 0.9;
	message_flag("本场抢旗战结果为红队 "+rsc+" 分，蓝队 "+bsc+" 分。");
	if(rsc == bsc) {
		message_flag("双方战况惨烈，不分轩轾，以平手收场，发放参加奖。");
		exp = REWARD_EXP / 4;
		pot = REWARD_POT / 4;
		expri = REWARD_EXPRI / 4;
		
		foreach(object pl in all_player_ob) {
			if(!objectp(pl)) continue;
			if(!pl->query_temp("flag_war")) continue;
			pl->add("combat_exp", exp);
			pl->add("potential", pot);
			pl->add("experience", expri);
			pl->add("action_point", 5);	
		  tell_object(pl, HIC"透过参加抢旗战你获得了"+chinese_number(exp)+"点经验，"+chinese_number(pot)+"点潜能和"+chinese_number(expri)+"点体会。\n"NOR);
		  restore_player(pl);
      	tell_object(pl, "你来到了扬州中央广场。\n");
      	pl->move("/d/city/guangchang");
      	message("vision", "只见" + pl->name() + "跑了过来。\n", environment(pl), ({ pl }));		  
		}
	} else if(rsc > bsc) {
		message_flag("本场抢旗战红队胜利，依积分发放奖励。");
		foreach(string id in keys(red)) {
			if(!objectp(ob = find_player(id))) continue;
			if(!ob->query_temp("flag_war")) continue;
			sc = red[id];
			if(sc <= 0) sc = 1;
			exp = base_exp*sc/rsc;
			pot = base_pot*sc/rsc;
			expri = base_expri*sc/rsc;
			m = reward_money*sc/rsc;
			ob->add("combat_exp", exp);
			ob->add("potential", pot);
			ob->add("experience", expri);
			ob->add("balance", m);
			ob->add("action_point", 15);
			send_rune(ob);
		  tell_object(ob, HIC"透过参加抢旗战你获得了"+chinese_number(exp)+"点经验，"+chinese_number(pot)+"点潜能和"+chinese_number(expri)+"点体会及"+MONEY_D->money_str(m)+"。\n"NOR);
		  restore_player(ob);
      	tell_object(ob, "你来到了扬州中央广场。\n");
      	ob->move("/d/city/guangchang");
      	message("vision", "只见" + ob->name() + "跑了过来。\n", environment(ob), ({ ob }));
		}
		foreach(string id in keys(blue)) {
			if(!objectp(ob = find_player(id))) continue;
			if(!ob->query_temp("flag_war")) continue;
		exp = REWARD_EXP / 4;
		pot = REWARD_POT / 4;
		expri = REWARD_EXPRI / 4;
		ob->add("combat_exp", exp);
  	ob->add("potential", pot);
		ob->add("experience", expri);
		ob->add("action_point", 10);
		send_rune(ob);
		  tell_object(ob, HIC"透过参加抢旗战你获得了"+chinese_number(exp)+"点经验，"+chinese_number(pot)+"点潜能和"+chinese_number(expri)+"点体会。\n"NOR);
		  restore_player(ob);
      	tell_object(ob, "你来到了扬州中央广场。\n");
      	ob->move("/d/city/guangchang");
      	message("vision", "只见" + ob->name() + "跑了过来。\n", environment(ob), ({ ob }));			
		}		
	} else {
		message_flag("本场抢旗战蓝队胜利，依积分发放奖励。");
		foreach(string id in keys(blue)) {
			if(!objectp(ob = find_player(id))) continue;
			if(!ob->query_temp("flag_war")) continue;
			sc = blue[id];
			if(sc <= 0) sc = 1;
			exp = base_exp*sc/bsc;
			pot = base_pot*sc/bsc;
			expri = base_expri*sc/bsc;
			m = reward_money*sc/bsc;
			ob->add("combat_exp", exp);
			ob->add("potential", pot);
			ob->add("experience", expri);
			ob->add("balance", m);
			ob->add("action_point", 15);
			send_rune(ob);
		  tell_object(ob, HIC"透过参加抢旗战你获得了"+chinese_number(exp)+"点经验，"+chinese_number(pot)+"点潜能和"+chinese_number(expri)+"点体会及"+MONEY_D->money_str(m)+"。\n"NOR);
		  restore_player(ob);
      	tell_object(ob, "你来到了扬州中央广场。\n");
      	ob->move("/d/city/guangchang");
      	message("vision", "只见" + ob->name() + "跑了过来。\n", environment(ob), ({ ob }));		  
		}
		foreach(string id in keys(red)) {
			if(!objectp(ob = find_player(id))) continue;
			if(!ob->query_temp("flag_war")) continue;
		exp = REWARD_EXP / 4;
		pot = REWARD_POT / 4;
		expri = REWARD_EXPRI / 4;
		ob->add("combat_exp", exp);
  	ob->add("potential", pot);
		ob->add("experience", expri);
		ob->add("action_point", 10);
		send_rune(ob);
		  tell_object(ob, HIC"透过参加抢旗战你获得了"+chinese_number(exp)+"点经验，"+chinese_number(pot)+"点潜能和"+chinese_number(expri)+"点体会。\n"NOR);				
		  restore_player(ob);
      	tell_object(ob, "你来到了扬州中央广场。\n");
      	ob->move("/d/city/guangchang");
      	message("vision", "只见" + ob->name() + "跑了过来。\n", environment(ob), ({ ob }));			
		}			
	}
	add_flag_round();
	remove_flag_war();
  clear_all_data();
}
void restore_player(object me) {
	      
	      if(!me) return;
        foreach(object inv in all_inventory(me)) 
       	if(inv->query("flag_war_item")) destruct(inv);   	
                   
        if(me->query_temp("flag_war/stab_event_id")) SCHEDULE_D->delete_event(me->query_temp("flag_war/stab_event_id"));
      	me->delete_temp("flag_war");
      	me->delete_temp("title");
        me->delete_override("quit");
        me->delete_override("die");
        me->delete_override("unconcious");
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->receive_damage("qi", 0);
        me->set("eff_qi", me->query("max_qi"));
        me->set("eff_jing", me->query("max_jing"));
        me->set("qi", me->query("max_qi"));
        me->set("jing", me->query("max_jing"));     	
	      if(!living(me)) me->revive();
}
void remove_flag_war() {
	      object ro;
	      if(check_event_id) SCHEDULE_D->delete_event(check_event_id);
	      if(round_event_id) SCHEDULE_D->delete_event(round_event_id);
        foreach(string f in get_dir("/d/flagwar/")) {
        	if(objectp(ro = find_object("/d/flagwar/"+f))) destruct(ro);
        }
	      round_event_id = SCHEDULE_D->set_event(ROUND_TIME, 0, this_object(), "start_flag_war");
}
void stab_flag(object me, object ob) {
	int stab_event_id;
	if(!me || !ob || !startnow) return;
	if(me->query_temp("flag_war/stab_now")) return;
	message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"在"+environment(me)->short()+HIG+"准备将"+ob->name()+HIG+"插上旗台。");
	if(!me->query_temp("flag_war/move_busy")) stab_event_id = SCHEDULE_D->set_event(1, 0, this_object(), "stab_flag_count", 1, me, ob);
	else stab_event_id = SCHEDULE_D->set_event(1, 0, this_object(), "stab_flag_count", 5+random(5), me, ob);
	
	message_vision("$N准备将$n插上旗台。\n" , me, ob);
	me->set_temp("flag_war/stab_now", 1);
	me->set_temp("flag_war/stab_event_id", stab_event_id);
	me->start_busy(5);
}
void stab_flag_count(int num, object me, object ob) {
  int reward, pa, stab_event_id;
  string *msgs = ({"$N努力的将$n插上旗台，却不知怎么的插不进去。","$N用力的将$n搬上旗台，但是$N太累了偷懒休息。","$N默默的放空发着呆，不知道在想些什么。","$N不断的忙碌着，但却不知道在忙些什么。"});
	if(!me || !ob || !num || !startnow) return;
	if(me->is_fighting() || !environment(me)->query("stab_flag")) {
		message_vision(HIY"$N装设旗子的动作被打断了。\n"NOR, me);
		if(me->query_temp("flag_war/stab_event_id")) SCHEDULE_D->delete_event(me->query_temp("flag_war/stab_event_id"));
		me->delete_temp("flag_war/stab_now");
		me->start_busy(5);
    return;
	}
  if(num <= 1) {
  reward = 50;
  pa = me->query_temp("flag_war/stab_count");
  if(pa >= 2) reward = reward/pa;
  if(reward < 5) reward = 5;
  message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"在"+environment(me)->short()+HIG+"将"+ob->name()+HIG+"插上旗台了。");
  me->add_temp("flag_war/stab_count", 1);
  me->delete_temp("flag_war/stab_now");
  if(me->query_temp("flag_war/stab_event_id")) SCHEDULE_D->delete_event(me->query_temp("flag_war/stab_event_id"));
  me->delete_temp("flag_war/stab_event_id");
	if(me->query_temp("flag_war/party") == "blue") {
		bfin++;
		me->set_temp("title", HIB"抢旗蓝队"NOR);
	} else {
		rfin++;
		me->set_temp("title", HIR"抢旗红队"NOR);
  }
  me->delete_temp("flag_war/move_busy");
  add_score(me, reward);
  destruct(ob);
  SCHEDULE_D->set_event(RESET_TIME+random(RESET_TIME), 0, this_object(), "put_flag_in_room", "random");
  } else {
  num--;
	stab_event_id = SCHEDULE_D->set_event(1, 0, this_object(), "stab_flag_count", num, me,ob);
	me->set_temp("flag_war/stab_event_id", stab_event_id);
	me->start_busy(5);
	message_vision(msgs[random(sizeof(msgs))] +"\n" , me, ob);
  }
}
int add_score(object me, int reward)
{
	if(!me || !reward) return 0;
	if(!me->query_temp("flag_war/party")) return 0;
	if(set_score(me->query("id"), me->query_temp("flag_war/party"), reward)) {
	message_flag_tell(me->query_idname()+HIG+"为"+party_str[me->query_temp("flag_war/party")]+HIG+"夺得 "+reward+" 分。");
  } else {
  	tell_object(me, "分数增加出错，请使用 sos post 回报。\n");
    return 0;
  }
  return 1;
}
int set_score(string id, string party, int reward)
{
	if(!id || !party || !reward) return 0;
	if(member_array(id, keys(red)) != -1) {
		red[id] += reward;
	  rsc += reward;
	  return 1;
	} else {
		blue[id] += reward;
		bsc += reward;
		return 1;
	}
	return 0;
}

string query_party_score(string party)
{
	int scs, scs2;
	string result;
	mapping partys;
	object pp;
	result = "";
	if(party == "blue") {
		scs = bsc;
		scs2 = bfin;
		partys = blue;
	} else {
		scs = rsc;
		scs2 = rfin;
		partys = red;
	}
	result += sprintf(" "+party_str[party]+"： 队伍人数 %d 人、目前积分 %d 分、插旗成功\ %d 次。\n", sizeof(partys), scs, scs2);
	foreach(string ppid, int ppnum in partys) {
		if(!objectp(pp = find_player(ppid))) continue;
		if(pp->query_temp("flag_war/party") != party) continue;
		result += sprintf("  "+"%-12s %-30s 积分：%d 分\n", pp->query_temp("title"), ANSI_D->remove_ansi(pp->query_idname()), ppnum);		
	}
	return result;
}

string query_party_score_total()
{
	return sprintf("总参加人数： %d 人、总奖金：%s、进行时间：%s\n", sizeof(all_player), MONEY_D->money_str(reward_money), time_period(time() - start_time));
}

void put_flag_in_room(string t)
{
	  object flag, room;
	  string *all_flag_room;
	  if(!t) return;
		flag = new(FLAG_OB);
		switch(t) {
			case "west":
       flag->move(load_object(WEST_FLAG));
       message_flag_tell(flag->name()+HIG+"出现在"+environment(flag)->short()+"。");
			break;
			case "east":
			 flag->move(load_object(EAST_FLAG));
			 message_flag_tell(flag->name()+HIG+"出现在"+environment(flag)->short()+"。");
			break;
			case "random":
			 all_flag_room = ({WEST_FLAG,EAST_FLAG,CENTER_FLAG});
			 room = load_object(all_flag_room[random(sizeof(all_flag_room))]);
			 flag->move(room);
			 message_flag_tell(flag->name()+HIG+"出现在"+environment(flag)->short()+"。");
			break;
			default:
			 flag->move(load_object(CENTER_FLAG));
			 message_flag_tell(flag->name()+HIG+"出现在"+environment(flag)->short()+"。");
			break;
		}
}

int sort_user(object ob1, object ob2)
{
    return (ob2->query("level") - ob1->query("level"));
}
