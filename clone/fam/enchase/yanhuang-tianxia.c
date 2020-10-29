inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "炎黄·君临天下" NOR, ({"junlin tianxia", "junlin", "tianxia" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIG "炎黄·君临天下乃炎黄之神品，你将它放在手上却隐隐有种临摄天下的感觉。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "炎黄·君临天下");
                set("enchase/point", 220);
                set("enchase/type", "all");
                set("enchase/cur_firm", 90);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
