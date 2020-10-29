#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "火凤凰之筋" NOR, ({ "phoenix vein", "vein" }));
        set_weight(4000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "一根火凤凰的筋，晶莹透亮。\n" NOR);
                set("unit", "根");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}