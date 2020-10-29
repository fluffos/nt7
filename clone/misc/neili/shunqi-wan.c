#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "顺气丸" NOR, ({"shunqi wan", "shunqi", "wan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 30000);
                set("only_do_effect", 1);
                set("long", HIY "一颗紫色的药丸。恢复1000点内力。\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if (time() - me->query_temp("last_eat") < 2)
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        me->set_temp("last_eat", time());

        message_vision(HIW "$N吃下一颗顺气丸，感到内力有所补充。\n" NOR, me);

        if (me->query("max_neili") - me->query("neili") < 1000)
                  me->set("neili", me->query("max_neili"));
        else
                  me->add("neili", 1000);


        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}