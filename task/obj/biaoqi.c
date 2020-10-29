#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIR"镖旗"NOR, ({ "biaoqi" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "一张林家镖局的镖旗\n");
          }
    set("owner", "林震南");
    setup();
}
