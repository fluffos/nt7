#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
        set_name(HIY "八卦艮山带" NOR, ({ "genshan dai", "genshan", "dai" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIY"炎黄风雨十年纪念套装之：八卦艮山带\n" NOR);
                set("unit", "条");
                set("value", 100);
                set("armor_prop/damage", 1000);
                set("armor_prop/T_bagua", 1); // 套装计数标志
        }
        setup();
}

int query_autoload()
{
        return 1;
}