#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "龍筋" NOR, ({ "dragon vein", "vein" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "一根龍筋，闪闪发光。\n" NOR);
                set("unit", "根");
                set("value", 400000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}