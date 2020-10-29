// timed.c

#include <ansi.h>
#include <localtime.h>
#include <mudlib.h>

inherit F_DBASE;

#define CRONTAB         "/adm/etc/crontab"
#define MAZE_DOOR       "/clone/misc/maze_door1"

#define MIN             0
#define HOUR            1
#define WDAY            2
#define MDAY            3
#define MON             4
#define YEAR            5

int gametime;
nosave int realtime;
nosave int tick;
nosave mapping event = allocate_mapping(0);
nosave int *real_time = allocate(6);
nosave int *game_time = allocate(6);
nosave int ready = 0;
protected void init_crontab();

class cron_item
{
        int flag;               // flag 0 现实生活; flag 1 游戏中
        string time;            // 时间
        string file;            // 触发物件的文件名
        string func;            // 触发函数
        string *args;           // 触发函数中的参数
}

class cron_item *all_items = ({});
mixed query_all_items() { return all_items; }

protected void out(string str)
{
        log_file("timed", str);
}

int clean_up()
{
        CHANNEL_D->channel_broadcast("news", 
                HIR + "MudOS CLEAN UP ALL NO ENVIRONMENT OBJECTS…\n" + NOR);   
        return 1;
}
void auto_relaim()
{
        int i;
        int cpu_cost;

        if (uptime() < 24000)
                call_other("/d/dongtian/create_d", "start");

        if (i = reclaim_objects())
                CHANNEL_D->do_channel( this_object(), "sys",
                        sprintf("系统自动清除 %d 个变量。", i));

        cpu_cost = CPU_D->get_current_cpu_cost();

        // cpu过高则降低mudos心跳
     
        if( cpu_cost >= 95 && (int)get_config(__RC_HEARTBEAT_INTERVAL_MSEC__) == 1000 )
        {
                set_config(__RC_HEARTBEAT_INTERVAL_MSEC__, 2000);
                log_file("heartbeat", sprintf("System changed mudOS heartbeat to 2 at %s\n", TIME_D->replace_ctime(time())));
        } 
        else 
        if( cpu_cost <= 65 && (int)get_config(__RC_HEARTBEAT_INTERVAL_MSEC__) > 1000 )
        {
                set_config(__RC_HEARTBEAT_INTERVAL_MSEC__, 1000);
                log_file("heartbeat", sprintf("System changed mudOS heartbeat to 1 at %s\n", TIME_D->replace_ctime(time())));
        }
}

protected void init_crontab()
{
        string *table, *time_zone;
        class cron_item item;
        int flag/*, legal = 0*/;
        object ob;
        string *items;
        int i, n;

        all_items = ({});

        if( file_size(CRONTAB) < 0 )
                return;

        items =  filter_array(explode(read_file(CRONTAB), "\n") - ({ "" }), (: $1[0] != '#' :));

        if( !n = sizeof(items) )
                return;

        for( i=0; i<n; i++ ) {
                reset_eval_cost();
                table = explode(items[i]," ");
                if( sizeof(table) < 3 ) {
                        out(sprintf("以下任务格式错误：\n%s\n\n",items[i]));
                        continue;
                }
                time_zone = explode(table[0],":");
                if( sizeof(time_zone) < 7 ) {
                        out(sprintf("以下任务时间部分格式错误：\n%s\n\n",items[i]));
                        continue;
                }

                if( file_size(table[1]+".c") < 0 ) {
                        out(sprintf("以下任务触发物件档案不存在：\n%s\n\n",items[i]));
                        continue;
                }
                if( !ob = find_object(table[1]) )
                        ob = load_object(table[1]);
                if( !ob ) {
                        out(sprintf("以下任务触发物件无法载入：\n%s\n\n",items[i]));
                        continue;
                }
                if( !function_exists(table[2],ob) ) {
                        out(sprintf("以下任务触发物件中触发函数不存在：\n%s\n\n",items[i]));
                        continue;
                }
                if( sscanf(time_zone[0],"%d",flag) ) {
                        if( (flag != 0) && (flag != 1) ) {
                                out(sprintf("以下任务 flag 格式错误：\n%s\n\n",items[i]));
                                continue;
                        }

                } else {
                        out(sprintf("以下任务 flag 格式错误：\n%s\n\n",items[i]));
                        continue;
                }

                item = new(class cron_item);

                item->file = table[1];
                item->func = table[2];
                item->args = table[3..];
                item->flag = flag;
                item->time = implode(time_zone[1..], " ");
                all_items += ({ item });
        }

        if( sizeof(all_items) )
                ready = 1;
}

// 可取代 call_out 之功能
void add_event(function fevent, int delay_time)
{
        if( !sizeof(event) || !event[fevent] )
                event = ([ fevent : delay_time ]);
        else
                event[fevent] = delay_time;
}

// 执行事件
void exec_event(function fevent)
{
        if( objectp(function_owner(fevent)) )
                evaluate(fevent);

        map_delete(event, fevent);
}

string replace_ctime(int t)
{
        string month, ctime = ctime(t);

        switch(ctime[4..6])
        {
                case "Jan"      :       month = "01";break;
                case "Feb"      :       month = "02";break;
                case "Mar"      :       month = "03";break;
                case "Apr"      :       month = "04";break;
                case "May"      :       month = "05";break;
                case "Jun"      :       month = "06";break;
                case "Jul"      :       month = "07";break;
                case "Aug"      :       month = "08";break;
                case "Sep"      :       month = "09";break;
                case "Oct"      :       month = "10";break;
                case "Nov"      :       month = "11";break;
                case "Dec"      :       month = "12";break;
        }

        return sprintf("%s/%s/%s %s", month, (ctime[8]==' '?"0"+ctime[9..9]:ctime[8..9]), ctime[<4..<1], ctime[11..15]);
}

string season_period(int m)
{
        switch(m)
        {
                case 2..4:      return "春";
                case 5..7:      return "夏";
                case 8..10:     return "秋";
                case 11:        return "冬";
                case 0..1:      return "冬";
                default:        return 0;
        }
}

string week_period(int w)
{
        switch(w)
        {
                case 0:         return "日";
                case 1:         return "一";
                case 2:         return "二";
                case 3:         return "三";
                case 4:         return "四";
                case 5:         return "五";
                case 6:         return "六";
                default:        return 0;
        }
}

string hour_period(int h)
{
        switch(h)
        {
                case 0..5:      return "凌晨";
                case 6..11:     return "上午";
                case 12:        return "中午";
                case 13..18:    return "下午";
                case 19..23:    return "晚上";
                default:        return 0;
        }
}

/* 回传时间阵列 ({ 分 时 礼 日 月 年 }) */
int *query_gametime_array()
{
        return game_time;
}

int *query_realtime_array()
{
        return real_time;
}

/* 回传数位时间表示 下午 3:39 */
string gametime_digital_clock()
{
        int h = game_time[HOUR];
        int m = game_time[MIN];

        return hour_period(h)+" "+(h==12 || (h%=12)>9?""+h:" "+h)+":"+(m>9?""+m:"0"+m);
}
string realtime_digital_clock()
{
        int h = real_time[HOUR];
        int m = real_time[MIN];

        return hour_period(h)+" "+(h==12 || (h%=12)>9?""+h:" "+h)+":"+(m>9?""+m:"0"+m);
}

string time_description(string title, int *t)
{
        return sprintf( NOR WHT+title+NOR"%s年，%s，%s月%s日星期%s，%s%s点%s分"NOR
            ,t[YEAR]==1?"元":CHINESE_D->chinese_number(t[YEAR])
            ,season_period(t[MON])
            ,!t[MON]?"元":CHINESE_D->chinese_number(t[MON]+1)
            ,CHINESE_D->chinese_number(t[MDAY]+1)
            ,week_period(t[WDAY])
            ,hour_period(t[HOUR])
            ,CHINESE_D->chinese_number(t[HOUR] > 12 ? t[HOUR]%12 : t[HOUR])
            ,CHINESE_D->chinese_number(t[MIN])
        );
}

string game_time_description()
{
        return time_description(CHINESE_MUD_NAME, game_time);
}

string real_time_description()
{
        return time_description("公元", real_time);
}

int query_game_time()
{
        return gametime*60;
}

int query_real_time()
{
        return realtime;
}

int *analyse_time(int t)
{
        int *ret = allocate(6);
        string ctime;

        ctime = ctime(t);

        sscanf(ctime,"%*s %*s %d %d:%d:%*d %d",ret[MDAY], ret[HOUR], ret[MIN], ret[YEAR]);

        switch(ctime[0..2])
        {
                case "Sun": ret[WDAY] = 0; break;
                case "Mon": ret[WDAY] = 1; break;
                case "Tue": ret[WDAY] = 2; break;
                case "Wed": ret[WDAY] = 3; break;
                case "Thu": ret[WDAY] = 4; break;
                case "Fri": ret[WDAY] = 5; break;
                case "Sat": ret[WDAY] = 6; break;
                default   : return 0;
        }

        switch(ctime[4..6])
        {
                case "Jan": ret[MON] = 0; break;
                case "Feb": ret[MON] = 1; break;
                case "Mar": ret[MON] = 2; break;
                case "Apr": ret[MON] = 3; break;
                case "May": ret[MON] = 4; break;
                case "Jun": ret[MON] = 5; break;
                case "Jul": ret[MON] = 6; break;
                case "Aug": ret[MON] = 7; break;
                case "Sep": ret[MON] = 8; break;
                case "Oct": ret[MON] = 9; break;
                case "Nov": ret[MON] = 10; break;
                case "Dec": ret[MON] = 11; break;
                default   : return 0;
        }
        ret[MDAY] -= 1;
        return ret;
}

void process_crontab(int *timearray, int flag)
{
        int i, n, t, row, divider, fit, timecost;
        string str, script, *timescript;
        object ob;
        mixed args;

        if( !ready )
                return;

        if( !n = sizeof(all_items) )
                return;

        for( row=0; row<n; row++ ) {
                reset_eval_cost();
                if( all_items[row]->flag != flag )
                        continue;

                script = all_items[row]->time;
                timescript = allocate(6);

                // %s%*(( |\t)+) 的意思是 %s(空格 or \t 跳过)接著 + 可以相配一串一个以上符合的单元
                if( sscanf(script, "%s%*(( |\t)+)%s%*(( |\t)+)%s%*(( |\t)+)%s%*(( |\t)+)%s%*(( |\t)+)%s",
                        timescript[0],
                        timescript[1],
                        timescript[2],
                        timescript[3],
                        timescript[4],
                        timescript[5]) != 11 ) continue;

                for( i=0; i<6; i++ ) {
                        fit = 0;

                        foreach( str in explode(timescript[i], ",") ) {
                                t = to_int(str);

                                if( str == "*" || (sscanf(str, "*/%d", divider) && !(timearray[i]%divider)) ) {
                                        fit = 1;
                                        break;
                                }
                                else if( !undefinedp(t) ) {
                                        if( t == timearray[i] ) {
                                                fit = 1;
                                                break;
                                        }
                                }
                        }
                        if( !fit ) break;
                }

                if( !fit )
                        continue;

                ob = find_object(all_items[row]->file);
                if( !ob )
                        ob = load_object(all_items[row]->file);
                if( !ob )
                        continue;
                args = ({ all_items[row]->func }) + all_items[row]->args;
                timecost = time_expression {
                        catch(call_other(ob, args));
                };

                if( timecost > 1000000 )
                        CHANNEL_D->do_channel(this_object(), "sys",
                                sprintf("TIME_D: crontab '%s'(%.6f sec) %s", script, timecost/1000000., all_items[row]->file));

        }
}

// 独立出来每秒执行函式
void process_per_second()
{

        
}

int reset_gametime(int time)
{
        gametime = time;
}

/* 游戏时间每一分钟(即实际时间每2秒)执行一次 process_gametime */
void process_gametime()
{
        game_time = analyse_time(++gametime * 60);
        game_time[YEAR] -= 1970;

        process_crontab(game_time, 1);
}

/* 真实时间每一秒钟执行一次 process_realtime */
void process_realtime()
{
        mixed *local_time = localtime(realtime);

        real_time = ({
                to_int(local_time[LT_MIN]),
                to_int(local_time[LT_HOUR]),
                to_int(local_time[LT_WDAY]),
                to_int(local_time[LT_MDAY])-1,
                to_int(local_time[LT_MON]),
                to_int(local_time[LT_YEAR]) });
        
        process_per_second();
        
        if( !local_time[LT_SEC] )
                process_crontab(real_time, 0);
}

// 每 1 秒运算一次
// 实际一天等于游戏一月

void heart_beat()
{
        while(realtime < time())
        {
                realtime++;
                process_realtime();
        }

        // 执行 event 处理
        if( sizeof(event) )
        foreach( function fevent, int delay_time in event )
                if( !--event[fevent] )
                        exec_event(fevent);

        // 每 2 秒相当于游戏一分钟, time 每增加 1 代表游戏一分钟
        //if( !(++tick % 2) )
                process_gametime();
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "时间精灵");
        //write("时间精灵已经启动。\n");

        init_crontab();
        
        realtime = time();
        game_time = allocate(6);
        real_time = allocate(6);
        event = allocate_mapping(0);

        process_gametime();
        set_heart_beat(1);
}

#define BOAT_FILE      "/clone/misc/dream_boat"

// 分配船只
void alloate_boat(int which)
{
        object ob_boat/*, ob_old_boat*/; 
        string *key_boats, *key_para;
        int i, n;
        object ob_place;
        object *obs;
        
        mapping boats = ([
                // 源地点 中文名 目的地点 中文名 默认等船时间 默认行使时间
                "boat1" : ({ "/d/tulong/tulong/haian", "东海之滨海港", "/d/shenlong/haitan", "神龙岛", 600, 600 }),
                "boat2" : ({ "/d/beijing/haigang", "东海之滨海港", "/d/shenlong/japangames/japan0", "日本岛", 600, 600 }),
                "boat3" : ({ "/d/xiakedao/haibin", "南海之滨", "/d/penglai/haitan", "蓬莱仙岛", 900, 900 }),
        ]);
        
        key_boats = keys(boats);

        // 删除掉当前环境中的BOAT
        for( i = 1; i <= sizeof(key_boats); i ++ )
        {               
                if( i == 1 )
                {
                        if( sizeof(obs = children(BOAT_FILE)) )
                                for( n = 0; n < sizeof(obs); n++ )
                                        destruct(obs[n]);
                        continue;
                }
                
                if( sizeof(obs = children(BOAT_FILE + sprintf("%d", i))) )
                        for( n = 0; n < sizeof(obs); n++ )
                                destruct(obs[n]);
        }
        
        
        for( i = 0 ; i < sizeof(key_boats); i ++ )
        {
                key_para = ({});
                key_para = boats[key_boats[i]];
                /*              
                if (i > 0)
                {
                        ob_old_boat = find_object(BOAT_FILE + sprintf("%d", i + 1));
                        if (! ob_old_boat)ob_old_boat = load_object(BOAT_FILE + sprintf("%d", i + 1));
                        if (! environment(ob_old_boat))ob_boat = new(BOAT_FILE + sprintf("%d", i + 1));
                        else
                                continue;
                }*/
                if (key_boats[i] == "boat1")ob_boat = new(BOAT_FILE);
                if (key_boats[i] == "boat2")ob_boat = new(BOAT_FILE + "2");
                if (key_boats[i] == "boat3")ob_boat = new(BOAT_FILE + "3");

                // 设置参数
                set("source_place", key_para[0], ob_boat);
                set("source_place_name", key_para[1], ob_boat);
                set("dest_place", key_para[2], ob_boat);
                set("dest_place_name", key_para[3], ob_boat);
                set("waiting", key_para[4], ob_boat);
                set("running_time", key_para[5], ob_boat);
                set("stop_time", time(), ob_boat);

                ob_place = find_object(key_para[0]);
                if (! ob_place)ob_place = load_object(key_para[0]);
                ob_boat->move(ob_place);
        }
        CHANNEL_D->channel_broadcast("news",  
                HIG + "开往蓬莱仙岛的巨型帆船出现在南海之滨…\n" + NOR); 
}

int give_money(int count)
{
        mapping ips;
        object pob;
        string ip;
        string *ks;

        CHANNEL_D->channel_broadcast("news",  
                HIG + "系统开始给每个玩家馈赠NT，本次馈赠数量为"+count+"NT…\n" + NOR); 

        count = to_int(count);
        ips = ([ ]);
        //foreach( pob in all_interactive() )
        foreach( pob in users() )
        {
                if( wizardp(pob) || !query("born", pob) ||  
                !environment(pob) ) continue; 

                ip = query_ip_number(pob);
                if( undefinedp(ips[ip]) ) ips[ip] = ({ pob }); else ips[ip] += ({ pob }); 
        }

        if( sizeof(ips) >= 1 ) 
        {
                ks = keys(ips); 
                foreach( ip in ks ) 
                {
                        pob = ips[ip][random(sizeof(ips[ip]))]; 
                        if( MEMBER_D->is_member(pob) )
                                MEMBER_D->db_pay_member(pob, count);  
                        else
                                MEMBER_D->db_create_member(pob, count);
                }
        }
        return 1;
}


int pay_tutor_money(int count)
{
        object *obs, pob;

        CHANNEL_D->channel_broadcast("news",  
                HIG + "系统开始给新手导师发放周薪，本次发放薪水为"+count+"NT…\n" + NOR); 

        count = to_int(count);
        
        obs = filter_array(users(), (: query("viremploy/job", $1) :));
        foreach( pob in obs ) 
        {
                if( MEMBER_D->is_member(pob) )
                        MEMBER_D->db_pay_member(pob, count);  
                else
                        MEMBER_D->db_create_member(pob, count);
        }
        return 1;
}

string query_name()
{
        return "时间系统(TIME_D)";
}
