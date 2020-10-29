// This program is a part of NITAN MudLIB 
// redl 2012/11/1 

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIB "玉清丸" NOR, ({"yuqing wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一颗玉清丸，据说是沈芝毓从武当玉清散提纯出来的增强秘药。\n");
                set("base_unit", "颗");
                set("base_value", 150000000);
                set("base_weight", 800);
                set("only_do_effect", 1);
                set("unit", "堆");
        }
        setup();
}

int do_effect(object me)
{
                if( query("max_jingli", me)>=me->query_current_jingli_limit() )
                {
                        return notify_fail(YEL + "你很想再吃一颗..直觉却告诉你不会再有啥效果了...\n" + NOR); 
                }
                
        message_vision(YEL "$N" YEL "吃下一颗" + name() +
                       YEL "，内息急转大小周天，感觉精气发生了一些变化。\n", me);

        addn("max_jingli", 6000+random(500), me);
        if( query("max_jingli", me)>me->query_current_jingli_limit() )
                set("max_jingli", me->query_current_jingli_limit(), me);
        // me->start_busy(3);
        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 
        return 1;
}

