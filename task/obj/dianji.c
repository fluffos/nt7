#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIG"藏经阁典籍"NOR, ({ "dian ji" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "这可是从少林藏经阁流传出来的武学典籍。\n");
          }
    set("owner", "无名老僧");
    setup();
}
