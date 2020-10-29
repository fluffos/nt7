inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "龙女·曙光" NOR, ({"longnv shuguang", "longnv", "shuguang" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "龙女·曙光乃东海宝物，见光则暗，无光则明。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "龙女·曙光");
                set("enchase/point", 200);
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
