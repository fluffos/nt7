#include <ansi.h>
inherit TASK;
void create()
{
    set_name(BLU"黑玉镯"NOR, ({ "yu zhuo", "zhuo" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "支");
            set("material", "steel");
            set("long", "这是一支黑玉镯，相传是大侠杨过送给郭襄的生日礼物。\n");
          }
    set("owner", "郭芙");
    setup();
}
