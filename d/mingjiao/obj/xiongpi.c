#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIW"熊皮"NOR, ({ "xiong pi", "pi" }) );
        set_weight(9000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("material", "fur");
                set("value", 30000);
                set("warm_cloth", 1);
                set("armor_prop/armor", 80);
        }
        setup();
}
