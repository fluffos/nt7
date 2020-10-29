#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIC"醉仙楼菜谱" NOR, ({ "cai pu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "stone");
            set("long", "一本醉仙楼菜谱\n");
          }
    set("owner", "冼老板");
    setup();
}
