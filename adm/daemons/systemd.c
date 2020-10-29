// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <mudlib.h>

string *preload_list;
object *loginuser;

#define PRELOAD_PATH    CONFIG_DIR + "preload"

void broadcast(string msg)
{
        foreach( object ob in loginuser ) {
                if( objectp(ob) )
                        ob->directly_receive(msg);
        }
}

void distributed_preload()
{
        mixed err;
        object ob;

#ifdef LONELY_IMPROVED
        // 关闭系统心跳
        //set_config(__RC_HEARTBEAT_INTERVAL_MSEC__, 10000);

        foreach(ob in loginuser)
                if( objectp(ob) )
                        flush_messages(ob);
#endif

        if( !sizeof(preload_list) ) {
                foreach( ob in loginuser ) {
                        if( objectp(ob) ) {
                                ob->directly_receive("\n"+MUD_FULL_NAME+"启动完毕，重新连线中...。\n");
                                destruct(ob);
                        }
                }
#ifdef LONELY_IMPROVED
                // 启动系统心跳
                //set_config(__RC_HEARTBEAT_INTERVAL_MSEC__, 1000);
#endif
                return;
        }

        //log_file("static/preload",sprintf("载入 %s\n", preload_list[0]));



        if( !(ob = find_object(preload_list[0])) )
        {
                reset_eval_cost();

                if( err = catch(ob = load_object(preload_list[0])) )
                {
                        broadcast(sprintf(HIW+"%'0'3d "NOR"- 载入 %s ...", sizeof(preload_list), preload_list[0]));
                        broadcast(HIR"Failed\n"NOR);
                        log_file("static/preload",sprintf("载入 %s 时发生错误: %O\n", preload_list[0], err));
                }
                else
                {
                        broadcast(sprintf(HIW+"%'0'3d "NOR"- 载入 %s ...", sizeof(preload_list), preload_list[0]->query_name() || preload_list[0]));
                        broadcast(sprintf(HIG"Done (%.2f Kbytes)\n"NOR, memory_info(ob)/1024.));
                }
                preload_list = preload_list[1..];
                call_out((: distributed_preload :), 1);
        }
        else
        {
                broadcast(sprintf(HIW+"%'0'3d "NOR"- 载入 %s ...", sizeof(preload_list), preload_list[0]->query_name() || preload_list[0]));
                broadcast(sprintf(HIC"Loaded (%.2f Kbytes)\n"NOR, memory_info(ob)/1024.));
                preload_list = preload_list[1..];
                distributed_preload();
        }
}

void distributed_system_preload()
{
        string path, file;
        string str;
        int i;

        loginuser = allocate(0);

        str = read_file(PRELOAD_PATH);
        str = replace_string(str, "\r", "");
        preload_list = explode(str, "\n");
        for (i = 0; i < sizeof(preload_list); i++)
                if( preload_list[i][0] == '#' )
                        preload_list[i] = 0;

        preload_list -= ({ 0 });
        //preload_list = filter_array( explode(read_file(PRELOAD_PATH), "\n") , (: $1[0] != '#' :) );

        foreach( path in preload_list )
        {
                if( path[<1] == '/' && file_size(path)==-2 )
                {
                        foreach( file in get_dir(path) )
                        {
                                if( file[<2..<1] == ".c" && file_size(path+file) > 0 )
                                        preload_list += ({ path+file });
                        }
                        preload_list -= ({ path });
                }
                else if( path[<2..<1] != ".c" || file_size(path) <= 0 )
                        preload_list -= ({ path });
        }

        log_file("static/preload",sprintf("Preload 列表 %O\n", preload_list));

        distributed_preload();
}

int valid_login()
{
        return !preload_list || !sizeof(preload_list);
}

void add_loginuser(object ob)
{
        if( !loginuser ) loginuser = allocate(0);
#ifdef LONELY_IMPROVED
        loginuser |= ({ ob });
#else
        if( member_array(ob, loginuser) == -1 )
                loginuser += ({ ob });
#endif
}

string dsize(int size)
{
        if( size < 1024 )
                return size + " Bytes";

        if( size < 1048576 )
                return sprintf("%.3f KBytes", size / 1024.);

        if( size < 1073741824 )
                return sprintf("%.3f MBytes", size / 1048576.);

        if( size < 1099511627776 )
                return sprintf("%.3f GBytes", size / 1073741824.);

        if( size < 1125899906842624 )
                return sprintf("%.3f TBytes", size / 1099511627776.);
}

string query_network_packet_stats()
{
#ifdef LONELY_IMPROVED
        mapping networkstats = network_stats();

        return sprintf("已接收 %s 封包(%.2f/sec)，已传送 %s 封包(%.2f/sec)",
                        NUMBER_D->number_symbol(networkstats["incoming packets total"]),
                        to_float(networkstats["incoming packets total"])/uptime(),
                        NUMBER_D->number_symbol(networkstats["outgoing packets total"]),
                        to_float(networkstats["outgoing packets total"])/uptime());
#else
        return "";
#endif
}

string query_network_volume_stats()
{
#ifdef LONELY_IMPROVED
        mapping networkstats = network_stats();

        return sprintf("已接收 %s 资料(%.3f KBytes/sec)，已传送 %s 资料(%.3f KBytes/sec)",
                        dsize(networkstats["incoming volume total"]),
                        to_float(networkstats["incoming volume total"])/1024./uptime(),
                        dsize(networkstats["outgoing volume total"]),
                        to_float(networkstats["outgoing volume total"])/1024./uptime());
#else
        return "";
#endif
}

string query_total_system_info()
{
        mapping rusage = rusage();
        int module_room, module_npc, module_product;
        string msg = "";
        float cpuload = (rusage["stime"] + rusage["utime"]) / 10. / to_float(uptime());

        foreach(object ob in objects())
        {
                if( ob->is_room() )
                        ++module_room;
        }

        msg += "真实时间   - "+TIME_D->replace_ctime(time())+"\n";
        msg += "游戏时间   - "+TIME_D->game_time_description()+"\n";
        msg += "启动时间   - "+CHINESE_D->chinese_period(uptime())+"\n";
        msg += "使用者总数 - "+sizeof(users())+" 人\n";
        msg += "物件总数   - "+sizeof(objects())+" 个\n";
        msg += "房间模组数 - "+module_room+" 间\n";
        msg += "心跳总数   - "+sizeof(heart_beats())+" 个\n";
        msg += "延迟呼叫数 - "+sizeof(call_out_info())+" 个\n";
        msg += "系统负载   - "+query_load_average()+"、平均 CPU 负荷："+sprintf("%.2f", cpuload)+"%\n";
        msg += "封包传输   - "+query_network_packet_stats()+"\n";
        msg += "资料传输   - "+query_network_volume_stats()+"\n";
        msg += "记忆体使用 - "+sprintf("%.6f MBytes\n", memory_info()/1024./1024. );

        return msg;
}

/*
void save_all(int level)
{
        object ob;

        foreach(ob in users())
        {
                reset_eval_cost();

                if( objectp(ob) && objectp(environment(ob)) )
                        ob->save();
        }

        FAMILY_D->save();
        BUNCH_D->save();
        NAME_D->save();
        CLOSE_D->save();
        DBASE_D->save();
        SKILLS_D->save();
        STORAGE_D->save();
        INTERMUD2_D->save();
        reset_eval_cost();

        if( level >= 1 )
        {
                foreach(ob in objects((: $1->is_module_npc() :)))
                        ob->save();
        }

        if( level >= 2 )
        {
                foreach(ob in objects((: $1->is_module_room() :)))
                        ob->save();
        }

        if( level >= 3 )
        {
                foreach(ob in objects((: $1->is_module_product() && !clonep($1) :)))
                        ob->save();
        }
}

void startup_save_all(int level)
{
        int costtime;

        // 关闭系统心跳计算
        //set_config(__RC_HEARTBEAT_INTERVAL_MSEC__, 10000);

        costtime = time_expression { catch(save_all(level)); };

        CHANNEL_D->channel_broadcast("news", sprintf("系统资料全面储存完毕(Lv "+level+")，共花费 %.3f 秒。", costtime/1000000.));

        set("system/save_all/time/"+level, costtime/1000000., DATABASE_D->query_ob());

        // 重新启动系统心跳计算
        //set_config(__RC_HEARTBEAT_INTERVAL_MSEC__, 1000);
}

void prepare_to_save_all(int level)
{
        float estimate_time = query("system/save_all/time/"+level, DATABASE_D->query_ob());


        if( undefinedp(estimate_time) )
                CHANNEL_D->channel_broadcast("news", "五秒钟后系统进行资料全面储存(Lv "+level+")，存档过程可能耗费数秒钟至数分钟，请稍候。");
        else
        {
                int low = to_int(estimate_time - estimate_time/5);
                int high = to_int(estimate_time + estimate_time/5);

                if( low < 0 ) low = 0;

                CHANNEL_D->channel_broadcast("news", "五秒钟后系统进行资料全面储存(Lv "+level+")，存档过程估计约需要耗费 "+low+" 至 "+high+" 秒左右，请稍候。");
        }
        call_out((: startup_save_all :), 5, level);
}
*/

void create()
{
        if( uptime() < 30 )
                distributed_system_preload();
}

int remove()
{

}
string query_name()
{
        return "中央管理系统(SYSTEM_D)";
}
