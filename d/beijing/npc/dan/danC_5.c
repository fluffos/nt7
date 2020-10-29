#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIC"修罗"NOR+HIR"无常"NOR+HIY"丹"NOR, ({"xiuluo dan", "dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("base_unit", "粒");
                set("base_value", 150);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/dan(C, me)")<90 )
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

        set_temp("last_eat/dan(C)", time(), me);

        message_vision(HIR "$N吃下一粒修罗无常丹，精力得到了完全的调整。\n" NOR, me);
        set("jingli",query("max_jingli",  me), me);

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}