#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + WHT "蚕丝" NOR, ({ "can si", "can", "si" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + WHT "这是一根普通的蚕丝。\n" NOR);
                set("base_unit", "根");
                set("unit", "根");
                set("base_value", 1000);
                set("base_weight", 1);
        }
        setup();
}
int query_autoload()
{        
        return 1;
}