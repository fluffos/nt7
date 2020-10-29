// This program is a part of NITAN MudLIB 
// redl 2013/8
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(YEL"百元泥潭币"NOR, ({ "ntb" }));
                set("long", NOR + WHT "这是一张百元大钞，使用(exchange)来兑换成100泥潭币。\n" NOR);
                set("base_unit", "张");
                set("base_value", 10000000000);
                set("base_weight", 3600);
                set("unit", "叠");
        set_amount(1);
                                     set("set_data", 1);
                                     set("auto_load", 1);
}

int do_exchange()
{
        object ob, me = this_player();
        string target = query("id", me);
        
        if(me->is_busy()) return notify_fail("你正忙着，没空兑换泥潭币。\n");
        me->start_busy(2);
        
//        if (! objectp(ob = UPDATE_D->global_find_player(target)))
//            return notify_fail("没有这个人！\n");

        if (MEMBER_D->is_member(target))
                MEMBER_D->db_pay_member(target, 100);
        else
                MEMBER_D->db_create_member(target, 100);

        log_file("static/yangyong2",sprintf("%s %s 百元泥潭币->100 $NT, 账户余 %d $NT\n",TIME_D->replace_ctime(time()), target, MEMBER_D->db_query_member(me, "money"))); 

//         UPDATE_D->global_destruct_player(ob, 1);
        
        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 
        return 1;
}


void init()
{
                if (! interactive(this_player()))
                        return;
        add_action("do_exchange", "exchange");
}



