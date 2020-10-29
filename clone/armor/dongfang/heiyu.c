#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIB "黑玉指环" NOR, ({ "heiyu zhihuan", "heiyu", "zhihuan" }));
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("long", HIB "此乃千年黑玉锻造而成的指环，遇寒则热，遇热则寒，佩戴后有特殊功效。\n" NOR);
                set("value", 20000000);
                set("material", "gold");
                set("armor_prop/damage", 1000);
                set("armor_prop/int", 10);
                set("armor_prop/add_tihui_xiaolv", 5); // 增加体会汲取效率5% jiqu.c中处理
                set("special/desc", HIR "提升实战体会汲取效率5%。" NOR);
                set("limit", ([ 
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
