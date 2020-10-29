#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
        set_name(HIY "九皇补心丹" NOR, ({ "buxin dan", "dan" }));
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

        if( time()-query_temp("last_eat/dan(A, me)")<40 )
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["jing"] == my["max_jing"])
        {
                write("你现在精神状态很好，无需服用" + name() + "。\n");
                return 1;
        }

        set_temp("last_eat/dan(A)", time(), me);

        message_vision(HIY "$N吃下一粒九皇补心丹，精神一振，神采奕奕。\n" NOR, me);
        me->receive_curing("jing", 800);
        me->receive_heal("jing", 800);

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}