// qingshan.c 青衫

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(HIC"青衫"NOR, ({ "qing shan", "shan" ,"cloth" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("value", 100);
                set("armor_prop/armor", 5);
        }
        setup();
}