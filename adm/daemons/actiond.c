// action_d.c
// Written by Akuma@fy4
// Updated by Lonely@nt7 将每日活动修改为同时支持特定日活动
// 活动精灵，负责发起和关闭每日的活动
// 这个daemon我倾向于做成广播器和活动状态的容器
// 他本身什么也不做，其他系统从他这里获取某个活动是否开启的状态

#include <localtime.h>
#include <ansi.h>

mapping action_settings = ([]);
mapping active_actions = ([]);
int setup();
int get_minute_by_string(string time);
void check_action_startend();

int compare_date(mixed a,mixed b)
{
        //小于等于是1
        //大于是0
        if(a[0]<b[0]) {
                return 1;
        } else if(a[0]>b[0]) {
                return 0;
        } else {
                if(a[1] < b[1]) {
                        return 1;
                } else if(a[1]>b[1]) {
                        return 0;
                } else {
                        if(a[2] < b[2]) {
                                return 1;
                        } else if(a[2]>b[2]) {
                                return 0;
                        } else {
                                return 1;
                        }
                }
        }       
}

int is_action(string arg)
{
        mixed lc;
        int y,m,d;

        lc = localtime(time());
        y = lc[LT_YEAR];
        m = lc[LT_MON] + 1;
        d = lc[LT_MDAY];

        if(!arg || undefinedp(action_settings[arg]))
                return 0;

        if(compare_date(({action_settings[arg]["stimey"],action_settings[arg]["stimem"],action_settings[arg]["stimed"]}),({y,m,d})) && 
           compare_date(({y,m,d}),({action_settings[arg]["etimey"],action_settings[arg]["etimem"],action_settings[arg]["etimed"]})) )
                return 1;
        return 0;
}

void create()
{
        seteuid(getuid());
        if( setup() ) {
                CHANNEL_D->channel_broadcast("sys", "活动精灵已经启动。");
                check_action_startend();
                SCHEDULE_D->set_event(600, 1, this_object(), "check_action_startend");
        }
}

void check_action_startend()
{
        mixed *ltime;
        int now_min;
        int tmp;

        tmp = 0;
        ltime = localtime(time());
        now_min = ltime[LT_HOUR]*60+ltime[LT_MIN]; // 当前分钟，这里要用localtime(获取本地时间)

        // 逐个setting做判断，60秒一次，这个效率可以接受
        foreach( string key in keys(action_settings) ) {
                // 当前时间在开始时间以前，那么什么也不做
                if( now_min<action_settings[key]["start"] )
                        continue;
                // 当前时间在结束时间之后，则需要试试是否应该关闭它
                if( !is_action(key) || now_min>=action_settings[key]["end"] ) {
                        // 存在于活跃列表，则结束之
                        if( !undefinedp(active_actions[key]) ) {
                                map_delete(active_actions,key);
                                // 广播
                                message("system", YEL "【"HIY"活"NOR+YEL"动"HIY"】本日活动："+action_settings[key]["name"]+"[倍率："+action_settings[key]["times"]+"]已经结束。\n" NOR, users());
                        } // 否则什么也不做
                        continue;
                }
                // 考虑到create的情况，所以当时间落在start和end之间的时候，需要多一个判断

                if( undefinedp(active_actions[key]) ) {
                        tmp ++;
                        active_actions[key] = action_settings[key]["times"];// 获得倍率
                        // 广播
                        message("system", YEL "【"HIY"活"NOR+YEL"动"HIY"】本日活动："+action_settings[key]["name"]+"[倍率："+action_settings[key]["times"]+"]已经开始（本活动今日将持续约"+chinese_number(action_settings[key]["end"]-now_min)+"分钟）。\n" NOR, users());
                }
        }
        if( !tmp && !random(3) ) {// 平均每三分钟announc一次
                if( sizeof(keys(active_actions)) > 1 )
                        message("system", YEL "【"HIY"活"NOR+YEL"动"HIY"】本日多项活动正在进行中（详细情况请使用指令 action 进行查看）。\n" NOR, users());
                else
                foreach( string key in keys(active_actions) ) {
                        message("system", YEL "【"HIY"活"NOR+YEL"动"HIY"】当前活动："+action_settings[key]["name"]+"[倍率："+action_settings[key]["times"]+"]进行中（本活动今日将持续约"+chinese_number(action_settings[key]["end"]-now_min)+"分钟）。\n" NOR, users());
                }
        }
}
//测试接口，获取所有的action列表
mixed query_action_settings()
{
        return action_settings;
}

// 给查询指令留的接口
string str2(int i)
{
        return (i<10)?("0"+i):(""+i);
}

string query_action_string()
{
        string ret;
        mixed *ltime;
        int now_min;

//      if(!sizeof(active_actions))
//              return HIY"当前没有正在进行中的活动。\n"NOR;

        ltime = localtime(time());
        now_min = ltime[LT_HOUR]*60+ltime[LT_MIN];
/*      ret = HIY"当前正在进行中的活动有：\n";
        foreach(string key in keys(active_actions)) {
                ret += action_settings[key]["name"]+"："+chinese_number(action_settings[key]["times"])+"倍[剩余"+chinese_number(action_settings[key]["end"]-now_min)+"分钟]\n";
        }
        ret += NOR;
        return ret;
*/
        ret = HIY"目前"+MUD_NAME+"提供的活动包括：\n";
        foreach( string key in keys(action_settings) ) {
                ret += "\t"+action_settings[key]["name"]+"："+str2(action_settings[key]["start"]/60)+":"+str2(action_settings[key]["start"]%60)+"～"+str2(action_settings[key]["end"]/60)+":"+str2(action_settings[key]["end"]%60)+"（"+chinese_number(action_settings[key]["times"])+"倍）";
                if( active_actions[key] ) {
                        ret += HIG"-当前进行中-今日剩余"+chinese_number(action_settings[key]["end"]-now_min)+"分钟\n"HIY;
                } else {
                        ret +=HIG"-当前未开启\n"HIY;
                }
        }

        return ret+NOR;
}

// 这里是其他系统调用查询当前是否处于某个活动中的接口，返回的是倍率
int query_action(string action)
{
        if( undefinedp(active_actions[action]) )
                return 0;
        else
                return active_actions[action];
}

int get_minute_by_string(string time)
{
        int hour,minute;
        hour = atoi(time[0..1]);
        minute = atoi(time[2..3]);
        return hour*60+minute;
}

int setup()
{
        int y, m, d;
        mixed file;
        mixed tmp;

        // 这里应该判断是否有文件
        if( !(file = read_file("/adm/etc/action_list")) )
                return 0;
        // 过滤win的换行符
        file = replace_string(file,"\r","");
        file = explode(file,"\n");
        file = filter_array( file , (: $1[0] != '#' :) );
        foreach( string line in file ) {
                //确保不是空行
                if( strlen(line) ) {
                        // action_list形如：
                        // action_name:chinese_name:startday:starttime:endday:endtime:times
                        // task_reward:多倍TASK奖励:*:1500:*:1700:2
                        // 活动英文标识:活动中文名:开始时间:结束时间:倍率
                        // 时间应该形如0830(前两位表示小时-24小时制，后两位表示分钟)，并且开始时间应当小于结束时间
                        // 这里假设配置文件是对的。。。
                        tmp = explode(line, ":");
                        action_settings[tmp[0]] = ([]);
                        action_settings[tmp[0]]["name"] = tmp[1];
                        action_settings[tmp[0]]["sday"] = tmp[2]; // 日期
                        action_settings[tmp[0]]["eday"] = tmp[3]; // 日期
                        action_settings[tmp[0]]["start"] = get_minute_by_string(tmp[4]);//一天的第几分钟
                        action_settings[tmp[0]]["end"] = get_minute_by_string(tmp[5]);  //一天的第几分钟
                        action_settings[tmp[0]]["times"] = atoi(tmp[6]);
                        
                        sscanf(tmp[2],"%d-%d-%d",y,m,d);
                        action_settings[tmp[0]]["stimey"] = y;
                        action_settings[tmp[0]]["stimem"] = m;
                        action_settings[tmp[0]]["stimed"] = d;
                        sscanf(tmp[3],"%d-%d-%d",y,m,d);
                        action_settings[tmp[0]]["etimey"] = y;
                        action_settings[tmp[0]]["etimem"] = m;        
                        action_settings[tmp[0]]["etimed"] = d;   
                }
        }
        return 1;
}

string query_name()
{
        return "活动精灵(ACTION_D)";
}
