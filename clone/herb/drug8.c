#include "herb.h"

void create()
{
        set_name("八品龙丹", ({ "dragon soul", "herb_drug8" }) );
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long","这是龙的内丹，鸡蛋大小，如火焰般赤红。用法：boost\n");
                set("base_unit", "颗");
                set("base_value", 50000);
                set("base_weight", 5);
        }
        setup();
}

