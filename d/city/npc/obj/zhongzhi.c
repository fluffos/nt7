#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(YEL "花种" NOR, ({"hua zhong", "zhong"}));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一枚无法确定品种的花种。\n");
                set("unit", "只");
                set("value", 20);
                set("food_remaining", 1);
                set("food_supply", 10);
        }
}

void init()
{
        add_action("do_zhonghua", "zhonghua");
}

int do_zhonghua()
{
        object me,ob;
 
        me = this_player();
        ob = this_object();

        if( query_temp("zhonghua", me) == 1 )
        {
                tell_object(me,HIR "种子已经拨下了，现在该培育(peiyu)花种。\n" NOR);
                return 1;
        }

        message_vision("$N用手在地上挖了一个坑，把花种放了进去。\n", me);
        tell_object(me, HIR "种子已经拨下了，现在该培育(peiyu)花种。\n" NOR);
        addn_temp("zhonghua", 1, me);
        destruct(ob);
        addn("jing", -50, me);
        return 1;
}