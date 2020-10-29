
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIY "天师斩鬼符" NOR, ({ "zhangui fu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "这是一张天师斩鬼符。\n");
          }
    set("owner", "张天师");
    setup();
}

