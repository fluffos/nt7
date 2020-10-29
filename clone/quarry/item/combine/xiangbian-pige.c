#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "镶边皮革" NOR, ({ "xiangbian pige", "xiangbian", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM  "这是一张薄而通透的皮革，做甲衣时，是用来镶边的绝佳材料。\n" NOR);
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