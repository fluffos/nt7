#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "天牢钥匙" NOR, ({ "tianlao key", "key" }));
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("long", "一把开启天牢的钥匙。\n");
                set("value", 200);
                set("maze_item", 1);
        }
        setup();
}
