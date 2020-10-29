inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(NOR + YEL "普氏野马" NOR, ({ "pushi yema"}));
        set("long", NOR + YEL "生活在新疆的普氏野马一小时可奔跑六十公里，还有连续奔跑四小时的耐力。\n" NOR);

    set("tili", 5000);
        set("max_tili", 5000);
        set("level", 2);

        setup();
}