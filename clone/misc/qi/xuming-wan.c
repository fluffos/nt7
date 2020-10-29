#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "续命丸" NOR, ({"xuming wan", "xuming", "wan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("long", HIR "一颗黑色的药丸。恢复2000点气血和最大气血。\n" NOR);
                set("value", 50000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        if (time() - me->query_temp("last_eat_p1") < 600)
        {
                write("你刚吃过药，药力还没有完全吸收。\n");
                return 1;
        }
        me->set_temp("last_eat_p1", time());

        message_vision(HIR "$N" HIR "吃下一颗续命丸，只觉舒泰之极！\n" NOR, me);

        if (me->query("max_qi") - me->query("eff_qi") <= 2000)
        {
                 me->set("eff_qi", me->query("max_qi"));
                 if (me->query("max_qi") - me->query("qi") <= 2000)
                        me->set("qi", me->query("max_qi"));
                 
                 else 
                        me->add("qi", 2000);  
        }

        else 
        {
                me->add("eff_qi", 2000);
                me->add("qi", 2000);
        }

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}