// lvshan.c 淡绿绸衫

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name(HIG"淡绿绸衫"NOR, ({ "danlv choushan", "shan" ,"cloth" }) );
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