// This program is a part of NITAN MudLIB 
// redl 2013/8
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        int d = (time() - 1392799000) / 864000; //每10天增值1nt
        set_name(NOR BBLU HIW "泥潭周岁股票" NOR, ({ "ntb" }));
        //基础价值25nt，建议商店出售为50nt(考虑最低七折情况下售价35nt)，一年后等于25+36=61nt
                set("base_value", d+25);
                set("long", NOR + WHT "这是发行在泥潭周岁时的股票，目前可以(exchange)兑换成" + (string)(query("base_value")) + "点泥潭币。\n" NOR);
                set("base_unit", "张");
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
        int d = query("base_value");
        
        if(me->is_busy()) return notify_fail("你正忙着，没空兑换泥潭币。\n");
        me->start_busy(2);

        //30天后才准许兑换
        if (time() < (1392799000 + 86400 * 30)) return notify_fail("这种股票还没有到兑换期，再等等吧。\n");
        
//        if (! objectp(ob = UPDATE_D->global_find_player(target)))
//            return notify_fail("没有这个人！\n");

 if (d > 50) d = 50;


        if (MEMBER_D->is_member(target))
                MEMBER_D->db_pay_member(target, d);
        else
                MEMBER_D->db_create_member(target, d);

        log_file("static/yangyong2",sprintf("%s %s 泥潭周岁股->? $NT, 账户余 %d $NT\n",TIME_D->replace_ctime(time()), target, MEMBER_D->db_query_member(me, "money"))); 


        CHANNEL_D->channel_broadcast("chat", ( NOR + HIC + query("name", me) + NOR + HIC + "兑换泥潭周岁股获得" + chinese_number(d) + NOR + HIC + "点泥潭币。\n" + NOR )); 
//      write("兑换ok\n");


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


