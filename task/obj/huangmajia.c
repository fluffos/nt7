#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIY"黄马甲"NOR, ({ "huang majia", "majia" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "件");
            set("material", "cloth");
            set("long", "这是一件皇上御赐给鳌拜的黄马甲。\n");
          }
    set("owner", "鳌拜");
    setup();
}
