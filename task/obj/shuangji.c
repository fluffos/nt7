
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIW "短柄双戟" NOR, ({ "duanbing shuangji" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "把");
            set("material", "steel");
            set("long", "这是一把短柄双戟。\n");
          }
    set("owner", "郭啸天");
    setup();
}

