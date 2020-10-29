#include <ansi.h>
inherit TESSERA;

void create()
{
        set_name(HIB "玄武圣石" NOR, ({"xuanwu shengshi", "xuanwu", "shengshi" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "玄武圣石");
                set("enchase/point", 1);
                set("enchase/type", "armor");
                set("can_be_qiling", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
