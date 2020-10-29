#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        object target;
        mapping waitback_list, info;
        string msg, my_id;
        string no_tell, can_tell;
        
        if( !arg )
                return notify_fail("你想要等谁回神？\n");

        /*
        if (sscanf(arg, "%s %s", arg, msg) != 2)
                return help(me);
        */
        sscanf(arg, "%s %s", arg, msg);
                
        if( !objectp(target = find_player(arg)) || ! me->visible(target) )
                return notify_fail("这个用户没有登录，你无法和他交谈。\n");

        my_id=query("id", me);
        no_tell=query("env/no_tell", target);
        if (! wizardp(me) && (no_tell == "all" || no_tell == "ALL" ||
            is_sub(my_id, no_tell)))
        {
                can_tell=query("env/can_tell", target);
                if (! is_sub(my_id, can_tell))
                        return notify_fail("这个人不想听你罗嗦啦。\n");
        }
        
        if (! interactive(target) || target->is_net_dead())
                return notify_fail("此人现在不在线上，听不到你的话。\n");

        if (! living(target))
                return notify_fail("这人现在恐怕听不到你说的话了...\n");

        if (me->ban_say(1))
                return 0;
                
        if( target == me )
                return notify_fail("等你自己回神？？\n");

        info = allocate_mapping(2);
        info["time"] = time();
        info["msg"] = msg;
        
        if( mapp(waitback_list=query_temp("waitback_list", target)) )
        {
                waitback_list += ([ me : info ]);
                set_temp("waitback_list", waitback_list, target);
        }
        else
                set_temp("waitback_list", ([me:info]), target);
        
        tell_object(me, HIG "你开始等待着" HIG + target->query_idname(1) + HIG "回神。\n" NOR);
        tell_object(target, HIG + me->query_idname(1) + HIG "开始等待着你回神。\n" NOR);
        tell_object(target, "\a", 0);
        return 1;
}

int help(object me)
{
        write(@HELP
等待指令

这个指令可以让您等待闲置中的使用者，直到该使用者开始活动时通知您。

指令格式:
waitback <使用者代号> <留言>

相关指令: beep
HELP);
        return 1;
}