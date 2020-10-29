inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIW "白马" NOR, ({ "bai ma"}));
        set("long", HIW "一匹普通的白马。\n" NOR);

        set("tili", 1000);
        set("max_tili", 1000);
        set("level", 1);

        setup();
}