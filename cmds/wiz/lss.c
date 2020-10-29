// ls.c
// creator:     Fan@falling-sun.chinesemud.net
// creat time:  1999/04/05


#include <localtime.h>

inherit F_CLEAN_UP;
#define L_LINE sprintf("%-30s%8s  %s", "最后修改时间", "尺寸", "文件名")
#define DASHES "-----------------------------------------------------------------"
#define F_FLAG  1
#define S_FLAG  2
#define L_FLAG  4
#define A_FLAG  8
#define T_FLAG  16
#define R_FLAG  32
#define X_FLAG  64
#define ONE_FLAG 128
#define CAP_A_FLAG 256

protected mixed   internal_ls(string path, int active, int internal_call);
mixed           map_junk(mixed junk, int index);
int             sort_by_time(mixed a, mixed b);
int             sort_by_ext(mixed a, mixed b);
int             filter_directories(mixed junk);
int             filter_no_period(mixed junk);
int      filter_valid_directories(mixed junk);
nosave string pathname;

int main(object me, string arg)
{
    int         i;
    int         active;
    string      flags,str;
    string  *output;
    
             if (! SECURITY_D->valid_grant(me, "(wizard)")) 
                  return 0; 
    seteuid(geteuid(me));

    if (!arg)  arg = "";
    else    arg += " ";

    while (sscanf(arg, "-%s %s", flags, str) > 1
    || sscanf(arg, "%s -%s", str,flags) > 1 ) {
      arg=str;
           i = strlen(flags);
           while (i--)
              switch (flags[i]) {
                 case 'F':   active |= F_FLAG;    break;
                 case 's':      active |= S_FLAG;               break;
                 case 'l':      active |= L_FLAG;               break;
                 case 'a':      active |= A_FLAG;               break;
                 case 't':      active |= T_FLAG;               break;
                 case 'r':      active |= R_FLAG;               break;
                 case 'x':      active |= X_FLAG;               break;
                 case '1':      active |= ONE_FLAG;     break;
                 case 'A':      active |= CAP_A_FLAG;   break;
              }
    }
    if (arg[<1..<1] == " ")   arg = arg[0..<2];
    if (arg == "/..") {
           write("ls: 没有这样的目录。\n");
           return 1;
    }
//  '-l'和'-s'是不能兼容的参数
    if (active & L_FLAG) active &= ~S_FLAG;

    arg=resolve_path(query("cwd", me),arg);

//  防止在根目录使用'-r' 参数    
    output=explode(arg,"/");
    if (!sizeof(output) && R_FLAG)
        active &=~R_FLAG;

    if (output = internal_ls(arg, active, 0)) {
           me->start_more(sprintf("\n%s\n",implode(output,"\n")));
    }
    return 1;
}
//  返回文件所在的目录

protected string get_path(string str)
{
    mixed *tmp;
    string path;

    if(str == "/")       return "/";

    if(str[strlen(str)-1] == '/')   return str;
    else if(file_size(str)==-2)  return str+"/";
 
    tmp = explode(str, "/") - ({ 0 });
    if (sizeof(tmp)>=2)
        path = "/" + implode( tmp[0..sizeof(tmp)-2], "/")+"/";
    else
        path="/";
    if(path == "//")  path = "/";
 
    return path; 
}

protected mixed internal_ls(string arg, int active, int internal_call)
{
    mixed   *junk,*local;
    string  *files;
    int     *times;
    int     *sizes;
    string  *dirs;
    int         first_period;
    int   i;
    string  *output;
    mixed       tmp;
    string      path,file_time;

    pathname=get_path(arg);

    output = ({ sprintf("目录: [%s]", pathname) });

    if (internal_call) {
              path = arg;
              arg += "*";
    } else {
              if (arg[<1..< 1] != "/" && file_size(arg + "/") == -2)
                 arg += "/";
              path = arg;
              if (arg[<1..<1] == "/") {
                 arg += "*";
              } else {
                 for (i = strlen(path); path[--i] != '/';);
                 first_period = path[i+1] == '.';
                 path = path[0..i];
              }
    }

    junk = get_dir(arg, -1);
    if (!sizeof(junk)) {
              write("ls: "+arg+" 没有这样的文件或者目录。\n");
              return 0;
    }
   junk=filter_array(junk,"filter_valid_directories",this_object());

    if (!(active & A_FLAG) && !first_period) {
           junk = filter_array(junk, (active & CAP_A_FLAG)?"filter_limit_period":
                            "filter_no_period", this_object());
           if (!sizeof(junk)) {
              if (internal_call)
                return ({ sprintf("%s: 目录是空的。", path) });
              write(pathname+" 目录是空的。\n");
              return 0;
           }
    }

    if (active & T_FLAG)
           junk = sort_array(junk, "sort_by_time", this_object());

    if (active & X_FLAG)
           junk = sort_array(junk, "sort_by_ext", this_object());

    if (active & R_FLAG)
           dirs = map_array(
                filter_array(junk, "filter_directories", this_object()),
                "map_junk", this_object(), 0);

    files = map_array(junk, "map_junk", this_object(), 0);
    sizes = map_array(junk, "map_junk", this_object(), 1);
    times = map_array(junk, "map_junk", this_object(), 2);

    if (active & (F_FLAG | S_FLAG)) {
           for (i = sizeof(sizes); i--;) {
              if (active & S_FLAG) {
                      tmp = (sizes[i] >= 0) ?
                      sprintf("%3d %s", (sizes[i] + 1023) / 1024, files[i]) :
                      sprintf("  - %s", files[i]);
              } else {
                      tmp = files[i];
              }
              if (active & F_FLAG) {
                      if (sizes[i] == -2) {
                         tmp += "/";
                      } else if (files[i][<2..<1] == ".c" &&
                              find_object(path + files[i])) {
                            tmp += "*";
                         }
              }
              files[i] = tmp;
           }
    }

    if (active & L_FLAG) {
           int out_idx, max;

           out_idx = sizeof(output += ({L_LINE,DASHES}));
           output += allocate(max = sizeof(files)+1);

           for (i = 0; i < max-1; i++) {
              local=localtime(times[i]);
              file_time=sprintf("%4d年%2d月%2d日%2d时%2d分%2d秒",local[LT_YEAR],local[LT_MON]+1,local[LT_MDAY],local[LT_HOUR],local[LT_MIN]+1,local[LT_SEC]+1);
              output[out_idx++] = (sizes[i] >= 0) ?
                   sprintf("%-30s %8d %s", file_time, sizes[i], files[i]) :
                   sprintf("%-30s %8s %s", file_time, "<DIR>", files[i]);
           }
           output += ({DASHES});
    } else if (!(active & ONE_FLAG) ) {
                 for (i = 0; i < sizeof(files); i += 300) {
                    output += explode(sprintf("%-79#s\n", implode(files[i..(i + 299)],
                                                          "\n")), "\n");
                 }  
      } else {
              output += files;
      }

    if (active & R_FLAG) {
         reset_eval_cost();
              for (i = 0; i < sizeof(dirs); i++)
              output += ({ "" }) + internal_ls(path + dirs[i] + "/", active, 1);
    }
    return output;
}

mixed map_junk(mixed junk, int index)
{
    return junk[index];
}

int filter_no_period(mixed junk)
{
    if (junk[0][0] != '.') return 1;
}

int filter_limit_period(mixed junk)
{
    if (junk[0] != "." && junk[0] != "..") return 1;
}


int filter_directories(mixed junk)
{
    if (junk[1] == -2 && junk[0] != "." && junk[0] != "..")
        return 1;
}

int sort_by_time(mixed file_a, mixed file_b)
{
    return file_a[2] > file_b[2] ? 1 : -1;
}

int sort_by_ext(mixed file_a, mixed file_b)
{
    file_a = " ." + file_a[0];
    file_b = " ." + file_b[0];
    file_a = explode(file_a, ".");
    file_b = explode(file_b, ".");
    if (sizeof(file_a) == 2 || sizeof(file_b) == 2)
        return sizeof(file_a) > sizeof(file_b) ? 1 : -1;
    return file_a[sizeof(file_a) - 1] > file_b[sizeof(file_b) - 1] ? 1 : -1;
}

int filter_valid_directories(mixed junk)
{
   if (junk[0] == "." || junk[0] == "..") return 1;
   if (file_size(pathname+junk[0]) == -1)
      return 0;
   else
           return 1;
        
}

int help(object me)
{
    write(@HELP
指令格式: ls [ -aslFrtx1 ] [<路径名>]
 
列出目录下所有的子目录及档案, 如果没有指定目录, 则列出所在目录
的内容，所列出的档案中后面标示 * 号的是已经载入的物件。
 
例:
'ls /' 会列出所有位于根目录下的档案及子目录.
  参数：
        -a  列出所有指定目录下的文件，包括'.'和'..'
        -A  类似于参数-a，除了不显示'.' 和 '..'
        -s  在文件前以KilloBytes的近似值显示文件大小
        -F  在目录名后以 '/' 表示一个目录，以'*' 表示一个已经载入的文件
        -l  以详细的格式显示
        -r  递归显示指定目录下的文件及子目录下的文件
        -t  按时间顺序排列
        -x  按文件的扩展名排列
        -1  以一行一个文件的格式显示
        不支持的参数将被忽略。
        你可以通过alias 设定自己喜欢的参数，如： alias ls ls -F $*
 
HELP
    );
    return 1;
}

