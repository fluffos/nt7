inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "镇魂之精" NOR, ({"zhenhun zhijing", "zhenhun", "zhijing" }));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "镇魂之精");
                set("enchase/point", 1);
                set("enchase/type", "head");
                set("limit", 10); // 至少有10个孔的时候方可镶嵌
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["add_yanjiu" : 10]) );  // 每个提高研究效率10%
        }
        setup();
}

int query_autoload()
{
        return 1;
}
