// more.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string file;
        object ob;
        int    with_line_number = 1;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(geteuid(me));

        if (! arg) return notify_fail("指令格式 : more <档名>|<物件名> \n");

        if (sscanf(arg, "%s -n", file)) with_line_number = 0;
        else file = arg;

        file = resolve_path(query("cwd", me), file);
        if (file_size(file) < 0)
        {
                ob = present(arg, me);
                if (! ob) ob = present(arg, environment(me));
                if (! ob) return notify_fail("没有这个档案。\n");
                file = base_name(ob) + ".c";
        }

        if (! SECURITY_D->valid_read(file, me, "read_file"))
                return notify_fail("没有这个档案。\n");

        if (with_line_number)
                me->start_more_file(file);
        else me->start_more(read_file(file));

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : more <档案名> [-n]

这个指令让你可以以分页方式查阅一个文件的内容。如果带 -n
参数，则表示不显示行号。

see also: cat
HELP );
        return 1;
}
