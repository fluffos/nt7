// Cmds:/cmds/usr/gmanage.c
 
inherit F_CLEAN_UP;

#ifndef GAMBLE_D
#define GAMBLE_D          "/adm/daemons/gambled"
#endif

int main(object me, string arg)
{

        if (! SECURITY_D->valid_grant(me, "(arch)")) 
                return 0; 

        GAMBLE_D->start_manage(me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : gmanage 

这条指令用于管理博彩系统。

HELP );
    return 1;
}