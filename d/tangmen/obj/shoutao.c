// shoutao.c  手套

#include <armor.h>

inherit HANDS;

void create()
{
        set_name( "鹿皮手套", ({ "lupi shoutao", "shoutao" }) );
        set_weight(500);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "双");
                set("long", "这是一双鹿皮手套，上面有硬物刻勒的痕迹，可以避毒。\n");
                set("value", 10000);
                set("material", "leather");
                set("armor_prop/armor", 10);
        }
        setup();
}