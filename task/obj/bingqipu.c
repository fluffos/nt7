#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIG "兵器谱" NOR, ({ "bingqipu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "记载各种兵器的一本奇书，不过你觉得它的封面也太厚了，厚的不象话。\n");
          }
    set("owner", "史松");
    setup();
}
