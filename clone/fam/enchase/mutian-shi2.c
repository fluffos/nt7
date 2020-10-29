inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "幕天石" NOR, ({"mutian shi", "mutian", "shi"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "幕天石");
                set("enchase/point", 100);
                set("enchase/type", "waist");
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
