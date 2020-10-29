
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIR "平西大将军印" NOR, ({ "jiangjun yin" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "个");
            set("material", "stone");
            set("long", "这是一个平西大将军印。\n");
          }
    set("owner", "吴三桂");
    setup();
}

