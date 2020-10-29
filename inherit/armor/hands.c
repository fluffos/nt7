// hands.c
#include <ansi.h>
#include <armor.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

int is_armor() { return 1; }
varargs void setup()
{
        //if( !clonep(this_object()) )
                set("armor_type", TYPE_HANDS);

        ::setup();
}
