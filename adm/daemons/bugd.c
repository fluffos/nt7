// This program is a part of NT MudLIB

#include <ansi.h>
#include <mudlib.h>

#define DATA_PATH               "/data/bug/"
#define DEFAULT_LOAD            10
#define SERIAL_NUMBER_KEY       "bug"

#define REPLY_AUTHOR            0
#define REPLY_MESSAGE           1

#define LIST_OPT_ALL    (1<<0)

string *buginfo;

int bug_exists(string number)
{
        return file_exists(DATA_PATH+number);
}

void reset_buginfo()
{
        buginfo = allocate(0);

        foreach(string file in sort_array(get_dir(DATA_PATH), (: (to_int($1) < to_int($2)) ? 1 : -1 :))[0..DEFAULT_LOAD-1])
                buginfo += ({ restore_variable(read_file(DATA_PATH+file)) });
}

// 列出 Bug 列表
string list_bug(int options)
{
        int len;
        string listmsg;
        string *list_buginfo;

        if( options & LIST_OPT_ALL )
        {
                list_buginfo = allocate(0);

                foreach(string file in get_dir(DATA_PATH))
                        list_buginfo += ({ restore_variable(read_file(DATA_PATH+file)) });
        }
        else
                list_buginfo = buginfo;

        list_buginfo = sort_array(list_buginfo, (: (to_int($1["number"]) < to_int($2["number"])) ? 1 : -1 :));
        listmsg =  "\n"+MUD_FULL_NAME+HIY" 臭虫回报系统\n"NOR;
        listmsg += WHT"--------------------------------------------------------------------------\n"NOR;
        listmsg += "编号 回报者                   主题                          处理状态  回应\n";
        listmsg += WHT"--------------------------------------------------------------------------\n"NOR;

        foreach( mapping data in list_buginfo )
        {
#ifdef LONELY_IMPROVED
                len = 0;
#else
                len = color_len(data["status"]);
#endif
                listmsg += sprintf(HIY"%-4s"NOR" %-24s %-:30s%-"+(8+len)+"s %5s\n", data["number"],
                                   data["author_idname"], data["title"], data["status"],
                                   sizeof(data["reply"]) ? sizeof(data["reply"])+"" : "");
        }
        listmsg += WHT"--------------------------------------------------------------------------\n"NOR;

        if( options & LIST_OPT_ALL )
                listmsg += "列出所有回报资料\n";
        else
                listmsg += "列出最近 "+DEFAULT_LOAD+" 项回报资料\n";

        return listmsg;
}

// 新增 Bug 资料
string add_bug(object me, string title, string content)
{
        mapping bugdata = allocate_mapping(0);

        if( !objectp(me) || !stringp(title) || !stringp(content) )
                error("BUG_D add_bug() 错误输入参数");

        bugdata["time"] = time();
        bugdata["where"] = base_name(environment(me));
        bugdata["number"] = SERIAL_NUMBER_D->query_serial_number(SERIAL_NUMBER_KEY);

        bugdata["author_id"] = me->query_id(1);
        bugdata["author_idname"] = me->query_idname();

        bugdata["title"] = title;
        bugdata["content"] = content;

        bugdata["status"] = HIR"未处理"NOR;

        bugdata["reply"] = allocate(0);

        assure_file(DATA_PATH+bugdata["number"]);
        if( write_file(DATA_PATH+bugdata["number"], save_variable(bugdata)) )
                reset_buginfo();
        else
                error("BUG_D 无法储存新增 bug 资料");

        CHANNEL_D->channel_broadcast("sys", HIW+me->query_idname()+HIW"新增 Bug 回报，“"+title+NOR+HIW"”，编号："+bugdata["number"]+"。");

        return bugdata["number"];
}

// 回应 Bug 处理情形
varargs void reply_bug(object me, string number, string status, string message)
{
        mapping data;

        if( !bug_exists(number) )
                error("BUG_D reply_bug() 无此档案");
        else
                data = restore_variable(read_file(DATA_PATH+number));

        data["status"] = status;
        CHANNEL_D->channel_broadcast("sys", me->query_idname()+"修改编号第 "+number+" 号 Bug 处理状况为“"+status+"”");

        if( find_player(data["author_id"]) )
                tell_object(find_player(data["author_id"]), me->query_idname()+"回应编号第 "+number+" 号 Bug 处理状况为“"+status+"”。\n");

        if( !undefinedp(message) )
        {
                if( !arrayp(data["reply"]) )
                        data["reply"] = allocate(0);

                data["reply"] += ({ ({ me->query_idname(), message }) });
                CHANNEL_D->channel_broadcast("sys", me->query_idname()+"输入编号第 "+number+" 号 Bug 处理回应");
        }

        write_file(DATA_PATH+number, save_variable(data), 1);
        reset_buginfo();
}

// 移除 Bug 资料
varargs void remove_bug(object me, string number, int reply)
{
        if( !bug_exists(number) )
                error("BUG_D remove_bug() 无此档案");

        // 删除整个 Bug 资讯
        if( undefinedp(reply) )
        {
                if( !rm(DATA_PATH+number) )
                        error("BUG_D remove_bug() 无法删除档案");

                reset_buginfo();
        }
        // 删除其中一个回应资料
        else
        {
                mapping data = restore_variable(read_file(DATA_PATH+number));

                reply--;

                if( reply < sizeof(data["reply"]) && reply >= 0 )
                {
                        if( reply == 0 )
                                data["reply"] = data["reply"][1..];
                        else
                                data["reply"] = data["reply"][0..reply-1] + data["reply"][reply+1..];
                }

                write_file(DATA_PATH+number, save_variable(data), 1);
                reset_buginfo();
        }
}

// 查询 Bug 资料
string query_bug(string number)
{
        string bugmsg;
        mapping data;
        int len;

        if( !bug_exists(number) )
                error("BUG_D query_bug() 无此档案");
        else
                data = restore_variable(read_file(DATA_PATH+number));

#ifdef LONELY_IMPROVED
                len = 0;
#else
                len = color_len(data["status"]);
#endif

        bugmsg =  sprintf(HIM"编号"NOR" %-20s "HIM"主题"NOR" %s\n"NOR, data["number"], data["title"]);
        bugmsg += sprintf(HIM"时间"NOR" %-20s "HIM"回报"NOR" %s\n", TIME_D->replace_ctime(data["time"]), data["author_idname"]);
        bugmsg += sprintf(HIM"状况"NOR" %-"+(20+len)+"s "HIM"回应"NOR" %d\n", data["status"], sizeof(data["reply"]));
        bugmsg += sprintf(HIM"地点"NOR" %s\n", data["where"]);
        bugmsg += WHT"--------------------------------------------------------------------------\n"NOR;
        bugmsg += data["content"]+"\n";

        if( sizeof(data["reply"]) )
        {
                int replies;

                foreach( string *reply in data["reply"] )
                {
                        replies++;
                        bugmsg += HIY"\n\n*** 第 "+replies+" 篇回应："+reply[REPLY_AUTHOR]+HIY+" ***\n"NOR;
                        bugmsg += reply[REPLY_MESSAGE]+NOR"\n";
                }
        }

        bugmsg += WHT"--------------------------------------------------------------------------\n"NOR;

        return bugmsg;
}

void create()
{
        reset_buginfo();
}
string query_name()
{
        return "臭虫回报系统(BUG_D)";
}
