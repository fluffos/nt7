inherit TESSERA;
#include <ansi.h>

void create()
{
        set_name(HIC "真武宝石" NOR, ({"zhenwu baoshi", "zhenwu", "baoshi" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "真武宝石");
                set("enchase/point", 1000);
                set("enchase/type", "weapon");
                set("can_be_qiling", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
