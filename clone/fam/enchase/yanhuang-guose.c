inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "炎黄·国色天香" NOR, ({"guose tianxiang", "guose", "tianxiang" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "炎黄·国色天香乃炎黄之神品，放在手心，只见从中透射出阵阵醉人的光芒。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "炎黄·国色天香");
                set("enchase/point", 160);
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
