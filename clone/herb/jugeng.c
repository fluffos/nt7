#include "herb.h"

void create()
{
        set_name(HIY "菊梗" NOR, ({"ju geng"}));

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ 
        {
                set("long","菊梗：菊花根茎，清热败火。\n");
                set("base_unit", "块");
                set("base_value", 4000);
                set("base_weight", 60);
                set("cure_s",0);
                set("cure_d",5);
                set("cure_n",0);
                
        }
        setup();
}