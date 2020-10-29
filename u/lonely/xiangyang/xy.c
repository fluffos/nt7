#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string poision;
        
        // 显示襄阳战状态
        // 根据XYWAR_D->now_status()
        if (! arg)
        {
                return 1;
        }
        
        // 显示襄阳士兵情况
        if (arg == "soldier")
        {
                if (me->is_busy())return notify_fail("你正忙呢。\n");
                
                if (XYWAR_D->now_status() != 2 && XYWAR_D->now_status() != 3 && ! wizardp(me))
                        return notify_fail("襄阳保卫战目前还没有开始，无法查看。\n");
                
                XYWAR_D->show_soldier(me);
                return 1;
        }
        
        // 调动襄阳守军，只有玩家将领才可以调动
        if (sscanf(arg, "xmove %s", poision))
        {
                if (XYWAR_D->leader_player() != me->query("id") && ! wizardp(me))
                        return notify_fail("对不起，你没有权利调动襄阳守军。\n");
                
                XYWAR_D->move_xysoldier(me, poision);
                
                return 1;
        }
                
        // 增派蒙古军
        // 只有巫师有权利
        if (arg == "add mgb" && wizardp(me))
        {
                
                // 增加蒙古兵时间间隔ADD_MGB_TIME
                /*
                if (time() - last_add_mgb_time < 120)
                {
                        return notify_fail("蒙古兵刚增援过，兵力还调配不过来。\n");
                }
                */
                XYWAR_D->combat_add_soldier();
                return 1;
        }
        
        me->start_busy(2);
        return 1;
}


int help (object me)
{
        write(@HELP


HELP);
        return 1;
}

