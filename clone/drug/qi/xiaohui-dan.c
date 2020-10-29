#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "小回丹" NOR, ({"xiaohui dan", "xiaohui", "dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("long", HIR "一颗黑色的药丸。恢复300点气血和最大气血。\n" NOR);
                set("value", 2000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat", me)<2 )
        {
                write("你刚吃过药，药力还没有完全吸收。\n");
                return 1;
        }
        set_temp("last_eat", time(), me);
        message_vision(HIR "$N" HIR "吃下一颗小回丹，只觉舒泰之极！\n" NOR, me);

        if( query("max_qi", me)-query("eff_qi", me) <= 300 )
        {
                 set("eff_qi",query("max_qi",  me), me);
                 if( query("max_qi", me)-query("qi", me) <= 300 )
                        set("qi",query("max_qi",  me), me);
                 
                 else 
                        addn("qi", 300, me);
        }


        else 
        {
                addn("eff_qi", 300, me);
                addn("qi", 300, me);
        }

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}