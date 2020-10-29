#include "herb.h"

void create()
{
        set_name(YEL "蝉蜕" NOR, ({"chan tui"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ 
        {
                set("long", "蝉蜕：蝉由幼虫蜕变至成虫所遗的壳，有去风湿的效果。\n");
                set("base_unit", "个");
                set("base_value", 4000);
                set("base_weight", 60);
                set("cure_s", 3);
                set("cure_d", 0);
                set("cure_n", 0);        
        }
        setup();
}