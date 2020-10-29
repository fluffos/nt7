// path.c

string user_cwd(string name)
{
        return ("/u/" + name);
}

string user_path(string name)
{
        return (user_cwd(name) + "/");
}

string wiz_home(string name)
{
        return ("/u/" + name);
}

string resolve_path(string curr, string new_path)
{
        int i;
        string *tmp;
        string t1;

        if( !curr ) curr = "/";
        if( !new_path || new_path == "." ) return curr;
        if( new_path == "here" && this_player() )
                return file_name(environment(this_player())) + ".c";
        if( new_path == "~" || new_path == "~/" )
                new_path = user_path(getuid(this_player()));
        if( sscanf(new_path,"~/%s",t1) )
                new_path = user_path(getuid(this_player())) + t1;
        else if( sscanf(new_path,"~%s",t1) )
                new_path = user_path(t1);
        else if( new_path[0] != '/' ) {
                if( curr[sizeof(curr)-1] != '/' ) new_path = curr + "/" + new_path;
                else new_path = curr + new_path;
        }

        tmp = explode(new_path,"/");
        for (i = 0; i < sizeof(tmp); i++)
                if( tmp[i] == ".." ) {
                        if( sizeof(tmp) > 2 ) {
                                tmp = tmp[0..(i-2)] + tmp[(i+1)..(sizeof(tmp)-1)];
                                i -= 2;
                        } else {
                                tmp = tmp[2 ..(sizeof(tmp)-1)];
                                i = 0;
                        }
                }
         new_path = "/" + implode(tmp,"/");
         if( new_path == "//" ) new_path = "/";
         return new_path;
}

string resolvePath(string path, int op)
{
        string *dn;
        string tmp;
        int    i;

        if( path == "/" ) // 对这个情况特殊处理
                return (op) ? "/" : "*";

        dn = explode(path, "/");
        if( op ) { // op为非0表示需要返回路径
                // dn = dn - ({dn[sizeof(dn) - 1]});
                // tmp = implode(dn, "/") + "/";
                // 上面的程序不好，不能对同名路径正确处理，比如不能在/log/log文件里搜索
                tmp = "/";
                for (i = 0; i < sizeof(dn) - 1; i++) {
                        // write("合并" + dn[i] + "\n");
                        tmp += dn[i] + "/";
                }
                return tmp;
        }
        else
                return dn[sizeof(dn) - 1];
}

int in_same_dir(string file1, string file2)
{
        string dir_a = "", dir_b = "", *dirs;
        int i;

        if( !stringp(file1) || !stringp(file2) )
              return 0;

        dirs = explode(file1, "/");

        if( sizeof(dirs) < 2 )
                dir_a = "/";
        else {
                for (i = 0; i < sizeof(dirs) - 1; i++) {
                        dir_a += "/";
                        dir_a += dirs[i];
                }
        }

        dirs = explode(file2, "/");
        if( sizeof(dirs) < 2 )
                dir_b = "/";
        else {
                for (i = 0; i < sizeof(dirs) - 1; i++) {
                        dir_b += "/";
                        dir_b += dirs[i];
                }
        }

        if( dir_a == dir_b )
                return 1;
        else
                return 0;
}
