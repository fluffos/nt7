#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        string *order = ({HIW "大白兔" NOR,HIM "酥糖" NOR, HIY "话梅" NOR, HIR "夹心巧克力" NOR, HIG "薄荷" NOR});
        set_name( (order[random(5)]), ({ "sugar" }) );
        set_weight(80);
        set("value", 0);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一粒高级喜糖。\n");
                set("unit", "粒");
                set("food_remaining", 2);
                set("food_supply", 10);

        }
}