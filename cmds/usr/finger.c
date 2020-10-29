// finger.c

inherit F_CLEAN_UP;

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        object *ob;

        if( !wizardp(me) && time()-query_temp("last_finger", me)<10 )
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");  

        set_temp("last_finger", time(), me);

        if (! arg)
        {
                if( !wizardp(me) )
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");  
                if( query("jing", me)<50 )
                        return notify_fail("你的精神无法集中。\n");

                if (! wizardp(me))
                        me->receive_damage("jing", 50);

                me->start_more(FINGER_D->finger_all());
        } else
        if (arg == "-m")
        {
                if (! wizardp(this_player()))
                        return notify_fail("你无权使用 -m 参数。\n");
                ob = filter_array(users(), (: $1->name() != $1->name(1) :));
                me->start_more(FINGER_D->user_list(ob), 0);
        } else
        {
                if( query("jing", me)<15 )
                        return notify_fail("你的精神无法集中。\n");

                if (! wizardp(me))
                        me->receive_damage("jing", 15);

                if ((arg == "lonely") && ! wizardp(me))
                        return notify_fail("没有这个玩家。\n");

                write(FINGER_D->finger_user(arg));
        }
        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : finger [-m] [使用者姓名]
 
这个指令，如果没有指定使用者姓明，会显示出所有正在线上玩家
的连线资料。反之，则可显示有关某个玩家的连线，权限等资料。
如果使用了 -m 参数，可以列出使用面具的玩家。
 
see also : who
HELP );
    return 1;
}
