#include "herb.h"

void create()
{
        set_name(NOR + WHT "附子" NOR, ({ "fu zi", "fu", "zi", "herb_fuzi" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + WHT "附子是常见的中药药材。\n" NOR);
                set("base_unit", "粒");
                set("base_value", 1000);
                set("base_weight", 20);
                set("no_sell", "药王谷的丹药非常有名，但普通草药随地都有啊。"); 
                set("yaowang", 1); 
        }
        setup();
}