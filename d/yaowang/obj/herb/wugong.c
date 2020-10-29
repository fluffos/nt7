#include "herb.h"

void create()
{
        set_name(HIY "飞天蜈蚣" NOR, ({ "wugong", "Aralia chinensis", "herb_wugong" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "五加科植物楤木(Aralia chinensis)的根、根皮及茎皮。因其小枝密被黄棕色针刺，犹如蜈蚣飞天，故得此名。\n" NOR);
                set("base_unit", "根");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}