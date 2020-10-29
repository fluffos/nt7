// workd.c

/********************************************************
  工作管理守护

绝代双骄使用类似于 QUEST_D 的工作管理机制，所有的简单工作
并不保存在请求或者执行具体工作的 npc 或者房间上，而是保存
在 /adm/daemons/work/ 目录下以该工作英文命名的程序中， 比
如客栈工作即为 /adm/daemons/work/kezhan.c。这样可以方便全
局的管理、修改和简化调用(比如同类工作就不要复制一次代码)。

系统(globals.h)提供的宏定义：

#define WORK_DIR     "/adm/daemons/work/"

WORK_D 提供的操作 API：

int    request_work(object who, object ob, string name);
string assign_work(object who, string name);
int    query_work(object who, string name);
int    start_work(object who, string name);
int    finish_work(object who, object ob, string name, mixed m);

WORK_OB 必须提供的接口：

int    request_work(object me, object ob);
int    query_work(object who);
string assign_work(object who);
int    start_work(object me);
int    finish_work(object me, object ob);

********************************************************/

#include <ansi.h>

#define WORK_DIR     "/adm/daemons/work/"

public int request_work(object who, object ob, string name)
{
        if (! playerp(who) || playerp(ob))
                return 0;

        if (! can_talk_with(ob, who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;

        return (WORK_DIR + name + ".c")->request_work(who, ob);
}

public string assign_work(object who, string name)
{
        if (! playerp(who) || ! interactive(who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;

        return (WORK_DIR + name + ".c")->assign_work(who);
}

public int query_work(object who, string name)
{
        if (! playerp(who) || ! interactive(who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;

        return (WORK_DIR + name + ".c")->query_work(who);
}

public int start_work(object who, string name)
{
        if (! playerp(who) || ! interactive(who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;

        return (WORK_DIR + name + ".c")->start_work(who);
}

public varargs int finish_work(object who, object ob, string name, mixed m)
{
        if (! playerp(who) || playerp(ob))
                return 0;

        if (! can_talk_with(ob, who))
                return 0;

        if (! file_size(WORK_DIR + name + ".c"))
                return 0;

        if (m)
                return (WORK_DIR + name + ".c")->finish_work(who, ob, m);
        else return (WORK_DIR + name + ".c")->finish_work(who, ob);
}

public string query_all_work()
{
        string *wlist;
        string info;
        string work;
        mixed *winfo;

        wlist = get_dir(WORK_DIR + "*.c");
        if (! arrayp(wlist) || ! sizeof(wlist))
                return "目前系统中没有任何工作。\n";

        info = HIC "目前系统中有 " HIW + sizeof(wlist) + HIC " 项工作：\n" NOR
               HIW "--工作----奖励------人数----最低经验----最高经验--\n" NOR;
        foreach(work in wlist)
        {
                winfo = (WORK_DIR + work + ".c")->query_info();
                info += sprintf(WHT "%-10s" CYN " %-10d %-10d %-10d %-10d\n" NOR,
                                winfo[0], winfo[1], winfo[2], winfo[3], winfo[4]);
        }
        info += HIW "--------------------------------------------------" NOR;
        return info;
}
