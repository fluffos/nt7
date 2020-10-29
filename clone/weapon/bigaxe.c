// bigaxe
#include <ansi.h>
#include <weapon.h>
inherit AXE;
void create()
{
        set_name(HIW "巨斧" NOR, ({"big axe","axe"}));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("long", "这是盘古用来开天辟地的巨斧，传说有神奇的力量。\n");
                set("value", 1);
                set("flag", 1);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", "$N从背上拔出一把"+HIW+"巨斧"+NOR+"，握在手中。\n");
                set("unwield_msg", "$N将一把"+HIW+"巨斧"+NOR+"插在背上。\n");
        }  
        init_axe(1000,1);
        setup();
}   