inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(MAG "紫霹雳" NOR, ({"zi pili"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "粒");
                set("value", 500000);
                set("enchase/name", "紫霹雳");
                set("enchase/point", 1);
                set("enchase/type", "wrists");
                                set("enchase/cur_firm", 100);
                                set("nine_object", 1); // 九孔镶嵌物品标记
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
