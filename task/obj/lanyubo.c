#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIC"蓝玉钵"NOR,({ "lanyu bo", "bo" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "只");
            set("material", "stone");
            set("long", "一只蓝田美玉精制而成的药钵，虽然使用日久，但丝毫没有破痕。药钵里\n残留了微量剧毒, 然已足够毒死偷宝之人。\n");
          }
    set("owner", "买卖提");
    setup();
}
