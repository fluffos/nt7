#include "herb.h"

void create()
{
        set_name(RED "舒筋草" NOR, ({ "shujin cao", "Cucubalus baccifer", "herb_sjcao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "石竹科植物狗筋蔓(Cucubalus baccifer)的全草。因其具舒筋活络功效，故得此名。\n" NOR);
                set("base_unit", "株");
                set("base_value", 50000);
                set("base_weight", 100);
        }
        setup();
}

