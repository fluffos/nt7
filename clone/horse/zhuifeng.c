inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIW "追  风" NOR, ({ "zhui feng"}));
        set("long", HIW "相传追风乃唐太宗李世民的坐骑，日行千里，夜行八百。\n"
                        "身高丈许，雄伟非常，追风而行，故得名。\n" NOR);
        set("tili", 6000);
        set("max_tili", 6000);
        set("level", 4);

        set("can_go_any", 1);
        setup();
}