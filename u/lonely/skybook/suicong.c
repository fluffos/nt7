cat suicong.c
// 随从系统

#include <ansi.h>
inherit F_CLEAN_UP;

#define SUICONG_D    "/adm/daemons/suicongd"

int help(object me);

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{

        string arg1, arg2, arg3;
        if (! arg)return help(me);
        
        
        if (! find_object(SUICONG_D))load_object(SUICONG_D);
        
        // 显示所有可以获得随从列表
        if (arg == "list")
        {
                return SUICONG_D->show_suicong(me);             
        }
        
        // 查看指定随从
        if (sscanf(arg, "cha %s", arg1) == 1)
        {
                return SUICONG_D->show_suicong_target(me, arg1);
        }
        // 查看指定玩家的指定随从
        if (sscanf(arg, "chaplayer %s %s", arg1, arg2) == 2)
        {
                object ob = find_player(arg1);
                if (! ob)return notify_fail("玩家不存在！\n");
                                
                return SUICONG_D->show_suicong_target(ob, arg2);
        }
        // 召唤随从     
        if (sscanf(arg, "sum %s", arg1) == 1)
        {
                return SUICONG_D->summon_suicong(me, arg1);
        }
        // 隐藏随从
        if (arg == "hide")
        {
                return SUICONG_D->hide_suicong(me, arg1);
        }
        // 测试开发期间使用，玩家可领取2名随从体验
        if (arg == "tiyan")
        {
                SUICONG_D->give_suicong(me, "少侠·平一指");

                write(HIG "领取了【少侠·平一指】，请使用 suicong sum 少侠·平一指 召唤！\n" NOR);
                return 1;
        }
}

int help(object me)
{
        string sMsg;
        
        write(@TEXT              
        
=--------------------------------------------------------------------------------------=
        随从系统控制指令  >>

        suicong                   查看指令说明和当前召唤出的随从
        suicong list              查看所有已经开放的随从
        suicong cha 随从名        查看指定随从的详细信息
        suicong sum 随从名        召唤指定随从出战，召唤后会替换掉当前已出战的随从
        suicong hide 随从名       将召唤出来的随从收回
        suicong tiyan             领取1名随从进行体验，正式开放后会删除
TEXT);  
        
        if (wizardp(me))
        {
                write("\n        suicong chaplayer ID 随从名   ： 可查看指定玩家指定的随从属性\n");
        }
        
        
        sMsg = "\n=--------------------------------------------------------------------------------------=\n";
        sMsg+= "当前召唤出的随从有：" + HIG + SUICONG_D->get_sum(me) + "\n" NOR;
        sMsg+=   "=--------------------------------------------------------------------------------------=\n";
        write(sMsg);
        return 1;
}
