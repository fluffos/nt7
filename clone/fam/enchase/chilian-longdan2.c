#include <ansi.h>
inherit TESSERA;

void create()
{
        set_name(HIR "赤炼龙胆" NOR, ({"chilian longdan", "chilian", "longdan" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "赤炼龙胆");
                set("enchase/point", 1000);
                set("enchase/type", "surcoat");
                set("can_be_qiling", 1); 
        }
        setup();
}

int query_autoload()
{
        return 1;
}
