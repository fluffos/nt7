inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "龙女·蚀" NOR, ({"longnv shi", "longnv", "shi" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "龙女·蚀呈深红色，乃东海邪灵所化，拿在手中有种不祥的感觉。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "龙女·蚀");
                set("enchase/point", 180);
                set("enchase/type", "all");
                                set("enchase/cur_firm", 90);
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
