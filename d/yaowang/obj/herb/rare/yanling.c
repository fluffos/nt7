#include "herb.h"

void create()
{
        set_name(NOR + MAG "头顶一颗珠" NOR, ({ "trillium tschonoskii", "herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "植物延龄草(Trillium tschonoskii)的根茎或成熟果实。因这种植物有3片叶轮生于茎的顶端，花单生于轮生叶之上，开花后结出圆球形的果实，成熟后黑紫色 ......\n" NOR);
                set("base_unit", "颗");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

