inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "麒麟之魂" NOR, ({"qilin zhihun", "qilin", "zhihun" }));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "麒麟之魂");
                set("enchase/point", 1);
                set("enchase/type", "head");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["add_yanjiu" : 5]) );  // 每个提高研究效率5%
        }
        setup();
}

int query_autoload()
{
        return 1;
}
