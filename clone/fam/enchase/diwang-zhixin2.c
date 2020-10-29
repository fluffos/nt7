inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "帝王之心" NOR, ({"diwang zhixin", "diwang", "zhixin" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "帝王之心");
                set("enchase/point", 30);
                set("enchase/type", "waist");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
