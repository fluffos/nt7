// clong.c

#include <ansi.h>
#include <bunch.h>

protected void get_room_long(string str, object who, object env, string ldesc);
protected void change_room_long(object who, object env, string ldesc);

int main(object me, string arg)
{
        object env;
        string content;

        if(!me || (me != this_player(1)) || !objectp(env = environment(me)))
                return 0;

        seteuid(getuid(this_object()));

        if(!BUNCH_D->valid_modify_room(me, env))
                return 0;

        if(!content = read_file(base_name(env)+".c"))
                return notify_fail("无法读取当前档案");

        write(sprintf("请为%s设定新的描述：
·为了房间的美观，每一行请不要超过%s个中文字
·第一行的内容长度比其它行的长度少两个中文字宽才能对齐
·描述内容不能超过%s行\n请输入('.'结束输入，'q'退出)：\n------------------------------------------------------\n",
                query("short", env),chinese_number(room_desc_l/2),chinese_number(room_desc_h)));

        input_to( (: get_room_long :), me, env, "" );
        return 1;
}

protected void get_room_long(string str, object who, object env, string ldesc)
{
        if(!who || !env)
                return;

        if(!stringp(str) || (str == ""))
        {
                input_to( (: get_room_long :), who, env, ldesc );
                return;
        }

        if( (str[0] == 'q')
        || (str[0] == 'Q') )
        {
                tell_object(who, "终止房间修改。\n");
                return;
        }

        if(str[0] == '.')       // 结束输入
        {
                if( (ldesc == "") || (sizeof(ldesc) < 10) )
                {
                        tell_object(who,"你没有设定足够的描述内容\n房屋修改失败\n");
                        return;
                }

                if( sizeof(explode(ldesc, "\n")) > room_desc_h)
                {
                        tell_object(who, sprintf(HBCYN HIG"·描述内容不能超过%s行\n房屋修改失败。\n"NOR, chinese_number(room_desc_h)));
                        return;
                }

                change_room_long(who, env, ldesc);
                return;
        }

        if(strsrch(str, '\n'))
        {
                int n;
                string *tmp;

                n = sizeof(tmp = explode(str, "\n"));
                for(int i=0; i<n; i++)
                        if(strlen(tmp[i]) > room_desc_l)
                        {
                                tell_object(who, sprintf(HBCYN HIG"每一行不能超过%s个中文字，请重新输入上一次输入的内容：\n"NOR, chinese_number(room_desc_l/2)));
                                input_to( (: get_room_long :), who, env, ldesc );
                                return;
                        }

                if((n + sizeof(explode(ldesc, "\n"))) > room_desc_h)
                {
                        tell_object(who, sprintf(HBCYN HIG"·描述内容不能超过%s行\n房屋创建失败。\n"NOR, chinese_number(room_desc_h)));
                        return;
                }
        }

        else
        {
                if(strlen(str) > room_desc_l)
                {
                        tell_object(who, sprintf(HBCYN HIG"每一行不能超过%s个中文字，请重新输入上一次输入的内容：\n"NOR, chinese_number(room_desc_l/2)));
                        input_to( (: get_room_long :), who, env, ldesc );
                        return;
                }

                if( sizeof(explode(ldesc, "\n")) > (room_desc_h -1) )
                {
                        tell_object(who, sprintf(HBCYN HIG"·描述内容不能超过%s行\n房屋创建失败。\n"NOR, chinese_number(room_desc_h)));
                        return;
                }
        }

        ldesc += str + "\n";
        input_to( (: get_room_long :), who, env, ldesc );
}

protected void change_room_long(object who, object env, string ldesc)
{
        string newf, fname, content, f_sect, e_sect;

        if(!who || !env || !ldesc)
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
        if(!BUNCH_D->parse_set_value(ref content, "long", ref f_sect, ref e_sect))
        {
                tell_object(who, "无法剖析当前档案，修改失败。\n");
                return;
        }
        */
        newf = sprintf("// Room: %s\n\n%s\n\tset(\"long\", @LONG\n%sLONG\n);\n%s\n",
                fname, f_sect, ldesc, e_sect);

        if(!write_file(fname, newf, 1))
        {
                tell_object(who, "无法写入档案，修改失败。\n");
                return;
        }

        if( !BUNCH_D->update_room(env) )
        {
                tell_object(who, "重新载入房间错误，修改失败。\n");
                return;
        }
        tell_object(who, "修改成功。\n");
}
