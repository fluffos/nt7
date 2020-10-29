#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIG "续命八丸" NOR,({ "xuming bawan" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "粒");
                set("material", "wood");
                set("long", "这是一粒续命八丸。\n");
        }
        set("owner", "祖千秋");
        setup();
}

