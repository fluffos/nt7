#include <ansi.h>
inherit TASK;
void create()
{
    set_name(WHT"铁剑"NOR, ({ "tie jian", "sword" }) );
    set_weight(100);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "柄");
            set("material", "iron");
            set("long", "这是一柄非常锋利的铁剑。\n");
          }
    set("owner", "独臂神尼");
    setup();
}
