inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(MAG "汗血宝驹" NOR, ({ "hanxue baoju", "hanxue", "baoju"}));
        set("long", HIR "西南大宛宛丘，有良马，其大二丈，鬣至膝，尾委于地，蹄\n"
                        "如汗，腕可握。日行千里，至日中而汗血\n" NOR);
        set("tili", 10000);
        set("max_tili", 10000);
        set("level", 5);

        set("can_go_any", 1);

        setup();
}