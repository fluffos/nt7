#include <ansi.h>

inherit F_SAVE;
inherit F_DBASE;


void create()
{
        seteuid(getuid());
        restore();
}

public string query_save_file() { return DATA_DIR "dbd"; }

public string *sort_mapping(mapping mp, int flag)
{
        string key_mp;
        string *result_mp, *temp_s1, *temp_s2, *temp_s3;
        string *str_temp;
        int i;
        
        temp_s1 = ({});
        temp_s2 = ({});
        temp_s3 = ({});
                
        if (! sizeof(mp)) return temp_s1;

        // 先将mp中的序列与值进行 值:序列 方式组合，然后对 值:序列 由大到小排序
        result_mp = keys(mp);

        for (i = 0; i < sizeof(result_mp); i ++)
        {
                temp_s1 += ({ sprintf("%06d", mp[result_mp[i]]) + ":" + result_mp[i] });
        }
        temp_s2 = sort_array(temp_s1, -1);
        
        for (i = 0; i < sizeof(temp_s2); i ++)
        {
                str_temp = ({});
                str_temp = explode(temp_s2[i], ":");
                temp_s3 += ({ str_temp[1] });
        }

        return temp_s3;
}

int set_data(string prop, mixed data)
{
        set(prop, data);
        save();
        return 1;
} 

mixed query_data(string arg)
{
        if (query(arg)) return query(arg);

        return 0;               
}

mixed add_data(string prop, mixed data)
{
        mixed old;
        
        if( !(old = query_data(prop)) ) 
                return set_data(prop, data); 

        return set(prop, old + data); 
}

int delete_data(string str)
{
        delete(str);
        save();

        return 1;
}

void remove()
{
        save();
}
