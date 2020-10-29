inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "龙凰紫珠" NOR, ({"longhuang zizhu", "longhuang", "zizhu"}));
        set_weight(2000);
        set("long", HIM "这一颗紫色的珠子，晶莹剔透，珠子中央刻绘着龙凤呈祥的图案。\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "龙凰紫珠");
                set("enchase/point", 7);
                set("enchase/type", "medal2");
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
