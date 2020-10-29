#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIW"狂生曲谱"NOR, ({ "ksqupu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本狂生曲曲谱。\n");
          }
    set("owner", "黄药师");
    setup();
}
