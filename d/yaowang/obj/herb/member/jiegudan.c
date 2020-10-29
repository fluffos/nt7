#include "herb.h"

void create()
{
        set_name(HIC "接骨丹" NOR, ({ "jiegudan", "Torricellia angulata", "herb_jgdan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "山茱萸科(鞘柄木科)植物角叶鞘柄木(Torricellia angulata)的根、根皮及叶。因其有治疗骨折的功效，故得此名。\n" NOR);
                set("base_unit", "根");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}

