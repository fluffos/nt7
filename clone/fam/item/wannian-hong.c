#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "万年红" NOR, ({"wannian hong"}));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "此乃万年红，为宫廷禁品，天下间最上乘的颜料。\n" NOR);
                set("unit", "盒");
                set("value", 8000);
        }
}

int query_autoload()
{
        return 1;
}
