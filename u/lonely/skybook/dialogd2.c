/***************************************************
???
***************************************************/
#include <ansi.h>

inherit F_DBASE;

// 指定时间是否为周末
public int is_weekend_at(int t)
{       
        string str_ctime;


        // 判断指定时间是否为周末
        if (t > 0)
        {
                if (sscanf(ctime(t), "Sat %s", str_ctime) || sscanf(ctime(t), "Sun %s", str_ctime))
                        return 1;               
                else
                        return 0;
        }
        
        return 0;
}

int weekend()
{
        string str_ctime;
                
        // 当前时间是否为周末
        if (sscanf(ctime(time()), "Sat %s", str_ctime) || sscanf(ctime(time()), "Sun %s", str_ctime))
                return 1;

        return 0;               
}

// 当前时间是否为周末
public int is_weekend()
{
        

        // 周五晚20:00开始到周日晚23：59为周末
        if (weekend() || 
            is_weekend_at(time() + 4 * 3600))   // 周五20：00后
            return 1;
            
        return 0;
        
}

// 指定时间是周几
/*
Mon  - 1
Tue  - 2
Wed  - 3
Thu  - 4
Fri  - 5
Sat  - 6
Sun  - 7
*/
public int weeknum(int t)
{
        string stmp, swk;
        
        mapping wk = ([
                "Mon" : 1,
                "Tue" : 2,
                "Wed" : 3,
                "Thu" : 4,
                "Fri" : 5,
                "Sat" : 6,
                "Sun" : 7,
        ]);
        
        if (sscanf(ctime(t), "%s %s", swk, stmp) == 2)
                return wk[swk];

        return 0;
}

void create() 
{
        seteuid(ROOT_UID);
        set("channel_id", "对话精灵");
        set("name", HIW "对话精灵" HIM);

        // 定时播报缤纷周末信息
        remove_call_out("broad_weekendinfo");
        call_out("broad_weekendinfo", 3600);
}

// 播报缤纷周末信息
void broad_weekendinfo()
{
        remove_call_out("broad_weekendinfo");
        call_out("broad_weekendinfo", 3600);
        
        if (is_weekend())
        {
                message_system(HIY "炎黄" HIG "缤" HIM "纷" HIC "周" HIM "末" HIY
                               "火热进行中，详情请输入 " HIR "wkgift info" HIY " 查看。 \n" NOR);
        }       

        return;
}

// 模拟对话模式输出信息：仅给玩家1个人看到，且与说话NPC必须在同一房间
public void start_dialog(object npc, object me, string *msg, int index, int flag)
{

        if (! objectp(npc) || ! objectp(me))return;
        
        if (index == 0)
        {
                if (me->query_temp("is_in_dialog"))
                {
                        tell_object(me, HIR "你正在进行情景对话或故事，请稍后再试或退出(exit)游戏后重新登录！\n" NOR);
                        return;
                }
                else
                {
                        me->set_temp("is_in_dialog", 1);
                }
        }
        
        if (environment(npc) != environment(me))
        {
                me->delete_temp("is_in_dialog");
                return;
        }
        
        // 对话结束，进行回调
        if (index >= sizeof(msg))
        {
                me->delete_temp("is_in_dialog");
                npc->dialog_end(me, flag);
                return;
        }
        
        if (index % 2 == 1)             
                tell_object(me, HIY + "=" + msg[index] + "\n" NOR);
        else
                tell_object(me, HIM + "=" + msg[index] + "\n" NOR);     

        index += 1;

        call_out("start_dialog", 6, npc, me, msg, index, flag);

        return;
}

// 模拟对话模式输出信息：周围房间内所有人看到，且与说话NPC必须在同一房间
public void start_dialog2(object npc, object me, string *msg, int index, int flag)
{

        if (! objectp(npc) || ! objectp(me))return;
        
        if (index == 0)
        {
                if (me->query_temp("is_in_dialog"))
                {
                        tell_object(me, HIR "你正在进行情景对话或故事，请稍后再试或退出(exit)游戏后重新登录！\n" NOR);
                        return;
                }
                else
                {
                        me->set_temp("is_in_dialog", 1);
                }
        }

        if (environment(npc) != environment(me))
        {
                me->delete_temp("is_in_dialog");
                return;
        }


        // 对话结束，进行回调
        if (index >= sizeof(msg))
        {
                me->delete_temp("is_in_dialog");
                npc->dialog_end(me, flag);              
                return;
        }
        
        if (index % 2 == 1)             
                message_vision(HIY + "=" + msg[index] + "\n" NOR, npc, me);
        else
                message_vision(HIM + "=" + msg[index] + "\n" NOR, npc, me);

        index += 1;

        call_out("start_dialog2", 6, npc, me, msg, index, flag);

        return;
}

// 模拟对话模式输出信息：周围房间所有人看到，只要玩家在线无论什么地方都可以看到对话输出
public void start_dialog3(object npc, object me, string *msg, int index, int flag)
{

        if (! objectp(npc) || ! objectp(me))return;
        
        // if (environment(npc) != environment(me))return;
        
        if (index == 0)
        {
                if (me->query_temp("is_in_dialog"))
                {
                        tell_object(me, HIR "你正在进行情景对话或故事，请稍后再试或退出(exit)游戏后重新登录！\n" NOR);
                        return;
                }
                else
                {
                        me->set_temp("is_in_dialog", 1);
                }
        }
                
        // 对话结束，进行回调
        if (index >= sizeof(msg))
        {
                me->delete_temp("is_in_dialog");
                npc->dialog_end(me, flag);
                return;
        }
        
        if (index % 2 == 1)             
                message_vision(HIM + "=" + msg[index] + "\n" NOR, npc, me);
        else
                message_vision(HIM + "=" + msg[index] + "\n" NOR, npc, me);

        index += 1;

        call_out("start_dialog3", 6, npc, me, msg, index, flag);

        return;
}


// 模拟对话模式输出信息：只有玩家一人看到，只要玩家在线无论什么地方都可以看到对话输出
public void start_dialog4(object npc, object me, string *msg, int index, int flag)
{

        if (! objectp(npc) || ! objectp(me))return;
        
        // if (environment(npc) != environment(me))return;
        
        if (index == 0)
        {
                if (me->query_temp("is_in_dialog"))
                {
                        tell_object(me, HIR "你正在进行情景对话或故事，请稍后再试或退出(exit)游戏后重新登录！\n" NOR);
                        return;
                }
                else
                {
                        me->set_temp("is_in_dialog", 1);
                }
        }
                
        // 对话结束，进行回调
        if (index >= sizeof(msg))
        {
                me->delete_temp("is_in_dialog");
                npc->dialog_end(me, flag);              
                return;
        }

        if (index % 2 == 1)             
                tell_object(me, HIY + "=" + msg[index] + "\n" NOR, npc);
        else
                tell_object(me, HIM + "=" + msg[index] + "\n" NOR, npc);

        index += 1;

        call_out("start_dialog4", 6, npc, me, msg, index, flag);

        return;
}
