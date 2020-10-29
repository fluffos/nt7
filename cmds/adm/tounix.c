// tounix.c
// by zjpwxh@sjpl 2004.5.5
// rewrited by lonely


#include <ansi.h>
inherit F_CLEAN_UP;

#define MS sprintf("%c%c", 13, 10 )
#define CC sprintf("%c", 10 )

string *deep_file_list(string dir);
int convert_file(string file);

int main(object me, string arg)
{
        string file;
        mixed *dir;
        int i, total = 0;

        seteuid(geteuid(this_player(1)));

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;
                
        if (! arg || sscanf(arg, "%s", file) != 1) 
                return notify_fail("指令格式 tounix <file|dir>\n");
                
        if (! SECURITY_D->valid_write(file, me))
                return notify_fail("没有足够的读写权限.\n");

        if (file_size(file) == -1 )
                file=resolve_path(query("cwd", me),file);

        if (file_size(file) > 0)
        { 
                convert_file(file);
                write("ok.\n");
                return 1;
        }
        
        if (file_size(file) == -2 && file[strlen(file) - 1] != '/') 
                file += "/";

        if (file_size(file) != -2) 
                return notify_fail(file + " 并不是一个目录。\n");
                
        write(HIW "批量档案转换中，请稍候...\n" NOR);

        dir = deep_file_list(file);
        for(i = 0; i < sizeof(dir); i++)
        {
                reset_eval_cost();
                if (file_size(dir[i]) > 0)
                {
                        convert_file(dir[i]);
                        total++;
                        // write(dir[i] +" 文转换完成。\n");
                }
        }
        write("\n目录∶" + file + "内所有文件转换完成。\n");

        if (total > 0)
                write(HIC "总共有 " + HIW + total + HIC " 个档案被成功转换为 UNIX 格式！\n" NOR);
        else
                write(HIC "没有转换任何档案。\n" NOR);
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
                {
                        if (file[strlen(file) - 1] == 'o' && 
                            file[strlen(file) - 2] == '.')
                                continue;
                                
                        result += ({ file });
                }

        }
        return result;
}

int convert_file(string file)
{
        string text;

        text = read_file(file);

        if (! text)
        {
                write(sprintf("read file %s error!\n", file));
                return 0;
        }

        text = replace_string(text, MS, CC);
        write_file(file, text, 1);
        return 1;
}
