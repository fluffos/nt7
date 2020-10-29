#include <ansi.h>
#include <armor.h>

inherit RINGS;

void create()
{
        set_name(HIY "八卦坎水环" NOR, ({ "kanshui huan", "kanshui", "huan" }));
        set_weight(100);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIY"炎黄风雨十年纪念套装之：八卦坎水环\n" NOR);
                set("unit", "枚");
                set("value", 100);
                set("armor_prop/int", 10);
                set("armor_prop/T_bagua", 1); // 套装计数标志
        }
        setup();
}

int query_autoload()
{
        return 1;
}