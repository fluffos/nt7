#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(HIY "八卦兑泽衣" NOR, ({ "duize yi", "duize", "yi" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIY"炎黄风雨十年纪念套装之：八卦兑泽衣\n" NOR);
                set("unit", "件");
                set("value", 100);
                set("armor_prop/armor", 1000);
                set("armor_prop/T_bagua", 1); // 套装计数标志
        }
        setup();
}

int query_autoload()
{
        return 1;
}