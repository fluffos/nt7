#include <ansi.h>
inherit TASK;
void create()
{
    set_name(YEL"一撮金毛"NOR, ({ "jin mao", "mao" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一撮金黄色的毛发。\n");
          }
    set("owner", "谢逊");
    setup();
}
