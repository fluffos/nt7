// This program is a part of NT MudLIB
// battelfieldd.c

#include <ansi.h>

#define BATTLE_TIME             900
#define BATTLE_JOIN_TIME        300
#define BATTLE_ROOM             "/maze/jingcheng/"
#define ENTRY_ROOM              "/d/city/wumiao"

string battle_name = HIY"门派"NOR HIR"仇杀"HIR;
object *battle_npc = allocate(0);
mapping battle_player = allocate_mapping(0);
object *total = allocate(0);

int battle_open_flag = 0;
int battle_start_flag = 0;
int battle_time_countdown = 0;
int battle_start_time = 0;

int check_out(object me);
private void restore_status(object me);
void add_damage_score(object me, int score);
void add_killplayer_score(object me, int score);
void add_killnpc_score(object me, int score);
void add_bouns_score(object me, int score);
void calculate_score();

mapping area=([
        "西城" : ({"/maze/jingcheng/","dadao36","dadao35","dadao34","dadao33","dadao32",
         "dadao31","dadao30","dadao29","dadao28","dadao27","dadao26","dadao25",
         "dadao24","dadao23","dadao22","dadao21","dadao20","dadao19","dadao18",
         "dadao17","dadao16","dadao15","dadao14","dadao13","dadao12","dadao11",
         "dadao10","dadao9","dadao8","dadao7"
          }),
        "东城" : ({"/maze/jingcheng/","dao1","dao2","dao3","dao4","dao5",
         "dao6","dao7","dao8","dao9","dao10","dao11","dao12",
         "dao13","dao14","dao15","dao16","dao17","dao18","dao19",
         "dao20","dao21","dao22","dao23","dao24","dao25","dao26",
         "dao27","dao28","dao29","dao30"
          })
]);

mapping menpai1=([
        "玄慈大师":   "少林派",
        "宋远桥":     "武当派",
        "灭绝师太":   "峨嵋派",
        "洪七公":     "丐帮",
        "岳不群":     "华山派",
        "张无忌":     "明教",
        "小龙女":     "古墓派",
        "丘处机":     "全真教",
]);

mapping menpai2=([
        "丁春秋":     "星宿派",
        "洪安通":     "神龙教",
        "血刀老祖":   "血刀门",
        "欧阳峰":     "欧阳世家",
        "慕容复":     "慕容世家",  
        "苏星河":     "逍遥派",
        "天山童姥":   "灵鹫宫",
        "鸠摩智":     "雪山寺",   
]);
string *master1=({
        "玄慈大师",
        "宋远桥",
        "灭绝师太",
        "洪七公",
        "岳不群",
        "张无忌",
        "小龙女",
        "丘处机",
});

string *master2=({
        "丁春秋",
        "洪安通",
        "血刀老祖",
        "欧阳峰",
        "慕容复",
        "苏星河",
        "天山童姥",
        "鸠摩智",
});

nosave string fam1;
nosave string fam2;

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

void move_to_site(object me)
{
        if( objectp(me) && query_temp("chousha/fam", me) )
        {
                if( query_temp("chousha/fam", me) == fam2 )
                        me->move("/maze/jingcheng/juyi");
                else if( query_temp("chousha/fam", me) == fam1 )
                        me->move("/maze/jingcheng/yingxiong");
        }
        message_vision(YEL"$N一路马不停蹄，连夜赶到了紫禁城！\n"NOR, me);
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

        //tell_object(me, HIR "你被传送到战场中...。\n");
        set("backup/condition", me->query_condition(), me);
        me->clear_condition();

        if( !arrayp(total) )
                total = ({ me });
        else
        if( member_array(me, total) == -1 )
                total += ({ me });
        
        if( query_temp("chousha/fam",me)==fam2 )
        {
                set_temp("apply/short", 
                                ({HIW+fam1+"同道"NOR+HIG"   江湖义士   "NOR+query("name",me)+"("+query("id",me)+")"}),me);
        } 
        else if( query_temp("chousha/fam",me)==fam1 )
        {
                set_temp("apply/short", 
                                ({CYN+fam2+"助拳"NOR+HIG"   江湖豪客   "NOR+query("name",me)+"("+query("id",me)+")"}),me);
        }
        move_to_site(me);
}

// 参与战争
void join_battle(object me)
{
        mapping cnd;
        string id = me->query_id(1);
        string temp;
        int exp, exp_rate;
        
        if( me->is_busy() )
                return tell_object(me, BUSY_MESSAGE);

        if( me->is_fighting() )
                return tell_object(me, "你目前正在战斗中，还是先处理目前的对手再说吧。\n");

        if (me->is_in_prison()) 
                return tell_object(me, "你正在做牢呢，你想干什么？！\n"); 

        if (me->is_ghost()) 
                return tell_object(me, "你还是等还阳后再说吧！\n"); 

        if( !battle_open_flag )
                return tell_object(me, battle_name+"目前无法报名。\n");

        if( query("combat_exp",me)<1000000 )
                return tell_object(me, CYN"凭你现在这点本事，不相干的事还是不要多管的好！\n"NOR);

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
                
                if( !query_temp("chousha/fam", me) )
                        return tell_object(me, "你还是等下一场门派仇杀吧。\n");
                        
                if( !query_temp("chousha_rejoin", me) )
                        return tell_object(me, "你必须使用仇杀勋章方可重新进入战场。\n");

                delete_temp("chousha_rejoin", me);
                init_player(me);
                return;
        }
        
        exp=query("combat_exp", me);
        temp=read_file("/quest/quest4/exp_rate",1,1);
        exp_rate=atoi(temp);
        if( !wizardp(me) && (exp_rate*exp_rate/4) < exp/100000 )
        {
              do{
                        exp_rate++;
                }       while( (exp_rate*exp_rate/4) < exp/100000 );

                temp=sprintf("%d",exp_rate);
                write_file("/quest/quest4/exp_rate",temp,1);  
        }

        if( query_temp("chousha/fam", me) )
        {
                CHANNEL_D->channel_broadcast("mess", query("name",me)+"报名加入门派仇杀对付门派"+query_temp("chousha/fam",me)+"！\n");
                
        } else
        if( query("shen",me) >= 200000 || (query("shen",me) > -200000 && random(2)) )  
        {
                set_temp("chousha/fam",fam2,me);
                CHANNEL_D->channel_broadcast("mess", query("name",me)+"报名加入门派仇杀对付门派"+fam2+"！\n");
        } else
        {
                set_temp("chousha/fam",fam1,me);
                CHANNEL_D->channel_broadcast("mess", query("name",me)+"报名加入门派仇杀对付门派"+fam1+"！\n");
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
                                if( query_temp("chousha/fam", me) != query_temp("chousha/fam", ob) )
                                        add_killplayer_score(ob, 1);
                        }
                        else
                        {
                                if( query_temp("chousha/fam", me) != query_temp("chousha/fam", ob) )
                                        add_killnpc_score(ob, 1);
                                return 0;
                        }
                } 
        } else
                 msg = me->name(1) + "运气不佳，本领有限、已经惨遭ＰＫ。\n";
        
        if( !userp(me) ) return 0;
        
        message("vision", msg, environment(me), ({ me }));

        restore_status(me);
        total -= ({ me });
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

int place_room(string site_name,object ob)
{
        string *location, site_file;
        int size;

        location = area[site_name];
        size = sizeof(location);
        site_file=location[0]+location[random(size-1)+1];
        set("area",site_name, ob);
        set("place_name",site_file,ob);
        set_temp("override/receive_damage", (:call_other,__FILE__,"receive_damage":), ob); 
        ob->move(site_file);
        tell_room(site_file, HIY+ob->query_idname()+HIY"突然从角落窜了出来！\n"NOR);
        return 1;
}

void add_npc(int n)
{
        int i;
        object killer1, killer2;
        
        for( i=0; i<n; i++ )
        {
                if( sizeof(children("/quest/quest4/killer1.c")) < 80 )
                { 
                        killer1 = new("/quest/quest4/killer1");
                        place_room("西城",killer1);
                        killer1->start_escape(900);
                        killer1->set_override("die", (: call_other, __FILE__, "check_out" :));
                        set_temp("battle_npc", 1, killer1);
                        battle_npc += ({ killer1 });
                }
                if( sizeof(children("/quest/quest4/killer2.c")) < 80 )
                { 
                        killer2 = new("/quest/quest4/killer2");
                        place_room("东城",killer2);
                        killer2->start_escape(900);
                        killer2->set_override("die", (: call_other, __FILE__, "check_out" :));
                        set_temp("battle_npc", 1, killer2);
                        battle_npc += ({ killer2 });
                }
        }      
}

// 启动战争
void start_battle()
{
        int n;
        object player;
        object* unavailable_players = allocate(0);

        if( sizeof(battle_player) < 2 )
        {
                set_heart_beat(0);
                total = allocate(0);
                battle_player = allocate_mapping(0);
                battle_open_flag = 0;
                battle_start_time = 0;
                CHANNEL_D->channel_broadcast("war", "报名参与「"+battle_name+"」战役的玩家不足 2 人，取消本次战役。");
                return;
        }
        
        n = sizeof(battle_player)*15;
        if( n > 100 ) n = 100;
        add_npc(n);
        
        CHANNEL_D->channel_broadcast("mess", HIR+fam1+HIC"与"+HIR+fam2+HIC"两大门派积怨已久，此刻正在紫金城正相互仇杀。"NOR);
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
void start_join()
{
        int i,j,k;
        object *ulist;
        
        i = random(sizeof(master1));
        j = random(sizeof(master2));
        ulist = users();
        k = sizeof(ulist);

        fam1 = menpai1[master1[i]];
        fam2 = menpai2[master2[j]];
        while( k-- )
        {
                if( !environment(ulist[k]) ) continue;
                delete_temp("chousha", ulist[k]);
                
                if( ulist[k]->query_family() == fam1 )
                        set_temp("chousha/fam",fam2,ulist[k]);
                else if( ulist[k]->query_family() == fam2 )
                        set_temp("chousha/fam",fam1,ulist[k]);
        }

        write_file("/quest/quest4/fam1",fam1,1);
        write_file("/quest/quest4/fam2",fam2,1); 
                                
        CHANNEL_D->channel_broadcast("mess", master1[i]+"："+fam1+"门下弟子听令，命你们在半个时辰内将"+fam2+"彻底击溃，以匡武林正义！"); 
        CHANNEL_D->channel_broadcast("mess", master2[j]+"："+fam2+"弟子听令，命你们在半个时辰内将"+fam1+"彻底荡平，让他们尝尝我们的厉害！");
        CHANNEL_D->channel_broadcast("war", HIY"荣耀"NOR YEL"之战"HIR"发出战争集结，即将在 "+(BATTLE_JOIN_TIME/60)+
                                            " 分钟后发动「"+battle_name+"」，请使用 chousha join 指令加入战役。");
        total = allocate(0);
        battle_npc = allocate(0);
        battle_player = allocate_mapping(0);
        battle_open_flag = 1;

        battle_start_time = BATTLE_JOIN_TIME;

        set_heart_beat(1);

        //tell_object(users(), "\a");
}

int get_player_score(string id)
{
        if( undefinedp(battle_player[id]) ) return 0;

        return battle_player[id]["killplayer"]*100 + battle_player[id]["killnpc"]*30 + (battle_player[id]["damage"]/500000>1500?1500:battle_player[id]["damage"]/500000) + battle_player[id]["bonus"];
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

void stop_battle()
{
        object player;
        object *ulist;
        int k;

        ulist = users();
        k = sizeof(ulist);

        while( k-- )
        {
                if( !environment(ulist[k]) ) continue;
                if( query_temp("chousha", ulist[k]) )
                {
                        delete_temp("chousha", ulist[k]);
                } 
        }

        CHANNEL_D->channel_broadcast("mess", "历时半月的"+fam1+"与"+fam2+"之间的仇杀终于结束了，双方皆死伤无数！");
        
        set_heart_beat(0);

        foreach( string id in keys(battle_player))
        {
                if( !objectp(player = find_player(id)) )
                        continue;

                //player->remove_all_killer();
                player->remove_all_enemy(1);
                tell_object(player, BLINK"忽然你心中生起一股厌倦的感觉，"
                                    "开始疑惑的这样的江湖仇杀有何意义，\n"
                                    "你看着自己沾满鲜血的手，开始不断地问自己为什么？为什么？.....\n"NOR);
        }

        foreach( object npc in battle_npc )
        {
                if( !objectp(npc) )
                        continue;

                destruct(npc);
        }
        
        fam1 = fam2 = "";
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
                
                addn("battle/score", score, player);
                addn("honors", score, player);
                
                if( score > 5000 ) score = 5000;
                        GIFT_D->delay_battle_bonus(player, ([ "exp" : score*2000, "pot" : score*600, "mar" : score*100, "gongxian": score*10, "score" : score ]));

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
                        insigne = new("/clone/battle/chousha_insigne");
                        insigne->set_amount(insigne_count);
                        tell_object(player, "你获得 "+insigne_count+" 枚"+insigne->name(1)+"。\n");
                        insigne->move(player, 1);
                }
        }

        CHANNEL_D->channel_broadcast("war", WHT"————————————————————————————————"NOR);

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
}


mapping query_battle_player()
{
        return battle_player;
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
        fam1 = fam2 = "";
        return 1;
}

void heart_beat()
{
//      mapping buff,data;
        string *directions = ({ "north", "south", "east", "west" });
//      object where;
//      int i;
        
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
                        case 240:
                                CHANNEL_D->channel_broadcast("mess", HIB"据可靠消息，会有两大门派在不久以后大火拼。");
                                CHANNEL_D->channel_broadcast("war", HIY"荣耀"NOR YEL"之战"HIR"发出战争集结，即将在 "+(battle_start_time/60)+
                                                                    " 分钟后发动「门派仇杀」，请使用chousha join加入战役。");
                                break;
                        case 270:                               
                                CHANNEL_D->channel_broadcast("mess", HIR "据说江湖中某两大门派为解宿怨，半个时辰内要以武力解决。");
                                CHANNEL_D->channel_broadcast("war", HIY"荣耀"NOR YEL"之战"HIR"发出战争集结，即将在 "+(battle_start_time/60)+
                                                                    " 分钟后发动「门派仇杀」，请使用chousha join加入战役。");  
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

        if( !(battle_time_countdown%120) )
        {
                add_npc(sizeof(battle_player)*8);
        }

        if( battle_time_countdown == 60 || battle_time_countdown == 180 )
                CHANNEL_D->channel_broadcast("war", "「门派仇杀」即将在 "+(battle_time_countdown/60)+" 分钟后结束...");

/* 因为被利用这个buff吸内力，故而关闭
        if( !(battle_time_countdown%60) )
        {
                object player;
                string* sorted_players = get_sorted_players();
                int size = sizeof(sorted_players);

                for( i=size*2/3;i<size;++i )
                {
                        if( objectp(player = find_player(sorted_players[i])) )
                        {
                                if( !inside_battlefield(player) ) continue;
                                
                                if( BUFF_D->check_buff(player, "chousha_bonus") ) continue;
                                
                                //tell_object(player, pnoun(2, player)+"目前的战绩落后，获得额外能力加持。\n");
                                
                                if( i > size*4/5 )
                                {
                                        data = ([
                                                "attack": player->query_skill("force",1),
                                                "defense":player->query_skill("dodge",1),
                                                "add_skill": player->query_skill("parry",1)/10,
                                        ]);
                                } else
                                {
                                        data = ([
                                                "attack": player->query_skill("force"),
                                                "defense":player->query_skill("dodge"),
                                                "add_skill": player->query_skill("parry")/10,
                                        ]);
                                }
                                
                                buff = ([
                                        "caster":player,
		                        "target":player,
		                        "type":"chousha_bonus",
		                        "attr":"bless",
		                        "name":"战场荣耀·能力加持",
		                        "time":battle_time_countdown,
		                        "buff_data":data,
		                        "buff_msg":HIY"$N目前的战绩落后，获得额外能力加持。\n"NOR,
		                        "disa_msg":"你的战场荣耀·能力加持逐渐消失。\n",
                                ]);
                                BUFF_D->buffup(buff);
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