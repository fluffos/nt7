// replace.c

#include <ansi.h>
inherit F_CLEAN_UP;

string *deep_file_list(string dir);

int main(object me, string arg)
{
        string str, dir, file, pattern, replace;
        string *result;
        int i;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0; 

        seteuid(geteuid(me)); 

        if (! arg || sscanf(arg, "%s %s to %s", dir, pattern, replace) != 3)
                return notify_fail("指令格式：replace <目录|文件名> <原字符> to <新字符>\n");

        replace = replace_string(replace, "\\t", "\t"); 
        replace = replace_string(replace, "\\n", "\n"); 
        replace = replace_string(replace, "\"\"", ""); 
                                  
        if (file_size(dir) == -1)
                dir=resolve_path(query("cwd", me),dir);

        if (! SECURITY_D->valid_write(dir, me)) 
                return notify_fail("没有足够的读写权限。\n"); 
                
        if (file_size(dir) > 0)
        {               
                str = read_file(dir);
                str = replace_string(str, pattern, replace);                            
                rm(dir);
                if (write_file(dir, str, 1))
                        write(HIW + dir + "替换成功。\n");
                else 
                        write(HIR + dir + "替换失败……\n");
                
                return 1;
        }

        if (file_size(dir) == -2 && dir[strlen(dir) - 1] != '/') dir += "/";
        if (file_size(dir) != -2) 
                return notify_fail("没有这个文件或目录。\n");
                        
        result = deep_path_list(dir);
        //result = deep_file_list(dir);
        
        for (i = 0; i < sizeof(result); i++)
        {
                reset_eval_cost();
                
                file = result[i];
                if (file_size(file) > 0)
                {   
                        str = read_file(file);
                        str = replace_string(str, pattern, replace);                            
                        rm(file);
                        if (write_file(file, str, 1))
                                write(HIW + file + "替换成功。\n");
                        else 
                                write(HIR + file + "替换失败……\n");                                                      
                }                
        }

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

int help(object me)
{
        write(@HELP
指令格式: replace <目录|文件名> <原字符> to <新字符>
将文件内容里的所有<原字串>转换成<新字串>。
注意∶如果指令目录，是会深入该目录下的所有目录提取文件进行虑理，要小心使用！
HELP );
        return 1;
}



