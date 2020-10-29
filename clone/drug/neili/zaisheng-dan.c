#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "灵穴再生丹" NOR, ({"zaisheng dan", "zaisheng", "dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 100000);
                set("only_do_effect", 1);
                set("long", HIY "一颗紫色的药丸。恢复全部内力。\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if( time()-query_temp("last_eat", me)<2 )
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        set_temp("last_eat", time(), me);

        message_vision(HIW "$N吃下一颗灵穴再生丹，感到内力有所补充。\n" NOR, me);

        set("neili",query("max_neili",  me), me);

        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}