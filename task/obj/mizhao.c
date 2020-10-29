#include <ansi.h>
inherit TASK;
void create()
{
    set_name("皇帝密旨", ({ "mizhao" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "一张折的很好的纸条，纸身上好像还盖了大印。\n");
          }
    set("owner", "李可秀");
    setup();
}
