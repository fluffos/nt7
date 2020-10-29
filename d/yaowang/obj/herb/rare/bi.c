#include "herb.h"

void create()
{
          set_name(NOR + CYN "文王一支笔" NOR, ({ "wenwang yizhibi", "herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIR "筒鞘蛇菰(Balanophora involucrata)或蛇菰(BalanophoraJWjaponica)的干燥全株。因它的花序形如粗粗的毛笔，民间传说周文王路经神农架 ......\n" NOR);
                set("base_unit", "颗");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

