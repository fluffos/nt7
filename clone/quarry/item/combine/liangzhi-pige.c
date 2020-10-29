#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "亮质皮革" NOR, ({ "liangzhi pige", "liangzhi", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG  "这是一张通体透亮的皮革，是制作甲衣的上好材料。\n" NOR);
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