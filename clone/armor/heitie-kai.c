
#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(HIB "黑铁铠" NOR, ({ "heitie kai", "heitie", "kai" }) );
        set_weight(30000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("material", "steel");
                set("value", 800000);
                set("armor_prop/armor", 500);
                set("limit", ([
                        "exp"  :  400000,
                        "str"  :  30,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}