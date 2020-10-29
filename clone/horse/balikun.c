inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIC "巴里坤马" NOR, ({ "balikun ma"}));
        set("long", HIC "巴里坤马是“神马“（胭脂马）的后代，体型矮小，但速度极快。\n" NOR);

        set("tili", 2000);
        set("max_tili", 2000);
        set("level", 2);

        setup();
}