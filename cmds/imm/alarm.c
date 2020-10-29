// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// alarm.c

#include <ansi.h>
inherit F_CLEAN_UP;

#define SHOUT_LIST      ({ })

int help(object me);
void create() {seteuid(getuid());}


int main(object me, string arg)
{
        object ob;
        string target, msg, mud,from;
        object obj;

        if (! SECURITY_D->valid_grant(me, "(immortal)"))
                return 0;
                        
        if (! arg || sscanf(arg, "%s %s", target, msg) != 2) 
                return help(me);
                
        obj = find_player(target);
        write(HIG "\n 你警告" + obj->name(1) + "，因其" + msg + "的行为。 \n" NOR);
        
        tell_object(obj, sprintf( HIR "\n 游戏管理者警告你：\n \n \n \n" + "      你的" HIW "「%s」" HIR "行为违反了游戏规则，请输入"HIW" help rules "HIR"查询游戏规则，特此警告。\n \n"+"      如有任何问题，请立刻申诉。若有再犯，将按照规则处理。\n \n \n \n \n \n" NOR, msg));

        if (! wizardp(me) && member_array(query("id", me), SHOUT_LIST) == -1)
                return notify_fail("目前暂不开放玩家 shout。\n");
                
        if (! arg) return notify_fail("你想要大叫什么？\n");

        shout( HIG "【系统】泥潭公告："+ obj->name(1) + "因为" + msg + "被系统警告。\n" NOR );
        write( HIG "【系统】泥潭公告："+ obj->name(1) + "因为" + msg + "被系统警告。\n" NOR );

        return 1;
}




int help(object me)
{
        write(@HELP
指令格式：alarm <某人> <讯息>
你可以用这个指令警告违反规则的玩家。
同时神仙保留不经警告就直接处理违规玩家的权利。
HELP
        );
        return 1;
}
