#include <ansi.h>

inherit ITEM;

void create()
{
         set_name(NOR + CYN "天山玄铁加强型" NOR, ({ "tianshan xuantie2", "tianshan", "xuantie" }));
        set_weight(20000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + CYN "世间极为罕见的玄铁，采至天山，着手极为沉重。\n" NOR);
                set("unit", "块");
                set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + CYN "天山玄铁" NOR);
                set("can_make", "all");
                                set("not_make", ({ "披风","项链"}));
                                 set("power_point", 160);
        }
}

int query_autoload()
{
        return 1;
}
