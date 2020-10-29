#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(HIW"西服"NOR, ({"xi fu", "xifu", "cloth"}));
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("value", 50000);
                set("material", "cloth");
                set("armor_prop/armor", 300);
                set("male_only", 1);
                set("armor_prop/dodge", 35);
                set("armor_prop/force", 45);
                set("armor_prop/per", 10);
                           }
   setup();
}