
#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY "金丝背心" NOR, ({ "jinsi beixin2", "jinsi", "beixin2" }) );
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("material", "steel");
                                set("value", 800000);
                set("armor_prop/armor", 600);
                                set("limit", ([
                                        "exp"  :  5000000,
                                        "int"  :  45,
                                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}