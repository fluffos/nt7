#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIM "战魂" NOR, ({ "zhan hun3", "zhan", "hun3" }) );
        set_weight(4000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "双");
                set("long", HIM "这便传说中天兵天将所穿之宝靴，靴子周身散发着寒光。\n" NOR);
                set("value", 2000000);
                set("armor_prop/armor", 100);
                                set("armor_prop/dex", 8);
                                set("armor_prop/str", 8);
                                set("armor_prop/damage", 300);
                                set("limit", ([ 
                                        "exp" : 80000000,
                                ]));
                set("material", "steal");
        }
        setup();
}

int query_autoload()
{
        return 1;
}