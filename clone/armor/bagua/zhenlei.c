#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
        set_name(HIY "八卦震雷腕" NOR, ({ "zhenlei wan", "zhenlei", "wan" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIY"炎黄风雨十年纪念套装之：八卦震雷腕\n" NOR);
                set("unit", "双");
                set("value", 100);
                set("armor_prop/armor", 100);
                set("armor_prop/int", 10);
                set("armor_prop/T_bagua", 1); // 套装计数标志
        }
        setup();
}

int query_autoload()
{
        return 1;
}