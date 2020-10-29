inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "蓝宝石" NOR, ({"lan baoshi1", "baoshi1" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIC "一颗蓝色闪亮的宝石，乃人间真品。\n" NOR);
                set("unit", "颗");
                set("value", 50000);
                set("enchase/name", "蓝宝石");
                set("enchase/point", 1);
                set("enchase/type", "neck");
                                set("enchase/cur_firm", 90);
                                //set("nine_object", 1); // 九孔镶嵌物品标记
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
