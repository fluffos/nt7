#include <ansi.h>
inherit ITEM;

inherit F_LIQUID;

void create()
{
        set_name(NOR + YEL "牛皮水袋" NOR, ({ "shui dai", "shui", "dai" }));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + YEL "这是一支特大号的牛皮水袋，质量"
                            "相当不错。甚至可以用它来穿越沙漠。\n" NOR);
                set("unit", "支");
                set("value", 5000);
                set("max_liquid", 30000);
                set("can_drink", 1);
                set("only_do_effect", 1);
        }
        set("liquid", ([
                "type"         : "water",
                "name"         : "清水",
                "remaining"    : 30000,
                "drunk_supply" : 3000,
        ]));
}

int do_effect(object me)
{
        int remain;

        if ((remain = query("liquid/remaining")) < 1)
        {
                write(name() + "里的" + query("liquid/name") + "已经被喝得一滴也不剩了。\n"); 
        if( query("env/auto_drinkout", me) && environment(this_object()) != environment(me) )
           {
                message_vision("$N丢下一个$n。\n", me, this_object());  
                this_object()->move(environment(me));  
           }
                return 1;
        }
        
        if( query("water", me) >= me->max_water_capacity() )
        {
                write("你已经喝太多了，再也灌不下一滴水了。\n"); 
                return 1;
        }

        message_vision("$N拿起" + name() + "咕噜噜地喝了几大口" + query("liquid/name") + "。\n" NOR, me);
        
        if (remain < 3000)
        {
                addn("water", remain, me);
                set("liquid/remaining", 0);
        } else
        {
                addn("water", 3000, me);
                addn("liquid/remaining", -3000);
        }

        if (query("liquid/remaining") < 1 &&
            query("env/auto_drinkout", me) && 
            environment(this_object()) != environment(me)) 
        {
                message_vision("$N丢下一个$n。\n", me, this_object()); 
                this_object()->move(environment(me)); 
        }
        
        return 1;
}