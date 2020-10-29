inherit ITEM;
#include <ansi.h>

void create()
{
         set_name(HIW "轮回·炼狱" NOR, ({"lunhui lianyu","lunhui","lianyu" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                  set("long", HIW "轮回之苦·炼狱为首。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                 set("enchase/name", "轮回·炼狱");
                 set("enchase/point", 90);
                  set("enchase/type", "all");
                 set("enchase/cur_firm", 85);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
