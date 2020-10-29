#include "herb.h"

void create()
{
        set_name(NOR + YEL "江边一碗水" NOR, ({ "diphylleia sinensis", "herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "南方山荷叶(Diphylleia sinensis)的干燥根茎。因其根茎的每一茎节处有一碗状小凹窝(茎痕)，且最初是在河边高山坡林下挖得此药，故得此名。其根茎黄褐色 ......\n" NOR);
                set("base_unit", "根");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

