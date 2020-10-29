inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIG "的卢马" NOR, ({ "dilu ma"}));
        set("long", HIG "此马极其雄俊，奔跑有力，通人性，忠心。眼下有泪槽，额"
                        "上有白点，乃三国刘备的爱马，曾数次助其脱险。\n" NOR);

        set("tili", 3000);
        set("max_tili", 3000);
        set("level", 3);

        setup();
}