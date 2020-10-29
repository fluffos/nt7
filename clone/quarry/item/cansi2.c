#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "天蚕丝" NOR, ({ "tiancan si", "tiancan", "si" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + WHT "这是一根天蚕丝，晶莹剔透、珍贵非常。\n" NOR);
                set("base_unit", "根");
                set("unit", "根");
                set("base_value", 100000);
                set("base_weight", 1);
        }
        setup();
}
int query_autoload()
{        
        return 1;
}