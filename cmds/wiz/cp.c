// This program is a part of NITAN MudLIB
// cp.c

#include <ansi.h>

inherit F_CLEAN_UP;

int copy_dir(string src, string dst, int dir_existed, int copy_filter);
int help(object me);

// value of call parameter
#define DIR_EXISTED             1
#define DIR_MAY_NOT_EXISTED     0

int main(object me, string arg)
{
        string *fn;
        string src, dst, dir;
        int copy_dir;
        int copy_filter = 0;
        int count;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(geteuid(me));

        if (! arg)
        {
                help(me);
                return 1;
        }

        if (sscanf(arg, "-R %s %s", src, dst) == 2)
        {
                if (me && ! is_root(me))
                {
                        write("只有管理员才能使用 -R 参数。\n");
                        return 1;
                }

                copy_dir = 1;
        } else
        if (sscanf(arg, "-F %s %s", src, dst) == 2)
        {
                if (me && ! is_root(me))
                {
                        write("只有管理员才能使用 -F 参数。\n");
                        return 1;
                }

                copy_filter = 1;
        } else
        if (sscanf(arg, "%s %s", src, dst) == 2)
        {
                copy_dir = 0;
        } else
        {
                write("格式错误！\n");
                help(me);
                return 1;
        }

        src=resolve_path(query("cwd", me),src);
        dst=resolve_path(query("cwd", me),dst);
        if (! me->is_admin()) 
        {
                dir = SECURITY_D->query_site_privilege("edit");
                if( !dir && !sscanf(dst, "/u/%*s") )
                        return notify_fail("你只能复制文件到你自己的目录下。\n");
                        
                if( dir != "all" && !sscanf(dst, "/%s/%*s", dir) )
                        return notify_fail("你只能复制文件到你自己目录下以及" + dir + "目录下。\n");
        }
        switch (file_size(src))
        {
        case -1:
                if (copy_filter) break;
                write("没有这个(" + src + ")文件或目录，无法复制。\n");
                return 1;

        case -2:
                if (copy_dir) break;
                write("没有指定 -R 参数，不能复制目录(" + src + ")。\n");
                return 1;
        default:
                // copy file, not directory.
                copy_dir = 0;
                break;
        }

        if (! copy_dir && ! copy_filter)
        {
                if (file_size(dst) == -2)
                {
                        // destination is a directory
                        fn = explode(src, "/");
                        dst += "/" + fn[sizeof(fn) - 1];
                        fn = 0;
                }

                SECURITY_D->backup_file(dst);
                if (cp(src, dst) == 1)
                        write("Ok.\n");
                else
                {
                        if (! SECURITY_D->valid_read(src, me, "ls"))
                                write("没有这个(" + src + ")文件或目录，无法复制。\n");
                        else
                                write("你没有权限复制这个文件。\n");
                }
                return 1;
        }

        if (strlen(dst) >= strlen(src) && dst[0..strlen(src) - 1] == src)
        {
                write("你不能将一个路径复制到自身或者是子路径中。\n");
                return 1;
        }

        switch (file_size(dst))
        {
        case -2:
                // destination is a directory
                fn = explode(src, "/");
                if (! copy_filter)
                        dst += "/" + fn[sizeof(fn) - 1];
                fn = 0;
                break;
        case -1:
                // no destination
                break;

        default:
                // destition is a file, error
                write("目录不能复制到文件内，请修正你的目的路径。\n");
                return 1;
        }

        message_system(HIC "复制目录中，请稍候..." NOR);

        count = copy_dir(src, dst, DIR_MAY_NOT_EXISTED, copy_filter);
        if (count)
                write(HIY "总共有" + count + "个文件被成功复制。\n" NOR);
        return 1;
}

int copy_dir(string src, string dst, int dir_existed, int copy_filter)
{
        mixed *file;
        int count;
        int i;

        if (! is_root(previous_object()))
                return 0;

        count = 0;
        if (! copy_filter && 
            src[strlen(src) - 1] != '/') src += "/";
        if (dst[strlen(dst) - 1] != '/') dst += "/";

        // assure dst existed
        if (! dir_existed) assure_file(dst);

        file = get_dir(src, -1);
        if (! sizeof(file))
                return count;

        if (copy_filter)
        {
                int idx = strsrch(src, "/", -1); 
                
                if (idx == -1 || idx == 0) return count;
                src = src[0..idx]; 
                write (HIC "复制目录(" + src + ")中符合条件文件 -- > (" + dst + ")。\n" NOR);
        } else        
                write (HIC "复制目录(" + src + ") -- > (" + dst + ")。\n" NOR);
                
        i = sizeof(file);
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] != -2)
                        if (cp(src + file[i][0], dst + file[i][0]))
                                count++;
        }

        i = sizeof(file);
        while (i--)
        {
                reset_eval_cost();
                if (file[i][1] == -2)
                {
                        mkdir(dst + file[i][0]);
                        count += copy_dir(src + file[i][0],
                                          dst + file[i][0],
                                          DIR_EXISTED, copy_filter);
                }
        }
        return count;
}

int help(object me)
{
        write(@HELP
指令格式 : cp [-R|-F] <文件|路径名> <目的文件|目的路径名>
 
这个指令可以复制源文件成目的文件或复制到目的路径。如果使用了参数-R则
可以复制一个目录，没有这个参数则不能复制路径。

see also: rm, mv
HELP );
        return 1;
}
