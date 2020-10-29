#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "红质皮革" NOR, ({ "hongzhi pige", "hongzhi", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG  "这是一张红色的皮革，是制作甲衣的上好材料。\n" NOR);
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