#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "青龙之角" NOR, ({ "dragon horn", "horn" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "一根青龙之角，通体深红。\n" NOR);
                set("unit", "根");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}