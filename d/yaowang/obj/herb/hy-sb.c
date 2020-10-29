#include "herb.h"

void create()
{
        set_name(HIC "菱叶红景天" NOR, ({ "hy-sb", "Rhodiola henryi", "herb_hy_sb" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "景天科植物豌豆七(又称菱叶红景天)(Rhodiola henryi)的带根全草。因其有活血、止痛、消肿之功效，且药效作用快，故名“十步还阳”和“大救驾”。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}