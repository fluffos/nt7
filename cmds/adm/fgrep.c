#include <ansi.h>
#include <feature.h>
#include <message.h>

inherit COMMAND;

string help = @HELP
指令格式：fgrep [-l] [-r] <样式> [路径]

显示档案中有相符样式的的行, <样式> 可为正规表示法(regular expression)
欲知正规表示法的用法可 help regexp() 以取得更进一步资讯。

详关参数说明如下：

-l      显示行号
-r      显示不符合 <样式> 行
HELP;
string last_file;
mapping grep(string path, string *files, string pattern, int flag);
private void command(object me, string arg)
{
        string path, *files;
        mapping match_files;
        int fsize, flag, gcnt, fcnt;

        if( !arg )
        {
                printf("指令格式：fgrep [-l] [-r] <样式> [路径]\n");
                return;
        }
        if( sscanf(arg, "-l %s", arg) ) flag  = 1;
        if( sscanf(arg, "-r %s", arg) ) flag += 2;
        if( sscanf(arg, "'%*s' %*s") == 2 )
                sscanf(arg, "'%s' %s", arg, path);
        else if( sscanf(arg, "'%*s'") )
                sscanf(arg, "'%s'", arg);
        else if( sscanf(arg, "%*s %*s") == 2 )
                sscanf(arg, "%s %s", arg, path);

        if( arg )
        {
                int idx, chr, marked, i, j;
                for(idx=0; idx<strlen(arg); idx++)
                {
                        chr = arg[idx];
                        marked = idx && arg[idx-1] == '\\';
                        if( chr == '(' && !marked ) i++;
                        if( chr == ')' && !marked ) i--;
                        if( chr == '[' && !marked ) j++;
                        if( chr == '[' && !marked ) j--;
                }
                if( i )
                {
                        printf("fgrep: 参数 <样式> 格式错误，() 必须为一对。\n", arg);
                        return;
                }
                if( j )
                {
                        printf("fgrep: 参数 <样式> 格式错误，[] 必须为一对。\n", arg);
                        return;
                }
        }
        
        path = resolve_path(me, path);
        
        fsize = file_size(path);
        
        if( fsize == -2 )
        {
                if( path[<1] != '/' ) path += "/";
                files = get_dir(path);
        }
        else
        {
                int idx = strsrch(path, '/', -1);
                files = get_dir(path);
                path = path[0..idx];
        }
        if( !files )
                return tell(me, "fgrep: 没有 " + path + " 这个档案或目录。\n", CMDMSG);

        if( !sizeof(files) )
                return tell(me, "fgrep: 在 " + path + " 目录中没有任何档案。\n", CMDMSG);

        tell(me, sprintf(HIY"搜寻样式"HIW" %s "NOR + HIY"于 %s ... \n\n"NOR, arg, path), CMDMSG);
        
        match_files = grep(path, files, arg, flag);
        foreach(string file, mixed match in match_files)
        {
                gcnt = sizeof(match);
                if( !gcnt ) continue;
                for(int i=0; i<gcnt; i++)

                {
                        if( flag%2 && !(i%2) )
                        {
                                tell(me, sprintf(HIW"%4d- "NOR, match[i+1]), CMDMSG);
                        }
                        
                        tell(me, sprintf("%s\n"NOR, match[i]), CMDMSG);
                        if( flag ) i++;
                }
                if( flag ) gcnt = gcnt/2;
                tell(me, sprintf(HIR"在 %s 档案中共找到 %d 个符合结果。\n\n"NOR, path + file, gcnt), CMDMSG);
                fcnt ++;
        }
        
        tell(me, sprintf(HIY"共 %d 个档案符合比对样式。\n"NOR, fcnt), CMDMSG);
}

mapping grep(string path, string *files, string pattern, int flag)
{
        string *lines;
        mapping match_files = allocate_mapping(0);
        mixed match;

        if( path[<1] != '/' ) path += "/";
        foreach(string file in files)
        {
                last_file = path + file;
                if( file_size(last_file) < 0 ) continue;
                lines = explode(read_file(path + file), "\n");
                match = regexp(lines, pattern, flag);
                if( match ) match_files[file] = match;
        }
        return match_files;
}
string query_last_file()
{
        return last_file;
}

