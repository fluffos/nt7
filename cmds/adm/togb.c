/***** Written by ken@NT.  All rights reserved. *****/
// togb.c
/****************************************************/
/* 中文字分两种，中国大陆用GB码，香港和台湾用BIG5码 */
/* 由于内码不同，就会出现乱码的情况，GB码的编码是由 */  
/* 0xa1 - 0xf7 ，BIG5码的编码是由 0x40 - 0x7e，因此 */
/* 我们做有两个字库，分别是字库 "BtoG.tab"   和字库 */ 
/* "GtoB.tab" ，在对应的字库中找出对应的文字， 这个 */
/* 动作由"/adm/daemons/languaed.c" 完成，本程序只需 */
/* 调用它里面的函数就可以了。                       */
/****************************************************/

inherit F_CLEAN_UP;
#define CONVERT "/adm/daemons/languaged.c"

protected int help(object me);
protected int to_gb(string file);
protected string *deep_file_list(string dir);

int main(object me, string arg)
{
        string file;
        mixed *dir;
        int i, total;

        if (!SECURITY_D->valid_grant(me, "(admin)"))
                return 0; 

        if (!arg || sscanf(arg, "%s", file) != 1) 
                return help( me );

        seteuid(geteuid(this_player(1)));
             
        if (!SECURITY_D->valid_write(file, me))
                return notify_fail("没有足够的读写权限.\n");

        if (file_size(file) == -1 )
                file=resolve_path(query("cwd", me),file);
   
        if (file_size(file) > 0)
        { 
                to_gb(file);
                write("\n目录∶"+file+"内所有文件转换完成.\n");
                return 1;
        }
   
        else if(file_size(file) == -2) 
        {
                dir = deep_file_list(file);
                for(i=0; i<sizeof(dir); i++)
                {
                        reset_eval_cost();
                        if ( file_size(dir[i]) > 0)
                        {
                                to_gb(dir[i]);
                                total = total + 1;
                                write("\n "+ dir[i] +" 文转换完成。\n");
                        }
                }
                write("\n目录∶"+file+"内所有文件转换完成.\n");
                return 1;
        }
        else return notify_fail("没有这个文件或目录.\n");
        return 1;               
}

protected string *deep_file_list(string dir)
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

protected int to_gb(string file)
{
        string *text;
        int i;   
        
        text = explode(read_file(file), "\n");
        rm(file);
        
        for(i=0; i<sizeof(text); i++)
        {
                text[i] = CONVERT-> toGB(text[i]);                      
                write_file(file, text[i]+"\n");
        }       
        return 1;
}

protected int help(object me) 
{ 
write(@HELP
Written by ken@NT. All rights reserved.
E-mail: printken@yahoo.com.hk

指令格式: togb <文件或目录> 
本指令可让你把文件或目录转换成GB码。
比如togb /d/　会把 /d/　下的所有文件及目录内的所有文都转成GB
我不建意使用转换目录，除非你很了解你想要做什么！
(此指令建议放在/cmds/adm/下)
注意：本命令比较危险，请小心使用。

HELP);
return 1;
}

