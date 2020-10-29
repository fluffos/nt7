inherit F_CLEAN_UP;
#include <mudlib.h>
#include <getconfig.h>
#include <ansi.h>
#include <command.h>
#define SCALE   (1.0/10.0)
#define STATUS  "系统函数库改写中，游戏正完善中"

string memory_expression(int m);
string dotime();

int count_ppls();

void create() { seteuid(getuid(this_object())); }

#ifdef LONELY_IMPROVED
string query_rusage_message()
{
        mapping networkstats = network_stats();
        return sprintf("已接收 %d 封包(%.2f/sec)，已传送 %d 封包(%.2f/sec)",
                networkstats["incoming packets total"],
                to_float(networkstats["incoming packets total"])/uptime(),
                networkstats["outgoing packets total"],
                to_float(networkstats["outgoing packets total"])/uptime());
}
#endif

int main(object me)
{
        float value;
        mapping r;
        int cpu;

        if( time()-query_temp("scan_time", me)<10
           && ! wizardp(me))
                return notify_fail("等等，系统喘气中……\n");

        r = rusage();
        value = SCALE * (r["utime"] + r["stime"]) / uptime();
        cpu = CPU_D->get_current_cpu_cost();

        write(NOR + WHT "\n\t\t         .__________ 系 统 资 讯 __________.\n");
        write(NOR + WHT "\t\t --------------------------------------------------\n");
        write(NOR + WHT "\t\t 游戏的识别名称：  " + MUD_NAME + "\n");
        write(NOR + WHT "\t\t 界面系统的版本：  " + __VERSION__ + "\n");
        write(NOR + WHT "\t\t 系统函数库版本：  " + MUDLIB_VERSION_NUMBER + "\n");
        printf(NOR + WHT "\t\t CPU 使用百分比：  实时：%d %%，平均：%2.2f %%\n", cpu, value );
        printf(NOR + WHT "\t\t 共使用的记忆体：  %s bytes\n", memory_expression(memory_info()) );
        write(NOR + WHT "\t\t 线上使用者总数：  " + sizeof( users() ) + "  个人在线上\n");
        write(NOR + WHT "\t\t 注册使用者总数：  " + DATABASE_D->db_count_user() + "  个人在本游戏注册\n");
        write(NOR + WHT "\t\t 载入的物件总数：  " + sizeof( objects() ) + " 个物件\n");
        write(NOR + WHT "\t\t 心跳总数的资讯：  " + sizeof(heart_beats()) + " 个\n");
        write(NOR + WHT "\t\t 当前的心跳时间：  " + get_config(__RC_HEARTBEAT_INTERVAL_MSEC__)/1000 + " 秒\n"NOR);
        write(NOR + WHT "\t\t 当前的TICK时间：  " + get_config(__RC_GAMETICK_MSEC__) + " 毫秒\n"NOR);
        write(NOR + WHT "\t\t 延迟呼叫数资讯：  " + sizeof(call_out_info()) + " 个\n");
        write(NOR + WHT "\t\t 系统负载的资讯：  " + query_load_average() + "\n");
#ifdef LONELY_IMPROVED
        write(NOR + WHT "\t\t 讯息传输的资讯：  " + query_rusage_message() + "\n");
#endif
        write(NOR + WHT "\t\t 连续执行的时间：  " + dotime() + "\n");

        set_temp("scan_time", time(), me);

        return 1;
}

string memory_expression(int m)
{
        float mem;

        mem = m;
        if( mem<1024 ) return m + "";
        if( mem<1024*1024 )

                return sprintf("%.2f K", (float)mem / 1024);
        return sprintf("%.3f M", (float)mem / (1024*1024));
}

int count_ppls()
{
        int count,i;
        string *dir;
        string *ppls;

        seteuid(getuid());

        dir = get_dir(DATA_DIR + "login/");
        for(i=0; i<sizeof(dir); i++) {
        ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/");
        count += sizeof(ppls);
        }
        return count;
}

string dotime()
{
        int t, d, h, m, s;
        string time;

        t = uptime();
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if (d) time = chinese_number(d) + "天";
        else time = "";

        if (h) time += chinese_number(h) + "小时";
        if (m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒\n";

        return time;
}

int help() {

   write(@HELP
指令格式：mudinfo

这个指令将会显示有关这个 Mud 的一些系统资讯。

HELP
        );
         return 1;
}
