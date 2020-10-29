#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
        set_name( HIR "红血飞魂" NOR, ({ "hongxue feihun", "hongxue" }) );
        set_weight(4000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "双");
                set("value", 2000000);
                set("armor_prop/armor", 100);
                                set("armor_prop/dex", 10);
                                set("armor_prop/damage", 300);
                                set("limit", ([ 
                                        "exp" : 5000000,
                                        "scborn" : 1,
                                ]));
                set("material", "gold");
        }
        setup();
}

int query_autoload()
{
        return 1;
}