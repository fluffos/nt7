// time.c                                          
#include <ansi.h>

// #define END_TIME 874425565
#define END_TIME 875981023
#define FETEDAY "中秋节"
inherit F_CLEAN_UP;

int main(object me, string arg)
{   int time, date;
    time = time();
        write(sprintf("现在的时间是北京时间 " + ctime( time ) + "。\n"));
    date = (END_TIME-time) / 24 / 3600;
    if (date > 1)
    {
        write(sprintf("距离" + FETEDAY + "还有"BBLU YEL"%s"NOR"天。\n", 
            chinese_number(date)));
    }
    else if (date == 1)
    {
        write(sprintf(BBLU YEL "\n\t\t明天就是" + FETEDAY + "了！\n\n" NOR));
    }
    else if (!date)
    {
        write(sprintf(BBLU YEL "\n\t\t今天是" + FETEDAY + "！\n\n"NOR));
    }
        return 1;
}

int help(object me)
{
     write(@HELP
指令格式: time

这个指令告诉你现实世界中现在的时间。

HELP
    );
    return 1;
}