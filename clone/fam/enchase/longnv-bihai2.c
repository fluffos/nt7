inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "龙女·碧海神龙" NOR, ({"bihao shenlong", "bihai", "shenlong" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIC "龙女·碧海神龙乃东海之宝，散发着碧蓝色的锋芒。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "龙女·碧海神龙");
                set("enchase/point", 190);
                set("enchase/type", "all");
                                set("enchase/cur_firm", 100);
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
