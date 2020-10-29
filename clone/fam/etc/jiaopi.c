#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "紫蛟皮" NOR, ({ "dragon skin", "skin" }));
        set_weight(4000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + MAG "一块蛟皮，呈紫黑色，坚硬无比，乃上等皮革原料。\n" NOR);
                set("unit", "块");
                set("value", 100000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}