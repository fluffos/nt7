inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "露华之晶" NOR, ({"luhua zhijing", "luhua", "zhijing" }));
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "露华之晶乃是昆仑仙境之颠的露珠，吸取宇宙大地之尘埃结晶而成，蕴涵宇宙万物之精华。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "露华之晶");
                set("enchase/point", 1);
                set("enchase/type", "10k");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["luhua-zhijing":1]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
