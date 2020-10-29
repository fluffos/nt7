#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name( HIR "火麒麟·疾行" NOR, ({ "jixing xue", "jixing", "xue" }) );
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "双");
                set("long", HIR "这是一双通体火红的靴子，散发着令人窒息的光芒。\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60); //后天身法+60
                set("material", "boots");
                set("limit", ([
                        "exp"  :  50000000,
                        "dex"  :  80,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}