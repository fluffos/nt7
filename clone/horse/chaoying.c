inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIM "超影" NOR, ({ "chao ying", "chao", "ying"}));
        set("long", HIC "八龙之骏，一名超影，逐日而追。\n" HIY
                    "摘自本游戏网游小说《终极地狱》。\n" NOR);
        set("tili", 20000);
        set("max_tili", 20000);
        set("level", 5);

        set("can_go_any", 1);

        setup();
}