#include "herb.h"

void create()
{
        set_name(HIR"枸枳子"NOR, ({"gouzhi zi","gouzhi","zi"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ 
        {
                set("long","枸枳子，味甘，色红，补血良药。\n");
                set("base_unit", "粒");
                set("base_value", 4000);
                set("base_weight", 60);
                set("cure_s",5);
                set("cure_d",0);
                set("cure_n",0);                
        }
        setup();
}