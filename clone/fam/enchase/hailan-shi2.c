inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "海蓝石" NOR, ({"hailan shi", "hailan", "shi" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIC "东海之宝，千年难求。据说是东海龙女嫁妆。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "海蓝石");
                set("enchase/point", 1);
                set("enchase/type", "att");
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
