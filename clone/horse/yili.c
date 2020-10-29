inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIC "伊犁马" NOR, ({ "yili ma"}));
        set("long", HIC "此马产自新疆伊犁，乃乌孙马的后代，脚力甚好，有“天马”之称。\n" NOR);

        set("tili", 2000);
        set("max_tili", 2000);
        set("level", 2);

        setup();
}