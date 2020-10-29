inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + BLU "钨精" NOR, ({"wu jing", "wu", "jing"}));
        set_weight(800);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", NOR + BLU "一块看似普通的矿物，周身乌黑，投射出阵阵摄人气息。\n" NOR);
                set("unit", "块");
                set("value", 5000);
                set("enchase/name", "钨精");
                set("enchase/point", 40);
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
