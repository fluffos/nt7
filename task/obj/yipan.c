
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIC "风水仪盘" NOR, ({ "yi pan" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "个");
            set("material", "stone");
            set("long", "这是一个风水仪盘。\n");
          }
    set("owner", "黄大仙");
    setup();
}

