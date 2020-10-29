// cshort.c

#include <ansi.h>
#include <bunch.h>

protected void get_room_short(string str, object who, object env);
protected void change_room_short(object who, object env, string sdesc);

int main(object me, string arg)
{
        object env;
        string content;

        if(!me || (me != this_player(1)) || 
           !objectp(env = environment(me)))
                return 0;

        seteuid(getuid(this_object()));

        if(!BUNCH_D->is_valid_modify_room(me, env))
                return 0;

        if(!content = read_file(base_name(env)+".c"))
                return notify_fail("无法读取当前档案。\n");

        write("请输入房间的名称[2-6个汉字]('q'退出)：\n");
        input_to( (: get_room_short :), me, env );
        return 1;
}

protected void get_room_short(string sdesc, object who, object env)
{
        int l;

        if(!who || !env)
                return;

        if(!stringp(sdesc) || (sdesc == ""))
        {
                tell_object(who, "请输入房间的名称[2-6个汉字]，输入('q'退出)：\n");
                input_to( (: get_room_short :), who, env);
                return;
        }

        if( (sdesc[0] == 'q')
        || (sdesc[0] == 'Q') )
        {
                tell_object(who, "终止房间修改。\n");
                return;
        }

        if( ((l = strlen(sdesc)) < 4) || (l > 12) )
        {
                tell_object(who, "房间的名称必须为2-6个汉字，输入('q'退出)：\n");
                input_to( (: get_room_short :), who, env);
                return;
        }

        while(l--)
        {
                int section;

                if( sdesc[l]<128 )
                {
                        tell_object(who, "房间的名称必须使用中文，输入('q'退出)：\n");
                        input_to( (: get_room_short :), who, env);
                        return;
                }

                if( l%2==0 )
                {
                        section = sdesc[l] - 160;

                        if( (section < 16)
                        || (section > 87) )
                        {
                                tell_object(who,"\n房间的名称必须使用常用「汉字」，输入('q'退出)：\n");
                                input_to( (: get_room_short :), who, env);
                                return;
                        }
                }
        }

        change_room_short(who, env, sdesc);
}

protected void change_room_short(object who, object env, string sdesc)
{
        string newf, fname, content, f_sect, e_sect;

        if(!who || !env || !sdesc)
                return;

        if(environment(who) != env)
        {
                tell_object(who, "你的位置发生了变化，修改被停止。\n");
                return;
        }

        if(!content = read_file(fname = base_name(env)+".c"))
        {
                tell_object(who, "无法读取当前档案，修改失败。\n");
                return;
        }
        /*
        if(!BUNCH_D->parse_set_value(ref content, "short", ref f_sect, ref e_sect))
        {
                tell_object(who, "无法剖析当前档案，修改失败。\n");
                return;
        }
        */
        newf = sprintf("// Room: %s\n\n%s\n\tset(\"short\", \"%s\");\n%s\n",
                fname, f_sect, sdesc, e_sect);

        if(!write_file(fname, newf, 1))
        {
                tell_object(who, "无法写入档案，修改失败。\n");
                return;
        }

        if(!BUNCH_D->update_room(env))
        {
                tell_object(who, "重新载入房间错误，修改失败。\n");
                return;
        }
        tell_object(who, "修改成功。\n");
}
