#include "herb.h"

void create()
{
        set_name(HIC "五月还阳" NOR, ({ "huanyang5", "Sedum odontophyllum", "herb_5yhuanyang" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "景天科植物齿叶景天(Sedum odontophyllum)的全草。因它消肿止痛功效很强，又因这一植物一般在5月开花，所以也称“五月还阳”。\n" NOR);
                set("base_unit", "根");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}