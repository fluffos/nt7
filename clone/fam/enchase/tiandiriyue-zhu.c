inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY "天地日月灵珠" NOR, ({"tiandi riyuezhu", "tiandi", "riyuezhu" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "一颗晶莹通透，犹露欲滴的宝石，世间罕见。。\n" NOR);
                set("unit", "颗");
                set("value", 5000);
                set("enchase/name", "天地日月灵珠");
                set("enchase/point", 1);
                set("enchase/type", "def");
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
