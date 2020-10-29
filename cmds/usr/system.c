// system.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

string fs(int supplied);
string fc(int cost);

int main(object me, string arg)
{
        string msg;
        mapping cm;

        if (! SECURITY_D->valid_grant(me, "(apprentice)"))  
                return 0;

        cm = COMBAT_D->query_entire_dbase();
        msg = "系统现在的配置：\n";
        if (! mapp(cm))
                msg += "不祥。\n\n";
        else
                msg += "PK 人数限制：每天不超过 " HIR +
                       cm["pk_perday"] + NOR " 人，每人不超过 "
                       HIR + cm["pk_perman"] + NOR + " 次。\n\n";

        cm = CPU_D->query_entire_dbase();
        msg += "最近一段时间系统使用CPU的情况统计：\n";
        msg += "系统提供CPU资源的满足度：" + fs(cm["last_0"]["supplied"]) +
              "  游戏对CPU的占用率：" + fc(cm["last_0"]["cost"]) + "。\n";

        msg += sprintf("前一些时间CPU的满足度和占用率：%s/%s  %s/%s  %s/%s  %s/%s。\n",
                       fs(cm["last_1"]["supplied"]), fc(cm["last_1"]["cost"]),
                       fs(cm["last_2"]["supplied"]), fc(cm["last_2"]["cost"]),
                       fs(cm["last_3"]["supplied"]), fc(cm["last_3"]["cost"]),
                       fs(cm["last_4"]["supplied"]), fc(cm["last_4"]["cost"]));
        write(msg);
        return 1;
}

string fs(int supplied)
{
        if (supplied <= 70)
                return sprintf(RED "%d%%" NOR, supplied);
        else
        if (supplied <= 90)
                return sprintf(HIR "%d%%" NOR, supplied);

        return sprintf(WHT "%d%%" NOR, supplied);
}

string fc(int cost)
{
        if (cost < 0) cost = 0;
        if (cost >= 90)
                return sprintf(RED "%d%%" NOR, cost);
        else
        if (cost >= 70)
                return sprintf(HIR "%d%%" NOR, cost);

        return sprintf(WHT "%d%%" NOR, cost);
}


int help(object me)
{
        write(@HELP
指令格式 : system [-ui] [+|- <门派> <点数>]
 
这个指令可以显示出目前游戏的通用配置和使用系统资源的状况。使
用 ui 参数可以查阅目前 MUD 设计者对于的门派的更新优先级别。
 
HELP );
        return 1;
}
