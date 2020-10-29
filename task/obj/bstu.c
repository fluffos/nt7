#include <ansi.h>
inherit TASK;
void create()
{
    set_name( WHT "巴山图" NOR, ({ "bstu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "一张详细的巴山地图，左下角写了一行小字：
            成都东十里，左三右四，子午双时．．\n");
          }
    set("owner", "马超兴");
    setup();
}
