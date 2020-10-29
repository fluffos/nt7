inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIG "翡翠驹" NOR, ({ "feicui ju"}));
        set("long", HIG "据说翡翠驹产自四川，脚力不错　。\n" NOR);

        set("tili", 1000);
        set("max_tili", 1000);
        set("level", 1);

        setup();
}