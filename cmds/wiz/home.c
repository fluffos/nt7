// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// home.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string msg, file1, file2, str;
        string who;
        object body, ob, user;

        if (! SECURITY_D->valid_grant(me, "(immortal)")) 
                return 0; 

        seteuid(getuid()); 
                                    
        file1 = "/clone/misc/workroom.c";
        
        if (query("viremploy/workroom", me))
        {
                message_vision("$N回家去了。\n\n",me);
                me->move("/u/viremploy/" + query("viremploy/workroom", me)); 
                return 1;
        }
        if (! arg || arg == geteuid(me)) 
        {
                file2 = "/u/" + geteuid(me) + "/workroom.c";
                arg = 0;
        } else 
        {
                ob = UPDATE_D->global_find_player(arg);  
                if (! objectp(ob)) 
                        return notify_fail( "没有这个玩家。\n");
                        
                file2 = "/u/" + arg + "/workroom.c";
        }

        if (file_size(file2) <= 0)
        {
                if (arg) 
                        return notify_fail(query("name", ob)+"没有自己的工作室。\n");
                else 
                if (! get_dir("/u/" + geteuid(me) + "/"))
                {
                        if (mkdir("/u/" + geteuid(me)))
                                write(GRN "\n你的目录建在 /u 下。\n\n" NOR);
                        else 
                                return notify_fail("建立目录失败！\n");
                }
                str = read_file(file1);
                str = replace_string(str, "NAME", this_player()->name());
                write_file(file2, str);
        }
        
        if( arg && !query("env/invisible", me) )
                message_vision("$N去"+query("name", ob)+"家做客了。\n\n",me);
        else 
        if( stringp(msg=query("env/msg_home", me)) && !query("env/invisible", me) )
                message_vision(msg + "\n", me);
        else 
        if( !query("env/invisible", me) )
                message_vision("$N回家去了。\n\n",me);
                
        me->move(file2);
        
        UPDATE_D->global_destruct_player(ob, 1);  
        return 1;
}

int help(object me)
{
 write(@HELP
指令格式 : home 或 home <sb>

利用此一指令可直接回到自己的工作室或到有工作室的巫师家做客。
如果你有 'msg_home' 这个设定, 则在场的人都会看到那个讯息.
HELP
    );
    return 1;
}
