#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIR"摄心诀"NOR, ({ "shexin jue" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "丐帮长老彭有敬的摄心诀，里面记录的无功据说可以控制别人的心智。\n");
          }
    set("owner", "彭有敬");
    setup();
}
