// employ.c

#include <ansi.h>
inherit F_CLEAN_UP;

#ifndef DB_D
#define DB_D      "/adm/daemons/dbd.c"
#endif

int main(object me, string arg)
{
        object ob;
        string old_status, new_status;
        int my_level, ob_level, level;
        string *tlist;

        mapping job = ([
                       "新手导师"  :  "teacher.c",
                       "高手导师"  :  "master.c",
                       "主页维护"  :  "webmaster.c",
                       "游戏宣传"  :  "presell.c",
        ]);

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg || sscanf(arg, "%s %s", arg, new_status) != 2)
                return notify_fail("指令格式：employ <使用者> <职位>\n");

        if (new_status != "新手导师" &&
            new_status != "高手导师" &&
            new_status != "主页维护" &&
            new_status != "游戏宣传" &&
            new_status != "取消雇佣" )
                return notify_fail("没有这种职位。\n");

/*
        if (! objectp(ob = present(arg, environment(me))) ||
            ! playerp(ob))
*/
        ob = UPDATE_D->global_find_player(arg); 
        if (! objectp(ob)) 
                return notify_fail("你只能改变使用者的职位。\n");

        if( query("viremploy/job", ob) == new_status )
        {
                UPDATE_D->global_destruct_player(ob, 1); 
                return notify_fail("该玩家已经担任该职位。\n");
        }

        if (new_status == "取消雇佣")
        {
                  if( !mapp(query("viremploy", ob)) )
                  {
                        UPDATE_D->global_destruct_player(ob, 1); 
                           return notify_fail("该玩家没有担任任何职位。\n");
                  }

                  CHANNEL_D->do_channel(this_object(), "rumor",
                             ob->name()+"("+query("id", ob)+")所担任"
                             "的职位："+query("viremploy/job", ob)+"被取消了！\n");

                // 新手导师需要移除记录
                if( query("viremploy/job", ob) == "新手导师" )
                {
                        tlist = DB_D->query_data("virlist/teacher");
                        if (sizeof(tlist))
                        {
                                if( member_array(query("id", ob),tlist) != -1 )
                                {
                                        tlist-=({query("id", ob)});
                                        DB_D->set_data("virlist/teacher", tlist);
                                }
                        }
                }

                delete("viremploy", ob);
                delete("flowers", ob);
                SECURITY_D->remove_grant(query("id", ob),"home");
                tell_object(ob, HIG + me->name(1) + "收回了你 home 的权限。\n" NOR);
                ob->save();
                UPDATE_D->global_destruct_player(ob, 1); 

                return 1;
        }

        CHANNEL_D->do_channel(this_object(), "rumor",
                             ob->name()+"("+query("id", ob)+")被任命为"+HIG+
                             new_status + NOR + "。\n");

        set("viremploy/job", new_status, ob);
        delete("flowers", ob);

        // 新手导师需要记录
        if (new_status == "新手导师")
        {
                tlist = DB_D->query_data("virlist/teacher");
                if (sizeof(tlist))
                {
                        tlist+=({query("id", ob)});
                        DB_D->set_data("virlist/teacher", tlist);
                }
                else
                {
                        DB_D->set_data("virlist/teacher",({query("id", ob)}));
                }
        }

        set("viremploy/workroom", job[new_status], ob);
        SECURITY_D->grant(query("id", ob),"home");
        tell_object(ob, HIG + me->name(1) + "授予了你 home 的权限。\n" NOR);

        ob->save();
        UPDATE_D->global_destruct_player(ob, 1); 

        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : employ <某人> (权限等级)

用来提升权限等级, [主页维护、游戏宣传、新手导师、巫师助理]

           employ <某人> 取消雇佣

取消该虚拟工作人员的职位。

HELP );
    return 1;
}
