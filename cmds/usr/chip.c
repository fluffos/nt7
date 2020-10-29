// Cmds:/cmds/usr/chip.c
 
inherit F_CLEAN_UP;

#ifndef GAMBLE_D
#define GAMBLE_D          "/adm/daemons/gambled"
#endif

int main(object me, string arg)
{
        GAMBLE_D->do_chip(me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : gmanage 

这条指令用于博彩投注。

HELP );
    return 1;
}