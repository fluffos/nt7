#include <ansi.h>
inherit TESSERA;

void create()
{
        set_name(HIG "孔雀圣石" NOR, ({"kongque shengshi", "kongque", "shengshi" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "孔雀圣石");
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
