// mccp.c
#include <ansi.h> 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
#ifdef MCCP_SUPPORT
        object *mccp, *user;
        
        user = filter_array(users(), (: interactive($1) :));
        mccp = filter_array(user, (: compressedp($1) :));
        
        write(sprintf("你的 MCCP 状态为：" HIR "%s\n" NOR, compressedp(me) ? "ON" : "OFF"));
        write(sprintf("现在共 " HIC "%d" NOR "/%d 个使用者开启 MCCP。\n", sizeof(mccp), sizeof(user)));
#else
        write("驱动程序目前不支持网路传输压缩功能。\n");
#endif
        return 1;
}

int help(object me)
{
        write(@HELP
指令说明:
    检查玩家的程式是否有启动 MCCP(Mud Client Compression Protocol)功能
此功能可以加速网路传输速度

HELP );
    return 1;
}