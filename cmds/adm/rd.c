// Written by Lonely@nitan.org

#include <ansi.h>
inherit F_CLEAN_UP;

int do_replace(string filename);
string *deep_file_list(string dir);

int main(object me, string arg)
{
        string str, dir, filename;
        string *result;
        int i, n = 0;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        seteuid(geteuid(me));

        if (! arg)
                return notify_fail("指令格式：rd <目录|文件名>\n");

        if (file_size(arg) == -1)
                arg = resolve_path(query("cwd", me), arg);

        filename = arg;

        if (! SECURITY_D->valid_write(filename, me))
                return notify_fail("没有足够的读写权限。\n");

        if (file_size(filename) > 0)
        {
                return do_replace(filename);
        }

        if (file_size(filename) == -2 && filename[strlen(filename) - 1] != '/') filename += "/";
        if (file_size(filename) != -2)
                return notify_fail("没有这个文件或目录。\n");

        result = deep_file_list(filename);

        for (i = 0; i < sizeof(result); i++)
        {
                reset_eval_cost();

                if (file_size(result[i]) > 0)
                {
                        /*
                        if( !is_c_file(result[i]) )
                                continue;
                        */
                        if( do_replace(result[i]) )
                                n++;
                }
        }
        write("目录" + filename + "总共有" + n + "个文件被成功转换。\n" NOR);

        return 1;
}

int do_replace(string filename)
{
        string file;
        string *lines;
        int i, n;
        string str3, str1, str2;

        file = read_file(filename);
        if( !file ) return 0;

        lines = explode(file, "\n");
        n = sizeof(lines);
        for (i = 0; i < n; i++)
        {
                reset_eval_cost();
                if( i+2 > n-1 ) break;

                str1 = lines[i];
                str2 = lines[i+1];
                str3 = lines[i+2];
                str1 = replace_string(str1, " ", "");
                str1 = replace_string(str1, "\t", "");
                str2 = replace_string(str2, " ", "");
                str2 = replace_string(str2, "\t", "");
                str3 = replace_string(str3, " ", "");
                str3 = replace_string(str3, "\t", "");
                
                if( str1 == "if(clonep())" && 
                    str2 == "set_default_object(__FILE__);" &&
                    (str3 == "else{" || str3 == "else")) {
                        lines[i] = replace_string(lines[i], "if", "/*if");
                        lines[i+2] = replace_string(lines[i+2], "else", "else*/");
                        break;
                }
        }

        rm(filename);
        if (write_file(filename, implode(lines, "\n")))
        {
                write(HIW + filename + "替换成功。\n");
                return 1;
        }
        else
        {
                write(HIR + filename + "替换失败……\n");
                return 0;
        }
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
                        continue;//result += deep_file_list(file + "/");
                else
                        result += ({ file });

        }
        return result;
}


