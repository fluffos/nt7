#include <ansi.h>

#include "tr.h"

int query_tongren() { return 2; }
void create()
{
        set_name(YEL "无名大铜人" NOR, ({ "wuming tongren", "wuming", "tongren" }));
        set_weight(50);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "个");
                set("base_unit", "个"); 
                set("long", YEL "这是一个破旧的铜人，上面绘制了一些图案，但是已经无法辩识。\n" NOR);
                //set("long", NOR + YEL "这里是一个冲穴铜人，上面刻有经络穴位图，可习得经络学。\n" NOR);
                set("value", 10000);
                set("material", "steal");
                set("no_identify", 1);

                set("skill", ([
                        "name"         : "jingluo-xue",
                        "exp_required" : 500000,
                        "jing_cost"    : 150,
                        "difficulty"   : 30,
                        "max_skill"    : 99,
                        "min_skill"    : 0
                ]));
        }
        setup();
}
