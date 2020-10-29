// baiyunwan.c 白云熊胆丸

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW"白云熊胆丸"NOR, ({"baiyun xiongdanwan", "wan"}));
        set("unit", "粒");
        set("vegetable", 26);
        set("nostrum", 92);
        set("level", 40);
        set("pour_type", "1");
        set("long", "这是一粒白云熊胆丸，雪白透亮。\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("你要吃什么？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什么？\n");
        if( me->is_busy() )
                return notify_fail("别急，慢慢吃，小心别噎着了。\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) && 
                query("neili", me) >= query("max_neili", me) )
        {
                message_vision("$N没必要吃白云熊胆丸。\n",me);
        }
        else
        {
                set("eff_jing",query("max_jing",  me), me);
                set("jing",query("eff_jing",  me), me);
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                set("neili",query("max_neili",  me), me);
                message_vision("$N吃下一粒白云熊胆丸，只觉得周身热乎乎的，十分舒坦。\n",me);
                destruct(this_object());
        }
        return 1;
}