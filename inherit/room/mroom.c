// inherit: mroom.c

// 怪物练级房间
// n_time    怪物刷新时间
// n_npc     怪物刷新数量
// n_max_npc 房间容纳最多怪物数量，即一次最多刷新多少个怪物
// s_npc     怪物种类，文件路径
// n_av_refresh 平均刷新速率
// 一个房间只能定义一种怪物

#include <ansi.h>

inherit ROOM;

// 计算刷新速率的间隔时间
// 每过一段时间通过一定算法计算刷新速率
#define COUNT_REFRESH_TIME         45

void start_heart_beat()
{
        // 默认为心跳1
        set_heart_beat(1);
}

void setup()
{
        mapping product;
        string mine;
        int count;

        set("no_clean_up", 1);
                set("no_roar", 1);
                //set("no_flyto", 1); // 不能骑马或MISS到这里，已经在horse.c做限制

                // 设置房间怪物属性
                if (! query("n_time"))set("n_time", 60);                                // 默认怪物45秒刷新一次
                if (! query("n_npc"))set("n_npc", 1);                                   // 默认怪物每次刷新一个
                if (! query("n_max_npc"))set("n_max_npc", 1);                           //默认为1，房间容纳最多怪物数量，即一次最多刷新多少个怪物
                if (! query("s_npc"))set("s_npc", "/clone/quarry/zhu");                 // 默认怪物为野兽—猪

                set("n_die", 0);                    // 单位时间内怪物死亡数量
                if (query("last_refresh_time"))     // 上次刷新时间
                        set("last_refresh_time", query("last_refresh_time"));


                if (query("last_count_refresh_time"))     // 上次计算刷新速率的时间
                        set("last_count_refresh_time", query("last_count_refresh_time"));
                
                ::setup();

        start_heart_beat();
}

void init()
{
                if (random(2))this_player()->start_busy(1);                     
}

// 每次心跳执行的操作
// 刷新时间到后刷新怪物，并计算下次刷新时间及怪物数量

void heart_beat()
{
                object ob_npc;
                object env;
                object *inv, *obs;
                int n_left_npc; // 当前怪物数量和最大容纳怪物数的差
                int n_npc; // 设置怪物的数量
                int i;  // 计数变量
                int refresh_total; // 时间间隔内总共刷新的怪物数量
                int new_n_time;  // 设置新的刷新时间
                int new_n_npc; // 设置怪物刷新数量

                //object me;

                                
                env = this_object();

                if( new_n_time <= 0)new_n_time=query("n_time", env);
                if( new_n_npc <= 0)new_n_time=query("n_npc", env);
                
                // 如果为蓬莱岛，则判断蓬莱岛是否开放
                if( query("penglai", env) && !GIFT_D->is_open_pld())return ;

                inv = all_inventory(env);

                obs = filter_array(inv, (: base_name($1) == query("s_npc") :)); // 过滤掉非本房间怪物的其他文件

                // 时间到达则刷新怪物
                n_left_npc = query("n_max_npc") - sizeof(obs);
                if (n_left_npc > 0 && time() - query("last_refresh_time") >= query("n_time"))
                {
                        n_npc = n_left_npc >= query("n_npc") ? query("n_npc") : n_left_npc;

                        for (i = 0; i < n_npc; i ++ )
                        {
                                ob_npc = new(query("s_npc"));
                                if (! objectp(ob_npc))
                                {
                                        log_file("mroom", "无法找到npc文件 " + query("s_npc") + "\n");
                                        return;
                                }
                        
                                ob_npc->move(env);
                        }

                        set("last_refresh_time", time());
                }

                // 计算刷新速率的算法
                // 每间隔COUNT_REFRESH_TIME秒计算一次，然后根据计算结果重新设置
                // 怪物刷新时间和数量
                if (time() - query("last_count_refresh_time") >= COUNT_REFRESH_TIME)
                {
                        // 算法描述
                        // 通过统计单位时间内怪物死亡数量
                        // 判定刷新速度，只计算怪物减少或不变的数量，不计算增加的数量

                        // 时间间隔内总共刷新的怪物数量
                        refresh_total = COUNT_REFRESH_TIME / query("n_time") * query("n_npc");

                        if (refresh_total < 1)refresh_total = 1;
                        
                        // 设置刷新时间按照比例计算
                        new_n_time = query("n_time") * query("n_die") / refresh_total;
                        
                        // 满刷，即刷出多少怪都全部杀死增加刷新
                        if (new_n_time >= query("n_time"))
                        {
                                new_n_time = new_n_time - new_n_time / 3;
                                new_n_npc = query("n_npc") + 1;
                        }
                        // 杀死怪物超过刷出的一半增加刷新
                        else if (new_n_time >= query("n_time") / 2)
                        {
                                new_n_time = new_n_time - new_n_time / 5;
                                new_n_npc = query("n_npc") + 1;
                        }
                        else // 未超过一半刷新速度则降低刷新速度
                        {
                                new_n_time = new_n_time + new_n_time / 2;
                                new_n_npc = query("n_npc") / 2;
                        }
                        
                        // 溢出判断
                        if (new_n_time > query("n_time"))new_n_time = query("n_time");
                        if (new_n_time <= 0)new_n_time = query("n_time"); // n_die == 0                                         
                        if (new_n_time < 15)new_n_time = 15;
                        if (new_n_npc < 1)new_n_npc = 1;                                
                        if (new_n_npc > query("n_max_npc"))new_n_npc = query("n_max_npc");
                        set("n_time", new_n_time);
                        set("n_npc", new_n_npc);

                        // 计数清0
                        set("n_die", 0);

                        // 记录本次计算的时间
                        set("last_count_refresh_time", time()); 

                }

}

// 怪物死亡时通知该房间累计怪物死亡熟练，以便计算刷新速率
void npc_die(object ob)
{
        addn("n_die", 1);
}
