// This program is a part of NITAN MudLIB 
// redl 2014/3
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
                set_name(NOR WHT "钢镚" NOR, ({ "penny", "gang beng" }));
                set("base_value", 10);
                set("long", NOR + WHT "这是一枚硬币，可以望天上扔(throwing penny)。\n" NOR);
                set("base_unit", "枚");
                set("base_weight", 100);
                set("unit", "堆");
                set_amount(1);
                set("set_data", 1);
                set("auto_load", 1);
}

int do_exchange(string arg)
{
        object ob, me = this_player();
        string target = query("id", me);
        
        if (!arg || (arg!="penny" && arg!="gang beng")) {
                write(NOR "你要扔什么东西？\n" NOR);
                return 1;
        }
        
        if(me->is_busy()) return notify_fail("你正忙着呢。\n");

        me->start_busy(2);

        message_vision(NOR CYN "$N" NOR CYN "闭上眼睛掏出一枚$n" NOR CYN "，念念有词地往天上一扔...\n" NOR, me, this_object()); 
        if (random(3)) {
                if (MEMBER_D->is_member(target))
                        MEMBER_D->db_pay_member(target, 1);
                else
                        MEMBER_D->db_create_member(target, 1);
                write(NOR WHT "钢镚" NOR HIG "从天上击落1点泥潭币，一起跌回了你的衣兜里。" NOR HIK "(快使用member指令看看吧) \n" NOR); 
                return 1;//不销毁，返回继续可扔
        }

        message_vision(NOR CYN "$n" NOR CYN "飘啊飘，飘啊飘...\n就这样，再也没有望$N" NOR CYN "一眼地飞走了。\n" NOR, me, this_object()); 
        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 
        return 1;
}


void init()
{
            if (! interactive(this_player()))
                       return;
        add_action("do_exchange", "throwing");
}

