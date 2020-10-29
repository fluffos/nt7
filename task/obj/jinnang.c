
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIY "大汉锦囊" NOR, ({ "jin nang" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "个");
            set("material", "cloth");
            set("long", "这是一个大汉锦囊。\n");
          }
    set("owner", "李萍");
    setup();
}

