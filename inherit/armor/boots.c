// boots.c
#include <armor.h>
inherit EQUIP;

int is_armor() { return 1; }
void setup()
{
        //if( !clonep(this_object()) )
                set("armor_type", TYPE_BOOTS);
        ::setup();
}
