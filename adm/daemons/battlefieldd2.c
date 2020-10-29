// This program is a part of NT MudLIB
// battelfieldd.c

#include <ansi.h>

#define BATTLE_AREA             "battlefield"
#define BATTLE_NPC              ([ "/maze/battle/npc/berserker" : range_random(80, 100), "/maze/battle/npc/mars" : 10, ])
#define BATTLE_TIME             1200
#define BATTLE_JOIN_TIME        180
#define BATTLE_X_START          0
#define BATTLE_Y_START          0
#define BATTLE_X_END            9
#define BATTLE_Y_END            9
#define BATTLE_ROOM             "/maze/battle/"
#define ENTRY_ROOM              "/d/city/wumiao"

//string battle_name = HIY"荣耀"NOR YEL"之战"HIR;
string battle_name = HIY"门派"NOR YEL"荣耀"HIR;
object *battle_npc = allocate(0);
mapping battle_player = allocate_mapping(0);
object *total = allocate(0);

int battle_open_flag = 0;
int battle_start_flag = 0;
int battle_time_countdown = 0;
int battle_start_time = 0;
nosave int max_level = 300;

int check_out(object me);
private void restore_status(object me);
void add_damage_score(object me, int score);
void add_killplayer_score(object me, int score);
void add_killnpc_score(object me, int score);
void add_bouns_score(object me, int score);
void calculate_score();
void refresh_battlefield();

int clean_up()
{
        return 1;
}

int in_battle(object me)
{
        return battle_start_flag && !undefinedp(battle_player[me->query_id(1)]);
}

int inside_battlefield(object me)
{
        string room;
        object env = environment(me);

        if( !objectp(env) )
                return 0;

        room = base_name(env);
        if( !sscanf(room, BATTLE_ROOM "%*s") )
                return 0;

        return 1;
}

int query_battle_time()
{
        return battle_time_countdown;

}

int query_player_number(object player)
{
        return member_array(player->query_id(1), keys(battle_player)) + 1;
}

object query_random_site(int xstart, int xend, int ystart, int yend)
{
        object where;

        where = get_object(sprintf("/maze/battle/maze/%d/%d", range_random(xstart, xend), range_random(ystart, yend)));
        return where;
}

void move_to_random_site(object me)
{
        object site = query_random_site(BATTLE_X_START, BATTLE_X_END, BATTLE_Y_START, BATTLE_Y_END);

        me->move(site);
}

int is_battle_open()
{
        return battle_open_flag;
}

int is_battle_start()
{
        return battle_start_flag;
}

void init_player(object me)
{
        tell_object(me, HIY "你眼前忽然一花...\n" NOR);
        me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
        me->set_override("die", (: call_other, __FILE__, "check_out" :));
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        set_temp("override/receive_damage", (:call_other,__FILE__,"receive_damage":), me);
        set_temp("backup/killer", me->query_killer(), me);
        set_temp("backup/want", me->query_want(), me);
        set_temp("in_pkd", 1, me);

        tell_object(me, HIR "你被传送到战场中...。\n");
        set("backup/condition", me->query_condition(), me);
        me->clear_condition();

        if( !arrayp(total) )
                total = ({ me });
        else
        if( member_array(me, total) == -1 )
                total += ({ me });

        move_to_random_site(me);
}

// 参与战争
void join_battle(object me)
{
        mapping cnd;
        string id = me->query_id(1);

        if( me->is_busy() )
                return tell_object(me, BUSY_MESSAGE);

        if( me->is_fighting() )
                return tell_object(me, "你目前正在战斗中，还是先处理目前的对手再说吧。\n");

        if (me->is_in_prison()) 
                return tell_object(me, "你正在做牢呢，你想干什么？！\n"); 

        if (me->is_ghost()) 
                return tell_object(me, "你还是等还阳后再说吧！\n"); 

        if( sscanf(base_name(environment(me)), "/d/newbie/%s") )
                return tell_object(me, "你还没有正式闯到江湖呢，不能参加报名！\n");

        if( !battle_open_flag )
                return tell_object(me, battle_name+"目前无法报名。\n");

        if( query("combat_exp", me) < 1000000 )
                return tell_object(me, "你这点本事就别进去啦。\n");

        if( max_level && query("level", me) > max_level )
                return tell_object(me, "你就别进去欺负那些新鸟吧。\n");

        if( mapp(cnd = me->query_condition()) && sizeof(cnd))
        {
               if( !undefinedp(cnd["hunger"]) )
                        return tell_object(me, "你还是先找点吃的东西再说吧。\n");

               if( !undefinedp(cnd["killer"]) )
                        return tell_object(me, "官府正在通缉你，你还敢在这儿抛头露面？\n");

               if( !undefinedp(cnd["bandage"]) )
                        return tell_object(me, "你还是等包扎的伤口止住了血再说吧！\n");

               if( !undefinedp(cnd["putizi_drug"]) )
                        return tell_object(me, "你刚服完菩提子不久，好好运功夫吸纳吧！\n");

               if( !undefinedp(cnd["vote_clear"]) )
                        return tell_object(me, "现在玩家正在对你进行表决，你别到处乱走。\n");

                return tell_object(me, "你现在状态不佳，还是别进去了。\n");
        }

        if( !undefinedp(battle_player[id]) )
        {
                if( !battle_start_flag )
                        return tell_object(me, "你已经报名参与这次的战争，请耐心等候出征。\n");

                if( inside_battlefield(me) )
                        return tell_object(me, "你已经在战场中，快点杀敌吧。\n");

                if( !query_temp("battle_rejoin", me) )
                        return tell_object(me, "你必须使用战争勋章方可重新进入战场。\n");

                delete_temp("battle_rejoin", me);
                init_player(me);
                return;
        }

        battle_player[id] = allocate_mapping(0);
        battle_player[id]["jointime"] = time();

        CHANNEL_D->channel_broadcast("war", "目前共有 "+sizeof(battle_player)+
                                            " 位玩家报名参与「"+battle_name+"」");

        if( battle_start_flag )
        {
                init_player(me);
        }
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

        addn("honors", -100, me);
        if( query("honors", me) < 0 );
                set("honors", 0, me);

        CHANNEL_D->channel_broadcast("war", "目前共有 "+sizeof(battle_player)+
                                            " 位玩家报名参与「"+battle_name+"」");
}

int check_quit(object me)
{
        CHANNEL_D->channel_broadcast("war", "玩家" + me->name(1) +"在「"+battle_name+"」中临阵脱逃，溜走了。"NOR);
        restore_status(me);

        addn("honors", -500, me);
        if( query("honors", me) < 0 );
                set("honors", 0, me);

        if( arrayp(total) )
                total -= ({ me });

        tell_object(me, HIC "你一口气逃出了战场，来到扬州中央广场。\n" NOR);

        // continue run quit function
        me->move("/d/city/guangchang");
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
                add_damage_score(who, damage/3);

        return 0;
}

// check all the players who join the competition
private void auto_check()
{
        object ob;
//      string msg;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for (i = 0; i < sizeof(total); i++)
        {
                if( !objectp(total[i]) )
                        continue;
                room = base_name(environment(total[i]));
                if( !sscanf(room, BATTLE_ROOM "%*s"))
                {
                        // not in pk room
                        restore_status(total[i]);
                        total[i] = 0; // 保留报名参加战场的记录
                        continue;
                }
                if( query("qi", total[i])<1 || query("jing", total[i])<1 )
                        lost += ({ total[i] });
        }

        // kickout the players who lost competition
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
        if( !sscanf(room, BATTLE_ROOM "%*s") )
        {
                // not in pk room
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
                msg = me->name(1) + "惨遭" + ob->name(1) + "的毒手，被无情ＰＫ。\n";
                if( userp(ob) )
                {
                        if( userp(me) )
                        {
                                if( !query("doing", me) && query_ip_number(ob) != query_ip_number(me) )
                                if( me->query_family() != ob->query_family() )
                                        add_killplayer_score(ob, 1);
                        }
                        else
                        {
                                add_killnpc_score(ob, 1);
                                return 0;
                        }
                }
        } else
                 msg = me->name(1) + "运气不佳，本领有限、已经惨遭ＰＫ。\n";

        message("vision", msg, environment(me), ({ me }));

        restore_status(me);
        total -= ({ me });
        if( !playerp(me) )
        {
                destruct(me);
                return 1;
        }
        me->move(ENTRY_ROOM);
        message("vision", "一个黑影倏的窜了出来，随即就是“啪”的"
                "一声，就见" + me->name() +"摔倒了地上，一副半死不"
                "活的样子。\n", environment(me), ({ me }));
        tell_object(me, "半昏半迷中，你觉得被人拎了起来，又"
                "重重的摔倒了地上。\n");

        if( !living(me) )
                me->revive();

        return 1;
}

void add_npc(string file)
{
        object site = query_random_site(BATTLE_X_START, BATTLE_X_END, BATTLE_Y_START, BATTLE_Y_END);
        object npc = new(file);

        npc->set_override("die", (: call_other, __FILE__, "check_out" :));
        set_temp("override/receive_damage", (:call_other,__FILE__,"receive_damage":), npc);
        set_temp("battle_npc", 1, npc);
        battle_npc += ({ npc });
        npc->move(site);
        tell_room(site, HIY+npc->query_idname()+HIY"突然从角落窜了出来！\n"NOR);
}

// 启动战争
void start_battle()
{
        object player;
        object* unavailable_players = allocate(0);

        if( sizeof(battle_player) < 5 )
        {
                set_heart_beat(0);
                total = allocate(0);
                battle_player = allocate_mapping(0);
                battle_open_flag = 0;
                battle_start_time = 0;
                CHANNEL_D->channel_broadcast("war", "报名参与「"+battle_name+"」战役的玩家不足 5 人，取消本次战役。");
                return;
        }

        foreach(string file, int count in BATTLE_NPC)
        {

                while(count--)
                        add_npc(file);
        }

        CHANNEL_D->channel_broadcast("war", "「"+battle_name+"」开始出征！共计 "+sizeof(battle_player)+
                                            " 位玩家参与「"+battle_name+"」，计时 "+(BATTLE_TIME/60)+" 分钟结束");


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

                init_player(player);
                //tell_object(player, "\a「"+battle_name+"」开始，你被传送到战场中...\n");
        }

        foreach(player in unavailable_players)
                cancel_battle(player);

        battle_start_flag = 1;
        battle_time_countdown = BATTLE_TIME;
}

// 开始接受报名 TIME_D 调用
varargs void start_join(string level)
{
        CHANNEL_D->channel_broadcast("war", HIY"荣耀"NOR YEL"之战"HIR"发出战争集结，即将在 "+(BATTLE_JOIN_TIME/60)+
                                            " 分钟后发动「"+battle_name+"」("+level+"级)，请使用 fbattle 指令加入战役。");

        total = allocate(0);
        battle_npc = allocate(0);
        battle_player = allocate_mapping(0);
        battle_open_flag = 1;

        battle_start_time = BATTLE_JOIN_TIME;
        if( level ) max_level = to_int(level);

        set_heart_beat(1);

        //tell_object(users(), "\a");
}

int get_player_score(string id)
{
        if( undefinedp(battle_player[id]) ) return 0;

        return battle_player[id]["killplayer"]*100 + battle_player[id]["killnpc"]*3 + (battle_player[id]["damage"]/500000>500?500:battle_player[id]["damage"]/500000) + battle_player[id]["bonus"];
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

        if( undefinedp(battle_player[id]) )
            return;

        battle_player[id]["killplayer"] += score;

        return;
}

void add_dead_score(object me, int score)
{
        string id = me->query_id(1);
        string *sorted_players = get_sorted_players();

        if( undefinedp(battle_player[id]) )
                return;

        if( sizeof(sorted_players) > 0 && sorted_players[0] == id )

                battle_player[id]["bonus"] -= 40;

        battle_player[id]["dead"] += score;
}


void add_bonus_score(object me, int score)
{
        string id = me->query_id(1);

        if( undefinedp(battle_player[id]) )

            return;

        battle_player[id]["bonus"] += score;
        //addn("honors", score, me);

        return;
}

/*
void remove_battlefield_condition(object player)
{
        player->clear_condition(BATTLEFIELD_EXPERIENCE);
        player->clear_condition(BATTLEFIELD_GLORY);
        player->clear_condition(BATTLEFIELD_FEAR);
}
*/
void stop_battle()
{
        object player;

        set_heart_beat(0);

        foreach(string id in keys(battle_player))
        {
                if( !objectp(player = find_player(id)) )
                        continue;

                //player->remove_all_killer();
                player->remove_all_enemy(1);
        }

        foreach(object npc in battle_npc)
        {
                if( !objectp(npc) )
                        continue;

                destruct(npc);
        }

        battle_open_flag = 0;
        battle_start_flag = 0;
        battle_time_countdown = 0;

        call_out((: calculate_score :), 5);

        CHANNEL_D->channel_broadcast("war", WHT"————————————————————————————————"NOR);
        CHANNEL_D->channel_broadcast("war", "「"+battle_name+HIR"」终于渐渐平息..."NOR);
        CHANNEL_D->channel_broadcast("war", "「"+battle_name+HIR"」正在统计战绩..."NOR);
        CHANNEL_D->channel_broadcast("war", WHT"————————————————————————————————"NOR);
}

void calculate_score()
{
        int score;
        int rank;
        mapping famscore = allocate_mapping(0);
        string family;
        object player;
//      string file;
        object insigne;
        int insigne_count;
        string *sorted_players = get_sorted_players();
        int lv1,lv2,lv3,lv4;
        int players_count = sizeof(sorted_players);

        map_delete(battle_player, 0);

        CHANNEL_D->channel_broadcast("war", WHT"————————————————————————————————"NOR);

        lv2 = players_count/4;
        if( lv2 < lv1+2 ) lv2 = lv1+2;

        lv3 = to_int(players_count/1.5);
        if( lv3 < lv2+3 ) lv3 = lv2+3;

        lv4 = to_int(players_count/1.2);
        if( lv4 < lv3+5 ) lv4 = lv3+5;

        rank = 0;
        foreach(string id in sorted_players)
        {
                if( !objectp(player = find_player(id)) )
                        continue;

                family = player->query_family();
                score = get_player_score(id);

                CHANNEL_D->channel_broadcast("war", (++rank)+"."+(family||"普通百姓")+"的"+player->query_idname()+HIR"共击杀 "+battle_player[id]["killplayer"]+" 位玩家、"+battle_player[id]["killnpc"]+" 个NPC，总计造成敌人 "+NUMBER_D->number_symbol(battle_player[id]["damage"])+" 点伤害，战绩结算为 "+NUMBER_D->number_symbol(score)+(battle_player[id]["bonus"]>=0 ? "("NOR CYN"+"HIC+battle_player[id]["bonus"]+HIR")":"("NOR RED"-"HIR+(-battle_player[id]["bonus"])+HIR")")+" 分");

                if( undefinedp(famscore[family]) )
                        famscore[family] = allocate_mapping(0);

                //if( famscore[family]["score"] < score )
                        famscore[family]["score"] += score;

                famscore[family]["player"] += 1;
                
                addn("battle/score", score, player);
                addn("honors", score, player);
                
                if( score > 2000 ) score = 2000;
                        GIFT_D->delay_battle_bonus(player, ([ "exp" : score*3000, "pot" : score*1000, "mar" : score*300, "score" : score ]));

                if( score < 25 || battle_player[id]["jointime"] > time() - 600 ) continue;

                insigne_count = 0;

                if( rank <= lv1 )
                {
                        insigne_count = 8;
                }
                else if( rank <= lv2 )
                {
                        insigne_count = 7;
                }
                else if( rank <= lv3 )
                {
                        insigne_count = 7;
                }
                else if( rank <= lv4 )
                {
                        insigne_count = 6;
                }
                else
                {
                        insigne_count = 2;
                }

                if( insigne_count > 0 )
                {
                        insigne = new("/clone/battle/battle_insigne");
                        insigne->set_amount(insigne_count);
                        tell_object(player, "你获得 "+insigne_count+" 枚"+insigne->name(1)+"。\n");
                        insigne->move(player, 1);
                }
        }

        CHANNEL_D->channel_broadcast("war", WHT"————————————————————————————————"NOR);
        rank = 0;
        foreach(family in sort_array(keys(famscore), (: $(famscore)[$2]["score"] - $(famscore)[$1]["score"] :)))
        {
                CHANNEL_D->channel_broadcast("war", (family||"普通百姓")+"的战绩计算结果为 "+NUMBER_D->number_symbol(famscore[family]["score"])+"，获得门派排名第 "+(++rank)+" 名。\n");    
                
                switch(rank)
                {
                        case 1:
                                switch(random(3))
                                {
                                        case 0:
                                                CHANNEL_D->channel_broadcast("news", family+"所有弟子在接下来四小时内所有主流任务经验奖励增加一倍！\n");
                                                FAMILY_D->set_family_efficient(family, "exp", 14400);
                                                break;
                                        case 1:
                                                CHANNEL_D->channel_broadcast("news", family+"所有弟子在接下来四小时内所有主流任务潜能奖励增加一倍！\n");
                                                FAMILY_D->set_family_efficient(family, "pot", 14400);
                                                break;
                                        case 2:
                                                CHANNEL_D->channel_broadcast("news", family+"所有弟子在接下来四小时内掉宝率提高两成！\n");
                                                FAMILY_D->set_family_efficient(family, "mf", 14400);
                                                break;
                                        case 3:
                                                CHANNEL_D->channel_broadcast("news", family+"所有弟子在接下来四小时内研究效果增加一倍！\n");
                                                FAMILY_D->set_family_efficient(family, "yanjiu", 14400);
                                                break;
                                }                               
                                CHANNEL_D->channel_broadcast("news", family+"门派威望提高八百点。！\n");
                                FAMILY_D->add_family_fame(family, 800);
                                break;
                        case 2:
                                switch(random(3))
                                {
                                        case 0:
                                                CHANNEL_D->channel_broadcast("news", family+"所有弟子在接下来二小时内所有主流任务经验奖励增加一倍！\n");
                                                FAMILY_D->set_family_efficient(family, "exp", 7200);
                                                break;
                                        case 1:
                                                CHANNEL_D->channel_broadcast("news", family+"所有弟子在接下来二小时内所有主流任务潜能奖励增加一倍！\n");
                                                FAMILY_D->set_family_efficient(family, "pot", 7200);
                                                break;
                                        case 2:
                                                CHANNEL_D->channel_broadcast("news", family+"所有弟子在接下来二小时内掉宝率提高两成！\n");
                                                FAMILY_D->set_family_efficient(family, "mf", 7200);
                                                break;
                                        case 3:
                                                CHANNEL_D->channel_broadcast("news", family+"所有弟子在接下来二小时内研究效果增加一倍！\n");
                                                FAMILY_D->set_family_efficient(family, "yanjiu", 7200);
                                                break;
                                }                               
                                CHANNEL_D->channel_broadcast("news", family+"门派威望提高五百点。！\n");
                                FAMILY_D->add_family_fame(family, 500);
                                break;
                        default:
                                break;
                }
        }
        
        CHANNEL_D->channel_broadcast("combat", WHT"————————————————————————————————"NOR);

        //foreach(string id in keys(battle_player))
        foreach(player in total)
        {
                //if( !objectp(player = find_player(id)) )
                if( !objectp(player) )
                        continue;

                restore_status(player);
                player->move(ENTRY_ROOM);

                tell_object(player, "「"+battle_name+"」结束，你被传离战场...\n");

        }

        total = allocate(0);
        battle_npc = allocate(0);
        battle_player = allocate_mapping(0);
        refresh_battlefield(); 
}


mapping query_battle_player()
{
        return battle_player;
}

void refresh_battlefield()
{
        object maze;

        if( maze = find_object("/maze/battle/maze.c") )
                destruct(maze);
}

int remove()
{
        if( sizeof(battle_player) )
        {
                object player;

                CHANNEL_D->channel_broadcast("war", "系统更新，重置「"+battle_name+HIR"」"NOR);

                foreach(string id in keys(battle_player))
                {
                        if( !objectp(player = find_player(id)) )
                                continue;

                        restore_status(player);
                        player->move(ENTRY_ROOM);
                }
        }

        if( sizeof(battle_npc) )
        {
                foreach(object npc in battle_npc)
                {
                        if( !objectp(npc) )
                                continue;

                        destruct(npc);
                }
        }

        refresh_battlefield();
        return 1;
}

void heart_beat()
{
        string *directions = ({ "north", "south", "east", "west" });
        object where;

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
                                                                    " 分钟后发动「"+battle_name+"」，请使用 fbattle 指令加入战役。");
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

        auto_check();

        if( battle_time_countdown == 900 || battle_time_countdown == 600 || battle_time_countdown == 300 )
        {
                foreach(string file, int count in BATTLE_NPC)
                {
                        while(count--)
                                add_npc(file);
                }
        }

        if( battle_time_countdown == 60 || battle_time_countdown == 180 )
                CHANNEL_D->channel_broadcast("war", "「"+battle_name+"」即将在 "+(battle_time_countdown/60)+" 分钟后结束...");

        if( !(battle_time_countdown%90) )
        {
                object statue;

                if( !random(2) )
                        statue = new("/clone/battle/battlefield_glory_statue");
                else
                        statue = new("/clone/battle/battlefield_fear_statue");

                where = query_random_site(BATTLE_X_START+4, BATTLE_X_END-4, BATTLE_Y_START+4, BATTLE_Y_END-4);

                statue->move(where);

                CHANNEL_D->channel_broadcast("war", "具有强大神秘力量的石碑出现在"+where->short()+"附近...");
                //【战斗】21:07 战争：一笑置之(Eugene)获得「战争荣耀」加持，持续 2 分钟，目标座标为<maze 1 49,36>，击败此人可获得大量战绩
        }

/*
        if( !(battle_time_countdown%60) )
        {
                object player;
                string* sorted_players = get_sorted_players();
                int size = sizeof(sorted_players);

                for(int i=size*2/3;i<size;++i)
                {
                        if( objectp(player = find_player(sorted_players[i])) )
                        {
                                if( !inside_battlefield(player) ) continue;
                                tell_object(player, "你目前的战绩落后，获得额外能力加持。\n");

                                //player->apply_condition(BATTLEFIELD_EXPERIENCE);

                                //if( i > size*4/5 )
                                        //player->apply_condition(BATTLEFIELD_EXPERIENCE);
                        }
                }
        }
*/
        foreach(object npc in battle_npc)
        {
                if( !objectp(npc) )
                        continue;

                if( !random(10) )
                {

                        if( npc->is_fighting() )
                                continue;

                        if( sizeof(directions) )
                                npc->do_command("go "+directions[random(sizeof(directions))]);
                }
        }

        battle_npc -= ({ 0 });
}

private void restore_status(object me)
{
        mapping my, cnd;
        string *ks;
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
        delete_temp("apply/short", me);

        if( !mapp(cnd) ) return;
        ks = keys(cnd);
        for( i = 0; i < sizeof(ks); i++ )
            me->apply_condition(ks[i], cnd[ks[i]]);

        my = me->query_entire_dbase();
        if( my["qi"] < 1 )       my["qi"] = 1;
        if( my["eff_qi"] < 1 )   my["eff_qi"] = 1;
        if( my["jing"] < 1 )     my["jing"] = 1;
        if( my["eff_jing"] < 1 ) my["eff_jing"] = 1;
}

void create()
{
        seteuid(ROOT_UID);
}

string query_name()
{
        return "战场系统(BATTLEFIELD_D)";
}