#include "herb.h"

void create()
{
        set_name(NOR + YEL "陈皮" NOR, ({ "chen pi", "chen", "pi", "herb_chenpi" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + YEL "陈皮是常见的中药药材。\n" NOR);
                set("base_unit", "块");
                set("base_value", 10);
                set("base_weight", 20);
                set("no_sell", "药王谷的丹药非常有名，但普通草药随地都有啊。");
                set("yaowang", 1);
        }
        setup();
}