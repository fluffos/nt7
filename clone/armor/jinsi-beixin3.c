
#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY "金丝背心" NOR, ({ "jinsi beixin3", "jinsi", "beixin3" }) );
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("material", "steel");
                                set("value", 800000);
                set("armor_prop/armor", 700);
                                set("limit", ([
                                        "exp"  :  45000000,
                                        "int"  :  60,
                                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}