#include "herb.h"

void create()
{
        set_name(HIR "龙骨伸筋" NOR, ({ "longgu shenjin", "Smilax riparia var. acuminata", "herb_lgjin" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "百合科(菝葜科)植物尖叶牛尾菜(Smilax riparia var. acuminata)的根茎。因其形略似龙骨，坚硬，又有舒筋活络的功效，故得此名。\n" NOR);
                set("base_unit", "株");
                set("base_value", 50000);
                set("base_weight", 100);
        }
        setup();
}