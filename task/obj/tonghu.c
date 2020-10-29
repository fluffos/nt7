
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( YEL "大铜茶壶" NOR, ({ "tong hu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "个");
            set("material", "steel");
            set("long", "这是一个大铜茶壶。\n");
          }
    set("owner", "龟公");
    setup();
}

