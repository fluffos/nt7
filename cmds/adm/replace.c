// replace.c

#include <ansi.h>
inherit F_CLEAN_UP;

int replace(string file, string oldstr, string newstr);
string *deep_file_list(string dir);
int help(object me);

int main(object me, string arg)
{
        string file, oldstr, newstr;
        mixed *dir;
        int i;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0; 

        if (! arg || sscanf(arg, "%s %s to %s", file, oldstr, newstr) != 3)
                return help(me);
          
        seteuid(geteuid(me)); 

        if (! SECURITY_D->valid_write(file, me)) 
                return notify_fail("没有足够的读写权限。\n"); 
                
        if (file_size(file) == -1 )
                file=resolve_path(query("cwd", me),file);

        if (file_size(file) > 0)
        {               
                replace(file, oldstr, newstr);
                return 1;
        }
        
        else if (file_size(file) == -2) 
        {
                dir = get_dir(file);
                reset_eval_cost();
                for (i = 0; i < sizeof(dir); i++)
                {
                        if (file_size(file + dir[i]) > 0)
                        {                               
                                replace(file + dir[i], oldstr, newstr);
                                write(HIW "\n " + file + dir[i] + "\n" NOR);
                        }

                }
                write(HIW "转换完毕。\n" NOR);
                return 1;
        }
        else return notify_fail("没有这个文件或目录。\n");
        return 1;  
}

string *deep_file_list(string dir)
{
        int i;
        string *flist, *result = ({ });
        string file;
        
        flist = get_dir(dir);

        for (i = 0; i < sizeof(flist); i++)
        {
                file = dir + flist[i];
                
                if (file_size(file + "/") == -2)
                        result += deep_file_list(file + "/");
                else 
                        result += ({ file });

        }
        return result;
}

int replace(string file, string oldstr, string newstr)
{
        string *text, *strings;
        string line;
        int i, j;
   
        j = 0;
        if (file_size(file) < 1)
                return 0;
   
        text = explode(read_file(file), "\n");
        rm(file);
        for (i = 0; i < sizeof(text); i++)
        {
                reset_eval_cost(); 
                if (strsrch(text[i], oldstr) == -1)
                {
                        write_file(file, text[i] + "\n");
                }
                else
                {
                        line = replace_string(text[i], oldstr, newstr);
                        write_file(file, line + "\n");
                        j++;
                } 
        }

        write(HIW + file + "共有" + j + "个" + oldstr + "被换成" + newstr + "。\n" NOR);
        return 1;
}
int help(object me)
{
write(@HELP
Written by ken@NT. All rights reserved.
E-mail: printken@yahoo.com.hk

指令格式: replace <目录或文件名> <原字符> to <新字符>
将文件内容里的所有<原字串>转换成<新字串>。
注意∶如果指令目录，是会深入该目录下的所有目录提取文件进行
虑理，要小心使用！(建意放在/cmds/adm/下)
HELP );
return 1;
}



