#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIR"火麒丹"NOR, ({"huoqi dan", "dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("base_unit", "粒");
                set("base_value", 80);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if( time()-query_temp("last_eat/dan(D, me)")<150 )
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        nl=query("neili", me)+800;
        mn=query("max_neili", me)*2;

        if (nl > mn)
        {
                write("你现在内力修为无需服用" + name() + "。\n");
                return 1;
        }

        set_temp("last_eat/dan(D)", time(), me);

        message_vision(HIR "$N吃下一粒火麒丹，感到内力有所补充。\n" NOR, me);
        addn("neili", 800, me);

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}