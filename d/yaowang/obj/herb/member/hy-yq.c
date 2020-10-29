#include "herb.h"

void create()
{
        set_name(HIC "鸦雀还阳" NOR, ({ "hy-yq", "Pholidota yunnanensis", "herb_hy_yq" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "兰科植物云南石仙桃(Pholidota yunnanensis)的带假鳞茎的全草。因其两叶形似喜鹊张嘴.故得此名。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

