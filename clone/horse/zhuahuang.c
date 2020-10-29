inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIC "爪黄飞电" NOR, ({ "zhuahuang feidian"}));
        set("long", HIC "乃三国时曹操的爱马，奔跑如电，乃世间罕有。\n" NOR);

        set("tili", 3000);
        set("max_tili", 3000);
        set("level", 3);

        setup();
}