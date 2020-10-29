inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "红眼恶魔" NOR, ({"hongyan emo", "hongyan", "emo" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "一颗通红的宝石，犹如恶魔的眼珠。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "红眼恶魔");
                set("enchase/point", 1);
                set("enchase/type", "all");
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
