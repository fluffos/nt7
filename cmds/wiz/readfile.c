#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string file,result;
        object ob;
        int a,b,x;
        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(geteuid(me));
        if (! arg) return notify_fail("指令格式 : readfile <档名>|<物件名>,n1,n2  n1表示开始行，n2表示终止行。n1,n2没有则与more指令一样，嘿嘿。\n");
        if (sscanf(arg, "%s,%d,%d", arg, a, x) != 3)
                return notify_fail("请输入行数：n1,n2。\n");
        if ( a <= 0 || x < 0 || x - a < 0)
                return notify_fail("你真有思想，佩服。\n");
        file=resolve_path(query("cwd", me),arg);
        if (file_size(file) < 0)
        {
                ob = present(arg, me);
                if (! ob) ob = present(arg, environment(me));
                if (! ob) return notify_fail("没有这个档案。\n");
                file = base_name(ob) + ".c";
        }
        if (! SECURITY_D->valid_read(file, me, "read_file"))
                return notify_fail("你没有权限查看这个文件。\n");

                b = x - a + 1;

        message("", HIG "您所阅读的文件为"HIY + file + NOR "\n"
                                HIG "您所选取的是从第"  HIW + a + NOR  HIG "行到第"  HIW + x + NOR HIG"行\n"
                                HIG "具体内容如下：\n"NOR,me);
        result = HIC + read_file(file,a,b) + "\n";
        me->start_more(result);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : readfile <档案名>,起始行数，结束行数
HELP );
        return 1;
}
