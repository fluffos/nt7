// Written by Lonely@nitan.org
// rpefun.c

#include <ansi.h>
inherit F_CLEAN_UP;

int do_replace(string filename);
varargs string *deep_file_list(string dir, int times);
string get_leadspace(string arg)
{
        int i;

        if( !stringp(arg) || arg =="" )
                return "";
        for( i = 0; i < strlen(arg); i++ )
                if( arg[i..i] != " " )
                        return arg[0..i-1];
        return "";
}

int valid_str(string who)
{
        if( strsrch(who, "!") != -1
        ||  strsrch(who, "?") != -1
        ||  strsrch(who, ":") != -1
        ||  strsrch(who, "=") != -1
        ||  strsrch(who, "|") != -1
        ||  strsrch(who, "&") != -1
        ||  strsrch(who, ",") != -1
        ||  strsrch(who, "+") != -1
        ||  strsrch(who, "-") != -1
        ||  strsrch(who, "*") != -1
        ||  strsrch(who, "/") != -1
        ||  strsrch(who, "{") != -1
        ||  strsrch(who, ">") != -1
        ||  strsrch(who, "<") != -1 )
                return 0;

        return 1;
}

string restore_space(string arg)
{
        int l;

        if( !stringp(arg) || arg =="" )
                return "";

        arg = replace_string(arg, "return", "return ");
        arg = replace_string(arg, "else", "else ");
        arg = replace_string(arg, "||", " || ");
        arg = replace_string(arg, "&&", " && ");
        arg = replace_string(arg, "!=", " != ");
        arg = replace_string(arg, "==", " == ");
        arg = replace_string(arg, ">=", " >= ");
        arg = replace_string(arg, "<=", " <= ");
        arg = replace_string(arg, "if(", "if( ");

        l = strlen(arg);
        if( arg[l-1..l-1] == ")" )
                arg = arg[0..l-2]+" )";

        return arg;
}

int main(object me, string arg)
{
        string str, dir, filename;
        string *result;
        int i, n = 0;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        seteuid(geteuid(me));

        if (! arg)
                return notify_fail("指令格式：rpefun <目录|文件名>\n");

        if (file_size(arg) == -1)
                arg = resolve_path(query("cwd", me), arg);

        filename = arg;

        if (! SECURITY_D->valid_write(filename, me))
                return notify_fail("没有足够的读写权限。\n");

        if (file_size(filename) > 0)
        {
                return do_replace(filename);
        }

/*
        if (file_size(filename) == -2 && filename[strlen(filename) - 1] != '/') filename += "/";
        if (file_size(filename) != -2)
                return notify_fail("没有这个文件或目录。\n");
*/

        result = deep_file_list(filename, 1);

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
        string leadspace;
        string file;
        string *lines;
        int i, n;
        int idx;
        string tmp1, tmp2, str, str1, str2;
        string index, who;
        mixed value;

        file = read_file(filename);
        if( !file ) return 0;

        lines = explode(file, "\n");
        n = sizeof(lines);
        for (i = 0; i < n; i++)
        {
                reset_eval_cost();

                str = lines[i];
                str = replace_string(str, "add(", "addn(");
                lines[i] = replace_string(str, "add_temp(", "addn_temp(");

                str = replace_string(lines[i], " ", "");
                if( str[0..1] == "//" ) continue;
                if( strsrch(str, "->set(") == -1 &&
                    strsrch(str, "->set_temp(") == -1 &&
                    strsrch(str, "->addn(") == -1 &&
                    strsrch(str, "->addn_temp(") == -1 &&
                    strsrch(str, "->delete(") == -1 &&
                    strsrch(str, "->delete_temp(") == -1 &&
                    strsrch(str, "->query(") == -1 &&
                    strsrch(str, "->query_temp(") == -1 )
                        continue;

                leadspace = get_leadspace(lines[i]);
                lines[i] = replace_string(lines[i], "(string)", "");
                lines[i] = replace_string(lines[i], "(int)", "");
                lines[i] = replace_string(lines[i], "(object)", "");
                lines[i] = replace_string(lines[i], "(mapping)", "");
                tmp1 = tmp2 = replace_string(lines[i], " ", "");

                if( sscanf(tmp1, "%s->set(%s,%s);", who, index, value) == 3 )
                {
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->set(%s,%s);", who, index, value);
                        str2 = sprintf("set(%s, %s, %s);", index, value, who);
                } else
                if( sscanf(tmp1, "%s->set(%s,%d);", who, index, value) == 3 )
                {
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->set(%s,%d);", who, index, value);
                        str2 = sprintf("set(%s, %d, %s);", index, value, who);
                } else
                if( sscanf(tmp1, "%s->set_temp(%s,%s);", who, index, value) == 3 )
                {
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->set_temp(%s,%s);", who, index, value);
                        str2 = sprintf("set_temp(%s, %s, %s);", index, value, who);
                } else
                if( sscanf(tmp1, "%s->set_temp(%s,%d);", who, index, value) == 3 )
                {
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->set_temp(%s,%d);", who, index, value);
                        str2 = sprintf("set_temp(%s, %d, %s);", index, value, who);
                } else
                if( sscanf(tmp1, "%s->addn(%s,%s);", who, index, value) == 3 )
                {
                        // if( who->addn(index) > n ) 格式没有做分析
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->addn(%s,%s);", who, index, value);
                        str2 = sprintf("addn(%s, %s, %s);", index, value, who);
                } else
                if( sscanf(tmp1, "%s->addn(%s,%d);", who, index, value) == 3 )
                {
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->addn(%s,%d);", who, index, value);
                        str2 = sprintf("addn(%s, %d, %s);", index, value, who);
                } else
                if( sscanf(tmp1, "%s->addn_temp(%s,%s);", who, index, value) == 3 )
                {
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->addn_temp(%s,%s);", who, index, value);
                        str2 = sprintf("addn_temp(%s, %s, %s);", index, value, who);
                } else
                if( sscanf(tmp1, "%s->addn_temp(%s,%d);", who, index, value) == 3 )
                {
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->addn_temp(%s,%d);", who, index, value);
                        str2 = sprintf("addn_temp(%s, %d, %s);", index, value, who);
                } else
                if( sscanf(tmp1, "%s->delete(%s);", who, index, value) == 2 )
                {
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->delete(%s);", who, index);
                        str2 = sprintf("delete(%s, %s);", index, who);
                } else
                if( sscanf(tmp1, "%s->delete_temp(%s);", who, index, value) == 2 )
                {
                        if( strsrch(who, "if") != -1 )
                        if( (idx = strsrch(who, ")", -1)) != -1 )  who = who[idx+1..];
                        if( (idx = strsrch(who, "else")) != -1 ) who = who[idx+4..];
                        str1 = sprintf("%s->delete_temp(%s);", who, index);
                        str2 = sprintf("delete_temp(%s, %s);", index, who);
                }

                if( str1 && str2 )
                        tmp2 = replace_string(tmp2, str1, str2);

                if( strsrch(tmp1, "->query(") != -1 )
                {
                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s==%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "==", -1);
                                if( idx != -1 ) who = who[idx+2..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s=%s->query(%s,1)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "=", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s,1)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s=%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "=", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s!%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "!", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s||%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "||", -1);
                                if( idx != -1 ) who = who[idx+2..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s&&%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "&&", -1);
                                if( idx != -1 ) who = who[idx+2..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s?%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "?", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s:%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, ":", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s,%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, ",", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s>%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, ">", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s<%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "<", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s+%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "+", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s-%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "-", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s*%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "*", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s/%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "/", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s{%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "{", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s(%s->query(%s)%s", who, index, tmp1) >= 3 )
                        {
                                if( (idx = strsrch(who, "(", -1)) != -1 &&
                                    strsrch(who, ")") == -1 )  who = who[idx+1..];
                                if( who[0..0] == "(" ) who = who[1..];
                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        if( sscanf(tmp1, "%s->query(%s)%*s", who, index) >= 2 )
                        {
                                if( who[0..0] == "(" ) who = who[1..];
                                if( (idx = strsrch(who, "(")) != -1 &&
                                    strsrch(who, ")") == -1 )  who = who[idx+1..];
                                str1 = sprintf("%s->query(%s)", who, index);
                                str2 = sprintf("query(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }
                }

                if( strsrch(tmp1, "->query_temp(") != -1 )
                {
                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s==%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "==", -1);
                                if( idx != -1 ) who = who[idx+2..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s=%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "=", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s!%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "!", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s||%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "||", -1);
                                if( idx != -1 ) who = who[idx+2..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s&&%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "&&", -1);
                                if( idx != -1 ) who = who[idx+2..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s?%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "?", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s:%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, ":", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s,%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, ",", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s>%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, ">", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s<%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "<", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s+%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "+", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s-%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "-", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s*%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "*", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s/%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "/", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s{%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                idx = strsrch(who, "{", -1);
                                if( idx != -1 ) who = who[idx+1..];
                                if( !valid_str(who) ) continue;

                                if( who[0..0] == "(" ) who = who[1..];
                                if( strsrch(who, "(") != -1 &&
                                    strsrch(who, ")") == -1 ) continue;

                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        while( sscanf(tmp1, "%*s(%s->query_temp(%s)%s", who, index, tmp1) >= 3 )
                        {
                                if( (idx = strsrch(who, "(", -1)) != -1 &&
                                    strsrch(who, ")") == -1 )  who = who[idx+1..];
                                if( who[0..0] == "(" ) who = who[1..];
                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }

                        tmp1 = tmp2;
                        if( sscanf(tmp1, "%s->query_temp(%s)%*s", who, index) >= 2 )
                        {
                                if( who[0..0] == "(" ) who = who[1..];
                                if( (idx = strsrch(who, "(")) != -1 &&
                                    strsrch(who, ")") == -1 )  who = who[idx+1..];
                                str1 = sprintf("%s->query_temp(%s)", who, index);
                                str2 = sprintf("query_temp(%s, %s)", index, who);

                                tmp2 = replace_string(tmp2, str1, str2);
                        }
                }

                tmp2 = restore_space(tmp2);
                lines[i] = leadspace + tmp2;
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

varargs string *deep_file_list(string dir, int times)
{
        int i;
        string *flist, *result = ({ });
        string file;
        int len;

        flist = get_dir(dir);

        len = strsrch(dir, "/", -1);
        dir = dir[0..len];
        for (i = 0; i < sizeof(flist); i++)
        {
                file = dir + flist[i];

                if (file_size(file + "/") == -2)
                        result += deep_file_list(file + "/", times+1);
                else
                {
                        if( times == 1 ) continue;
                        result += ({ file });
                }

        }
        return result;
}

