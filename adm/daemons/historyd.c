// This program is a part of NT mudlib
#include <ansi.h>

#define DATA_PATH       "/data/history.o"

string *history;

int save()
{
        return save_object(DATA_PATH);  
}

int remove()
{
        return save();
}

void add_history(string key, string id, string value)
{
        object ob;
        
        ob = UPDATE_D->global_find_player(id);
        if(!ob) return;//baby在此引发过错误，特添加此行

        history = ({ time(), key, id, value }) + history;
        
        addn("achievement", 1, ob);
        tell_object(ob, HIY "恭喜你获得新的成就，你获得了１点的成就值奖励！\n" NOR);
        UPDATE_D->global_destruct_player(ob, 1);
        save();
}

void remove_history(int index)
{
        history = history[0..((index-1)*4)-1] + history[(index-1)*4+4..];

        save();
}

string *query_history()
{
        return copy(history);
}

void create()
{
        if( !restore_object(DATA_PATH) )
        {
                history = allocate(0);
                save();
        }
}

string query_name()
{
        return "历史事件系统(HISTORY_D)";
}
