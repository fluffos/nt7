// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// ls.c

#include <ansi.h>

inherit F_CLEAN_UP;

int filter_list(mixed ob, string path, object user);
int sort_list(mixed ob1, mixed ob2);

int main(object me, string arg)
{
        int i, j, w, x, col;
        string dir;
        string path;
        int opt_l,files,dirs,k;
        mixed *file;
        string result;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;
                
        if (arg)
        {
                if (arg == "-l")
                {
                        opt_l = 1;
                        arg = 0;
                } else
                        if (sscanf(arg, "%s -l", arg) || sscanf(arg, "-l %s", arg))
                        {
                                opt_l = 1;
                        } else
                                opt_l = 0;
        }
        
        dir=resolve_path(query("cwd", me),arg);
        
        if (me != this_player(1))
                return notify_fail("不是当前使用者进行操作。\n");
                
        seteuid(getuid());
        if (file_size(dir) == -2 && dir[strlen(dir) - 1] != '/') dir += "/";
        
        if (file_size(dir) == -2)
        {
                path = dir;
        } else
        {
                string *p;
                p = explode(dir, "/");
                if (sizeof(p) >= 2)
                {
                        p = p[0..sizeof(p) - 2];
                        path = "/" + implode(p, "/") + "/";
                } else
                        path = "/";
                p = 0;
        }
        
        file = get_dir(dir, -1);
        seteuid(geteuid(me));
        
        if (! sizeof(file))
        {
                if (file_size(dir) == -2)
                        return notify_fail(sprintf("目录(%s)是空的。\n", dir));
                else
                        return notify_fail(sprintf("没有这个目录(%s)。\n", dir));
        }
        
        file = filter_array(file, (: filter_list :), path, me);
        file = sort_array(file, (: sort_list :));
        
        i = sizeof(file);
        x = 0;
        k = 0;
        w = 0;
        while (i--)
        {
                if (file[i][1] == -2)
                {
                        file[i][0] += "/";
                        x++;
                }
                if (strlen(file[i][0]) > w) w = strlen(file[i][0]) + 1;
                file[i] += ({ MASTER_OB->valid_write(path + file[i][0], me, "ls") });
        }
        result = "目录：" + path + "\n";
        files = sizeof(file) - x;
        dirs = x;
        if (! sizeof(file))
        {
                write(sprintf("%s    没有任何档案。\n\n", result));
                return 1;
        }
        
        if (opt_l)
        {
                string syntax;
                syntax = sprintf("%%s%%-%ds  %%-8s  %%-8s  %%s\n" NOR, w);
                result += sprintf(syntax, HIR, "文件名", "大小", "是否装载", "最后更改时间");
                col = 82 / (w + 6);
                for (i = 0, j = sizeof(file); i < j; i++)
                result += sprintf(syntax,
                                  (file[i][3] ? NOR : HIR),
                                  file[i][0],
                                  (file[i][1] == -2 ? "<dir>" : sprintf("%d", file[i][1])),
                                  ((file[i][1] != -2 && find_object(path + file[i][0])) ? HIC "编译装载" NOR : NOR "--------"),
                                  CHINESE_D->chinese_time(5, ctime(file[i][2])));
        } else
        {
                col = 82 / (w + 6);
                for (i = 0, j = sizeof(file); i < j; i++) {
                        result += sprintf("%s%-*s%6s%s"NOR,
                                          (file[i][3] ? (file[i][1] == -2 || find_object(path + file[i][0])? HIC:GRN) : HIR),
                                           w + 1,file[i][0] ,
                                          (file[i][1]==-2 ? " [37m<DIR>[0m" : sprintf("%4dk", (file[i][1]+1023)/1024)),
                                          ((i+1)%col)?" [1;33m| [0m":"\n" );
                        k += ((file[i][1]+1023)/1024);
                }
        }
        me->start_more(result);
//        write(result);
        printf("\n                    文件有：%d 个，总共：%d K ，目录共有：%d 。\n", files, k, dirs);
        
        return 1;
}

int filter_list(mixed ob, string path, object user)
{
        return MASTER_OB->valid_read(path + ob[0], user, "ls");
}

int sort_list(mixed ob1, mixed ob2)
{
        if (ob1[1] == -2 && ob2[1] != -2)
                return -1;
                
        if (ob1[1] != -2 && ob2[1] == -2)
                return 1;
                
        return strcmp(ob1[0], ob2[0]);
}

int help(object me)
{
        write(@HELP
指令格式: ls [-l] [<路径名>]
 
列出目录下所有的子目录及档案, 如果没有指定目录, 则列出所在目录
的内容，所列出的档案中，白色的代表路径或是已经载入的物件对应的
文件，正常色的代表普通的文件。红色则表示你对该目录或文件没有写
入权限。-l参数可以列出详细资料。
 
范例:
'ls /' 会列出所有位於根目录下的档案及子目录。
'ls /adm/*.c -l' 则会列出/adm/目录下面所有以.c结尾的文件的详细
资料列表。
 
HELP );
        return 1;
}