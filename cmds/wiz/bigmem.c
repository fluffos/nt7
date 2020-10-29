// bigmem.c

#include <ansi.h>
inherit F_CLEAN_UP;

mapping sm_obj_mem;
mapping sm_obj_num;
int sm_all_mem;
int obj_num;

string memory_expression(int m);
int check_ob(object ob);

int main(object me,string arg)
{
    int i,large;
    string *obj_ind;
    string msg;

    sm_obj_mem = ([]);
    sm_obj_num = ([]);
    sm_all_mem = 0;
    obj_num = 0;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

    if (!arg || sscanf(arg, "%d", large) != 1)
        large = 10;

    objects((: check_ob :));

    //选择附和查询条件的
    reset_eval_cost();
    obj_ind = keys(sm_obj_mem);
    obj_ind = filter_array(obj_ind, (: $(sm_obj_mem)[$1] >= $2 :) , large*1024);

    // 排序
    reset_eval_cost();
    obj_ind = sort_array(obj_ind, (: $(sm_obj_mem)[$2] - $(sm_obj_mem)[$1] :));
    obj_ind = sort_array(obj_ind, (: $(sm_obj_num)[$2] - $(sm_obj_num)[$1] :));

    // 选择前100个
    msg = "目前系统中占用内存超过" + chinese_number(large) + "K的物品如下：\n";
    msg += sprintf(HIY "%-40s%-10s%s\n" NOR, "物品文件", "复制数量", "耗用内存");
    for (i = 0; i < sizeof(obj_ind) && i < 100; i++)
        msg += sprintf("%-40s %-10d %s\n",
                   obj_ind[i],
                   sm_obj_num[obj_ind[i]], 
                   memory_expression(sm_obj_mem[obj_ind[i]]));

    msg += sprintf( "共%s个物品，使用 %s bytes 记忆体。\n", 
        chinese_number(obj_num),
        memory_expression(sm_all_mem) );    

    msg += "检查完毕！\n";

    sm_obj_mem = 0;
    sm_obj_num = 0;
    obj_ind = 0;

    me->start_more(msg);
    return 1;
}

string memory_expression(int m)
{
    float mem;
    mem = m;

    if( mem<1024 ) return m + "";

    if( mem<1024*1024 )
        return sprintf("%.2f K", (float)mem / 1024);

    return sprintf("%.3f M", (float)mem / (1024*1024));
}

int check_ob(object ob)
{
    int i;
    int mem;
    string bn;

    bn = file_name(ob);
    sscanf(bn, "%s#%*d", bn);

    mem = memory_info(ob);
    if (!sm_obj_mem[bn])
        sm_obj_mem[bn] = mem;
    else
        sm_obj_mem[bn] += mem;
    if (!sm_obj_num[bn])
        sm_obj_num[bn] = 1;
    else
        sm_obj_num[bn] += 1;
    sm_all_mem += mem;
    if (! (obj_num++ & 0xFFF))
        reset_eval_cost();
    return 0;
}

int help(object me)
{
    write(@HELP

指令格式 : bigmem 记忆体大小

这个指令告诉你占用的记忆体数量超过指定大小的所有物品。
若没有指明数值，则缺省为10(k)。

HELP);
    return 1;
}
