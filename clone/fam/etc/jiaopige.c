#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "紫蛟皮革" NOR, ({ "dragon pige", "pige" }));
        set_weight(8000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + MAG "一张巨大蛟皮，呈紫黑色，坚硬无比。\n" NOR);
                set("unit", "张");
                set("value", 1000000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}