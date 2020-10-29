inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "轮回·修罗" NOR, ({"lunhui xiuluo","lunhui","xiuluo" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                 set("long", HIM "轮回之苦·修罗灭之。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "轮回·修罗");
                set("enchase/point", 95);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 85);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
