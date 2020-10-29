// replace.c
// Writed by Lonely

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string file, str, pattern, replace, *pats;
        object ob;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        seteuid(geteuid(me));

        if (!arg || sscanf(arg, "%s of %s to %s", pattern, file, replace) != 3)
                return notify_fail("指令格式 : replace <原字符串> of <档名> to <替换字符串>\n");

        file=resolve_path(query("cwd", me),file);

        if (file_size(file) < 0)
                return notify_fail("没有这个档案。\n");

        if (! SECURITY_D->valid_read(file, me, "read_file"))
                return notify_fail("你没有权限查看这个文件。\n");

        replace = replace_string(replace, "\\t", "\t");
        replace = replace_string(replace, "\\n", "\n");
        replace = replace_string(replace, "\"\"", "");

        str = read_file(file);

        /*
        pats = explode(pattern," ");
        foreach(string str1 in pats) {
                str = replace_string(str, str1, replace);
        }
        */
        str = replace_string(str, pattern, replace);

        rm( file );
        if(  write_file(file, str,1) )
                write(" 替换成功。\n");
        else write("失败……\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : replace <档案名>

这个指令让你XXXXX。

see also: cat
HELP );
        return 1;
}
