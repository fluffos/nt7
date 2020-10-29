inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIB "黑风" NOR, ({ "hei feng"}));
        set("long", HIB "一匹浑身黝黑的马，看起来很能跑。\n" NOR);

        set("tili", 1000);
        set("max_tili", 1000);
        set("level", 1);

        setup();
}