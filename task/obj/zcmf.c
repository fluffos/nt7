#include <ansi.h>
inherit TASK;
void create()
{
    set_name(MAG"祖传秘方"NOR, ({ "zuchuan mifang" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "一张非常陈旧的黄纸片。\n");
          }
    set("owner", "姚春");
    setup();
}
