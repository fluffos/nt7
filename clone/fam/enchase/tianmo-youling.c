inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "天魔·幽灵" NOR, ({"tianmo youling", "youling" }));
        set_weight(900);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "一块晶莹的宝石，拿在手中却有一种不详的感觉。\n" NOR);
                set("unit", "块");
                set("value", 50000);
                set("enchase/name", "天魔·幽灵");
                set("enchase/point", 65);
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
