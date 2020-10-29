inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "百炼寒精" NOR, ({"bailian hanjing1", "hanjing1"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "粒");
                set("value", 500000);
                set("enchase/name", "百炼寒精");
                set("enchase/point", 1);
                set("enchase/type", "neck");
                                set("enchase/cur_firm", 90);
                                set("nine_object", 1); // 九孔镶嵌物品标记
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
