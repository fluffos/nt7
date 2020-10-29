
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIW "徐霞客游记" NOR, ({ "xxk youji" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "这是一本徐霞客游记。\n");
          }
    set("owner", "徐霞客");
    setup();
}

