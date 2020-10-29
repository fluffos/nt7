#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "天王保命丹" NOR, ({"baoming dan", "baoming", "dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("long", HIR "一颗红色的药丸。恢复全部气血和最大气血。\n" NOR);
                set("value", 100000);
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

        message_vision(HIR "$N" HIR "吃下一颗天王保命丹，只觉舒泰之极！\n" NOR, me);

        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}