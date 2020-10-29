inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "鹰眼" NOR, ({"ying yan" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "鹰眼");
                set("enchase/point", 120);
                set("enchase/type", "wrists");
                                set("enchase/cur_firm", 100);
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
