// ultra_questd.c
// Create by Rcwiz for Heros.cn 2004/06/02
// 排名

#include <ansi.h>

inherit F_SAVE;
inherit F_DBASE;

void set_from_dbase_add_temp(string uid, mixed data, mixed preobj0, mixed preobj1, mixed preobj2)
{
        string s0, s1, s2, sdata;
        
        s0 = "";
        s1 = "";
        s2 = "";
        
        if (objectp(preobj0))s0 = base_name(preobj0);
        if (objectp(preobj1))s1 = base_name(preobj1);
        if (objectp(preobj2))s2 = base_name(preobj2);
        
        if (intp(data))sdata = sprintf("%d", data);
        
        log_file("0add_temp", "id = " + uid + ", p0 = " + s0 + ", p1 = " + s1 + ", p2 = " + s2 + ", sdata=" + sdata + "\n");
        
        
}

void create()
{
        seteuid(getuid());
        restore();
}

public string query_save_file() { return DATA_DIR "dbd"; }

// 公共调用函数
// 给定一个mapping ，值为数值，
// 为该mapping 根据数值进行从高到低的排序，返回该mapping 的新序列
public string *tongji_mapping(mapping mp, int flag)
{
        string key_mp;
        string *result_mp, *temp_s1, *temp_s2, *temp_s3;
        string *str_temp;
        int i;
        
        temp_s1 = ({});
        temp_s2 = ({});
        temp_s3 = ({});
                
        if (! sizeof(mp))return temp_s1;

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

// 得到允许登陆QQ列表
string *get_permit_list()
{
        restore();
        return query("permit_list");
}

// 得到拒绝登陆QQ列表
string *get_deny_list()
{
        restore();
        return query("deny_list");
}

void record_list(string qq, string s_type)
{
        string *deny_list, *permit_list;

        deny_list = get_deny_list();
        permit_list = get_permit_list();

        if (! deny_list)deny_list = ({});
        if (! permit_list)permit_list = ({});

        if (s_type == "deny") 
        {
                deny_list += ({ qq });
                set("deny_list", deny_list);
                save();
        }
        if (s_type == "permit")
        {
                permit_list += ({ qq });
                set("permit_list", permit_list);
                save();
        }
        write("OK\n");
        return;
}

// 得到海龟刻字信息
string query_crave()
{
        string msg;
        int i;
        mapping t;
        string *temp;

        restore();

        t = query("haigui");
        if (! t)return "";

        temp = keys(t);

        msg = "";
        for (i = 0; i < sizeof(temp); i ++)
        {
                msg = msg + t[temp[i]]["name"]+"(" + temp[i] + ")：" + t[temp[i]]["msg"] + "\n";
        }
        
        return msg;             
}

int do_crave(object me, string arg)
{
        if (! arg)
        {
                tell_object(me, "你要刻什么？\n");
                return 1;
        }

        if (! me->query("luck_number"))
        {
                tell_object(me, "你还没有注册呢！输入指令 help reg 查看注册信息！\n");
                return 1;
        }       
        if (sizeof(arg) > 60)
        {
                tell_object(me, "你要雕刻的信息过长，不能超过三十个汉字或六十个字符！\n");
                return 1;
        }

        set("haigui/" + me->query("id") + "/msg", arg);
        set("haigui/" + me->query("id") + "/name", filter_color(me->name()));
        save();

        tell_object(me, HIG "你成功在万年海龟背上雕刻了信息！\n" NOR);
        return 1;
}

int set_data(string darg, mixed ddata)
{
        set(darg, ddata);

        save();
}

mixed query_data(string arg)
{
        restore();
        if (query(arg))return query(arg);

        return 0;               
}

int delete_data(object me, string str)
{
        //if (! wizardp(me))return 0;

        delete(str);
        save();

        return 1;
}

// 统计总统含有SCB数量
// flag = 1 统计总量，flag = 2统计有多少玩家还有SCB
public int get_scb_total(int flag)
{
        mapping scb;
        string *key_scb;
        int i, n, total_scb;
        
        scb = query("yhshop/scb");
        
        if (sizeof(scb))key_scb = keys(scb);
        
        if (! sizeof(key_scb))return 0;
        
        n = 0;
        total_scb = 0;
        
        for (i = 0; i < sizeof(key_scb); i ++)
        {
                if (scb[key_scb[i]] < 1)continue;
                // 巫师不统计
                if (key_scb[i] == "rcwiz" || key_scb[i] == "cdlove")continue;
                
                n ++;
                total_scb += scb[key_scb[i]];
        }
        
        if (flag == 1)return total_scb;
        if (flag == 2)return n;
        
        return 0;
}
