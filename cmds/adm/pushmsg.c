// auth.c

#include <ansi.h>

inherit F_CLEAN_UP;

#define SCAN_D  "/adm/daemons/broadcastd"

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string title, info;
        int delay, times;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! is_root(me) && ! SECURITY_D->valid_grant(me, "(admin)"))
                return notify_fail("你没有权限访问安全系统。\n");

        if (! arg)
                return notify_fail("指令：pushmsg + 参数：\n" +
                                   "add 标题 间隔时长(秒) 循环次数 内容 ： 添加PUSHMSG\n" +
                                   "list : 显示当前广播\n" +
                                   "del 标题: 删除指定广播\n");

        if (arg == "list")
                return SCAN_D->show_push_lish();

        if (sscanf(arg, "del %s", title) == 1)
                return SCAN_D->delete_push_msg(title);

        if (sscanf(arg, "add %s %d %d %s", title, delay, times, info) != 4)
                return notify_fail("指令：pushmsg + 参数：\n" +
                                   "add 标题 间隔时长(秒) 循环次数 内容 ： 添加PUSHMSG\n" +
                                   "list : 显示当前广播\n" +
                                   "del 标题: 删除指定广播\n");


        // 添加
        return SCAN_D->add_push_msg(title, info, delay, times);
}
