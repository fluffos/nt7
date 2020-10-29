// cline.c 清除末尾几行

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int n;
        string msg;

        if (! stringp(arg) || ! sscanf(arg, "%d", n))
                n = 24;

        if (n < 1 || n > 500)
        {
                write("参数错误。\n");
                return 1;
        }

        msg = "";
        while (n--)
                msg += ESC "[1A" ESC "[K";

        write(msg);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : cline [<行数>]

此指令可让你清除最后几行文字，做什么用？自己想吧。
HELP );
        return 1;
}