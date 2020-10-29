inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIM "哈萨克马" NOR, ({ "hasake ma"}));
        set("long", HIM "此马产自内蒙古锡林郭勒地区，颇为强健。\n" NOR);

        set("tili", 2000);
        set("max_tili", 2000);
        set("level", 2);

        setup();
}