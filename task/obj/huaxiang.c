
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIW "陈圆圆画像" NOR, ({ "hua xiang" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "这是一张陈圆圆画像。\n");
          }
    set("owner", "胡逸之");
    setup();
}

