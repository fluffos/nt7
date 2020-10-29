
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIR "葵花宝典" NOR, ({ "kuihua baodian" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "这是一本葵花宝典。\n");
          }
    set("owner", "葵花太监");
    setup();
}

