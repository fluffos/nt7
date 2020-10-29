
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIC "大清律例" NOR, ({ "daqing lvli" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "这是一本大清律例。\n");
          }
    set("owner", "乾隆皇帝");
    setup();
}

