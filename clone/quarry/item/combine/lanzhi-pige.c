#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "蓝质皮革" NOR, ({ "lanzhi pige", "lanzhi", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC  "这是一张蓝色的皮革，是制作甲衣的上好材料。\n" NOR);
                set("base_unit", "张");
                set("unit", "张");
                set("base_value", 100);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}