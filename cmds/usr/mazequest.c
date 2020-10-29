// quest.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping to_kill, to_find;
        mapping killed, finded;
        string *tk, *tf;
        string msg;
        int i, n;

        ob = FUBEN_D->query_maze_mainobj(me);

        if (! ob) return notify_fail("你当前地点没有可以显示的副本任务。\n");

        if( !query("quest/quest_name", ob) )
                return notify_fail("你目前还没有领取任何副本任务。\n");

        to_kill=query("quest/to_kill", ob);
        killed=query("quest/killed", ob);
        to_find=query("quest/to_find", ob);
        finded=query("quest/finded", ob);

        write("任务名称: "+query("quest/quest_name", ob)+"\n");
        write("任务描述: "+query("quest/quest_desc", ob)+"\n");
        if (mapp(to_kill) && sizeof(to_kill))
        {
                write("杀敌任务进程: \n");
                msg = "";
                tk = keys(to_kill);
                for (i=0;i<sizeof(tk);i++)
                {
                        if (sizeof(killed) && !undefinedp(killed[tk[i]]))
                                n = killed[tk[i]];
                        else n = 0;
                        msg += tk[i] + ": " + n + "/" + to_kill[tk[i]] + "\n";
                }
                write(msg);
        }
        if (mapp(to_find) && sizeof(to_find))
        {
                write("寻物任务进程: \n");
                msg = "";
                tf = keys(to_find);
                for (i=0;i<sizeof(tf);i++)
                {
                        if (sizeof(finded) && !undefinedp(finded[tf[i]]))
                                n = finded[tf[i]];
                        else n = 0;
                        msg += tf[i] + ": " + n + "/" + to_find[tf[i]] + "\n";
                }
                write(msg);
        }
        if (n = ob->query_remove_time()-time())
                 write("副本将在"+CHINESE_D->chinese_period(n)+"后消失。\n");

        return 1;
}
