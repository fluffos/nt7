#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIY "锁脉" NOR, ({ "suo mai2", "suo", "mai2" }));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "根");
                set("value", 400000);
                                set("armor_prop/con", 22);
                set("armor_prop/dex", -10);
                                set("limit", ([ 
                                        "exp" : 12000000,
                                        "con" : 50, 
                                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}