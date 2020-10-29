inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "九天玲珑珠" NOR, ({"linglong zhu", "linglong", "zhu"}));
        set_weight(2000);
        set("long", HIM "看似平凡的珠子，拇指般大小，但却可以根据时辰的变化放射出不同的颜色，珍奇无比。\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "九天玲珑珠");
                set("enchase/point", 1);
                set("enchase/type", "surcoat");
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
