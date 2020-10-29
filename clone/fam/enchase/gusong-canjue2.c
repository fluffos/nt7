inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + YEL "古松残镢" NOR, ({"gusong canjue", "gusong", "canjue"}));
        set_weight(2000);
        set("long", NOR + YEL "看似普通的玉石，却蕴藏着奇异的能量。\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "古松残镢");
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
