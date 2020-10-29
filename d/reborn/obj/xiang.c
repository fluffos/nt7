// xiang.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG "召神香" NOR, ({ "magic xiang" }) );
        set_weight(2000);
        if( clonep() ){
                set_default_object(__FILE__);
        } else {
                set("value", 10);
                set("unit", "支");
                set("long", MAG "这是一支召神香，传说可以在五岳祭坛那里召唤神仙出现。\n" NOR);
        }
        setup();
}

void start_borrowing()
{
        remove_call_out("destroy");
        call_out("destroy", 30 + random(20));
}

void destroy()
{
        if (environment())
                message("visoin", RED "召神香渐渐的熄灭了，只留下了一点灰烬。\n" NOR,
                        environment());
        destruct(this_object());
}