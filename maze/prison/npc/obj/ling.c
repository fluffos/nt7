#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(RED "地宫通行令" NOR, ({ "tongxing ling", "ling" }));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("long", "此物品乃太监总管交给大侠燕非的出入令牌。\n");
                set("value", 200);
                set("maze_item", 1);
        }
        setup();
}
