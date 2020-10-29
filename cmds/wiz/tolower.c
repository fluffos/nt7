// tolower.c
// Written by ken@NT
// All rights reserved

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg);
protected int Ctoc(string file);
protected string *deep_file_list(string dir);
protected int help(object me);

int main(object me, string arg)
{
        string dir, flag;
        mixed *file;
        int i, len, total = 0;

        if (!SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;
        
        if (!arg || sscanf(arg, "%s", dir) != 1)
                return help( me );
                
        seteuid(geteuid(me));
        if (!SECURITY_D->valid_write(dir, me))
                return notify_fail("没有足够的读写权限.\n");
                
        else if(file_size(dir) == -2) 
        {
                file = deep_file_list(dir);
                             
                reset_eval_cost();
                for(i=0; i<sizeof(file); i++)
                {                       
                        len = strlen(file[i]);
                        if (file[i][len-2..len-1] == ".C")
                        {                               
                                Ctoc(file[i]);
                                total = total + 1;
                        }
                }
                write(HIW "共有" + total + "个文件虽要处理\n");
                write(HIW "所有文件处理完毕.\n" NOR);
                return 1;
        }
        else return notify_fail("没有这个目录.\n");
        return 1;  
}

protected string *deep_file_list(string dir)
{
        int i;
        string *flist;
        string *result = ({ });
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

protected int Ctoc(string file)
{
        write("把" + file + "转文小写(*.C->*.c)\n");
        rename(file , lower_case(file));
        return 1;
}
protected int help(object me)
{
write(@HELP
Written by ken@NT. All rights reserved.
E-mail: printken@yahoo.com.hk

将目录及该目录下的所有大写文件转换成小写文件.
格式 : tolower <目录>
HELP);
return 1;
}

