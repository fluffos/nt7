#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name(HIY "八卦地坤靴" NOR, ({ "dikun xue", "dikun", "xue" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIY"炎黄风雨十年纪念套装之：八卦地坤靴\n" NOR);
                set("unit", "双");
                set("value", 100);
                set("armor_prop/dex", 20);
                set("armor_prop/T_bagua", 1); // 套装计数标志
        }
        setup();
}

int query_autoload()
{
        return 1;
}