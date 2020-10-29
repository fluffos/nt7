// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// battlefieldd.c

#include <ansi.h>

#define LEAVE_ROOM              "/d/city/guangchang"
#define BATTLE_FIELD_DIR        "/adm/daemons/battle/"
#define BATTLE_TIME             1200
#define BATTLE_JOIN_TIME        180

nosave mapping battle_player = allocate_mapping(0);
nosave object *total = allocate(0);
nosave string *ip_number = allocate(0);

nosave int bunch_flag = 0;
nosave int battle_open_flag = 0;
nosave int battle_start_flag = 0;
nosave int battle_time_countdown = 0;
nosave int battle_start_time = 0;
nosave int percent = 100;
nosave int max_level = 300;
nosave string battle_name;
nosave string entry1;
nosave string entry2;

int check_out(object me);
private void restore_status(object me);
void add_damage_score(object me, int score);
void add_killplayer_score(object me, int score);
void add_killnpc_score(object me, int score);
void add_bouns_score(object me, int score);
void stop_battle();
void calculate_score();

int sort_user(object ob1, object ob2)
{
        return (query("level", ob2) - query("level", ob1));
}

class team
{
        int score;      // 积分
        int win;        // 获胜
        int lose;       // 失败
        string name;    // 队伍名称
        string *member; // 队伍成员
        string leader;  // 队长
}
nosave class team *all = ({});
nosave class team team1, team2;

int clean_up()
{
        return 1;
}

int is_battle_open()
{
        return battle_open_flag;
}

int is_battle_start()
{
        return battle_start_flag;
}

int in_battle(object me)
{
        return battle_start_flag && !undefinedp(battle_player[me->query_id(1)]);
}

int inside_battlefield(object me)
{
        object env = environment(me);

        if( !objectp(env) )
                return 0;

        if( !sscanf(base_name(env), "/maze/battle%*s") )
                return 0;

        return 1;
}

int query_battle_time()
{
        return battle_time_countdown;

}

mapping query_battle_player()
{
        return battle_player;
}

int query_player_number(object player)
{
        return member_array(player->query_id(1), keys(battle_player)) + 1;
}

// 设置战役名称
void set_battle_name(string name)
{
        battle_name = name;
}

// 设置队伍名称
void set_team_name(string name1, string name2)
{
        team1->name = name1;
        team2->name = name2;
}

// 设置队伍入口
void set_entry_room(string where1, string where2)
{
        entry1 = where1;
        entry2 = where2;
}

// 设置报名条件
void set_max_level(int level)
{
        max_level = level;
}

// 设置奖励比例%
void set_bonus_percent(int per)
{
        percent = per;
}

// 设置两支帮派
void set_bunch_team(string name1, string name2)
{
        bunch_flag = 1;
        team1->name = name1;
        team2->name = name2;
}

void move_to_battle(object me)
{
        string where;
        object entry;

        where = query_temp("battle/entrance", me);
        entry = get_object(where);
        me->move(entry);
}

void init_player(object me)
{
        int i;
        object *obs;
        
        tell_object(me, HIY "你眼前忽然一花...\n" NOR);
        me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
        me->set_override("die", (: call_other, __FILE__, "check_out" :));
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        //set_temp("override/receive_damage", (:call_other,__FILE__,"receive_damage":), me);
        set_temp("backup/killer", me->query_killer(), me);
        set_temp("backup/want", me->query_want(), me);
        set_temp("in_pkd", 1, me);

        set("backup/condition", me->query_condition(), me);
        me->clear_condition();
        
        obs = all_inventory(me);
        for( i=0; i<sizeof(obs); i++ )
        {
                if( query("id", obs[i]) == "mian ju" )
                        obs[i]->move();
        }
                
        if( !arrayp(total) )
                total = ({ me });
        else
        if( member_array(me, total) == -1 )
                total += ({ me });
       
        move_to_battle(me);
        tell_object(me, HIY "你被传送到战场中...。\n");
}

// 参与战争
void join_battle(object me)
{
        string where;
        mapping cnd;
        string id = me->query_id(1);

        if( battle_start_flag )
                return tell_object(me, "战场已经开启，报名终止。\n");

        if( me->is_busy() )
                return tell_object(me, BUSY_MESSAGE);

        if( me->is_fighting() )
                return tell_object(me, "你目前正在战斗中，还是先处理目前的对手再说吧。\n");

        if( me->query_condition("killer") )
                return tell_object(me, "官府正在通缉你，你还敢在这儿抛头露面？\n");

        if( !battle_open_flag )
                return tell_object(me, "战争没有发出集结，目前无法报名。\n");

        if( me->is_ghost() )
                return tell_object(me, "等你还阳后，再报名吧。\n");

        if (me->is_in_prison()) 
                return tell_object(me, "你正在做牢呢，你想干什么？！\n"); 

        if( query("level", me) < 5 )
                return tell_object(me, "你这个新鸟就不要参加高难度的战场吧。\n");

        if( query("level", me) > max_level )
                return tell_object(me, "你就别进去欺负那些新鸟吧。\n");
        
        if( bunch_flag )
        {
                if( !bunchp(me) )
                        return tell_object(me, "本次战争只能是帮派玩家报名参加。\n");
                
                if( me->query_bunch() != team1->name && 
                    me->query_bunch() != team2->name )
                        return tell_object(me, "本次战争你所在的帮派不能报名参加。\n");
        }
        
        where = base_name(environment(me));
        if( sscanf(where, "/d/newbie/%s") )
                return tell_object(me, "你还没有正式闯到江湖呢，不能参加报名！\n");

        if( !undefinedp(battle_player[id]) )
        {
                if( !battle_start_flag )
                        return tell_object(me, "你已经报名参与这次的战争，请耐心等候召集。\n");

                if( inside_battlefield(me) )
                        return tell_object(me, "你已经在战场中，快点杀敌吧。\n");

                if( !query_temp("battle_rejoin", me) )
                        return tell_object(me, "你必须使用战争勋章方可重新进入战场。\n");

                delete_temp("battle_rejoin", me);
                set_temp("battle/leave_room", where, me);
                init_player(me);
                return;
        }

        if( member_array(query_ip_number(me), ip_number) != -1 )
                return tell_object(me, "你所在的IP已经报名过了!\n");

        ip_number += ({ query_ip_number(me) });
        battle_player[id] = allocate_mapping(0);

        CHANNEL_D->channel_broadcast("war", "目前共有 "+sizeof(battle_player)+
                                            " 位玩家报名参与「"+battle_name+HIR"」");
}

// 取消参与战争
void cancel_battle(object me)
{
        string id = me->query_id(1);

        if( undefinedp(battle_player[id]) )
                return tell_object(me, "你原本就没有报名参与这次的战争。\n");

        if( battle_start_flag )
                return tell_object(me, "这次的战争已经开始，你无法取消，可用quit指令逃离战场。\n");

        map_delete(battle_player, id);
        ip_number -= ({ query_ip_number(me) });

        addn("honors", -100, me); // 扣减荣誉
        if( query("honors", me) < 0 );
                set("honors", 0, me);

        CHANNEL_D->channel_broadcast("war", "目前共有 "+sizeof(battle_player)+
                                            " 位玩家报名参与「"+battle_name+HIR"」");
}

int check_quit(object me)
{
        CHANNEL_D->channel_broadcast("war", HIR"战"NOR RED"场"HIR"：玩家" + me->name(1) +"在「"+battle_name+HIR"」中临阵脱逃，溜走了。"NOR);

        addn("honors", -500, me); // 扣减荣誉
        if( query("honors", me)<0);
                set("honors", 0, me);

        if( arrayp(total) )
                total -= ({ me });
        if( arrayp(ip_number) )
                ip_number -= ({ query_ip_number(me) });

        tell_object(me, "你一口气逃出了战场。\n");
        restore_status(me);
        message("vision", "只见" + me->name() + "慌里慌张的跑了过来。\n",
                environment(me), ({ me }));

        return 1;
}

varargs int receive_damage(object me, string type, int damage, object who)
{
        if( !who ) who = me->query_last_damage_from();
        if( !who ) return 0;

        if( type != "qi" || damage < 1 ) return 0;

        if( userp(me) )
                add_damage_score(who, damage);
        else
                add_damage_score(who, damage/2);

        return 0;
}

void auto_check()
{
        object ob;
        string msg;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for (i = 0; i < sizeof(total); i++)
        {
                if( !objectp(total[i]))
                        continue;
                room = base_name(environment(total[i]));
                if( !sscanf(room, "/maze/battle%*s") )
                {
                        // not in pk room
                        restore_status(total[i]);
                        total[i] = 0;
                        continue;
                }
                if( query("qi", total[i])<1 || query("jing", total[i])<1 )
                        lost += ({ total[i] });
        }

        foreach (ob in lost)
                check_out(ob);

        total -= ({ 0 });
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;

        room = base_name(environment(me));
        if( !sscanf(room, "/maze/battle%*s") )
        {
                // not in battle room
                total -= ({ me });
                return 0;
        }

        my = me->query_entire_dbase();
        my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["qi"] = 1;
        my["jing"] = 1;

        tell_object(me, HIR "\n你觉得眼前一阵模糊...这下完了！\n" NOR);
        if( ob = me->query_last_damage_from() )
        {
                msg = me->name(1) + "惨遭" + ob->name(1) + "的毒手，被无情ＰＫ。";
                if( userp(ob) )
                {
                        if( userp(me) )
                        {
                                if( query_temp("battle/team_name", ob) == query_temp("battle/team_name", me) )
                                        add_killplayer_score(ob, -5);
                                else {
                                        if( query_temp("battle/leader", me) )
                                                add_killplayer_score(ob, 5);
                                        else
                                                add_killplayer_score(ob, 1);
                                }
                        }
                        else
                        {
                                if( query_temp("battle/team_name", ob) == query_temp("battle/team_name", me) )
                                        add_killnpc_score(ob, -5);
                                else
                                        add_killnpc_score(ob, 1);
                                return 0;
                        }
                }
        } else
                 msg = me->name(1) + "运气不佳，本领有限、已经惨遭ＰＫ。";

        message("vision", msg, environment(me), ({ me }));

        restore_status(me);
        total -= ({ me });

        message("vision", "一个黑影倏的窜了出来，随即就是“啪”的"
                "一声，就见" + me->name() +"摔倒了地上，一副半死不"
                "活的样子。\n", environment(me), ({ me }));
        tell_object(me, "半昏半迷中，你觉得被人拎了起来，又"
                "重重的摔倒了地上。\n");

        if( !living(me) )
                me->revive();

        return 1;
}

void start_battle()
{
        object *all_player = ({});
        object *obs, *obn, ob;
        object *unavailable_players = allocate(0);
        object player;
        string where;
        int i;

        if( sizeof(battle_player) < 5 )
        {
                set_heart_beat(0);
                ip_number = allocate(0);
                total = allocate(0);
                all = allocate(0);
                battle_player = allocate_mapping(0);
                max_level = 200;
                bunch_flag = 0;
                battle_open_flag = 0;
                battle_start_time = 0;
                CHANNEL_D->channel_broadcast("war", "报名参与「"+battle_name+HIR"」战役的玩家不足 5 人，取消本次战役。");
                return;
        }

        CHANNEL_D->channel_broadcast("war", "「"+battle_name+HIR"」开始出征！共计 "+sizeof(battle_player)+
                                            " 位玩家参与「"+battle_name+HIR"」，计时 "+(BATTLE_TIME/60)+" 分钟结束");

        foreach(string id, mapping data in battle_player)
        {
                reset_eval_cost();

                if( !objectp(player = find_player(id)) )
                        continue;

                if( query_temp("running", player)  )
                {
                        tell(player, pnoun(2, player)+"正在飞行中，无法加入战场。\n");
                        unavailable_players |= ({ player });
                        continue;
                }
                all_player += ({ player });
        }

        foreach(player in unavailable_players)
                cancel_battle(player);
        
        team1->member = ({});
        team2->member = ({});
        
        // 如果是两支帮派作战，则按帮派分配阵营
        if( bunch_flag )
        {
                obs = filter_array(all_player, (: query("bunch/bunch_name", $1) == team1->name :));
                foreach( ob in obs )
                {
                        team1->member += ({ ob->query_id(1) });
                        set_temp("battle/team_name", team1->name, ob);
                        set_temp("battle/entrance", entry1, ob);
                        where = base_name(environment(ob)); // 记录玩家所在位置
                        set_temp("battle/leave_room", where, ob);
                        init_player(ob);
                }
                obn = all_player - obs;
                foreach( ob in obs )
                {
                        team2->member += ({ ob->query_id(1) });
                        set_temp("battle/team_name", team2->name, ob);
                        set_temp("battle/entrance", entry2, ob);
                        where = base_name(environment(ob)); // 记录玩家所在位置
                        set_temp("battle/leave_room", where, ob);
                        init_player(ob);
                }
        }
        else
        {
                // 开始分配队伍阵营        
                all_player = sort_array(all_player, (: sort_user :));

                for( i=0; i<sizeof(all_player); i++ )
                {
                        if( i % 2 == 0 ) {
                                if( i == 0 )
                                {
                                        team1->leader = all_player[i]->query_id(1);
                                        set_temp("battle/leader", 1, all_player[i]);
                                }
                                team1->member += ({ all_player[i]->query_id(1) });
                                set_temp("title", team1->name, all_player[i]);
                                set_temp("battle/team_name", team1->name, all_player[i]);
                                set_temp("battle/entrance", entry1, all_player[i]);
                        } else {
                                if( i == 1 )
                                {
                                        team2->leader = all_player[i]->query_id(1);
                                        set_temp("battle/leader", 1, all_player[i]);
                                }
                                team2->member += ({ all_player[i]->query_id(1) });
                                set_temp("title", team2->name, all_player[i]);
                                set_temp("battle/team_name", team2->name, all_player[i]);
                                set_temp("battle/entrance", entry2, all_player[i]);
                        }

                        where = base_name(environment(all_player[i])); // 记录玩家所在位置
                        set_temp("battle/leave_room", where, all_player[i]);

                        init_player(all_player[i]);
                }
        }
        all += ({ team1, team2 });
        battle_start_flag = 1;
        battle_time_countdown = BATTLE_TIME;
}

// 某战场开始接受报名 TIME_D 调用
void start_join(string name)
{
        object ob;

        name = BATTLE_FIELD_DIR + name;
        if( ob = find_object(name) )
                destruct(ob);

        catch(ob = load_object(name));

        if( !objectp(ob) ) return;

        team1 = new(class team);
        team2 = new(class team);
        ob->init_battle(); // 设置队伍的名称，队伍的入口，战场的名称以及初始化战场其他设置等
        CHANNEL_D->channel_broadcast("war", HIY"荣耀"NOR YEL"之战"HIR"发出战争集结，即将在 "+(BATTLE_JOIN_TIME/60)+
                                            " 分钟后发动「"+battle_name+HIR"」，请使用 battle 指令加入战役。");

        ip_number = allocate(0);
        total = allocate(0);
        all = allocate(0);
        battle_player = allocate_mapping(0);
        battle_open_flag = 1;

        battle_start_time = BATTLE_JOIN_TIME;

        set_heart_beat(1);

        //tell_object(users(), "\a");
}

int get_player_score(string id)
{
        if( undefinedp(battle_player[id]) ) return 0;

        return battle_player[id]["killplayer"]*10 + /*battle_player[id]["killnpc"] + battle_player[id]["damage"]/50000 +*/ battle_player[id]["bonus"];
}

string *get_sorted_players()
{
        return sort_array(keys(battle_player), (: get_player_score($2) - get_player_score($1) :));
}

void add_damage_score(object me, int score)
{
        string id = me->query_id(1);

        if( undefinedp(battle_player[id]) )
            return;

        battle_player[id]["damage"] += score;
}

void add_killnpc_score(object me, int score)
{
        string id = me->query_id(1);

        if( undefinedp(battle_player[id]) )
            return;

        battle_player[id]["killnpc"] += score;
}

void add_killplayer_score(object me, int score)
{
        string id = me->query_id(1);
        string name;

        if( undefinedp(battle_player[id]) )
            return;

        battle_player[id]["killplayer"] += score;

        name = query_temp("battle/team_name", me);
        if( filter_color(team1->name, 1) == filter_color(name, 1) )
                team1->score += score;
        else
                team2->score += score;

        return;
}

void add_bonus_score(object me, int score)
{
        string id = me->query_id(1);
        string name;

        if( undefinedp(battle_player[id]) )

            return;

        battle_player[id]["bonus"] += score;
        //addn("honors", score, me);

        name = query_temp("battle/team_name", me);
        if( filter_color(team1->name, 1) == filter_color(name, 1) )
                team1->score += score;
        else
                team2->score += score;

        return;
}

void win_battle(string name)
{
        if( filter_color(team1->name, 1) == filter_color(name, 1) )
        {
                team1->win = 1;
                team1->lose = 0;
                team2->win = 0;
                team2->lose = 1;
        } else
        {
                team2->win = 1;
                team2->lose = 0;
                team1->win = 0;
                team1->lose = 1;
        }

        stop_battle();
}

void stop_battle()
{
        object ob;
        object player;

        set_heart_beat(0);

        foreach( ob in total )
        {
                if( !objectp(ob) )
                        continue;

                //ob->remove_all_killer();
                ob->remove_all_enemy(1);
                restore_status(ob);
                tell_object(ob, "「"+battle_name+"」结束，你被传离战场...\n");
        }

        ip_number = allocate(0);
        total = allocate(0);
        max_level = 200;
        battle_open_flag = 0;
        battle_start_flag = 0;
        battle_time_countdown = 0;        

        CHANNEL_D->channel_broadcast("war", WHT"————————————————————————————————"NOR);
        CHANNEL_D->channel_broadcast("war", HIR"战"NOR RED"争"HIR"：「"+battle_name+HIR"」终于渐渐平息..."NOR);
        CHANNEL_D->channel_broadcast("war", HIR"战"NOR RED"争"HIR"：正在统计战绩..."NOR);
        CHANNEL_D->channel_broadcast("war", WHT"————————————————————————————————"NOR);


        if( ob = find_object(BATTLE_FIELD_DIR + battle_name) )
        {
                ob->refresh_map();
        }

        if( objectp(ob) && function_exists("calculate_score", ob) )
        {
                ob->calculate_score();
                
                bunch_flag = 0;
                all = allocate(0);
                battle_player = allocate_mapping(0);
                destruct(ob);
        }
        else
                call_out((: calculate_score :), 3);
}

void calculate_score()
{
        int score;
        string name;
        string msg;
        int rank;
        object home, player;
        string file;
        object insigne;
        int insigne_count;
        string *member;
        object ob;
        int i;

        map_delete(battle_player, 0);

        CHANNEL_D->channel_broadcast("war", WHT"————————————————————————————————"NOR);

        rank = 0;
        foreach(string id in get_sorted_players())
        {
                if( !objectp(player = find_player(id)) )
                        continue;

                name=query_temp("battle/team_name", player);

                score = get_player_score(id);

                CHANNEL_D->channel_broadcast("war", HIR"战"NOR RED"争"HIR"："+(++rank)+"."+name+HIR"的"+player->query_idname()+HIR"共击杀 "+battle_player[id]["killplayer"]+" 位玩家，战绩结算为 "+NUMBER_D->number_symbol(score)+(battle_player[id]["bonus"]>0 ? "("NOR CYN"+"HIC+battle_player[id]["bonus"]+HIR")":"")+" 分"NOR);

                //addn("battle/score", score, player);
                addn("honors", score, player);

                if( score > 1000 ) score = 1000;
                if( score < 10 ) score = 10;
                GIFT_D->battle_bonus(player, ([ "exp" : score*3000, "pot" : score*1000, "mar" : score*300, "score" : score, "percent" : percent ]));

                insigne_count = 0;

                if( score >= 25 )
                switch(rank)
                {
                        case 1:
                                insigne_count = 4;
                                break;
                        //case 2..3:
                        case 2:
                                insigne_count = 3;
                                break;
                        //case 4..6:
                        case 3:
                                insigne_count = 2;
                                break;
                        //case 7..9:
                        case 4:
                                insigne_count = 1;
                                break;
                }

                if( insigne_count > 0 )
                {
                        if( random(2) )
                                insigne = new("/clone/tongren/tongren1");
                        else
                                insigne = new("/clone/tongren/tongren2");
                        tell_object(player, "你获得 "+insigne_count+" 个"+insigne->name()+"。\n");
                        insigne->set_amount(insigne_count);
                        insigne->move(player);
                }

                player->save();
        }

        if( team1->win )
        {
                msg = team1->name + "胜" + team2->name;
                member = team1->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 1000, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 3000000, "pot" : 30000, "mar" : 3000, "score" : 30, "percent" : percent ]));
                }
                if( bunch_flag )
                        BUNCH_D->add_bunch_honors(team1->name, 1000);
        }
        else if( team2->win )
        {
                msg = team1->name + "负" + team2->name;
                member = team2->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 1000, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 3000000, "pot" : 30000, "mar" : 3000, "score" : 30, "percent" : percent ]));
                }
                if( bunch_flag )
                        BUNCH_D->add_bunch_honors(team2->name, 1000);
        }
        else if( team1->score > team2->score )
        {
                msg = team1->name + "胜" + team2->name;
                member = team1->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 1000, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 3000000, "pot" : 30000, "mar" : 3000, "score" : 30, "percent" : percent ]));
                }
                if( bunch_flag )
                        BUNCH_D->add_bunch_honors(team1->name, 800);
        }
        else if( team1->score < team2->score )
        {
                msg = team1->name + "负" + team2->name;
                member = team2->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 1000, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 3000000, "pot" : 30000, "mar" : 3000, "score" : 30, "percent" : percent ]));
                }
                if( bunch_flag )
                        BUNCH_D->add_bunch_honors(team2->name, 800);
        }
        else
        {
                msg = team1->name + "平" + team2->name;
                member = team1->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 500, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 1500000, "pot" : 15000, "mar" : 1500, "score" : 15, "percent" : percent ]));
                }
                member = team2->member;
                for( i=0; i<sizeof(member); i++)
                {
                        ob = find_player(member[i]);
                        if( !objectp(ob) ) continue;
                        addn("honors", 500, ob);
                        GIFT_D->battle_bonus(ob, ([ "exp" : 1500000, "pot" : 15000, "mar" : 1500, "score" : 15, "percent" : percent ]));
                }
                if( bunch_flag )
                {
                        BUNCH_D->add_bunch_honors(team1->name, 200);
                        BUNCH_D->add_bunch_honors(team2->name, 200);
                }
        }

        msg += "\n";

        CHANNEL_D->channel_broadcast("war", HIR"战"NOR RED"争"HIR"："+msg+NOR);

        bunch_flag = 0;
        all = allocate(0);
        battle_player = allocate_mapping(0);
}

string do_score()
{
        string desc, desc_temp;
        object player;
        int i, j, n;
        string *member;
        object ob;

        desc = HIY"
※※※※※※※※※※※※※※※※【当前战场成绩】※※※※※※※※※※※※※※※※
________________________________________________________________________________
队别  队名     积分  成员                                \n" NOR;

        n = sizeof(all);
        if( n > 1 )
        {
                for( i=0; i<n; i++ )
                {
                        desc_temp = "";
                        desc_temp += sprintf("%-6d%-9s%-6d ",
                                             i+1,
                                             (string)all[i]->name,
                                             (int)all[i]->score);

                        member = all[i]->member;
                        for( j=0; j<sizeof(member); j++ ) {
                                if( (j-1)%4==3 )
                                        desc_temp += "\n              ";

                                ob = find_player(member[j]);
                                if( objectp(ob) )
                                        desc_temp += sprintf("%-8s(%5d)",
                                                     ob->name(),
                                                     get_player_score(query("id", ob)));
                                else
                                {
                                        ob = UPDATE_D->global_find_player(member[j]);
                                        desc_temp += sprintf("%-8s(不 在)",
                                                     ob->name());
                                        UPDATE_D->global_destruct_player(ob, 1);
                                }
                        }
                        desc_temp += "\n";
                        desc += desc_temp;
                }
        }

        desc += "
________________________________________________________________________________\n"NOR;

        return desc;
}

void heart_beat()
{
        if( battle_start_time > 0 )
        {
                switch(--battle_start_time)
                {
                        case 0:
                                start_battle();
                                break;
                        case 60:
                        case 120:
                        case 180:
                        case 300:
                        case 600:
                        case 900:
                        case 1200:
                                CHANNEL_D->channel_broadcast("war", HIY"荣耀"NOR YEL"之战"HIR"发出战争集结，即将在 "+(battle_start_time/60)+
                                                                    " 分钟后发动「"+battle_name+HIR"」，请使用 battle 指令加入战役。");
                                break;
                }

                return;
        }

        if( !battle_start_flag )
                return;

        if( --battle_time_countdown <= 0 )
        {
                stop_battle();
                return;
        }

        if( sizeof(total) )
                auto_check();

        if( battle_time_countdown == 60 || battle_time_countdown == 180 )
                CHANNEL_D->channel_broadcast("war", HIR"战"NOR RED"争"HIR"：「"+battle_name+HIR"」即将在 "+(battle_time_countdown/60)+" 分钟后结束..."NOR);
}

void restore_status(object me)
{
        mapping my, cnd;
        string *ks;
        string where;
        int i;

        me->delete_override("unconcious");
        me->delete_override("die");
        me->delete_override("quit");
        delete_temp("override/receive_damage", me);
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->clear_condition();
        me->stop_busy();
        me->receive_damage("qi", 0);
        me->apply_killer(query_temp("backup/killer", me));
        me->apply_want(query_temp("backup/want", me));

        cnd=query("backup/condition", me);
        delete("backup/condition", me);
        delete_temp("block_msg/all", me);
        delete_temp("in_pkd", me);
        delete_temp("title", me);

        my = me->query_entire_dbase();
        if( my["qi"] < 1 )       my["qi"] = 1;
        if( my["eff_qi"] < 1 )   my["eff_qi"] = 1;
        if( my["jing"] < 1 )     my["jing"] = 1;
        if( my["eff_jing"] < 1 ) my["eff_jing"] = 1;

        if( stringp(where = query_temp("battle/leave_room", me)) )
        {
                if( where == "/inherit/room/chatroom" )
                        where = LEAVE_ROOM;
                me->move(where);
        }
        else
                me->move(LEAVE_ROOM);

        //delete_temp("battle", me);

        if( !mapp(cnd) ) return;
        ks = keys(cnd);
        for( i = 0; i < sizeof(ks); i++ )
            me->apply_condition(ks[i], cnd[ks[i]]);
}

int remove()
{
        if( sizeof(battle_player) )
        {
                object player;

                CHANNEL_D->channel_broadcast("war", HIR"战"NOR RED"争"HIR"：系统更新，重置「"+battle_name+HIR"」"NOR);

                foreach(string id in keys(battle_player))
                {
                        if( !objectp(player = find_player(id)) )
                                continue;

                        restore_status(player);
                        //player->move(LEAVE_ROOM);
                }
        }
        set_heart_beat(0);
}

void create()
{
        object ob;
        string *names;

        seteuid(ROOT_UID);

        names = get_dir(BATTLE_FIELD_DIR+ "*.c");
        names = map_array(names, (: $1[0..<3] :));

        // 析构所有的战场
        foreach (string name in names)
        {
                if (objectp(ob = find_object(BATTLE_FIELD_DIR + name)))
                {
                        ob->refresh_map();
                        destruct(ob);
                }
        }
}

string query_name()
{
        return "战场系统(BATTLEFIELD_D)";
}
