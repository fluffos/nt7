#include "herb.h"

void create()
{
        set_name(HIY "黄连" NOR, ({"huang lian"}));

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ 
        {
                set("long","黄连：草本植物，味苦，清热毒。\n");
                set("base_unit", "个");
                set("base_value", 4000);
                set("base_weight", 60);
                set("cure_s",0);
                set("cure_d",20);
                set("cure_n",0);
                
        }
        setup();
}