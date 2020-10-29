#include "herb.h"

void create()
{
        set_name(YEL "土茯苓" NOR, ({ "tu fuling" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("base_unit", "根");
                set("long", "草本植物，补气血，润五脏，是不可多得的上佳药材。\n");
                set("base_value", 4000);
                set("base_weight", 60);
                set("cure_s", 30);
                set("cure_d", 20);
                set("cure_n", 40);
        }
        setup();
}