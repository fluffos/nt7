inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "《安守阁地图》" NOR, ({"anshouge tu", "anshouge", "tu"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("long", HIW "这是一张绘有扶桑安守阁地形的图纸。\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}