#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
       if (! SECURITY_D->valid_grant(me, "(arch)"))
                return notify_fail("ARCH以上的巫师才可以发布系统提示。\n");
        if (!arg) return notify_fail("你想要大叫什么?\n");
                                message_system(arg);
        return 1;
}
int help(object me)
{
  write(@HELP
指令格式 : syschat <讯息>
 
这个指令让你将 <讯息> 传送出去, 所有正在游戏中的人都
会听见你的话.
 
HELP
    );
    return 1;
}