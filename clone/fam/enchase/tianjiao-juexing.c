inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "天轿·觉醒" NOR, ({"tianjiao juexing", "juexing" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("value", 50000);
                set("enchase/name", "天轿·觉醒");
                set("enchase/point", 100);
                set("enchase/type", "all");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
