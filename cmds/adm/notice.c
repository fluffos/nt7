// This program is a part of NITAN MudLIB
// notice.c

#include <ansi.h>
#include <login.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string msg)
{
        string *lines;
        string arg;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if( !msg || msg == "" )
        {
                if( file_size(NOTICE) < 0 )
                {
                        write("现在没有设定任何连线通知\n");
                        write("--------------------------------------------\n\n");
                        return help(me);
                }

                arg = read_file(NOTICE);
                write("你现在所设定的连线通知是：\n");
                write("--------------------------------------------\n\n");

                if( strlen(arg) > 8190 )
                        me->start_more(arg);
                else
                        write(arg);

                return 1;
        }

        if( msg == "-rm" )
        {
                rm(NOTICE);
                write("通知已被清除!\n");
                return 1;
        }

        msg = replace_string(msg, "\\t", "\t");
        msg = replace_string(msg, "\\n", "\n");
        msg = replace_string(msg, "\"\"", "");

        lines = explode(msg, "\n");
        for( int i=0; i<sizeof(lines); i++ )
                if ( i % 2 == 0)
                        lines[i] = BLINK + REDYEL "█" NOR "  " + lines[i];
                else
                        lines[i] = BLINK + YELRED "█" NOR "  " + lines[i];

        msg = implode(lines, "\n") + "\n";
        msg = color_filter(msg);
        msg += NOR;
        write_file(NOTICE, msg, 1);
        write("连线通知加入完毕。\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: notice <通知内容>

改指令用来添加玩家连线后的通知信息，如无必要尽量少用
notice -rm 用来清除信息。
HELP
        );
        return 1;
}

