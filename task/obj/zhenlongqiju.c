
#include <ansi.h>
inherit TASK;
void create()
{
    set_name( HIW "珍珑棋局" NOR, ({ "zhenlong qiju" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "这是一本珍珑棋局。\n");
          }
    set("owner", "虚竹子");
    setup();
}

