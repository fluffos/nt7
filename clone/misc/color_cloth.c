#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(MAG "粉"RED"红"BLU"披"HIW"风" NOR, ({ "color cloth", "cloth" }) );
        set_weight(1000);
        set("value", 5);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "这件粉红色的披风上面绣著几只凤凰，煞是性感。\n");
                set("unit", "块");
                set("material", "cloth");
                set("armor_prop/con",20);
                set("armor_prop/per", 200);
                set("female_only", 1);
        }
        setup();
}