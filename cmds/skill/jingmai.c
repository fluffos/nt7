// This program is a part of NT MudLIB

#include <ansi.h>

#define ZHOUTIAN_D      "/adm/daemons/zhoutiand"

inherit F_CLEAN_UP;

int help(object me);
int main(object me, string arg)
{
        string *xs;
        string msg;
        int i;

        if( me->is_busy() || me->is_fighting() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || arg == "" ) {
                msg  = HIC "经脉名冲穴状态\n" NOR;
                msg += HIC "≡" HIY "----------------------------------------------" HIC "≡\n" NOR;
                msg += HIC "\t\t小周天经脉\n" NOR;
                msg += HIC "≡" HIY "----------------------------------------------" HIC "≡\n" NOR;
                msg+=HIG"阴跷脉\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/阴跷脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"阳跷脉\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/阳跷脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"阴维脉\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/阴维脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"阳维脉\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/阳维脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"带脉\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/带脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"冲脉\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/冲脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"任外脉\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/任外脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"督外脉\t\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/督外脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"经外奇脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/经外奇脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg += HIC "≡" HIY "----------------------------------------------" HIC "≡\n" NOR;
                msg += HIY "\t\t大周天经脉\n" NOR;
                msg += HIC "≡" HIY "----------------------------------------------" HIC "≡\n" NOR;
                msg+=HIG"手太阴脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手太阴脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手太阳脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手太阳脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足太阴脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足太阴脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足太阳脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足太阳脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手少阴脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手少阴脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手少阳脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手少阳脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足少阴脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足少阴脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足少阳脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足少阳脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手阳明脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手阳明脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足阳明脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足阳明脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"手厥阴脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/手厥阴脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg+=HIG"足厥阴脉\t\t\t\t"+((query("jingmai/finish", me) || query("jingmai/足厥阴脉/chongxue_ok", me))?HIM"已打通":HIR"未打通")+"\n"NOR;
                msg += HIC "≡" HIY "----------------------------------------------" HIC "≡\n" NOR;
                write(msg);
                help(me);

                if( query("jingmai/finish", me) || query("jingmai/阴跷脉/chongxue_ok", me) )
                        MYGIFT_D->check_mygift(me, "newbie_mygift/yinqiaomai");

                return 1;
        }

        if( arg == "all" || arg == "bh" || arg == "bh2" )
        {
                me->start_more(ZHOUTIAN_D->show_bianhao(arg));
                return 1;
        }

        ZHOUTIAN_D->show_jingmai(me, arg);

        return 1;
}

int help(object me)
{
        write(@HELP
查看指定经脉冲学情况使用指令 jingmai <经脉名> 查询。
查看小周天铜人编号输入 jingmai bh 查询。
查看大周天铜人编号输入 jingmai bh2 查询。
查看大小周天铜人编号输入 jingmai all 查询。
更详细的参考文件请通过帮助文件 help zhoutian 查看。

HELP
);
        return 1;
}
