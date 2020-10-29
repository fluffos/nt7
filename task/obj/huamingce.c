#include <ansi.h>
inherit TASK;
void create()
{
    set_name( MAG "花名册" NOR, ({ "hua mingce", "mingce" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本红花会的花名册，上面记录了所有红花会好汉的名单。\n这个东西要是被官府得到了可不得了。\n");
          }
    set("owner", "陈家洛");
    setup();
}
