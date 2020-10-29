#include <ansi.h>

inherit ITEM;


void create()
{
        set_name(HIY "吸灵壶" NOR, ({"xiling hu", "xiling", "hu"}));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "这是一个散发着奇特光彩的玉壶，据说可以吸收蓬莱仙果中蕴涵的神力。\n\n" NOR);
                set("unit", "个");
                set("value", 1);
        }
}

int query_autoload()
{
        return 1;
}