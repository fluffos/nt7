// neck.c

#include <armor.h>

inherit EQUIP;

void setup()
{
        //if (! clonep(this_object()))
                set("armor_type", TYPE_MYHEART);

        ::setup();
}
